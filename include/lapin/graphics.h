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

/**
 * @doc-symbol t_bunny_clipable
 * @doc-module graphics
 * @doc-kind type
 * @doc-order 10
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Describes a graphic element that can be clipped, positioned, scaled, rotated and color-masked.
 * @description This structure inherits from t_bunny_buffer by having it as first field. It can therefore be passed to functions expecting a t_bunny_buffer when appropriate.
 * @description The clipping fields select the subpart used as a source. The position, origin, scale and rotation fields describe how the clipable is transformed when it is drawn.
 * @param buffer The inherited t_bunny_buffer header describing the size and kind of the graphic element.
 * @param clip_x_position The X position of the clipped source rectangle. The default value is 0.
 * @param clip_y_position The Y position of the clipped source rectangle. The default value is 0.
 * @param clip_width The width of the clipped source rectangle. The default value is buffer.width.
 * @param clip_height The height of the clipped source rectangle. The default value is buffer.height.
 * @param position The default drawing position used when a blit position parameter is NULL.
 * @param origin The hot spot of the clipable and its rotation center. The default value is 0, 0.
 * @param scale The scale applied to the clipable. The default value is 1, 1.
 * @param rotation The rotation angle in degrees. The default value is 0.
 * @param color_mask The color mask applied when the clipable is used as a source. The default value is WHITE.
 * @param smooth Enables texture smoothing when the backend supports it.
 * @param mosaic Enables repeated texture addressing when the backend supports it.
 * @see bunny_clipable_copy, bunny_set_clipable_attribute, bunny_blit, bunny_picture, t_bunny_pixelarray
 *
 * @doc-lang fr
 * @brief Décrit un élément graphique pouvant être découpé, placé, redimensionné, pivoté et masqué par couleur.
 * @description Cette structure hérite de t_bunny_buffer en le plaçant comme premier champ. Elle peut donc être transmise aux fonctions attendant un t_bunny_buffer lorsque c’est pertinent.
 * @description Les champs de découpe sélectionnent la sous-partie utilisée comme source. Les champs position, origin, scale et rotation décrivent la transformation appliquée au moment du dessin.
 * @param buffer L’en-tête t_bunny_buffer hérité, décrivant la taille et la nature de l’élément graphique.
 * @param clip_x_position La position X du rectangle source découpé. La valeur par défaut est 0.
 * @param clip_y_position La position Y du rectangle source découpé. La valeur par défaut est 0.
 * @param clip_width La largeur du rectangle source découpé. La valeur par défaut est buffer.width.
 * @param clip_height La hauteur du rectangle source découpé. La valeur par défaut est buffer.height.
 * @param position La position de dessin par défaut utilisée lorsque le paramètre de position d’un blit vaut NULL.
 * @param origin Le point d’accroche du clipable et son centre de rotation. La valeur par défaut est 0, 0.
 * @param scale Le facteur d’échelle appliqué au clipable. La valeur par défaut est 1, 1.
 * @param rotation L’angle de rotation en degrés. La valeur par défaut est 0.
 * @param color_mask Le masque de couleur appliqué lorsque le clipable est utilisé comme source. La valeur par défaut est WHITE.
 * @param smooth Active le lissage de texture lorsque le moteur sous-jacent le permet.
 * @param mosaic Active la répétition de texture lorsque le moteur sous-jacent le permet.
 * @see bunny_clipable_copy, bunny_set_clipable_attribute, bunny_blit, bunny_picture, t_bunny_pixelarray
 */
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

/**
 * @doc-symbol bunny_clipable_copy
 * @doc-module graphics
 * @doc-kind macro
 * @doc-order 15
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Copies the public transformation attributes of a clipable into another one.
 * @description The buffer itself and the underlying graphic resource are not copied. Only clipping, position, origin, scale, rotation, color mask and display flags are copied.
 * @param dest The clipable that receives the copied attributes.
 * @param ori The clipable used as source.
 * @see t_bunny_clipable
 *
 * @doc-lang fr
 * @brief Copie les attributs publics de transformation d’un clipable vers un autre.
 * @description Le buffer lui-même et la ressource graphique sous-jacente ne sont pas copiés. Seuls la découpe, la position, l’origine, l’échelle, la rotation, le masque de couleur et les drapeaux d’affichage sont copiés.
 * @param dest Le clipable qui reçoit les attributs copiés.
 * @param ori Le clipable utilisé comme source.
 * @see t_bunny_clipable
 */
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

