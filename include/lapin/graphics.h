/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file graphics.h
** The graphics module contains every function that is useful to create picture
** from scratch or from file and to draw inside them.
** The graphics module also contains an incomplete vector font and brings
** shader ability.
*/

#ifndef				__LAPIN_GRAPHICS_H__
# define			__LAPIN_GRAPHICS_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The t_bunny_clipable structure contains informations about a graphic element.
**
** It first contains a t_bunny_buffer with the height and width of the graphic element.
** It also contains four clipping fields: clip_x_position, clip_y_position, clip_width
** and clip_height.
**
** These clipping attributes are useful to select only a subpart of the graphic element
** to be used by functions. For example, bunny_blit will only copy the configured clip.
** By default, clip_x_position and clip_y_position are set to 0 and clip_width and
** clip_height to buffer.width and buffer.height.
**
** The attribute origin is useful to specify a hot spot. When blitting the graphic element
** to a specific position, for example, the origin define the point that will be drawn
** at the asked position throught the third parameter of bunny_blit.
** The origin also specify the rotation axis. By default, it is (0,0).
**
** Scale allow you to magnify or shrink the graphic element. The original size is multiplied
** by the scale to obtain the final size. By default, it is (1,1).
**
** The rotation is in degree and is the rotation of the graphic element when blitted.
** By default, it is 0.
**
** The color mask is a binary mask that will be applied to all pixel draw. By default,
** it is WHITE (0xFFFFFFFF)
**
*/
# ifdef				__MINGW32__
#  pragma			pack(4)
# endif

typedef struct			s_bunny_clipable
{
  t_bunny_buffer		buffer;
  int32_t			clip_x_position;
  int32_t			clip_y_position;
  int32_t			clip_width;
  int32_t			clip_height;
  t_bunny_accurate_position	position;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;
  bool				smooth;
  bool				mosaic;
}				t_bunny_clipable;

# define			bunny_clipable_copy(dest, ori) do {	\
    (dest)->clip_x_position = (ori)->clip_x_position;			\
    (dest)->clip_y_position = (ori)->clip_y_position;			\
    (dest)->clip_width = (ori)->clip_width;				\
    (dest)->clip_height = (ori)->clip_height;				\
    (dest)->position.x = (ori)->position.x;				\
    (dest)->position.y = (ori)->position.y;				\
    (dest)->origin.x = (ori)->origin.x;					\
    (dest)->origin.y = (ori)->origin.y;					\
    (dest)->scale.x = (ori)->scale.x;					\
    (dest)->scale.y = (ori)->scale.y;					\
    (dest)->rotation = (ori)->rotation;					\
    (dest)->color_mask.full = (ori)->color_mask.full;			\
    (dest)->smooth = (ori)->smooth;					\
    (dest)->mosaic = (ori)->mosaic;					\
  } while (0)

typedef enum			e_bunny_bitwidth
  {
    BBW_BLACK_AND_WHITE,
    BBW_4_COLORS,
    BBW_16_COLORS,
    BBW_256_COLORS,
    BBW_64K_COLORS,
    BBW_ARGB_COLORS,
    BBW_FLOAT_COLORS
  }				t_bunny_bitwidth;

