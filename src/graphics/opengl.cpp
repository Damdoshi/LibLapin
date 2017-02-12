// d0p1
//
// Lapin library

#include		"lapin_private.h"

void			bunny_GL_reset_states(const t_bunny_window	*pic)
{
  struct bunny_window	*win = (struct bunny_window *)pic;

  win->window->resetGLStates();
}

void			bunny_GL_push_states(const t_bunny_window	*pic)
{
  struct bunny_window	*win = (struct bunny_window *)pic;

  win->window->pushGLStates();
}

void			bunny_GL_pop_states(const t_bunny_window	*pic)
{
  struct bunny_window	*win = (struct bunny_window *)pic;

  win->window->popGLStates();
}
