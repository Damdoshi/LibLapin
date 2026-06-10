// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_get_fullscreen_modes
 * @doc-kind function
 * @doc-module window
 * @doc-order 190
 * @doc-since 11
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Returns the fullscreen modes accepted by the system.
 * @description The returned array contains every fullscreen mode reported by the system and is terminated by an item filled with zero.
 * @return-case success A pointer to an array of t_bunny_size structures. The last item is filled with zero.
 * @log Logs are written with the "system" label.
 * @see bunny_start, bunny_start_style, bunny_get_screen_resolution
 *
 * @doc-lang fr
 * @brief Renvoie les modes plein écran acceptés par le système.
 * @description Le tableau renvoyé contient tous les modes plein écran rapportés par le système et se termine par un élément rempli avec zéro.
 * @return-case success Un pointeur vers un tableau de structures t_bunny_size. Le dernier élément est rempli avec zéro.
 * @log Les logs sont écrits avec l'étiquette "system".
 * @see bunny_start, bunny_start_style, bunny_get_screen_resolution
 */
const t_bunny_size			*bunny_get_fullscreen_modes(void)
{
  static t_bunny_size			array[1024 / sizeof(t_bunny_position)] = {0, 0};
  const std::vector<sf::VideoMode>	&modes = sf::VideoMode::getFullscreenModes();
  std::vector
    <sf::VideoMode>::const_iterator	it;
  size_t				i;

  scream_log_if("-> %p", "system", &array[0]);
  if (array[0].x != 0)
    return (&array[0]);

  for (i = 0, it = modes.begin(); i < 1024 / sizeof(t_bunny_position) && it != modes.end(); ++i, ++it)
    {
      array[i].x = it->size.x;
      array[i].y = it->size.y;
    }
  if (it != modes.end())
    --i;
  array[i].x = array[i].y = 0;
  return (&array[0]);
}