/**
 * @doc-symbol t_bunny_bitwidth
 * @doc-module graphics
 * @doc-kind type
 * @doc-order 18
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Enumerates the color depths supported by forged pixelarrays.
 * @description Values describe indexed, direct ARGB and floating color layouts. For bitplane pixelarrays, the bit count is provided separately.
 * @see bunny_forge_pixelarray, t_bunny_pixelarray
 *
 * @doc-lang fr
 * @brief Énumère les profondeurs de couleur prises en charge par les pixelarrays forgés.
 * @description Les valeurs décrivent les formats indexés, ARGB direct et flottant. Pour les pixelarrays en bitplane, le nombre de bits est fourni séparément.
 * @see bunny_forge_pixelarray, t_bunny_pixelarray
 */
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
/**
 * @doc-symbol t_bunny_pixelarray
 * @doc-module graphics
 * @doc-kind type
 * @doc-order 20
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a graphic buffer stored in system memory with direct pixel access.
 * @description A pixelarray is convenient when pixels must be read or written manually. By default, LibLapin does not draw into pixelarrays unless the matching gl_bunny_my_* callbacks are provided.
 * @description The pixels field starts at the top-left pixel and is stored line after line.
 * @param clipable The inherited clipable header. Its clipping fields are meaningful when the pixelarray is used as a source.
 * @param pixels The raw pixel storage. Its layout is described by the following fields.
 * @param bits_per_pixels The color depth or bit count depending on bitplane.
 * @param bitplane True when the pixelarray uses bitplanes instead of direct color depth.
 * @param color_palette_size The amount of entries used in color_palette.
 * @param color_palette The palette used by indexed formats.
 * @param color_shifts The component shifts used to interpret direct color pixels.
 * @see bunny_new_pixelarray, bunny_forge_pixelarray, bunny_load_pixelarray, bunny_delete_clipable
 *
 * @doc-lang fr
 * @brief Représente un buffer graphique stocké en mémoire système avec accès direct aux pixels.
 * @description Un pixelarray est pratique lorsque les pixels doivent être lus ou écrits manuellement. Par défaut, la LibLapin ne dessine pas dans les pixelarrays sans les callbacks gl_bunny_my_* correspondants.
 * @description Le champ pixels commence au pixel en haut à gauche et se poursuit ligne après ligne.
 * @param clipable L’en-tête clipable hérité. Ses champs de découpe sont significatifs lorsque le pixelarray est utilisé comme source.
 * @param pixels Le stockage brut des pixels. Son organisation est décrite par les champs suivants.
 * @param bits_per_pixels La profondeur de couleur ou le nombre de bits selon bitplane.
 * @param bitplane Vaut true lorsque le pixelarray utilise des bitplanes plutôt qu’une profondeur de couleur directe.
 * @param color_palette_size Le nombre d’entrées utilisées dans color_palette.
 * @param color_palette La palette utilisée par les formats indexés.
 * @param color_shifts Les décalages de composantes utilisés pour interpréter les pixels en couleur directe.
 * @see bunny_new_pixelarray, bunny_forge_pixelarray, bunny_load_pixelarray, bunny_delete_clipable
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
/**
 * @doc-symbol bunny_read_pixelarray
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 60
 * @doc-since 5
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Reads an image file already loaded in memory and returns it as a pixelarray.
 * @description This is a convenience macro calling bunny_read_pixelarray_id with a NULL resource identifier.
 * @param buffer The memory buffer containing the complete encoded picture file.
 * @param len The size of buffer in bytes.
 * @return-success A newly allocated t_bunny_pixelarray.
 * @return-failure NULL on failure.
 * @see bunny_read_pixelarray_id, bunny_load_pixelarray, bunny_new_pixelarray
 *
 * @doc-lang fr
 * @brief Lit un fichier image déjà chargé en mémoire et le renvoie sous forme de pixelarray.
 * @description C’est une macro de confort appelant bunny_read_pixelarray_id avec un identifiant de ressource NULL.
 * @param buffer Le buffer mémoire contenant le fichier image encodé complet.
 * @param len La taille de buffer en octets.
 * @return-success Un t_bunny_pixelarray nouvellement alloué.
 * @return-failure NULL en cas d’échec.
 * @see bunny_read_pixelarray_id, bunny_load_pixelarray, bunny_new_pixelarray
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
/**
 * @doc-symbol t_bunny_my_load_pixelarray
 * @doc-module graphics
 * @doc-kind callback
 * @doc-order 70
 * @doc-since 5
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Type of a custom image-file loader returning a pixelarray.
 * @description This extension point is intended for image formats not handled by the library loader.
 * @param file The path of the file to load.
 * @return-success A loaded t_bunny_pixelarray.
 * @return-failure NULL when the custom loader cannot load the file.
 * @see gl_bunny_my_load_pixelarray, bunny_load_pixelarray
 *
 * @doc-lang fr
 * @brief Type d’un chargeur personnalisé de fichier image renvoyant un pixelarray.
 * @description Ce point d’extension est destiné aux formats d’image qui ne sont pas pris en charge par le chargeur de la bibliothèque.
 * @param file Le chemin du fichier à charger.
 * @return-success Un t_bunny_pixelarray chargé.
 * @return-failure NULL lorsque le chargeur personnalisé ne peut pas charger le fichier.
 * @see gl_bunny_my_load_pixelarray, bunny_load_pixelarray
 */
