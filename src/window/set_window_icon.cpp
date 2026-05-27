// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_set_window_icon
 * @doc-kind function
 * @doc-module window
 * @doc-order 360
 * @doc-since 13
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Changes the icon associated with a window.
 * @description The pixels from the sent t_bunny_pixelarray are sent to the underlying system window as the window icon.
 * @param window The window whose icon must be changed.
 * @param icon The pixelarray to use as window icon.
 *
 * @doc-lang fr
 * @brief Change l'icône associée à une fenêtre.
 * @description Les pixels du t_bunny_pixelarray envoyé sont transmis à la fenêtre système sous-jacente comme icône de fenêtre.
 * @param window La fenêtre dont l'icône doit être changée.
 * @param icon Le pixelarray à utiliser comme icône de fenêtre.
 */
void			bunny_set_window_icon(t_bunny_window		*_win,
					      t_bunny_pixelarray	*px)
{
  struct bunny_window	*win = (struct bunny_window*)_win;

  win->window->setIcon
    ({px->clipable.buffer.width,
       px->clipable.buffer.height},
      (uint8_t *)px->pixels);
}

