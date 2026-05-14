/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file shader.h
**
*/

#ifndef			__LAPIN_SHADER_H__
# define		__LAPIN_SHADER_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif


/**
 * @doc
 * @doc-symbol shader
 * @doc-kind module
 * @doc-module shader
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Creates GLSL shaders and higher-level shader configurations used while blitting pictures.
 * @header lapin/shader.h
 *
 * @doc-lang fr
 * @brief Crée des shaders GLSL et des configurations de shaders de plus haut niveau utilisées pendant le blit de pictures.
 * @header lapin/shader.h
 */

/*!
** The t_bunny_shader element is an effect that will be applied while blitting.
** The type is entirely private, so you cannot making anything else that
** use a pointer to it, there is no attribute.
*/


/**
 * @doc
 * @doc-symbol t_bunny_shader
 * @doc-kind type
 * @doc-module shader
 * @doc-order 5
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Represents an opaque shader object.
 * @description t_bunny_shader objects are created with bunny_new_shader, compiled with bunny_load_shader or bunny_read_shader, used with bunny_blit_shader, and destroyed with bunny_delete_shader.
 *
 * @doc-lang fr
 * @brief Représente un objet shader opaque.
 * @description Les objets t_bunny_shader sont créés avec bunny_new_shader, compilés avec bunny_load_shader ou bunny_read_shader, utilisés avec bunny_blit_shader et détruits avec bunny_delete_shader.
 */
typedef void		t_bunny_shader;

/*!
** The bunny_shader_set_variable function can takes several different types
** of values as parameter thanks to its variading design. In order to specify
** which type you wish to send, specify it thanks to this enumartion.
*/


/**
 * @doc
 * @doc-symbol t_bunny_variable_type
 * @doc-kind enum
 * @doc-module shader
 * @doc-order 10
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Selects the value type sent to bunny_shader_set_variable.
 * @enum BVT_1_FLOAT One numeric value.
 * @enum BVT_2_FLOAT Two numeric values.
 * @enum BVT_3_FLOAT Three numeric values.
 * @enum BVT_4_COLOR_COMPONENT Four color components.
 * @enum BVT_FULL_COLOR One packed t_bunny_color value.
 * @enum BVT_TRANSFORM A t_bunny_transform pointer.
 * @enum BVT_PICTURE A t_bunny_picture pointer.
 * @enum BVT_CURRENT_TEXTURE_TYPE The texture currently being blitted.
 *
 * @doc-lang fr
 * @brief Sélectionne le type de valeur envoyé à bunny_shader_set_variable.
 * @enum BVT_1_FLOAT Une valeur numérique.
 * @enum BVT_2_FLOAT Deux valeurs numériques.
 * @enum BVT_3_FLOAT Trois valeurs numériques.
 * @enum BVT_4_COLOR_COMPONENT Quatre composantes de couleur.
 * @enum BVT_FULL_COLOR Une valeur t_bunny_color compacte.
 * @enum BVT_TRANSFORM Un pointeur vers t_bunny_transform.
 * @enum BVT_PICTURE Un pointeur vers t_bunny_picture.
 * @enum BVT_CURRENT_TEXTURE_TYPE La texture actuellement blitée.
 */
typedef enum		e_bunny_variable_type
  {
    BVT_1_FLOAT,
    BVT_2_FLOAT,
    BVT_3_FLOAT,
    BVT_4_COLOR_COMPONENT,
    BVT_FULL_COLOR,
    BVT_TRANSFORM,
    BVT_PICTURE,
    BVT_CURRENT_TEXTURE_TYPE
  }			t_bunny_variable_type;

/*!
** The t_bunny_transform structure is useful to specify
** in only one call to bunny_shader_set_variable an entire
** set of transformations: moving the origin of the element,
** placing it on the output graphic, change its scale and
** its rotation.
*/


/**
 * @doc
 * @doc-symbol t_bunny_transform
 * @doc-kind struct
 * @doc-module shader
 * @doc-order 15
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Groups origin, translation, scale and rotation for shader variables.
 * @field origin Origin offset.
 * @field translation Destination translation.
 * @field scale Scale factor.
 * @field rotation Rotation angle in degrees.
 * @see bunny_shader_set_variable
 *
 * @doc-lang fr
 * @brief Regroupe origine, translation, échelle et rotation pour les variables de shader.
 * @field origin Décalage d'origine.
 * @field translation Translation de destination.
 * @field scale Facteur d'échelle.
 * @field rotation Angle de rotation en degrés.
 * @see bunny_shader_set_variable
 */