typedef t_bunny_pixelarray	*(*t_bunny_my_load_pixelarray)(const char	*file);

/*!
** The t_bunny_my_read_pixelarray type is currently unused by the library. It
** is the type of the function you have to implement to make the bunny library
** support specific formats it does not know how to manage (Like 32 bits bitmap)
** The self test function does not currently evaluate the function you would assign to
** gl_bunny_my_read_pixelarray.
*/
/**
 * @doc-symbol t_bunny_my_read_pixelarray
 * @doc-module graphics
 * @doc-kind callback
 * @doc-order 80
 * @doc-since 5
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Type of a custom in-memory image reader returning a pixelarray.
 * @description This extension point is intended for encoded image data already present in memory.
 * @param buf The memory buffer containing the encoded picture.
 * @param length The size of buf in bytes.
 * @return-success A loaded t_bunny_pixelarray.
 * @return-failure NULL when the custom reader cannot read the buffer.
 * @see gl_bunny_my_read_pixelarray, bunny_read_pixelarray_id
 *
 * @doc-lang fr
 * @brief Type d’un lecteur personnalisé d’image en mémoire renvoyant un pixelarray.
 * @description Ce point d’extension est destiné aux données d’image encodées déjà présentes en mémoire.
 * @param buf Le buffer mémoire contenant l’image encodée.
 * @param length La taille de buf en octets.
 * @return-success Un t_bunny_pixelarray chargé.
 * @return-failure NULL lorsque le lecteur personnalisé ne peut pas lire le buffer.
 * @see gl_bunny_my_read_pixelarray, bunny_read_pixelarray_id
 */
typedef t_bunny_pixelarray	*(*t_bunny_my_read_pixelarray)(const void	*buf,
							       size_t		length);

/*!
** The gl_bunny_my_load_pixelarray is supposed to be the function pointer to set
** in order to expand bunny_load_pixelarray functionnalities to manage new types
** of picture and having your function evaluate by bunny_self_test, but it is
** currently unused.
*/
/**
 * @doc-symbol gl_bunny_my_load_pixelarray
 * @doc-module graphics
 * @doc-kind global
 * @doc-order 90
 * @doc-since 5
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Custom pixelarray loader hook.
 * @description Assign a t_bunny_my_load_pixelarray function here to extend picture loading with additional file formats.
 * @see t_bunny_my_load_pixelarray, bunny_load_pixelarray
 *
 * @doc-lang fr
 * @brief Point d’accroche pour chargeur personnalisé de pixelarray.
 * @description Assignez ici une fonction t_bunny_my_load_pixelarray pour étendre le chargement d’images à des formats supplémentaires.
 * @see t_bunny_my_load_pixelarray, bunny_load_pixelarray
 */
extern t_bunny_my_load_pixelarray gl_bunny_my_load_pixelarray;

/*!
** The gl_bunny_my_read_pixelarray is supposed to be the function pointer to set
** in order to expand bunny_read_pixelarray functionnalities to manage new types
** of picture and having your function evaluate by bunny_self_test, but it is
** currently unused.
*/
/**
 * @doc-symbol gl_bunny_my_read_pixelarray
 * @doc-module graphics
 * @doc-kind global
 * @doc-order 100
 * @doc-since 5
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Custom in-memory pixelarray reader hook.
 * @description Assign a t_bunny_my_read_pixelarray function here to extend image decoding from memory.
 * @see t_bunny_my_read_pixelarray, bunny_read_pixelarray_id
 *
 * @doc-lang fr
 * @brief Point d’accroche pour lecteur personnalisé de pixelarray en mémoire.
 * @description Assignez ici une fonction t_bunny_my_read_pixelarray pour étendre le décodage d’image depuis la mémoire.
 * @see t_bunny_my_read_pixelarray, bunny_read_pixelarray_id
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
/**
 * @doc-symbol t_bunny_picture
 * @doc-module graphics
 * @doc-kind type
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a graphic resource stored on the graphic backend.
 * @description Pictures are faster than pixelarrays for blits and complex drawing operations. They do not provide fast direct pixel access.
 * @description All t_bunny_clipable attributes are meaningful on pictures.
 * @see t_bunny_clipable, bunny_new_picture, bunny_load_picture, bunny_delete_clipable
 *
 * @doc-lang fr
 * @brief Représente une ressource graphique stockée côté moteur graphique.
 * @description Les pictures sont plus rapides que les pixelarrays pour les blits et les opérations de dessin complexes. Elles ne fournissent pas d’accès direct rapide aux pixels.
 * @description Tous les attributs de t_bunny_clipable sont significatifs sur les pictures.
 * @see t_bunny_clipable, bunny_new_picture, bunny_load_picture, bunny_delete_clipable
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
/**
 * @doc-symbol bunny_read_picture
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 160
 * @doc-since 5
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Reads an image file already loaded in memory and returns it as a picture.
 * @description This is a convenience macro calling bunny_read_picture_id with a NULL resource identifier.
 * @param buffer The memory buffer containing the complete encoded picture file.
 * @param len The size of buffer in bytes.
 * @return-success A newly allocated t_bunny_picture.
 * @return-failure NULL on failure.
 * @see bunny_read_picture_id, bunny_load_picture, bunny_new_picture
 *
 * @doc-lang fr
 * @brief Lit un fichier image déjà chargé en mémoire et le renvoie sous forme de picture.
 * @description C’est une macro de confort appelant bunny_read_picture_id avec un identifiant de ressource NULL.
 * @param buffer Le buffer mémoire contenant le fichier image encodé complet.
 * @param len La taille de buffer en octets.
 * @return-success Un t_bunny_picture nouvellement alloué.
 * @return-failure NULL en cas d’échec.
 * @see bunny_read_picture_id, bunny_load_picture, bunny_new_picture
 */
