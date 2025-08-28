// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Lapin library

#include		"lapin_private.h"

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
