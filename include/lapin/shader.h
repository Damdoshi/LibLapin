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

/*!
** The t_bunny_shader element is an effect that will be applied while blitting.
** The type is entirely private, so you cannot making anything else that
** use a pointer to it, there is no attribute.
*/
typedef void		t_bunny_shader;

/*!
** The bunny_shader_set_variable function can takes several different types
** of values as parameter thanks to its variading design. In order to specify
** which type you wish to send, specify it thanks to this enumartion.
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

typedef enum		e_bunny_color_blind_tweak
  {
    BCBT_RED_GREEN_BLUE,
    BCBT_RED_BLUE_GREEN,
    BCBT_GREEN_BLUE_RED,
    BCBT_BLUE_GREEN_RED,
    BCBT_BLUE_RED_GREEN
  }			t_bunny_color_blind_tweak;

typedef enum		e_bunny_noise_color
  {
    BNC_COLOR_NOISE,
    BNC_GRAY_NOISE,
    BNC_BLACK_AND_WHITE_NOISE
  }			t_bunny_noise_color;

typedef enum		e_bunny_noise_type
  {
    BNT_NO_NOISE,
    BNT_PIXEL_NOISE,
    BNT_LINE_NOISE,
    BNT_ROW_NOISE
  }			t_bunny_noise_type;

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

t_bunny_shader		*bunny_screen_tweak_shader(const t_bunny_screen_tweak *bst);

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

typedef struct		s_bunny_normal_map
{
  t_bunny_size	window_size;
  t_bunny_picture	*normal_map;
  t_bunny_picture	*specular_map;
  t_bunny_normal_light	lights[8];
}			t_bunny_normal_map;

t_bunny_shader		*bunny_normal_map_shader(const t_bunny_normal_map	*nm);

#endif	/*		__LAPIN_SHADER_H__				*/