#define				bunny_read_picture(buffer, len)			\
  bunny_read_picture_id(buffer, len, NULL)

/*!
**
**
*/
/**
 * @doc-symbol t_bunny_clipable_type
 * @doc-module graphics
 * @doc-kind type
 * @doc-order 165
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Identifies the concrete kind of clipable configured by bunny_set_clipable_attribute.
 * @description The value tells the configuration loader whether it must create or configure a pixelarray, picture, sprite, font, tilemap, parallax or cinematic object.
 * @see bunny_set_clipable_attribute
 *
 * @doc-lang fr
 * @brief Identifie le type concret de clipable configuré par bunny_set_clipable_attribute.
 * @description La valeur indique au chargeur de configuration s’il doit créer ou configurer un pixelarray, une picture, un sprite, une police, une tilemap, un parallax ou une cinématique.
 * @see bunny_set_clipable_attribute
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

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
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
/**
 * @doc-symbol t_bunny_my_blit
 * @doc-module graphics
 * @doc-kind callback
 * @doc-order 190
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Type of a user blitter used when blitting pixelarrays together.
 * @description Set gl_bunny_my_blit to a function of this type to make bunny_blit work from one t_bunny_pixelarray to another.
 * @param pix The destination pixelarray.
 * @param in The source pixelarray.
 * @param pos The destination position, or NULL for the source position.
 * @see gl_bunny_my_blit, bunny_blit
 *
 * @doc-lang fr
 * @brief Type d’un blitter utilisateur utilisé pour blitter des pixelarrays entre eux.
 * @description Assignez une fonction de ce type à gl_bunny_my_blit pour permettre à bunny_blit de fonctionner d’un t_bunny_pixelarray vers un autre.
 * @param pix Le pixelarray de destination.
 * @param in Le pixelarray source.
 * @param pos La position de destination, ou NULL pour utiliser la position de la source.
 * @see gl_bunny_my_blit, bunny_blit
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
/**
 * @doc-symbol gl_bunny_my_blit
 * @doc-module graphics
 * @doc-kind global
 * @doc-order 200
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Pixelarray blitter hook used by bunny_blit.
 * @description The default value is NULL. When it is NULL, bunny_blit cannot draw into a t_bunny_pixelarray.
 * @see t_bunny_my_blit, bunny_blit
 *
 * @doc-lang fr
 * @brief Point d’accroche de blit pixelarray utilisé par bunny_blit.
 * @description La valeur par défaut est NULL. Lorsqu’elle vaut NULL, bunny_blit ne peut pas dessiner dans un t_bunny_pixelarray.
 * @see t_bunny_my_blit, bunny_blit
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
/**
 * @doc-symbol t_bunny_my_set_pixel
 * @doc-module graphics
 * @doc-kind callback
 * @doc-order 230
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Type of a user function that draws one pixel into a pixelarray.
 * @param pix The destination pixelarray.
 * @param pos The pixel position.
 * @param color The color to draw.
 * @see gl_bunny_my_set_pixel, bunny_set_pixel
 *
 * @doc-lang fr
 * @brief Type d’une fonction utilisateur dessinant un pixel dans un pixelarray.
 * @param pix Le pixelarray de destination.
 * @param pos La position du pixel.
 * @param color La couleur à dessiner.
 * @see gl_bunny_my_set_pixel, bunny_set_pixel
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
/**
 * @doc-symbol gl_bunny_my_set_pixel
 * @doc-module graphics
 * @doc-kind global
 * @doc-order 240
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Pixelarray pixel-drawing hook used by bunny_set_pixel.
 * @description The default value is NULL. Assign a matching callback to enable this operation on t_bunny_pixelarray targets.
 * @see t_bunny_my_set_pixel, bunny_set_pixel
 *
 * @doc-lang fr
 * @brief Point d’accroche de dessin de pixel dans un pixelarray utilisé par bunny_set_pixel.
 * @description La valeur par défaut est NULL. Assignez un callback correspondant pour activer cette opération sur les cibles t_bunny_pixelarray.
 * @see t_bunny_my_set_pixel, bunny_set_pixel
 */
