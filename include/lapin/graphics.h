/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
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
# if				defined(__MINGW32__) || defined(__GNUC__)
#  define			PACKED				__attribute__((packed))
# else
#  pragma			packed
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
typedef struct			s_bunny_clipable
{
  t_bunny_buffer		buffer;
  int32_t			clip_x_position;
  int32_t			clip_y_position;
  int32_t			clip_width;
  int32_t			clip_height;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;
} PACKED			t_bunny_clipable;

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
** gl_bunny_my_set_circle
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
}				t_bunny_pixelarray;

/*!
** The bunny_new_pixelarray creates a manual access picture. The t_bunny_pixelarray
** picture is the system memory and is fast when you need to access each pixels
** one per one. The bunny_new_pixelarray picture is stored inside the bunny_malloc space.
** \param wid The width of the picture
** \param hei The height of the picture
** \return Return a valid t_bunny_pixelarray structure or NULL if there is not
** enough memory available.
*/
t_bunny_pixelarray		*bunny_new_pixelarray(unsigned int		wid,
						      unsigned int		hei);

/*!
** The bunny_load_pixelarray load a picture from a file. Supported formats are
** .png, .jpg, .gif and 24 bits bitmap. Output is a manual access picture.
** \param file The file to open and read.
** \return Return a t_bunny_pixelarray filled with the picture or NULL on error.
*/
t_bunny_pixelarray		*bunny_load_pixelarray(const char		*file);

/*!
** The t_bunny_my_load_pixelarray type is currently unused by the library. It
** is the type of the function you have to implement to make the bunny library
** support specific formats it does not know how to manage (Like 32 bits bitmap)
** The self test function does not currently evaluate the function you would assign to
** gl_bunny_my_load_pixelarray.
*/
typedef t_bunny_pixelarray	*(*t_bunny_my_load_pixelarray)(const char	*file);

/*!
** The gl_bunny_my_load_pixelarray is supposed to be the function pointer to set
** in order to expand bunny_load_pixelarray functionnalities to manage new types
** of picture and having your function evaluate by bunny_self_test, but it is
** currently unused.p
*/
extern t_bunny_my_load_pixelarray gl_bunny_my_load_pixelarray;

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
** \param The file to open and read.
** \return Return a t_bunny_picture filled with the picture or NULL on error.
*/
t_bunny_picture			*bunny_load_picture(const char			*file);

/*!
** Destroy a clipable element. If the element is a t_bunny_pixelarray, you have
** to cast its address to the t_bunny_clipable* type or give the address of the
** clipable attribute of the pixelarray to the function.
** \param clp A pointer to a t_bunny_clipable structure to destroy
*/
void				bunny_delete_clipable(t_bunny_clipable		*clp);

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
** The bunny_set_pixel function draw a circle (1 pixel thick) on the sent t_bunny_buffer.
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
void				bunny_set_circle(t_bunny_buffer			*buf,
						 t_bunny_position		pos,
						 t_bunny_position		rad,
						 unsigned int			color);

/*!
** The t_bunny_my_set_circle type is the type you have to respect if you wish to expand
** the bunny library with your own circle drawing function. Set your function to the
** gl_bunny_my_set_circle function pointer to add it to the library.
*/
typedef void			(*t_bunny_my_set_circle)(t_bunny_pixelarray	*pix,
							 t_bunny_position	pos,
							 t_bunny_position	radius,
							 unsigned int		color);

/*!
** The gl_bunny_my_set_circle pointer is used when you call bunny_set_circle with
** a t_bunny_pixelarray. By default, this function pointer's value is NULL and so does
** not work. By setting your function to it, you can make bunny_set_circle works for
** pixelarrays.
*/
extern t_bunny_my_set_circle	gl_bunny_my_set_circle;

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
  t_bunny_position		pos;
  t_bunny_position		tex;
  unsigned int			color;
}				t_bunny_vertex;