typedef struct		s_bunny_transform
{
  t_bunny_accurate_position origin;
  t_bunny_accurate_position translation;
  t_bunny_accurate_position scale;
  double		rotation;
}			t_bunny_transform;

/*!
** The bunny_is_shader_available return true or false depending of the
** availibility of the shader system. If they are not available, do not
** try to use them.
** \return True if shaders are available, else false.
*/
bool			bunny_is_shader_available(void);

/*!
** The bunny_new_shader function creates an empty shader.
** \return NULL if there is not enough memory.
*/
t_bunny_shader		*bunny_new_shader(void);

/*!
** The bunny_load_shader function load two files and compile their code
** inside the sent shader. The vertex_file is optionnal and NULL may be
** sent.
** \param sha The shader that was previously created with bunny_new_shader.
** \param vertex_file A file that contains the vertex side of the GLSL code.
** \param frag_file A file that contains the fragment side of the GLSL code.
** \return True if everything went well. False on error.
*/
bool			bunny_load_shader(t_bunny_shader		*sha,
					  const char			*vertex_file,
					  const char			*frag_file);

/*!
** The bunny_read_shader function read two scripts and compile their code
** inside the sent shader. The vertex is optionnal and NULL may be
** sent.
** \param sha The shader that was previously created with bunny_new_shader.
** \param vrt A string that contains the vertex side of the GLSL code.
** \param frg A strubg that contains the fragment side of the GLSL code.
** \return True if everything went well. False on error.
*/
bool			bunny_read_shader(t_bunny_shader		*sha,
					  const char			*vrt,
					  const char			*frg);

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
void			bunny_shader_set_variable(t_bunny_shader	*sha,
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
void			bunny_blit_shader(t_bunny_buffer		*buffer,
					  const t_bunny_picture		*picture,
					  const t_bunny_position	*position,
					  const t_bunny_shader		*shader);

/*!
** This function delete a shader created with bunny_new_shader.
** \param shader The shader to destroy.
*/
void			bunny_delete_shader(t_bunny_shader		*shader);



/**
 * @doc
 * @doc-symbol t_bunny_color_blind_tweak
 * @doc-kind enum
 * @doc-module shader
 * @doc-order 55
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Selects a color-channel permutation for screen tweak shaders.
 * @see t_bunny_screen_tweak
 *
 * @doc-lang fr
 * @brief Sélectionne une permutation de canaux de couleur pour les shaders de retouche écran.
 * @see t_bunny_screen_tweak
 */
typedef enum		e_bunny_color_blind_tweak
  {
    BCBT_RED_GREEN_BLUE,
    BCBT_RED_BLUE_GREEN,
    BCBT_GREEN_BLUE_RED,
    BCBT_BLUE_GREEN_RED,
    BCBT_BLUE_RED_GREEN
  }			t_bunny_color_blind_tweak;



/**
 * @doc
 * @doc-symbol t_bunny_noise_color
 * @doc-kind enum
 * @doc-module shader
 * @doc-order 60
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Selects the color mode of generated screen noise.
 * @enum BNC_COLOR_NOISE Colored noise.
 * @enum BNC_GRAY_NOISE Gray noise.
 * @enum BNC_BLACK_AND_WHITE_NOISE Black and white noise.
 * @see t_bunny_screen_tweak
 *
 * @doc-lang fr
 * @brief Sélectionne le mode de couleur du bruit écran généré.
 * @enum BNC_COLOR_NOISE Bruit coloré.
 * @enum BNC_GRAY_NOISE Bruit gris.
 * @enum BNC_BLACK_AND_WHITE_NOISE Bruit noir et blanc.
 * @see t_bunny_screen_tweak
 */
typedef enum		e_bunny_noise_color
  {
    BNC_COLOR_NOISE,
    BNC_GRAY_NOISE,
    BNC_BLACK_AND_WHITE_NOISE
  }			t_bunny_noise_color;



/**
 * @doc
 * @doc-symbol t_bunny_noise_type
 * @doc-kind enum
 * @doc-module shader
 * @doc-order 65
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Selects how screen noise is spatially generated.
 * @enum BNT_NO_NOISE No noise.
 * @enum BNT_PIXEL_NOISE Per-pixel noise.
 * @enum BNT_LINE_NOISE Per-line noise.
 * @enum BNT_ROW_NOISE Per-row noise.
 * @see t_bunny_screen_tweak
 *
 * @doc-lang fr
 * @brief Sélectionne comment le bruit écran est généré spatialement.
 * @enum BNT_NO_NOISE Pas de bruit.
 * @enum BNT_PIXEL_NOISE Bruit par pixel.
 * @enum BNT_LINE_NOISE Bruit par ligne.
 * @enum BNT_ROW_NOISE Bruit par colonne.
 * @see t_bunny_screen_tweak
 */
typedef enum		e_bunny_noise_type
  {
    BNT_NO_NOISE,
    BNT_PIXEL_NOISE,
    BNT_LINE_NOISE,
    BNT_ROW_NOISE
  }			t_bunny_noise_type;



/**
 * @doc
 * @doc-symbol t_bunny_screen_tweak
 * @doc-kind struct
 * @doc-module shader
 * @doc-order 70
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Configures the built-in screen tweak shader.
 * @field blur_level Blur amount.
 * @field luminosity Global luminosity multiplier.
 * @field color Per-channel color multipliers.
 * @field color_blind Color-channel permutation.
 * @field invert_color Whether colors are inverted.
 * @field gray_scale Gray-scale amount or mode.
 * @field noise_color Noise color mode.
 * @field noise_type Noise spatial mode.
 * @field noise_strenght Noise strength.
 * @see bunny_default_screen_tweak, bunny_screen_tweak_shader
 *
 * @doc-lang fr
 * @brief Configure le shader intégré de retouche écran.
 * @field blur_level Niveau de flou.
 * @field luminosity Multiplicateur global de luminosité.
 * @field color Multiplicateurs par canal de couleur.
 * @field color_blind Permutation des canaux de couleur.
 * @field invert_color Indique si les couleurs sont inversées.
 * @field gray_scale Quantité ou mode de niveaux de gris.
 * @field noise_color Mode de couleur du bruit.
 * @field noise_type Mode spatial du bruit.
 * @field noise_strenght Force du bruit.
 * @see bunny_default_screen_tweak, bunny_screen_tweak_shader
 */
typedef struct		s_bunny_screen_tweak
{
  float			blur_level;
  float			luminosity;
  double		color[3];
  t_bunny_color_blind_tweak color_blind;
  bool			invert_color;
  int 			gray_scale;
  t_bunny_noise_color	noise_color;
  t_bunny_noise_type	noise_type;
  double		noise_strenght;
}			t_bunny_screen_tweak;

void			bunny_default_screen_tweak(t_bunny_screen_tweak *bst);
t_bunny_shader		*bunny_screen_tweak_shader(const t_bunny_screen_tweak *bst);



/**
 * @doc
 * @doc-symbol t_bunny_normal_light
 * @doc-kind struct
 * @doc-module shader
 * @doc-order 80
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Describes one light used by the normal-map shader.
 * @field active Enables this light.
 * @field x Light X position.
 * @field y Light Y position.
 * @field z Light depth.
 * @field light_color Diffuse light color.
 * @field light_attenuation Diffuse attenuation factor.
 * @field ambient_color Ambient light color.
 * @field ambient_depth Ambient depth.
 * @field ambient_attenuation Ambient attenuation factor.
 * @field specular_color Specular light color.
 * @field specular_depth Specular depth.
 * @field specular_attenuation Specular attenuation factor.
 * @see t_bunny_normal_map
 *
 * @doc-lang fr
 * @brief Décrit une lumière utilisée par le shader de normal map.
 * @field active Active cette lumière.
 * @field x Position X de la lumière.
 * @field y Position Y de la lumière.
 * @field z Profondeur de la lumière.
 * @field light_color Couleur de lumière diffuse.
 * @field light_attenuation Facteur d'atténuation diffuse.
 * @field ambient_color Couleur de lumière ambiante.
 * @field ambient_depth Profondeur ambiante.
 * @field ambient_attenuation Facteur d'atténuation ambiante.
 * @field specular_color Couleur de lumière spéculaire.
 * @field specular_depth Profondeur spéculaire.
 * @field specular_attenuation Facteur d'atténuation spéculaire.
 * @see t_bunny_normal_map
 */
typedef struct		s_bunny_normal_light
{
  bool			active;
  float			x;
  float			y;
  float			z;
  t_bunny_color		light_color;
  float			light_attenuation;

  t_bunny_color		ambient_color;
  float			ambient_depth;
  float			ambient_attenuation;

  t_bunny_color		specular_color;
  float			specular_depth;
  float			specular_attenuation;
}			t_bunny_normal_light;



/**
 * @doc
 * @doc-symbol t_bunny_normal_map
 * @doc-kind struct
 * @doc-module shader
 * @doc-order 85
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Configures the built-in normal-map shader.
 * @field window_size Size of the rendered target.
 * @field normal_map Picture containing normals.
 * @field specular_map Picture containing specular information.
 * @field lights Array of up to 8 lights.
 * @see bunny_normal_map_shader
 *
 * @doc-lang fr
 * @brief Configure le shader intégré de normal map.
 * @field window_size Taille de la cible rendue.
 * @field normal_map Picture contenant les normales.
 * @field specular_map Picture contenant les informations spéculaires.
 * @field lights Tableau de 8 lumières au maximum.
 * @see bunny_normal_map_shader
 */
typedef struct		s_bunny_normal_map
{
  t_bunny_size		window_size;
  t_bunny_picture	*normal_map;
  t_bunny_picture	*specular_map;
  t_bunny_normal_light	lights[8];
  double		rotation;
}			t_bunny_normal_map;

t_bunny_shader		*bunny_normal_map_shader(const t_bunny_normal_map	*nm);



/**
 * @doc
 * @doc-symbol t_bunny_spreading
 * @doc-kind struct
 * @doc-module shader
 * @doc-order 95
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Configures the built-in color spreading shader and its working buffers.
 * @field color Source and destination colors.
 * @field speed Number of propagation iterations.
 * @field layout Optional picture constraining the propagation.
 * @field source_len Number of source positions.
 * @field sources Source positions.
 * @field random Enables randomization.
 * @field alpha_buffer Private working buffer. Initialize to NULL.
 * @field spread_buffer Private working buffers. Initialize to NULL.
 * @field current_buffer Private current buffer index. Initialize to 0.
 * @see bunny_spreading_shader, bunny_blit_spreading, bunny_delete_spreading
 *
 * @doc-lang fr
 * @brief Configure le shader intégré de propagation de couleur et ses buffers de travail.
 * @field color Couleurs source et destination.
 * @field speed Nombre d'itérations de propagation.
 * @field layout Picture optionnelle contraignant la propagation.
 * @field source_len Nombre de positions sources.
 * @field sources Positions sources.
 * @field random Active la randomisation.
 * @field alpha_buffer Buffer de travail privé. À initialiser à NULL.
 * @field spread_buffer Buffers de travail privés. À initialiser à NULL.
 * @field current_buffer Index privé du buffer courant. À initialiser à 0.
 * @see bunny_spreading_shader, bunny_blit_spreading, bunny_delete_spreading
 */
typedef struct		s_bunny_spreading
{
  // Configuration
  t_bunny_color		color[2];
  int			speed;
  t_bunny_picture	*layout;
  size_t		source_len;
  t_bunny_position	sources[128];
  bool			random;

  // Private. You must set those fields to 0 at the beginning.
  t_bunny_picture	*alpha_buffer;
  t_bunny_picture	*spread_buffer[2];
  int			current_buffer;
}			t_bunny_spreading;

t_bunny_shader		*bunny_spreading_shader(t_bunny_spreading	*spread);

void			bunny_blit_spreading(t_bunny_buffer		*buffer,
					     const t_bunny_position	*pos,
					     t_bunny_spreading		*spread);

void			bunny_fill_spreading(t_bunny_spreading		*spread);
void			bunny_flip_spreading(t_bunny_spreading		*spread);
void			bunny_draw_spreading_source(t_bunny_spreading	*spread);
void			bunny_clear_spreading(t_bunny_spreading		*spread);
void			bunny_delete_spreading(t_bunny_spreading	*spread);



/**
 * @doc
 * @doc-symbol t_bunny_blur
 * @doc-kind struct
 * @doc-module shader
 * @doc-order 140
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Configures the built-in blur shader.
 * @field offset_factor Horizontal and vertical blur offset factors.
 * @see bunny_blur_shader
 *
 * @doc-lang fr
 * @brief Configure le shader intégré de flou.
 * @field offset_factor Facteurs de décalage horizontal et vertical du flou.
 * @see bunny_blur_shader
 */
typedef struct		s_bunny_blur
{
  t_bunny_accurate_position offset_factor;
}			t_bunny_blur;

t_bunny_shader		*bunny_blur_shader(const t_bunny_blur		*blur);

#endif	/*		__LAPIN_SHADER_H__				*/