extern t_bunny_my_set_pixel	gl_bunny_my_set_pixel;

/*!
** The bunny_set_circle function draw a circle (1 pixel thick) on the sent t_bunny_buffer.
**
** This funtion will not work on t_bunny_pixelarray if you did not have set a
** correct function to its associated gl_bunny_my_set_disk function pointer.
** You can test your function with the bunny_self_test function.
** /!\ It will also test the alpha management and gradiants
**
** \param buf The t_bunny_buffer where to draw
** \param pos The position of the middle of the circle
** \param rad The radius of the circle
** \param col The color of the pixel to draw
*/
/**
 * @doc-symbol bunny_set_circle
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 250
 * @doc-since 8
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Draws the outline of a circle on a buffer.
 * @description This is a convenience macro calling bunny_set_disk with a transparent inside color and a thickness of 1.
 * @param buf The target buffer.
 * @param pos The center of the circle.
 * @param rad The radius of the circle.
 * @param col The color of the circle outline.
 * @see bunny_set_disk, t_bunny_my_set_disk, gl_bunny_my_set_disk
 *
 * @doc-lang fr
 * @brief Dessine le contour d’un cercle dans un buffer.
 * @description C’est une macro de confort appelant bunny_set_disk avec une couleur intérieure transparente et une épaisseur de 1.
 * @param buf Le buffer cible.
 * @param pos Le centre du cercle.
 * @param rad Le rayon du cercle.
 * @param col La couleur du contour du cercle.
 * @see bunny_set_disk, t_bunny_my_set_disk, gl_bunny_my_set_disk
 */
# define			bunny_set_circle(buf, pos, rad, col)		\
  bunny_set_disk(buf, pos, rad, TRANSPARENT, col, 1)

/*!
** The bunny_set_disk function draw a disk on the sent t_bunny_buffer.

** This funtion will not work on t_bunny_pixelarray if you did not have set a
** correct function to its associated gl_bunny_my_set_disk function pointer.
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
/**
 * @doc-symbol t_bunny_my_set_disk
 * @doc-module graphics
 * @doc-kind callback
 * @doc-order 260
 * @doc-since 11
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Type of a user function that draws a disk or circle into a pixelarray.
 * @param pix The destination pixelarray.
 * @param pos The center of the disk.
 * @param rad The disk radius on X and Y.
 * @param icol The inside color.
 * @param ocol The outline color.
 * @param thik The outline thickness.
 * @see gl_bunny_my_set_disk, bunny_set_disk, bunny_set_circle
 *
 * @doc-lang fr
 * @brief Type d’une fonction utilisateur dessinant un disque ou un cercle dans un pixelarray.
 * @param pix Le pixelarray de destination.
 * @param pos Le centre du disque.
 * @param rad Le rayon du disque en X et en Y.
 * @param icol La couleur intérieure.
 * @param ocol La couleur du contour.
 * @param thik L’épaisseur du contour.
 * @see gl_bunny_my_set_disk, bunny_set_disk, bunny_set_circle
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
/**
 * @doc-symbol gl_bunny_my_set_disk
 * @doc-module graphics
 * @doc-kind global
 * @doc-order 270
 * @doc-since 11
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Pixelarray disk-drawing hook used by bunny_set_disk and bunny_set_circle.
 * @description The default value is NULL. Assign a matching callback to enable this operation on t_bunny_pixelarray targets.
 * @see t_bunny_my_set_disk, bunny_set_disk, bunny_set_circle
 *
 * @doc-lang fr
 * @brief Point d’accroche de dessin de disque dans un pixelarray utilisé par bunny_set_disk et bunny_set_circle.
 * @description La valeur par défaut est NULL. Assignez un callback correspondant pour activer cette opération sur les cibles t_bunny_pixelarray.
 * @see t_bunny_my_set_disk, bunny_set_disk, bunny_set_circle
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
/**
 * @doc-symbol t_bunny_my_set_line
 * @doc-module graphics
 * @doc-kind callback
 * @doc-order 290
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Type of a user function that draws a line into a pixelarray.
 * @param pix The destination pixelarray.
 * @param pos The two line endpoints.
 * @param col The endpoint colors used for the gradient.
 * @see gl_bunny_my_set_line, bunny_set_line
 *
 * @doc-lang fr
 * @brief Type d’une fonction utilisateur dessinant une ligne dans un pixelarray.
 * @param pix Le pixelarray de destination.
 * @param pos Les deux extrémités de la ligne.
 * @param col Les couleurs des extrémités utilisées pour le dégradé.
 * @see gl_bunny_my_set_line, bunny_set_line
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
/**
 * @doc-symbol gl_bunny_my_set_line
 * @doc-module graphics
 * @doc-kind global
 * @doc-order 300
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Pixelarray line-drawing hook used by bunny_set_line.
 * @description The default value is NULL. Assign a matching callback to enable this operation on t_bunny_pixelarray targets.
 * @see t_bunny_my_set_line, bunny_set_line
 *
 * @doc-lang fr
 * @brief Point d’accroche de dessin de ligne dans un pixelarray utilisé par bunny_set_line.
 * @description La valeur par défaut est NULL. Assignez un callback correspondant pour activer cette opération sur les cibles t_bunny_pixelarray.
 * @see t_bunny_my_set_line, bunny_set_line
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
/**
 * @doc-symbol t_bunny_my_set_polygon
 * @doc-module graphics
 * @doc-kind callback
 * @doc-order 320
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Type of a user function that draws a filled triangle into a pixelarray.
 * @param pix The destination pixelarray.
 * @param pos The three triangle points.
 * @param color The three point colors used for the gradient.
 * @see gl_bunny_my_set_polygon, bunny_set_polygon
 *
 * @doc-lang fr
 * @brief Type d’une fonction utilisateur dessinant un triangle plein dans un pixelarray.
 * @param pix Le pixelarray de destination.
 * @param pos Les trois points du triangle.
 * @param color Les trois couleurs des points utilisées pour le dégradé.
 * @see gl_bunny_my_set_polygon, bunny_set_polygon
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
/**
 * @doc-symbol gl_bunny_my_set_polygon
 * @doc-module graphics
 * @doc-kind global
 * @doc-order 330
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Pixelarray polygon-drawing hook used by bunny_set_polygon.
 * @description The default value is NULL. Assign a matching callback to enable this operation on t_bunny_pixelarray targets.
 * @see t_bunny_my_set_polygon, bunny_set_polygon
 *
 * @doc-lang fr
 * @brief Point d’accroche de dessin de polygone dans un pixelarray utilisé par bunny_set_polygon.
 * @description La valeur par défaut est NULL. Assignez un callback correspondant pour activer cette opération sur les cibles t_bunny_pixelarray.
 * @see t_bunny_my_set_polygon, bunny_set_polygon
 */
