/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_ADVANCED_H__
# define			__LAPIN_ADVANCED_H__
# include			<stdarg.h>
# ifdef				__cplusplus
#  include			"lapin/cpp_guard.hpp"
# endif
# include			"lapin/enum.h"
# include			"lapin/color.h"
# include			"lapin/self_test.h"
# include			"lapin/misc.h"

/*
** *****
** ****
** ***  A:\> ADVANCED\COLOR
** **
** *|
** || TO_ALPHA take an unsigned 8-bit integer (unsigned char) and turn in into a value
** || that can be assigned to a color (with the binary or operator) as an alpha value.
** ||
** || GET_COLOR return the color with a alpha set to 0.
** ||
** || ALPHA takes an unsigned 8-bit integer (char) for alpha value (with 0 as invisible
** || and 255 as fully opaque) and a color. It return the color mixed with the alpha.
** |*
** *
*/
# define			TO_ALPHA(a)			(((a) & 0xFF) << (ALPHA_CMP * 8))
# define			GET_COLOR(c)			((c) & ~TO_ALPHA(255))
# define			ALPHA(a, c)			(TO_ALPHA(a) | GET_COLOR(c))

/*
** *****
** ****
** ***  A:\> ADVANCED\WINDOW
** **
** *|
** || Specify a way to open your window
** |*
** *
*/
typedef enum			e_bunny_window_style
  {
    NO_BORDER			= 0,
    TITLEBAR			= 1,
    RESIZE_BUTTON		= 2,
    CLOSE_BUTTON		= 4,
    FULLSCREEN			= 9,
    DEFAULT_WIN_STYLE		= TITLEBAR | RESIZE_BUTTON | CLOSE_BUTTON
  }				t_bunny_window_style;

t_bunny_window			*bunny_start_style(unsigned int			wid,
						   unsigned int			hei,
						   t_bunny_window_style		sty,
						   const char			*nam);

/*
** *****
** ****
** ***  A:\> ADVANCED\GRAPHIC
** **
** *|
** || bunny_new_picture create a GPU side picture.
** || Operations on GPU side picture are usually faster than operations on CPU side.
** || GPU side picture and windows can use the alpha channel.
** || 
** || bunny_draw ask to compute every operations done on a t_bunny_picture.
** || You should call it if you drew on it, right before blitting it.
** ||
** || bunny_set_*, bunny_fill and bunny_clear works on a window, on a picture and
** || can work on a pixelarray under certain conditions.
** ||
** || bunny_set_pixel draw a single pixel.
** || /!\ This operation is quite slow on a pixelarray
** ||
** || bunny_set_line draw a single line with a gradian between two points.
** || 
** || bunny_set_polygon draw a triangle with a gradian between three points.
** ||
** || bunny_fill fill the clipable set area with a color and apply the alpha
** || Because there is not clipable information on window, it fill all the space.
** ||
** || bunny_clear fill the clipable set area with a color. It ignore alpha.
** || Because there is not clipable information on window, it fill all the space.
** ||
** || In order to make these functions to work with t_bunny_pixelarray (CPU side picture)
** || You need to create functions and to set them to gl_bunny_my_* function pointers
** ||
** || /!\ GPU side drawing functions are forbidden, unless you have programmed
** ||     an equivalent CPU side and passed successfuly bunny_self_test for the
** ||     concerned function.
** |*
** *
*/
typedef t_bunny_clipable	t_bunny_picture;

t_bunny_picture			*bunny_new_picture(unsigned int			wid,
						   unsigned int			hei);
void				bunny_draw(const t_bunny_picture		*picture);

void				bunny_set_pixel(t_bunny_buffer			*buf,
						t_bunny_position		pos,
						unsigned int			col);
typedef void			(*t_bunny_my_set_pixel)(t_bunny_pixelarray	*pix,
							t_bunny_position	pos,
							unsigned int		color);
extern t_bunny_my_set_pixel	gl_bunny_my_set_pixel;

void				bunny_set_circle(t_bunny_buffer			*buf,
						 t_bunny_position		pos,
						 t_bunny_position		rad,
						 unsigned int			color);
typedef void			(*t_bunny_my_set_circle)(t_bunny_pixelarray	*pix,
							 t_bunny_position	pos,
							 t_bunny_position	radius,
							 unsigned int		color);
extern t_bunny_my_set_circle	gl_bunny_my_set_circle;