/*!
** The t_bunny_pixelarray is a graphic element that is convenient to
** access pixels per pixel. It contains a t_bunny_clipable attribute that does not
** have any effect by default. (Except the clipping attributes, but only if
** you draw on a window or a t_bunny_picture, not on another t_bunny_pixelarray)
**
** To activate the t_bunny_clipable of the t_bunny_pixelarray, you have to
** provide the functionnality by yourself, implement your own blitter and
** set the gl_bunny_my_blit pointer to your t_bunny_my_blit function.
**
** The pixels attribute is an array of pixels. The first pixels is the top left
** one and it comes line after line. The last pixel is to bottom right one.
**
** The library do not bring any functionnality to draw on pixelarrays,
** you have to implement your functions. There is a lot of gl_bunny_my_* function
** pointers that will activate bunny_set_* pixelarray functionnalities if
** correct functions are set to them:
** gl_bunny_my_set_pixel
** gl_bunny_my_set_disk
** gl_bunny_my_set_line
** gl_bunny_my_set_polygon
** gl_bunny_my_fill
** gl_bunny_my_clear
**
** The bunny_self_test function will help you by testing you functions after
** you set them to these function pointers.
*/
typedef struct			s_bunny_pixelarray
{
  t_bunny_clipable		clipable;
  void * const			pixels;
  /* Definition of the organisation of the pixelarray */
  // If bitplane is false, bits_per_pixels is a t_bunny_bitwidth, else it is a int inside [1;8]
  const unsigned char		bits_per_pixels;
  const bool			bitplane;
  unsigned short		color_palette_size; // [0-256]
  t_bunny_color			color_palette[256];
  uint8_t			color_shifts[4];
}				t_bunny_pixelarray;
# pragma			pack()

/*!
** The bunny_new_pixelarray creates a manual access picture. The t_bunny_pixelarray
** picture is the system memory and is fast when you need to access each pixels
** one per one. The bunny_new_pixelarray picture is stored inside the bunny_malloc space.
** 32 bpp, t_bunny_rgba shift (*8), bitplane false, no palette.
** \param wid The width of the picture
** \param hei The height of the picture
** \return Return a valid t_bunny_pixelarray structure or NULL if there is not
** enough memory available.
*/
t_bunny_pixelarray		*bunny_new_pixelarray(unsigned int		wid,
						      unsigned int		hei);

t_bunny_pixelarray		*bunny_forge_pixelarray(unsigned int		wid,
							unsigned int		hei,
							const uint8_t		*shifts,
							t_bunny_bitwidth	bitw,
							bool			bitplane,
							t_bunny_color		*palette,
							size_t			palette_size);

/*!
** The bunny_load_pixelarray load a picture from a file. Supported formats are
** .png, .jpg, .gif and 24 bits bitmap. Output is a manual access picture.
** \param file The file to open and read.
** \return Return a t_bunny_pixelarray filled with the picture or NULL on error.
*/
t_bunny_pixelarray		*bunny_load_pixelarray(const char		*file);


/*!
** The bunny_read_pixelarray_d load a picture from memory. Supported formats are
** .png, .jpg, .gif and 24 bits bitmap. Output is a manual access picture.
** The picture will be stored inside the ressource manager if from_file is not NULL.
** \param buffer The buffer that contains the loaded in memory picture file
** \param len The size of the sent buffer
** \param from_file The file from which the data was loaded. Used to create a checksum
** to store the ressource inside the bunny ressource manager.
** \return Return a t_bunny_pixelarray filled with the picture or NULL on error.
*/
t_bunny_pixelarray		*bunny_read_pixelarray_id(const void		*buffer,
							  size_t		len,
							  const char		*from_file);

/*!
** The bunny_read_pixelarray load a picture from memory. Supported formats are
** .png, .jpg, .gif and 24 bits bitmap. Output is a manual access picture.
** \param buffer The buffer that contains the loaded in memory picture file
** \return Return a t_bunny_pixelarray filled with the picture or NULL on error.
*/
#define				bunny_read_pixelarray(buffer, len)		\
  bunny_read_pixelarray_id(buffer, len, NULL)

/*!
** The t_bunny_my_load_pixelarray type is currently unused by the library. It
** is the type of the function you have to implement to make the bunny library
** support specific formats it does not know how to manage (Like 32 bits bitmap)
** The self test function does not currently evaluate the function you would assign to
** gl_bunny_my_load_pixelarray.
*/
typedef t_bunny_pixelarray	*(*t_bunny_my_load_pixelarray)(const char	*file);

