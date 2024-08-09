// d0p1
// Jason Brillante "Damdoshi"
//
// Lapin library

#include		"lapin_private.h"

void			bunny_reset_gl_states(t_bunny_buffer		*pic)
{
  if (*(size_t*)pic == WINDOW)
    {
      struct bunny_window	*win = (struct bunny_window*)pic;

      win->window->resetGLStates();
    }
  else
    {
      struct bunny_picture	*bpc = (struct bunny_picture*)pic;

      if (bpc->texture)
	bpc->texture->resetGLStates();
    }
  scream_log_if("%p", "graphics", pic);
}

void			bunny_push_gl_states(t_bunny_buffer		*pic)
{
  if (*(size_t*)pic == WINDOW)
    {
      struct bunny_window	*win = (struct bunny_window*)pic;

      win->window->pushGLStates();
    }
  else
    {
      struct bunny_picture	*bpc = (struct bunny_picture*)pic;

      if (bpc->texture)
	bpc->texture->resetGLStates();
    }
  scream_log_if("%p", "graphics", pic);
}

void			bunny_pop_gl_states(t_bunny_buffer		*pic)
{
  if (*(size_t*)pic == WINDOW)
    {
      struct bunny_window	*win = (struct bunny_window*)pic;

      win->window->popGLStates();
    }
  else
    {
      struct bunny_picture	*bpc = (struct bunny_picture*)pic;

      if (bpc->texture)
	bpc->texture->resetGLStates();
    }
  scream_log_if("%p", "graphics", pic);
}