extern t_bunny_my_set_polygon	gl_bunny_my_set_polygon;

void				bunny_set_zpolygon(t_bunny_buffer		*buf,
						   const t_bunny_accurate_zposition *pos,
						   const unsigned int		*col);
/**
 * @doc-symbol t_bunny_my_set_zpolygon
 * @doc-module graphics
 * @doc-kind callback
 * @doc-order 333
 * @doc-since 0
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Type of a user function that draws a Z-aware triangle into a pixelarray.
 * @param pix The destination pixelarray.
 * @param pos The three triangle points with depth information.
 * @param col The three point colors used for the gradient.
 * @see gl_bunny_my_set_zpolygon, bunny_set_zpolygon
 *
 * @doc-lang fr
 * @brief Type d’une fonction utilisateur dessinant un triangle tenant compte du Z dans un pixelarray.
 * @param pix Le pixelarray de destination.
 * @param pos Les trois points du triangle avec information de profondeur.
 * @param col Les trois couleurs des points utilisées pour le dégradé.
 * @see gl_bunny_my_set_zpolygon, bunny_set_zpolygon
 */
typedef void			(*t_bunny_my_set_zpolygon)(t_bunny_pixelarray	*pix,
							   const t_bunny_accurate_zposition *pos,
							   const unsigned int	*col);
/**
 * @doc-symbol gl_bunny_my_set_zpolygon
 * @doc-module graphics
 * @doc-kind global
 * @doc-order 335
 * @doc-since 0
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Pixelarray Z-polygon drawing hook used by bunny_set_zpolygon.
 * @description The default value is NULL. Assign a matching callback to enable this operation on t_bunny_pixelarray targets.
 * @see t_bunny_my_set_zpolygon, bunny_set_zpolygon
 *
 * @doc-lang fr
 * @brief Point d’accroche de dessin de polygone avec Z dans un pixelarray utilisé par bunny_set_zpolygon.
 * @description La valeur par défaut est NULL. Assignez un callback correspondant pour activer cette opération sur les cibles t_bunny_pixelarray.
 * @see t_bunny_my_set_zpolygon, bunny_set_zpolygon
 */
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
/**
 * @doc-symbol t_bunny_my_fill
 * @doc-module graphics
 * @doc-kind callback
 * @doc-order 350
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Type of a user function that alpha-fills a pixelarray.
 * @param pix The destination pixelarray.
 * @param color The color to apply.
 * @see gl_bunny_my_fill, bunny_fill
 *
 * @doc-lang fr
 * @brief Type d’une fonction utilisateur remplissant un pixelarray avec alpha.
 * @param pix Le pixelarray de destination.
 * @param color La couleur à appliquer.
 * @see gl_bunny_my_fill, bunny_fill
 */
