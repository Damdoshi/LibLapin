// d0p1
// Jason Brillante "Damdoshi"
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_reset_gl_states
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 480
 * @doc-since 11
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Resets the OpenGL states of a window or picture target.
 * @description Use this when mixing custom OpenGL calls and LibLapin/SFML drawing on the same target.
 * @param buf The target buffer.
 * @log Logs are written with the "graphics" label.
 * @see bunny_push_gl_states, bunny_pop_gl_states, bunny_GL_reset_states
 *
 * @doc-lang fr
 * @brief Réinitialise les états OpenGL d’une cible fenêtre ou picture.
 * @description Utilisez cette fonction lorsque vous mélangez vos propres appels OpenGL et le dessin LibLapin/SFML sur la même cible.
 * @param buf Le buffer cible.
 * @log Les logs sont écrits avec le label "graphics".
 * @see bunny_push_gl_states, bunny_pop_gl_states, bunny_GL_reset_states
 */
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

/**
 * @doc-symbol bunny_push_gl_states
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 490
 * @doc-since 11
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Saves the OpenGL states of a window or picture target.
 * @description Use this when mixing custom OpenGL calls and LibLapin/SFML drawing on the same target.
 * @param buf The target buffer.
 * @log Logs are written with the "graphics" label.
 * @see bunny_reset_gl_states, bunny_pop_gl_states, bunny_GL_push_states
 *
 * @doc-lang fr
 * @brief Sauvegarde les états OpenGL d’une cible fenêtre ou picture.
 * @description Utilisez cette fonction lorsque vous mélangez vos propres appels OpenGL et le dessin LibLapin/SFML sur la même cible.
 * @param buf Le buffer cible.
 * @log Les logs sont écrits avec le label "graphics".
 * @see bunny_reset_gl_states, bunny_pop_gl_states, bunny_GL_push_states
 */
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

/**
 * @doc-symbol bunny_pop_gl_states
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 500
 * @doc-since 11
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Restores previously saved OpenGL states of a window or picture target.
 * @description Use this after bunny_push_gl_states when mixing custom OpenGL calls and LibLapin/SFML drawing.
 * @param buf The target buffer.
 * @log Logs are written with the "graphics" label.
 * @see bunny_reset_gl_states, bunny_push_gl_states, bunny_GL_pop_states
 *
 * @doc-lang fr
 * @brief Restaure les états OpenGL précédemment sauvegardés d’une cible fenêtre ou picture.
 * @description Utilisez cette fonction après bunny_push_gl_states lorsque vous mélangez vos propres appels OpenGL et le dessin LibLapin/SFML.
 * @param buf Le buffer cible.
 * @log Les logs sont écrits avec le label "graphics".
 * @see bunny_reset_gl_states, bunny_push_gl_states, bunny_GL_pop_states
 */
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