void				bunny_set_line(t_bunny_buffer			*buf,
					       const t_bunny_position		*pos,
					       const unsigned int		*col);
typedef void			(*t_bunny_my_set_line)(t_bunny_pixelarray	*pix,
						       const t_bunny_position	*pos,
						       const unsigned int	*col);
extern t_bunny_my_set_line	gl_bunny_my_set_line;

void				bunny_set_polygon(t_bunny_buffer		*buf,
						  const t_bunny_position	*pos,
						  const unsigned int		*col);
typedef void			(*t_bunny_my_set_polygon)(t_bunny_pixelarray	*pix,
							  const t_bunny_position*pos,
							  const unsigned int	*color);
extern t_bunny_my_set_polygon	gl_bunny_my_set_polygon;

void				bunny_fill(t_bunny_buffer			*buffer,
					   unsigned int				color);
typedef void			(*t_bunny_my_fill)(t_bunny_pixelarray		*pix,
						   unsigned int			color);
extern t_bunny_my_fill		gl_bunny_my_fill;

void				bunny_clear(t_bunny_buffer			*buffer,
					    unsigned int			color);
typedef void			(*t_bunny_my_clear)(t_bunny_pixelarray		*pix,
						    unsigned int		color);
extern t_bunny_my_clear		gl_bunny_my_clear;

/*
** *****
** ****
** ***  A:\> ADVANCED\GEOMETRY
** **
** *|
** || bunny_geometry can draw on a buffer:
** ||  - multiple points
** ||  - multiple lines
** ||  - a single broken line
** ||  - multiple triangles
** ||  - a strip of triangle sharing a side
** ||  - multiple triangle sharing a vertex
** ||  - quads
** || depending on the t_bunny_geometry parameter.
** || The array parameter is a structure containing a bunch of coordinates for vertex,
** || texture, color and their number. This is how it works:
** || length in the t_bunny_vertex_array is the length of the vertex array.
** ||
** || If the destination of the geometry is a picture or a window, the clipable
** || MUST be a picture. If the destination is a pixelarrat, you will have to
** || implement it by yourself and the clipable will HAVE TO be a pixelarray.
** ||
** || picture is optionnal: passing NULL will make the function use color.
** ||
** || To create a t_bunny_vertex_array, you can use malloc or alloca with
** || sizeof(t_bunny_vertex_array) + n * sizeof(t_bunny_vertex) where n is
** || the number of vertex you want. Do not forget to set the length
** || attribute.
** || You can browse your 0 length vertex the same way a normal array: it is
** || stretched to n thanks to the tricks before.
** |*
** *
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
typedef struct			s_bunny_vertex
{
  t_bunny_position		pos;
  t_bunny_position		tex;
  unsigned int			color;
}				t_bunny_vertex;
typedef struct			s_bunny_vertex_array
{
  size_t			length;
# ifndef			__ANSI__
  t_bunny_vertex  		vertex[0];
# else
  t_bunny_vertex		vertex[1];
# endif
}				t_bunny_vertex_array;

void				bunny_set_geometry(t_bunny_buffer		*buffer,
						   t_bunny_geometry		geometry,
						   t_bunny_vertex_array		*array,
						   t_bunny_clipable		*clipable);
typedef void			(*t_bunny_my_geometry)(t_bunny_pixelarray	*pix,
						       t_bunny_geometry		geometry,
						       t_bunny_vertex_array	*array,
						       t_bunny_pixelarray	*picture);
extern t_bunny_my_geometry	gl_bunny_my_geometry;

/*
** *****
** ****
** ***  A:\> ADVANCED\GRAPHIC_LOADING
** **
** *|
** || bunny_load_pixelarray and bunny_load_picture can load picture file.
** || Supported formats include bmp(24 bits), png, jpg, gif and psd
** || Progressive jpg is unsupported
** ||
** || bunny_load_* functions are forbidden unless you create an equivalent
** || picture loader and set its function pointer to gl_bunny_my_load_pixelarray
** || and passed successfuly bunny_self_test with this function.
** |*
** *
*/
t_bunny_pixelarray		*bunny_load_pixelarray(const char		*file);
typedef t_bunny_pixelarray	*(*t_bunny_my_load_pixelarray)(const char	*file);
extern t_bunny_my_load_pixelarray gl_bunny_my_load_pixelarray;