/*!
** The t_bunny_my_read_pixelarray type is currently unused by the library. It
** is the type of the function you have to implement to make the bunny library
** support specific formats it does not know how to manage (Like 32 bits bitmap)
** The self test function does not currently evaluate the function you would assign to
** gl_bunny_my_read_pixelarray.
*/
typedef t_bunny_pixelarray	*(*t_bunny_my_read_pixelarray)(const void	*buf,
							       size_t		length);

/*!
** The gl_bunny_my_load_pixelarray is supposed to be the function pointer to set
** in order to expand bunny_load_pixelarray functionnalities to manage new types
** of picture and having your function evaluate by bunny_self_test, but it is
** currently unused.p
*/
extern t_bunny_my_load_pixelarray gl_bunny_my_load_pixelarray;

/*!
** The gl_bunny_my_read_pixelarray is supposed to be the function pointer to set
** in order to expand bunny_read_pixelarray functionnalities to manage new types
** of picture and having your function evaluate by bunny_self_test, but it is
** currently unused.p
*/
extern t_bunny_my_read_pixelarray gl_bunny_my_read_pixelarray;

/*!
** The bunny_save_pixelarray save a t_bunny_pixelarray content into a picture file.
** Supported formats are .png, .jpg, .gif and .bmp. The alpha channel saving
** depends on the output file format. 
** \param buf The picture to save
** \param file The file in which the content of the picture will be saved.
*/
bool				bunny_save_pixelarray(const t_bunny_pixelarray	*buf,
						      const char		*file);

/*!
** The t_bunny_picture type is a graphic element that is fast and stored inside
** the graphic memory, on your graphic card. There is no fast way to access to pixels
** easily like in t_bunny_pixelarray but operation like blitting or drawing complex
** shape are infinitly faster on t_bunny_picture than on t_bunny_pixelarray
**
** Note that every t_bunny_clipable attributes are fully working with t_bunny_picture.
*/
typedef t_bunny_clipable	t_bunny_picture;

/*!
** The bunny_new_picture creates a picture in the graphic memory. The t_bunny_picture
** is fast when you need to draw complex shapes and other pictures to and from it.
** The reserved memory to handle it is outside the bunny_malloc space.
** \param wid The width of the picture
** \param hei The height of the picture
** \return Return a valid t_bunny_picture structure or NULL if there is not
** enough memory available.
*/
t_bunny_picture			*bunny_new_picture(unsigned int			wid,
						   unsigned int			hei);

/*!
** The bunny_load_picture load a picture from a file. Supported formats are
** .png, .jpg, .gif and 24 bits bitmap. Output is a fast picture.
** The reserved memory to handle it is outside the bunny_malloc space.
** \param file The file to open and read.
** \return Return a t_bunny_picture filled with the picture or NULL on error.
*/
t_bunny_picture			*bunny_load_picture(const char			*file);

/*!
** Save a picture into a file.
*/
bool				bunny_save_picture(const t_bunny_picture	*buf,
						   const char			*file);

/*!
** The bunny_read_picture load a picture from memory. Supported formats are
** .png, .jpg, .gif and 24 bits bitmap. Output is a fast picture.
** The reserved memory to handle it is outside the bunny_malloc space.
** The picture will be stored inside the ressource manager if from_file is not NULL.
** \param buffer The buffer to read.
** \param len The size of the sent buffer
** \param from_file The file from which the data was loaded. Used to create a checksum
** to store the ressource inside the bunny ressource manager.
** \return Return a t_bunny_picture filled with the picture or NULL on error.
*/
t_bunny_picture			*bunny_read_picture_id(const void		*pic,
						       size_t			l,
						       const char		*from_file);

/*!
** The bunny_read_picture load a picture from memory. Supported formats are
** .png, .jpg, .gif and 24 bits bitmap. Output is a fast picture.
** The reserved memory to handle it is outside the bunny_malloc space.
** The picture will be stored inside the ressource manager if from_file is not NULL.
** \param buffer The buffer to read.
** \param len The size of the sent buffer
** \param from_file The file from which the data was loaded. Used to create a checksum
** to store the ressource inside the bunny ressource manager.
** \return Return a t_bunny_picture filled with the picture or NULL on error.
*/
#define				bunny_read_picture(buffer, len)			\
  bunny_read_picture_id(buffer, len, NULL)