typedef void			(*t_bunny_my_fill)(t_bunny_pixelarray		*pix,
						   unsigned int			color);

/*!
** The gl_bunny_my_fill pointer is used when you call bunny_fill with
** a t_bunny_pixelarray. By default, this function pointer's value is NULL and so does
** not work. By setting your function to it, you can make bunny_fill works for
** pixelarrays.
*/
/**
 * @doc-symbol gl_bunny_my_fill
 * @doc-module graphics
 * @doc-kind global
 * @doc-order 360
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Pixelarray fill hook used by bunny_fill.
 * @description The default value is NULL. Assign a matching callback to enable this operation on t_bunny_pixelarray targets.
 * @see t_bunny_my_fill, bunny_fill
 *
 * @doc-lang fr
 * @brief Point d’accroche de remplissage d’un pixelarray utilisé par bunny_fill.
 * @description La valeur par défaut est NULL. Assignez un callback correspondant pour activer cette opération sur les cibles t_bunny_pixelarray.
 * @see t_bunny_my_fill, bunny_fill
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
/**
 * @doc-symbol t_bunny_my_clear
 * @doc-module graphics
 * @doc-kind callback
 * @doc-order 380
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Type of a user function that clears a pixelarray by setting pixels directly.
 * @param pix The destination pixelarray.
 * @param color The color to set.
 * @see gl_bunny_my_clear, bunny_clear
 *
 * @doc-lang fr
 * @brief Type d’une fonction utilisateur effaçant un pixelarray en fixant directement les pixels.
 * @param pix Le pixelarray de destination.
 * @param color La couleur à écrire.
 * @see gl_bunny_my_clear, bunny_clear
 */
typedef void			(*t_bunny_my_clear)(t_bunny_pixelarray		*pix,
						    unsigned int		color);

/*!
** The gl_bunny_my_clear pointer is used when you call bunny_clear with
** a t_bunny_pixelarray. By default, this function pointer's value is NULL and so does
** not work. By setting your function to it, you can make bunny_clear works for
** pixelarrays.
*/
/**
 * @doc-symbol gl_bunny_my_clear
 * @doc-module graphics
 * @doc-kind global
 * @doc-order 390
 * @doc-since 1
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Pixelarray clear hook used by bunny_clear.
 * @description The default value is NULL. Assign a matching callback to enable this operation on t_bunny_pixelarray targets.
 * @see t_bunny_my_clear, bunny_clear
 *
 * @doc-lang fr
 * @brief Point d’accroche d’effacement d’un pixelarray utilisé par bunny_clear.
 * @description La valeur par défaut est NULL. Assignez un callback correspondant pour activer cette opération sur les cibles t_bunny_pixelarray.
 * @see t_bunny_my_clear, bunny_clear
 */
extern t_bunny_my_clear		gl_bunny_my_clear;

/*!
** The t_bunny_geometry enumeration is useful to inform the bunny_set_geometry
** function about the content of the t_bunny_vertex_array structure.
** Each value make bunny_set_geometry interpret coordinates differently.
*/
/**
 * @doc-symbol t_bunny_geometry
 * @doc-module graphics
 * @doc-kind type
 * @doc-order 400
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Enumerates primitive modes for bunny_set_geometry.
 * @description Each value changes how the vertices stored in t_bunny_vertex_array are grouped before being drawn.
 * @see bunny_set_geometry, t_bunny_vertex_array
 *
 * @doc-lang fr
 * @brief Énumère les modes de primitives de bunny_set_geometry.
 * @description Chaque valeur change la manière dont les sommets stockés dans t_bunny_vertex_array sont regroupés avant le dessin.
 * @see bunny_set_geometry, t_bunny_vertex_array
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
/**
 * @doc-symbol t_bunny_vertex
 * @doc-module graphics
 * @doc-kind type
 * @doc-order 410
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores one vertex for geometry drawing.
 * @description A vertex contains a 2D position, a texture coordinate and a color. The texture coordinate is used when a clipable texture is supplied.
 * @param pos The position in the destination space.
 * @param tex The texture coordinate.
 * @param color The vertex color.
 * @see t_bunny_vertex_array, bunny_set_geometry
 *
 * @doc-lang fr
 * @brief Stocke un sommet pour le dessin géométrique.
 * @description Un sommet contient une position 2D, une coordonnée de texture et une couleur. La coordonnée de texture est utilisée lorsqu’une texture clipable est fournie.
 * @param pos La position dans l’espace de destination.
 * @param tex La coordonnée de texture.
 * @param color La couleur du sommet.
 * @see t_bunny_vertex_array, bunny_set_geometry
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
#pragma GCC diagnostic ignored "-Warray-bounds"
/**
 * @doc-symbol t_bunny_vertex_array
 * @doc-module graphics
 * @doc-kind type
 * @doc-order 420
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores a variable-length array of vertices.
 * @description Reserve enough memory for the header plus the required number of t_bunny_vertex entries before filling length and vertex.
 * @param length The number of vertices stored in vertex.
 * @param vertex The first element of the variable-length vertex storage.
 * @see t_bunny_vertex, bunny_set_geometry
 *
 * @doc-lang fr
 * @brief Stocke un tableau de sommets de taille variable.
 * @description Réservez assez de mémoire pour l’en-tête et pour le nombre voulu de t_bunny_vertex avant de remplir length et vertex.
 * @param length Le nombre de sommets stockés dans vertex.
 * @param vertex Le premier élément du stockage de sommets de taille variable.
 * @see t_bunny_vertex, bunny_set_geometry
 */
