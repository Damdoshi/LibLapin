/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2026
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_CONTEXT_CINEMATIC_H__
# define			__LAPIN_CONTEXT_CINEMATIC_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*
** Standard context for bunny_cinematic.
**
** Set head.screens to the destination buffers. If no subcontext display
** callback is provided, the context assumes those buffers are windows and
** calls bunny_display on them, like the splash context does. If you render to
** an intermediate picture, provide head.subcontext.display and perform your
** final blit/display there.
*/
typedef struct			s_bunny_cinematic_screen
{
  t_bunny_context_runtime_info	head;

  const char			*cinematic_file;
  const char			*language;
  unsigned int			width;
  unsigned int			height;

  bool				clear_screen;
  bool				centered;
  t_bunny_cinematic_event	validation_event;

  /*
  ** If cinematic is NULL, the context loads cinematic_file when entering.
  ** If cinematic is already set, the context uses this loaded cinematic
  ** directly. This allows callers to inspect or tune the clipable before the
  ** context starts.
  **
  ** When delete_cinematic_on_leave is true, the context deletes cinematic when
  ** leaving. Cinematics loaded internally are always deleted automatically.
  */
  t_bunny_cinematic		*cinematic;
  bool				delete_cinematic_on_leave;
  double			last_action;
  t_bunny_cinematic_event	pending_event;
}				t_bunny_cinematic_screen;

extern const t_bunny_context	gl_bunny_cinematic_context;

#endif /* __LAPIN_CONTEXT_CINEMATIC_H__ */