/*!
**
**
*/
typedef enum			t_bunny_clipable_type
  {
    BCT_PIXELARRAY,
    BCT_PICTURE,
    BCT_SPRITE			= BCT_PICTURE,
    BCT_FONT,
    BCT_TILEMAP,
    BCT_PARALLAX,
    BCT_CINEMATIC
  }				t_bunny_clipable_type;

/*!
** Load the sent configuration file (must be accepted by the bunny_configuration module)
** and set all values accordingly to what is inside the file.
**
** If conf_file or clipable is NULL, an error occurs.
** If *clipable is NULL, then a picture will be created et set thanks to the associated field
** in configuration file. The picture will be returned throught *clipable.
** If *clipable is not NULL, every of its attribute will be set depending on the config file.
**
** If config is NULL, then a configuration file will be loaded, used and destroyed.
** If *config is NULL, then a configuration file will be loaded, used and set to *config
** to be returned.
** If *config is not NULL, then it will be used as target to load the new configuration
** file.
**
** See formats/clipable to see how to format you files accordinly to their syntax.
**
** \param conf_file The configuration file that contains attributes.
** \param clipable The clipable to configure, or where to store the new one
** \param config The configuration file to use, or where to store the new loaded one,
** \param typ Is the clipable a pixelarray or a picture or bunny_font.
** \return True if the loading, reading and setting were done properly.
*/
bool				bunny_set_clipable_attribute(const char		*conf_file,
							     t_bunny_clipable	**clipable,
							     t_bunny_configuration **config,
							     t_bunny_clipable_type typ);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Destroy a clipable element. If the element is a t_bunny_pixelarray, you have
** to cast its address to the t_bunny_clipable* type or give the address of the
** clipable attribute of the pixelarray to the function.
** \param clp A pointer to a structure compatible with t_bunny_clipable to destroy.
** Like t_bunny_picture, sprite, pixelarray or font.
*/
#  define			bunny_delete_clipable(a)			\
  _bunny_delete_clipable							\
  (_Generic((a),								\
            t_bunny_clipable*: (t_bunny_clipable*)(a),				\
	    t_bunny_tilemap*: (t_bunny_clipable*)(a),				\
	    t_bunny_sprite*: (t_bunny_clipable*)(a),				\
	    t_bunny_pixelarray*: (t_bunny_clipable*)(a),			\
	    t_bunny_font*: (t_bunny_clipable*)(a)				\
	    ))
# else
#  define			bunny_delete_clipable(a)			\
  _bunny_delete_clipable(a)
# endif

/*!
** Destroy a clipable element. If the element is a t_bunny_pixelarray, you have
** to cast its address to the t_bunny_clipable* type or give the address of the
** clipable attribute of the pixelarray to the function.
**
** Use the bunny_delete_clipable macro instead of this function directly.
**
** \param clp A pointer to a t_bunny_clipable structure to destroy
*/
void				_bunny_delete_clipable(t_bunny_clipable		*clp);

/*!
** The bunny_blit function allow you to draw a picture on another picture.
** Because the first parameter is a t_bunny_buffer, you can use a t_bunny_pixelarray,
** a t_bunny_picture or a t_bunny_window as argument, because all of these structures
** got one t_bunny_buffer structure.
** The second parameter is a t_bunny_clipable, so you can use either a t_bunny_picture
** or a t_bunny_pixelarray as second parameter.
** The third parameter is the position where you wish to draw clp on buf. It may
** apply different transformations depending of the content of the t_bunny_clipable
** attributes (clip_*, scale, origin, rotation, color mask, ...)
** \param buf A t_bunny_buffer pointer that can be a t_bunny_window attribute or a
** a t_bunny_picture attribute or a t_bunny_clipable attribute inside a t_bunny_pixelarray
** attribute.
** \param clp The clipable picture that will be the source of pixels.
** \param pos The position in buf where to draw clp. Sending NULL means (0, 0)
*/
void				bunny_blit(t_bunny_buffer			*buf,
					   const t_bunny_clipable		*clp,
					   const t_bunny_position		*pos);