t_bunny_picture			*bunny_load_picture(const char			*file);

bool				bunny_save_pixelarray(const t_bunny_pixelarray	*buf,
						      const char		*file);

/*
** *****
** ****
** ***  A:\> ADVANCED\INTEGRATED_FONT
** **
** *|
** || LibLapin integrates a simple vector font.
** || Available characters are, in order, 'a' to 'z', '0' to '9' and '!'
** || Use it mainly for title. This font is not for plain text.
** ||
** || Because of its vector nature, the vector font can be transformed
** || (translated, scaled, rotated), but it is up to you to program it.
** ||
** || If you want a simple plain raster font, use font.png, which is
** || included with the LibLapin.
** |*
** *
*/
typedef struct			s_bunny_line_coord
{
  int				x0;
  int				y0;
  int				x1;
  int				y1;
}				t_bunny_line_coord;
typedef struct			s_bunny_letter
{
  int				nb_edge;
  t_bunny_line_coord		edge[5];
}				t_bunny_letter;

extern const t_bunny_letter	gl_vector[LAST_BUNNY_FONT];

/*
** *****
** ****
** ***  A:\> ADVANCED\SHADERS
** **
** *|
** || Shader are GPU features. You can use them thanks to this interface.
** || /!\ You will have to learn GLSL to make it works.
** ||
** || Always test if shaders are available! Some graphic cards does not have them.
** ||
** || bunny_new_shader create a new shader structure
** ||
** || bunny_load_shader load two GLSL file and set the shader structure with them.
** || The first file is the vertex file, the second the fragment file.
** ||
** || bunny_shader_set_variable allow you to give a variable from your program
** || to your GLSL script. You have to specify the shader, the variable name, the
** || type of the variable you want to give, and the variable itself.
** ||
** || bunny_blit_shader use a shader while pushing a picture on screen
** ||
** || bunny_delete_shader delete a shader
** |*
** *
*/
typedef void			t_bunny_shader;
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
typedef struct			s_bunny_transform
{
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	translation;
  t_bunny_accurate_position	scale;
  double			rotation;
}				t_bunny_transform;

bool				bunny_is_shader_available(void);

t_bunny_shader			*bunny_new_shader(void);
bool				bunny_load_shader(t_bunny_shader		*sha,
						  const char			*vertex_file,
						  const char			*frag_file);
void				bunny_shader_set_variable(t_bunny_shader	*sha,
							  const char		*varname,
							  t_bunny_variable_type	type,
							  ...);

void				bunny_blit_shader(t_bunny_buffer		*buffer,
						  const t_bunny_picture		*picture,
						  const t_bunny_position	*position,
						  const t_bunny_shader		*shader);

void				bunny_delete_shader(t_bunny_shader		*shader);
void				bunny_enable_full_blit(bool			alpha);

/*
** *****
** ****
** ***  A:\> ADVANCED\WINDOW_EVENTS
** **
** *|
** || bunny_set_text_response/t_bunny_type are usefull to manage keyboard not as
** || a collection of buttons but as a text input. It takes care of ALT/SHIFT/CTRL
** || key in the production of symbols. You just have to check.
** || It even works with special characters!
** ||
** || bunny_set_wheel_response manage the relative move of the mouse wheel.
** ||
** || bunny_set_joy_connect_response manage the joystick connection or disconnection.
** || You still have to pay attention when you plug some joystick before launching
** || Your program! Use bunny_get_joy_info to do so.
** ||
** || bunny_set_joy_axis_response and bunny_set_joy_button manage axis and button
** || event on a joystick. They also have bunny_get_* functions in case you need states.
** ||
** || bunny_get_joy_axis and bunny_get_joy_button are only active if you
** || have set response functions to their events.
** ||
** || These functions work with bunny_loop and bunny_loop_mw.
** ||
** || bunny_loop_mw takes several window as parameter. It makes you need bunny_get_window
** || in order to know on which one the action happenned (relatively useless for
** || joystick or keyboard, certainly mandatory for mouse).
** ||
** |*
** *
*/
typedef struct			s_bunny_joystick
{
  bool				connected;
  const char			*name;
  unsigned int			vendor;
  unsigned int			product;
  unsigned int			nb_button;
  unsigned char			axis;
}				t_bunny_joystick;

typedef t_bunny_response	(*t_bunny_type)(uint32_t			unicode,
						void				*data);