/*!
** The t_bunny_vertex_array is a structure that is useful to contains
** a collection of t_bunny_vertex. In order to use it, you have to
** manually reserve a specific amount of data depending of what you
** wish to store. For example, if you wish to draw two pixels:
**
** t_bunny_vertex_array		*array = alloca(sizeof(*array) + 2 * sizeof(array->vertex[0]));
**
** array->lenght = 2;
** fill(&array->vertex[0]);
** fill(&array->vertex[1]);
*/
typedef struct			s_bunny_vertex_array
{
  size_t			length;
# ifndef			__ANSI__
  t_bunny_vertex  		vertex[0];
# else
  t_bunny_vertex		vertex[1];
# endif
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
** The t_bunny_vector_font_line_coord contains two sets of coordinates that
** represent a complete line. It is used by the t_bunny_letter structure
** in order to store coordinates of the gl_vector font.
*/
typedef struct			s_bunny_vector_font_line_coord
{
  int				x0;
  int				y0;
  int				x1;
  int				y1;
}				t_bunny_vector_font_line_coord;

/*!
** The t_bunny_letter structure contains the amount of lines for a letter
** of the gl_vector font, and an array of nb_edge t_bunny_vector_font_line_coord.
*/
typedef struct			s_bunny_letter
{
  int				nb_edge;
  t_bunny_vector_font_line_coord edge[5];
}				t_bunny_letter;

/*!
** The gl_vector constant is a collection of letters, which are a collection of
** lines. Drawing thoses lines makes appeir a letter. The gl_vector contains
** letters in this order: a-z0-9!. There is a enumeration that describe completly
** how the gl_vector is made in the enum.h file: t_bunny_letter_tab.
*/
extern const t_bunny_letter	gl_vector[LAST_BUNNY_FONT];

/*!
** The t_bunny_shader element is an effect that will be applied while blitting.
** The type is entirely private, so you cannot making anything else that
** use a pointer to it, there is no attribute.
*/
typedef void			t_bunny_shader;

/*!
** The bunny_shader_set_variable function can takes several different types
** of values as parameter thanks to its variading design. In order to specify
** which type you wish to send, specify it thanks to this enumartion.
*/
typedef enum			e_bunny_variable_type
  {
    BVT_1_FLOAT,
    BVT_2_FLOAT,
    BVT_3_FLOAT,
    BVT_4_COLOR_COMPONENT,
    BVT_FULL_COLOR,
    BVT_TRANSFORM,
    BVT_PICTURE,
    BVT_CURRENT_TEXTURE_TYPE
  }				t_bunny_variable_type;

/*!
** The t_bunny_transform structure is useful to specify
** in only one call to bunny_shader_set_variable an entire
** set of transformations: moving the origin of the element,
** placing it on the output graphic, change its scale and
** its rotation.
*/
typedef struct			s_bunny_transform
{
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	translation;
  t_bunny_accurate_position	scale;
  double			rotation;
}				t_bunny_transform;

/*!
** The bunny_is_shader_available return true or false depending of the
** availibility of the shader system. If they are not available, do not
** try to use them.
** \return True if shaders are available, else false.
*/
bool				bunny_is_shader_available(void);

/*!
** The bunny_new_shader function creates an empty shader.
** \return NULL if there is not enough memory.
*/
t_bunny_shader			*bunny_new_shader(void);

/*!
** The bunny_load_shader function load two files and compile their code
** inside the sent shader. The vertex_file is optionnal and NULL may be
** sent.
** \param sha The shader that was previously created with bunny_new_shader.
** \param vertex_file A file that contains the vertex side of the GLSL code.
** \param frag_file A file that contains the fragment side of the GLSL code.
** \return True if everything went well. False on error.
*/
bool				bunny_load_shader(t_bunny_shader		*sha,
						  const char			*vertex_file,
						  const char			*frag_file);

/*!
** Set a variable inside the GLSL code with a value from your program.
** \param sha The shader where your variable is from.
** \param varname The name of the variable inside your GLSL.
** \param type The type of the data you will send as fourth parameter.
** \param ...
** If type is BVT_1_FLOAT, ... must be 1 float.
** If type is BVT_2_FLOAT, ... must be 2 float.
** If type is BVT_3_FLOAT, ... must be 3 float.
** If type is BVT_4_COLOR_COMPONENT, ... must be 4 int
** If type is BVT_FULL_COLOR, ... must be an unsigned int
** If type is BTV_TRANSFORM, ... must be a t_bunny_transform*
** If type is BVT_PICTURE, ... must be a t_bunny_picture*
** If type if BTV_CURRENT_TEXTURE_TYPE, ... must be nothing.
*/
void				bunny_shader_set_variable(t_bunny_shader	*sha,
							  const char		*varname,
							  t_bunny_variable_type	type,
							  ...);

/*!
** Do the same thing as bunny_blit and works almost the same way. Here are the differences:
** - It applies the sent shader on the sent picture.
** - buffer cannot be a pixelarray
** - picture cannot be a pixelarray
** \param buffer The surface where to draw, may be a t_bunny_window or a t_bunny_picture.
** \param picture The surface to draw. t_bunny_pixelarray is not a valid parameter.
** \param position The position where the picture will be blended.
** \param shader The shader that will be used while blitting picture on buffer.
*/
void				bunny_blit_shader(t_bunny_buffer		*buffer,
						  const t_bunny_picture		*picture,
						  const t_bunny_position	*position,
						  const t_bunny_shader		*shader);

/*!
** This function delete a shader created with bunny_new_shader.
** \param shader The shader to destroy.
*/
void				bunny_delete_shader(t_bunny_shader		*shader);

/*!
** This function enable the full support of t_bunny_pixelarray in bunny_blit.
** It enable the support of every t_bunny_clipable attributes and of the alpha channel.
** \param enable True to enable full support, false to disable it. False is the default.
*/
void				bunny_enable_full_blit(bool			enable);

#endif	/*			__LAPIN_GRAPHICS_H__	*/