/*!
** The t_bunny_my_blit type is the type you have to respect if you wish to expand
** the bunny library with your blitting function. Set your function to the gl_bunny_my_blit
** pointer to add it to the library.
*/
typedef void			(*t_bunny_my_blit)(t_bunny_pixelarray		*pix,
						   const t_bunny_pixelarray	*in,
						   const t_bunny_position	*pos);
/*!
** The gl_bunny_my_blit function pointer is used when you call bunny_blit with two
** t_bunny_pixelarray as first and second parameter. By default, this function pointer
** 's value is NULL and so does not work. By setting your function to it, you can
** make bunny_blit works for two pixelarrays.
*/
extern t_bunny_my_blit		gl_bunny_my_blit;

/*!
** The bunny_draw function ask to the graphic board to compute every drawing made
** previously. You should call bunny_draw on t_bunny_picture before using them
** as source for a bunny_blit.
** \param picture The t_bunny_picture to render.
*/
void				bunny_draw(const t_bunny_picture		*picture);

/*!
** The bunny_set_pixel function draw a single pixel on the sent t_bunny_buffer.
** /!\ Because t_bunny_picture need a graphic board access to draw something,
** using this function with them will result in poor performences.
**
** This funtion will not work on t_bunny_pixelarray if you did not have set a
** correct function to its associated gl_bunny_my_set_pixel function pointer.
** You can test your function with the bunny_self_test function.
** /!\ It will also test the alpha management and gradiants
**
** \param buf The t_bunny_buffer where to draw
** \param pos The position where to write on the sent t_bunny_buffer
** \param col The color of the pixel to draw
*/
void				bunny_set_pixel(t_bunny_buffer			*buf,
						t_bunny_position		pos,
						unsigned int			col);
/*!
** The t_bunny_my_set_pixel type is the type you have to respect if you wish to expand
** the bunny library with your own pixel drawing function. Set your function to the
** gl_bunny_my_set_pixel function pointer to add it to the library.
*/
typedef void			(*t_bunny_my_set_pixel)(t_bunny_pixelarray	*pix,
							t_bunny_position	pos,
							unsigned int		color);
/*!
** The gl_bunny_my_set_pixel pointer is used when you call bunny_set_pixel with
** a t_bunny_pixelarray. By default, this function pointer's value is NULL and so does
** not work. By setting your function to it, you can make bunny_set_pixel works for
** pixelarrays.
*/
extern t_bunny_my_set_pixel	gl_bunny_my_set_pixel;

/*!
** The bunny_set_circle function draw a circle (1 pixel thick) on the sent t_bunny_buffer.
**
** This funtion will not work on t_bunny_pixelarray if you did not have set a
** correct function to its associated gl_bunny_my_set_circle function pointer.
** You can test your function with the bunny_self_test function.
** /!\ It will also test the alpha management and gradiants
**
** \param buf The t_bunny_buffer where to draw
** \param pos The position of the middle of the circle
** \param rad The radius of the circle
** \param col The color of the pixel to draw
*/
# define			bunny_set_circle(buf, pos, rad, col)		\
  bunny_set_disk(buf, pos, rad, TRANSPARENT, col, 1)

/*!
** The bunny_set_disk function draw a disk on the sent t_bunny_buffer.

** This funtion will not work on t_bunny_pixelarray if you did not have set a
** correct function to its associated gl_bunny_my_set_circle function pointer.
** You can test your function with the bunny_self_test function.
** /!\ It will also test the alpha management and gradiants
**
** \param buf The t_bunny_buffer where to draw
** \param pos The position of the middle of the circle
** \param rad The radius of the circle
** \param col The color of the pixel to draw
*/
void				bunny_set_disk(t_bunny_buffer			*buf,
					       t_bunny_position			pos,
					       t_bunny_position			rad,
					       unsigned int			icol,
					       unsigned int			ocol,
					       int				thik);

