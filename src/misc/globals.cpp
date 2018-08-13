// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin Library

#include			<limits.h>
#include			"lapin_private.h"

std::queue<void*>		gl_completed_tasks;
ResManager			RessourceManager;
size_t				gl_bunny_frequency;

t_bunny_my_set_pixel		gl_bunny_my_set_pixel = NULL;
t_bunny_my_set_line		gl_bunny_my_set_line = NULL;
t_bunny_my_set_disk		gl_bunny_my_set_disk = NULL;
t_bunny_my_set_polygon		gl_bunny_my_set_polygon = NULL;
t_bunny_my_fill			gl_bunny_my_fill = NULL;
t_bunny_my_clear		gl_bunny_my_clear = NULL;
t_bunny_my_blit			gl_bunny_my_blit = NULL;
t_bunny_my_geometry		gl_bunny_my_geometry = NULL;

t_bunny_threadpool		*gl_bunny_loop_threadpool = NULL;

t_bunny_context			gl_callback;
bool				gl_keyboard[BKS_LAST_KEY];
t_bunny_position		gl_mouse;
bool				gl_button[sf::Mouse::ButtonCount];
bool				gl_joy_button[sf::Joystick::Count][sf::Joystick::ButtonCount];
float				gl_joy_axis[sf::Joystick::Count][sf::Joystick::AxisCount];
float				gl_axis_offset[LAST_BUNNY_AXIS];
t_bunny_joystick		gl_joystick[sf::Joystick::Count];
t_bunny_window			*gl_window;
bool				gl_full_blit;
void				*gl_loop_data;

const char			*DEFAULT_SCOPE = "";
const char			*default_scope = "";
const char			*erase_scope = NULL;
const unsigned int		erase_field = UINT_MAX;
const char			*erase_index = NULL;
const void			*last_scope = NULL;

t_steam_callback		gl_steam_callback = NULL;

char				bunny_big_buffer[16 * 1024 * 1024];
std::map<std::string, struct bunny_monitored_value> gl_monitor;