void				bunny_set_text_response(t_bunny_type		type);

typedef t_bunny_response	(*t_bunny_wheel)(int				wheelid,
						 int				delta,
						 void				*data);
void				bunny_set_wheel_response(t_bunny_wheel		wheel);

typedef t_bunny_response	(*t_bunny_joy_connect)(t_bunny_event_state	state,
						       int			joyid,
						       const t_bunny_joystick	*joyinfo,
						       void			*data);
void				bunny_set_joy_connect_response(t_bunny_joy_connect joy);
const t_bunny_joystick		*bunny_get_joy_info(int				id);

typedef t_bunny_response	(*t_bunny_joy_axis)(int				joyid,
						    t_bunny_axis		axis,
						    float			value,
						    void			*data);
void				bunny_set_joy_axis_response(t_bunny_joy_axis	axis);
const float			(*bunny_get_joy_axis(void))[LAST_BUNNY_AXIS];

typedef t_bunny_response	(*t_bunny_joy_button)(t_bunny_event_state	state,
						      int			joyid,
						      int			button,
						      void			*data);
void				bunny_set_joy_button_response(t_bunny_joy_button button);
const bool			(*bunny_get_joy_button(void))[LAST_BUNNY_BUTTON];

typedef t_bunny_response	(*t_bunny_get_focus)(const t_bunny_window	*win,
						     void			*data);
void				bunny_set_get_focus_response(t_bunny_get_focus	getf);

typedef t_bunny_response	(*t_bunny_lost_focus)(const t_bunny_window	*win,
						      void			*data);
void				bunny_set_lost_focus_response(t_bunny_lost_focus lost);

typedef t_bunny_response	(*t_bunny_resize)(const t_bunny_window		*win,
						  const t_bunny_position	*siz,
						  void				*data);
void				bunny_set_resize_response(t_bunny_resize	resize);

const t_bunny_window	       *bunny_get_window(void);

typedef t_bunny_response	(*t_bunny_display)(const void			*data);
void				bunny_set_display_function(t_bunny_display	display);

typedef t_bunny_response	(*t_bunny_close)(const t_bunny_window		*win,
						 void				*data);
void				bunny_set_close_response(t_bunny_close		close);

t_bunny_response		bunny_loop_mw(t_bunny_window			**win,
					      size_t				nwin,
					      uint8_t				freq,
					      void				*data);

/*
** *****
** ****
** ***  A:\> ADVANCED\CONTEXT_SWITCHING
** **
** *|
** || In a big program, it is common to have several "screen"/"view": we call it
** || context in liblapin.
** ||
** || The bunny_set_context allow you to change all response to events in a
** || single call. You have of course to create structure to do so. This is a
** || context switchin.
** ||
** || If your program have for example, 5 context, you can create an array of 5
** || t_bunny_context or t_bunny_anonymous_context in order to make your
** || context switching super easy: you just have to call bunny_set_context with
** || the good part of your array. (It is even easier you have a variable that
** || represent the context you are in, or the context where you wanna go)
** ||
** || The t_bunny_context make mandatory to respect the response prototype.
** || The t_bunny_anonymous_context does not. Of course, you still have to respect
** || the memory format of the prototype, but you can now do this:
** || For example, for the t_bunny_key function, instead of making this kind of thing:
** ||
** || t_bunny_response key(t_bunny_event_state state, t_bunny_keysym sym, void *data)
** || {
** ||   your_type *ptr = data;
** ||
** ||   stuff
** || }
** ||
** || You can make directly:
** || t_bunny_response key(t_bunny_event_state state, t_bunny_keysym, your_type *data)
** || {
** ||   stuff
** || }
** ||
** || You don't have to respect the void* type anymore in your prototype.
** || So you do not need to cast when creating your context.
** || Of course, if you use t_bunny_anonymous_context, you will have to cast
** || when using bunny_*_context functions, but it is only a single cast vs
** || a bunch of them.
** ||
** |*
** *
*/
typedef struct			s_bunny_context
{
  t_bunny_key			key;
  t_bunny_type			type;
  t_bunny_click			click;
  t_bunny_move			move;
  t_bunny_wheel			wheel;
  t_bunny_joy_connect		connect;
  t_bunny_joy_button		button;
  t_bunny_joy_axis		axis;
  t_bunny_get_focus		get_focus;
  t_bunny_lost_focus		lost_focus;
  t_bunny_resize		resize;
  t_bunny_loop			loop;
  t_bunny_display		display;
  t_bunny_close			close;
}				t_bunny_context;
typedef struct			s_bunny_anonymous_context
{
  void				*key;
  void				*type;
  void				*click;
  void				*move;
  void				*wheel;
  void				*connect;
  void				*button;
  void				*axis;
  void				*get_focus;
  void				*lost_focus;
  void				*resize;
  void				*loop;
  void				*display;
  void				*close;
}				t_bunny_anonymous_context;