/*!
** The t_bunny_my_set_disk type is the type you have to respect if you wish to expand
** the bunny library with your own disk drawing function. Set your function to the
** gl_bunny_my_set_disk function pointer to add it to the library.
*/
typedef void			(*t_bunny_my_set_disk)(t_bunny_pixelarray	*pix,
						       t_bunny_position		pos,
						       t_bunny_position		rad,
						       unsigned int		icol,
						       unsigned int		ocol,
						       int			thik);

/*!
** The gl_bunny_my_set_disk pointer is used when you call bunny_set_disk with
** a t_bunny_pixelarray. By default, this function pointer's value is NULL and so does
** not work. By setting your function to it, you can make bunny_set_disk works for
** pixelarrays.
*/
extern t_bunny_my_set_disk	gl_bunny_my_set_disk;

/*!
** The bunny_set_line function draw a single line on the sent t_bunny_buffer.
**
** This funtion will not work on t_bunny_pixelarray if you did not have set a
** correct function to its associated gl_bunny_my_set_line function pointer.
** You can test your function with the bunny_self_test function.
** /!\ It will also test the alpha management and gradiants features.
**
** \param buf The t_bunny_buffer where to draw
** \param pos Coordinates of the line in pos[0] and pos[1]
** \param col The color of the line, from its start with col[0] to its end with col[1]
*/
void				bunny_set_line(t_bunny_buffer			*buf,
					       const t_bunny_position		*pos,
					       const unsigned int		*col);

/*!
** The t_bunny_my_set_line type is the type you have to respect if you wish to expand
** the bunny library with your own line drawing function. Set your function to the
** gl_bunny_my_set_line function pointer to add it to the library.
*/
typedef void			(*t_bunny_my_set_line)(t_bunny_pixelarray	*pix,
						       const t_bunny_position	*pos,
						       const unsigned int	*col);
/*!
** The gl_bunny_my_set_line pointer is used when you call bunny_set_line with
** a t_bunny_pixelarray. By default, this function pointer's value is NULL and so does
** not work. By setting your function to it, you can make bunny_set_line works for
** pixelarrays.
*/
extern t_bunny_my_set_line	gl_bunny_my_set_line;

/*!
** The bunny_set_polygon function draw a single line on the sent t_bunny_buffer.
**
** This funtion will not work on t_bunny_pixelarray if you did not have set a
** correct function to its associated gl_bunny_my_set_polygon function pointer.
** You can test your function with the bunny_self_test function.
** /!\ It will also test the alpha management and gradiants features.
**
** \param buf The t_bunny_buffer where to draw
** \param pos Coordinates of the polygon in pos[0], pos[1] and pos[2]
** \param col The color of the polygon, from col[0] to col[2]
*/
void				bunny_set_polygon(t_bunny_buffer		*buf,
						  const t_bunny_position	*pos,
						  const unsigned int		*col);

/*!
** The t_bunny_my_set_polygon type is the type you have to respect if you wish to expand
** the bunny library with your own polygon drawing function. Set your function to the
** gl_bunny_my_set_polygon function pointer to add it to the library.
*/
typedef void			(*t_bunny_my_set_polygon)(t_bunny_pixelarray	*pix,
							  const t_bunny_position*pos,
							  const unsigned int	*color);

/*!
** The gl_bunny_my_set_polygon pointer is used when you call bunny_set_polygon with
** a t_bunny_pixelarray. By default, this function pointer's value is NULL and so does
** not work. By setting your function to it, you can make bunny_set_polygon works for
** pixelarrays.
*/
extern t_bunny_my_set_polygon	gl_bunny_my_set_polygon;

void				bunny_set_zpolygon(t_bunny_buffer		*buf,
						   const t_bunny_accurate_zposition *pos,
						   const unsigned int		*col);
