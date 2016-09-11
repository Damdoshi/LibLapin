/*
** MyName
** MyCompany 1970-2017
**
** BunnyProject
*/

#ifndef				__BUNNY_PROJECT_H__
# define			__BUNNY_PROJECT_H__
# include			<lapin.h>

typedef enum			e_bunny_project_context
  {
    DEMO			= 0,
    CONTEXT_COUNT
  }				t_bunny_project_context;

extern const
t_bunny_anonymous_context	bunny_project_context[CONTEXT_COUNT];
extern const double		bunny_move_speed;
extern const double		bunny_rot_speed;

typedef struct			s_bunny_project
{
  t_bunny_window		*window;
  t_bunny_project_context	context;
  t_bunny_picture		*bunny;
  t_bunny_accurate_position	bunny_position;
}				t_bunny_project;

t_bunny_response		bunny_project_key_handler(t_bunny_event_state		state,
							  t_bunny_keysym		sym,
							  t_bunny_project		*prj);
t_bunny_response		bunny_project_loop(t_bunny_project			*prj);
t_bunny_response		bunny_project_display(const t_bunny_project		*prj);

#endif	/*			__BUNNY_PROJECT_H__	*/