void				bunny_set_context(const t_bunny_context		*context);
void				bunny_get_context(t_bunny_context		*context);

/*
** *****
** ****
** ***  A:\> ADVANCED\WINDOW_UTILS
** **
** *|
** || Specify a way to open your window
** |*
** *
*/
void				bunny_set_key_repeat(const t_bunny_window	*win,
						     bool			active);
void				bunny_set_mouse_visibility(const t_bunny_window	*win,
							   bool			visible);
void				bunny_set_mouse_position_window(const t_bunny_window *win,
								int		x,
								int		y);
void				bunny_set_mouse_position(int			x,
							 int			y);
void				bunny_request_focus(const t_bunny_window	*win);

void				bunny_move_window(t_bunny_window		*win,
						  t_bunny_position		pos);
void				bunny_resize_window(t_bunny_window		*win,
						    t_bunny_position		pos);

t_bunny_position		bunny_get_screen_size(void);

/*
** *****
** ****
** ***  A:\> ADVANCED\CONFIGURATION
** **
** *|
** ||
** || bunny_ini_first return a pointer to the first scope (the default scope)
** ||
** || bunny_ini_scope_name return the name of the scope
** ||
** || bunny_ini_next return the scope right after the given one. It return LAST_SCOPE.
** || if the given scope was the last one.
** ||
** || bunny_ini_scope_get_field works the same way as bunny_ini_get_field but it
** || takes a current scope instead of taking a string to specify the scope.
** ||
** || bunny_ini_scope_set_field works the same way as bunny_ini_set_field but it
** || takes a current scope, the same way as bunny_ini_scope_get_field.
** ||
** || If you want to loop on every scope in a INI file, you can do this (this is
** || not currently norm compliant!)
** || for (scope = bunny_ini_first(ini); scope != LAST_SCOPE; scope = bunny_ini_next(ini, scop
e)
** || {}
** ||
** || bunny_ini_get_error return a string containing a human readable error description.
** || It return NULL if there is no error to read.
** |*
** *
*/
typedef void			t_bunny_ini_scope;
# define			LAST_SCOPE					NULL


t_bunny_ini_scope		*bunny_ini_first_scope(t_bunny_ini		*ini);
const char			*bunny_ini_scope_name(const t_bunny_ini		*ini,
						      const t_bunny_ini_scope	*scope);
t_bunny_ini_scope		*bunny_ini_next_scope(t_bunny_ini		*ini,
						      t_bunny_ini_scope		*scope);
const char			*bunny_ini_scope_get_field(const t_bunny_ini_scope *scope,
							   const char		*field,
							   unsigned int		index);
void				bunny_ini_scope_set_field(t_bunny_ini_scope	*scope,
							  const char		*field,
							  unsigned int		index,
							  const char		*value);

t_bunny_ini_scope		*bunny_ini_get_scope(t_bunny_ini		*ini,
						     const char			*scope);

typedef void			t_bunny_ini_field;
# define			LAST_FIELD					NULL
t_bunny_ini_field		*bunny_ini_first_field(t_bunny_ini_scope	*scope);
const char			*bunny_ini_field_name(const t_bunny_ini_scope	*scope,
						      const t_bunny_ini_field	*field);
t_bunny_ini_field		*bunny_ini_next_field(t_bunny_ini_scope		*scope,
						      t_bunny_ini_field		*field);
const char			*bunny_ini_field_get_value(const t_bunny_ini_field *field,
							   unsigned int		index);
void				bunny_ini_field_set_vaue(t_bunny_ini_field	*field,
							 unsigned int		index,
							 const char		*value);

# include			"lapin/compat.h"
# ifdef				__cplusplus
#  include			"lapin/cpp_guard_end.hpp"
# endif
#endif	/*			__LAPIN_ADVANCED_H__				*/