typedef void			(*t_bunny_my_set_zpolygon)(t_bunny_pixelarray	*pix,
							   const t_bunny_accurate_zposition *pos,
							   const unsigned int	*col);
extern t_bunny_my_set_zpolygon	gl_bunny_my_set_zpolygon;

/*!
** The bunny_fill function apply a color on the top of the clipped part of the sent picture.
** Because it applies a color, it means it apply alpha.
**
** This funtion will not work on t_bunny_pixelarray if you did not have set a
** correct function to its associated gl_bunny_my_fill function pointer.
** You can test your function with the bunny_self_test function.
** /!\ It will also test the alpha management and gradiants features.
**
** \param buffer The t_bunny_buffer where to draw
** \param color The color to apply on the t_bunny_buffer
*/
void				bunny_fill(t_bunny_buffer			*buffer,
					   unsigned int				color);

/*!
** The t_bunny_my_fill type is the type you have to respect if you wish to expand
** the bunny library with your own color filling function. Set your function to the
** gl_bunny_my_fill function pointer to add it to the library.
*/
typedef void			(*t_bunny_my_fill)(t_bunny_pixelarray		*pix,
						   unsigned int			color);

/*!
** The gl_bunny_my_fill pointer is used when you call bunny_fill with
** a t_bunny_pixelarray. By default, this function pointer's value is NULL and so does
** not work. By setting your function to it, you can make bunny_fill works for
** pixelarrays.
*/
extern t_bunny_my_fill		gl_bunny_my_fill;

/*!
** The bunny_clear function set pixels from the clipped part of the sent picture to color.
** Because it sets colors, it ignores alpha.
**
** This funtion will not work on t_bunny_pixelarray if you did not have set a
** correct function to its associated gl_bunny_my_clear function pointer.
** You can test your function with the bunny_self_test function.
** /!\ It will also test the alpha management and gradiants features.
**
** \param buffer The t_bunny_buffer where to draw
** \param color The color to set in the t_bunny_buffer
*/
void				bunny_clear(t_bunny_buffer			*buffer,
					    unsigned int			color);

/*!
** The t_bunny_my_clear type is the type you have to respect if you wish to expand
** the bunny library with your own color filling function. Set your function to the
** gl_bunny_my_clear function pointer to add it to the library.
*/
typedef void			(*t_bunny_my_clear)(t_bunny_pixelarray		*pix,
						    unsigned int		color);

/*!
** The gl_bunny_my_clear pointer is used when you call bunny_clear with
** a t_bunny_pixelarray. By default, this function pointer's value is NULL and so does
** not work. By setting your function to it, you can make bunny_clear works for
** pixelarrays.
*/
extern t_bunny_my_clear		gl_bunny_my_clear;

/*!
** The t_bunny_geometry enumeration is useful to inform the bunny_set_geometry
** function about the content of the t_bunny_vertex_array structure.
** Each value make bunny_set_geometry interpret coordinates differently.
*/
typedef enum			e_bunny_geometry
  {
    BGY_PIXELS,
    BGY_LINES,
    BGY_LINE_STRIP,
    BGY_TRIANGLES,
    BGY_TRIANGLE_STRIP,
    BGY_TRIANGLE_FAN,
    BGY_QUADS,
    LAST_GEOMETRY
  }				t_bunny_geometry;

/*!
** The t_bunny_vertex structure contains all information a shape may need
** to represent one single coordinate:
** - A position in the 2D space
** - The matching texture position (if there is a texture)
** - The color of the position (if there is no texture)
*/
typedef struct			s_bunny_vertex
{
  t_bunny_accurate_position	pos;
  t_bunny_position		tex;
  unsigned int			color;
}				t_bunny_vertex;

