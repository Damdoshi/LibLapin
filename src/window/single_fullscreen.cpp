// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_single_fullscreen
 * @doc-kind function
 * @doc-module window
 * @doc-order 440
 * @doc-since 13
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Opens a fullscreen window on the first autonomous monitor.
 * @description This function uses bunny_list_autonomous_monitors to find a monitor and opens a fullscreen window matching its size. The returned window must be destroyed with bunny_stop.
 * @param name The name of the window.
 * @return-case success A pointer to an opened t_bunny_window.
 * @return-case failure NULL if the monitor list cannot be retrieved or if the window cannot be opened.
 * @see bunny_all_fullscreen, bunny_list_autonomous_monitors, bunny_stop
 *
 * @doc-lang fr
 * @brief Ouvre une fenêtre plein écran sur le premier moniteur autonome.
 * @description Cette fonction utilise bunny_list_autonomous_monitors pour trouver un moniteur et ouvre une fenêtre plein écran correspondant à sa taille. La fenêtre renvoyée doit être détruite avec bunny_stop.
 * @param name Le nom de la fenêtre.
 * @return-case success Un pointeur vers une t_bunny_window ouverte.
 * @return-case failure NULL si la liste des moniteurs ne peut pas être récupérée ou si la fenêtre ne peut pas être ouverte.
 * @see bunny_all_fullscreen, bunny_list_autonomous_monitors, bunny_stop
 */
t_bunny_window		*bunny_single_fullscreen(const char	*name)
{
  const t_bunny_area	*area;
  
  if ((area = bunny_list_autonomous_monitors()) == NULL)
    return (NULL);
  return (bunny_start(area->w, area->h, true, name));
}