typedef struct			s_bunny_vertex_array
{
  size_t			length;
  t_bunny_vertex  		vertex[__ZERO_LENGTH__];
}				t_bunny_vertex_array;
#pragma GCC diagnostic pop

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
/**
 * @doc-symbol t_bunny_my_geometry
 * @doc-module graphics
 * @doc-kind callback
 * @doc-order 440
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Type of a user function that draws vertex geometry into a pixelarray.
 * @param pix The destination pixelarray.
 * @param geometry The primitive interpretation mode.
 * @param array The vertices to draw.
 * @param picture The optional pixelarray texture.
 * @see gl_bunny_my_geometry, bunny_set_geometry
 *
 * @doc-lang fr
 * @brief Type d’une fonction utilisateur dessinant de la géométrie de sommets dans un pixelarray.
 * @param pix Le pixelarray de destination.
 * @param geometry Le mode d’interprétation des primitives.
 * @param array Les sommets à dessiner.
 * @param picture La texture pixelarray optionnelle.
 * @see gl_bunny_my_geometry, bunny_set_geometry
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
/**
 * @doc-symbol gl_bunny_my_geometry
 * @doc-module graphics
 * @doc-kind global
 * @doc-order 450
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Pixelarray geometry hook used by bunny_set_geometry.
 * @description The default value is NULL. Assign a matching callback to enable this operation on t_bunny_pixelarray targets.
 * @see t_bunny_my_geometry, bunny_set_geometry
 *
 * @doc-lang fr
 * @brief Point d’accroche de dessin géométrique dans un pixelarray utilisé par bunny_set_geometry.
 * @description La valeur par défaut est NULL. Assignez un callback correspondant pour activer cette opération sur les cibles t_bunny_pixelarray.
 * @see t_bunny_my_geometry, bunny_set_geometry
 */
extern t_bunny_my_geometry	gl_bunny_my_geometry;

/*
**
**
*/

/**
 * @doc-symbol t_bunny_scale_type
 * @doc-module graphics
 * @doc-kind type
 * @doc-order 452
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Selects how bunny_scale_clipable fits a clipable into a target buffer.
 * @description BST_STRETCH distorts to fill the target, BST_CONTAIN keeps the whole source visible, and BST_COVER fills the target while preserving proportions.
 * @see bunny_scale_clipable
 *
 * @doc-lang fr
 * @brief Sélectionne la manière dont bunny_scale_clipable ajuste un clipable dans un buffer cible.
 * @description BST_STRETCH déforme pour remplir la cible, BST_CONTAIN garde toute la source visible et BST_COVER remplit la cible en conservant les proportions.
 * @see bunny_scale_clipable
 */
typedef enum			e_bunny_scale_type
  {
    BST_STRETCH,
    BST_CONTAIN,
    BST_COVER
  }				t_bunny_scale_type;

void				bunny_scale_clipable(const t_bunny_buffer	*target,
						     t_bunny_clipable		*clip,
						     t_bunny_scale_type		scale_type,
						     bool			square_pixel);

/*!
** This function enable the full support of t_bunny_pixelarray in bunny_blit.
** It enable the support of every t_bunny_clipable attributes and of the alpha channel.
** \param enable True to enable full support, false to disable it. False is the default.
*/
void				bunny_enable_full_blit(bool			enable);
void				bunny_set_alpha_blit(bool			enable);
void				bunny_set_additional_blit(bool			enable);
void				bunny_set_multiply_blit(bool			blend);

void				bunny_enable_normal_map(bool			enable);
void				bunny_display_normal_map(bool			enable);
bool				bunny_swap_color_and_normal_map(t_bunny_clipable *s);

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