/*!
** The t_bunny_vertex_array is a structure that is useful to contains
** a collection of t_bunny_vertex. In order to use it, you have to
** manually reserve a specific amount of data depending of what you
** wish to store. For example, if you wish to draw two pixels:
**
** t_bunny_vertex_array		*array = bunny_alloca(sizeof(*array) + 2 * sizeof(array->vertex[0]));
**
** array->lenght = 2;
** fill(&array->vertex[0]);
** fill(&array->vertex[1]);
*/
typedef struct			s_bunny_vertex_array
{
  size_t			length;
  t_bunny_vertex  		vertex[__ZERO_LENGTH__];
}				t_bunny_vertex_array;

/*!
** The bunny_set_geometry function draw a shape in a buffer. The shape is determined
** by every sent coordinates and eventually the texture.
** /!\ It is impossible to mix t_bunny_picture and t_bunny_pixelarray.
**     If clipable is a pixelarray, then buffer must be a pixelarray.
**     If clipable is a picture, then buffer must be a picture or a window.
** \param buffer The t_bunny_buffer where to draw
** \param geometry The type of shape that is describded by the array of vertex.
** \param array A t_bunny_vertex_array that contains coordinates of the shape
** \param clipable The texture to use to draw the shape. May be NULL to use color instead.
*/
void				bunny_set_geometry(t_bunny_buffer		*buffer,
						   t_bunny_geometry		geometry,
						   t_bunny_vertex_array		*array,
						   t_bunny_clipable		*clipable);

/*!
** The t_bunny_my_geometry type is the type you have to respect if you wish to expand
** the bunny library with your own geometry drawing function. Set your function to the
** gl_bunny_my_geometry function pointer to add it to the library.
** The bunny_self_test does not currently evaluate the gl_bunny_my_geometry.
*/
typedef void			(*t_bunny_my_geometry)(t_bunny_pixelarray	*pix,
						       t_bunny_geometry		geometry,
						       t_bunny_vertex_array	*array,
						       t_bunny_pixelarray	*picture);

/*!
** The gl_bunny_my_geometry pointer is used when you call bunny_clear with
** a t_bunny_pixelarray. By default, this function pointer's value is NULL and so does
** not work. By setting your function to it, you can make bunny_set_geometry works for
** pixelarrays.
** The bunny_self_test does not currently evaluate the gl_bunny_my_geometry.
*/
extern t_bunny_my_geometry	gl_bunny_my_geometry;

/*!
** This function enable the full support of t_bunny_pixelarray in bunny_blit.
** It enable the support of every t_bunny_clipable attributes and of the alpha channel.
** \param enable True to enable full support, false to disable it. False is the default.
*/
void				bunny_enable_full_blit(bool			enable);
void				bunny_set_alpha_blit(bool			enable);
void				bunny_set_additional_blit(bool			enable);
void				bunny_set_multiply_blit(bool			blend);

/*!
** All picture loading function in the bunny library use a ressource manager to avoid
** loading several times the same file. This means behind every t_bunny_clipable
** you will create throught bunny_load_pi* functions, there is only one true
** load.
** bunny_set_*, bunny_blit, bunny_clear and bunny_fill functions are actually
** calling this function when you try to use them on a clipable that share datas
** to make it unique: like with copy on write, the data will be duplicated
** before being written.
** Pictures and pixelarrays created with bunny_new_* are already unique.
**
** The direct acces to pixels of t_bunny_pixelarray of course does not provoke
** the data duplication: so you may use this function before.
** Calling this function on an already unique clipable does not make anything.
**
** This function is the graphic equivalent of bunny_make_effect_unique in sound.
**
** \param clipable The clipable that will be turned unique
** \return True if everything went well. If the clipable was already unique,
** everything went well.
*/
bool				bunny_make_clipable_unique(t_bunny_clipable	*clipable);

size_t				bunny_get_maximum_picture_width(void);

void				bunny_reset_gl_states(t_bunny_buffer		*buf);
void				bunny_push_gl_states(t_bunny_buffer		*buf);
void				bunny_pop_gl_states(t_bunny_buffer		*buf);

#endif	/*			__LAPIN_GRAPHICS_H__	*/

