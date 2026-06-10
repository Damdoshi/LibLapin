// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_all_fullscreen
 * @doc-kind function
 * @doc-module window
 * @doc-order 450
 * @doc-since 13
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Opens one borderless window on every autonomous monitor.
 * @description This function lists autonomous monitors, creates one NO_BORDER window for each monitor size, moves each window to the corresponding monitor position, and returns a NULL-terminated array. Release the array with bunny_end.
 * @param name The name used for every created window.
 * @return-case success A NULL-terminated array of opened t_bunny_window pointers.
 * @return-case failure NULL if the monitor list cannot be retrieved, if the window array cannot be allocated, or if a window cannot be opened.
 * @see bunny_single_fullscreen, bunny_list_autonomous_monitors, bunny_end
 *
 * @doc-lang fr
 * @brief Ouvre une fenêtre sans bordure sur chaque moniteur autonome.
 * @description Cette fonction liste les moniteurs autonomes, crée une fenêtre NO_BORDER pour chaque taille de moniteur, déplace chaque fenêtre vers la position du moniteur correspondant et renvoie un tableau terminé par NULL. Libérez le tableau avec bunny_end.
 * @param name Le nom utilisé pour chaque fenêtre créée.
 * @return-case success Un tableau terminé par NULL de pointeurs vers les t_bunny_window ouvertes.
 * @return-case failure NULL si la liste des moniteurs ne peut pas être récupérée, si le tableau de fenêtres ne peut pas être alloué ou si une fenêtre ne peut pas être ouverte.
 * @see bunny_single_fullscreen, bunny_list_autonomous_monitors, bunny_end
 */
t_bunny_window		**bunny_all_fullscreen(const char	*name)
{
  t_bunny_window	**wins;
  const t_bunny_area	*area;
  size_t		i;
  
  if ((area = bunny_list_autonomous_monitors()) == NULL)
    return (NULL);
  for (i = 0; area[i].w && area[i].h; ++i);
  if ((wins = (t_bunny_window**)bunny_malloc(sizeof(*wins) * (i + 1))) == NULL)
    return (NULL);
  wins[i] = NULL;
  for (i = 0; area[i].w && area[i].h; ++i)
    if ((wins[i] = bunny_start_style(area[i].w, area[i].h, NO_BORDER, name)) == NULL)
      {
	bunny_free(wins);
	return (NULL);
      }
    else
      bunny_move_window(wins[i], {area[i].x, area[i].y});
  return (wins);
}
