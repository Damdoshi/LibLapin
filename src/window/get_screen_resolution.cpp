// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_get_screen_resolution
 * @doc-kind function
 * @doc-module window
 * @doc-order 180
 * @doc-since 9
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Returns the current desktop resolution.
 * @description Starting a fullscreen window with this size should not force the system to resize the desktop brutally.
 * @return-case success A pointer to a t_bunny_size structure containing the current screen width and height.
 * @log Logs are written with the "system" label.
 * @see bunny_get_fullscreen_modes, bunny_start, bunny_start_style
 *
 * @doc-lang fr
 * @brief Renvoie la résolution courante du bureau.
 * @description Ouvrir une fenêtre plein écran avec cette taille ne devrait pas forcer le système à redimensionner brutalement le bureau.
 * @return-case success Un pointeur vers une structure t_bunny_size contenant la largeur et la hauteur courantes de l'écran.
 * @log Les logs sont écrits avec l'étiquette "system".
 * @see bunny_get_fullscreen_modes, bunny_start, bunny_start_style
 */
const t_bunny_position		*bunny_get_screen_resolution(void)
{
  static t_bunny_position	screen;
  const sf::VideoMode		&mode = sf::VideoMode::getDesktopMode();

  screen.x = mode.size.x;
  screen.y = mode.size.y;
  scream_log_if("-> %p(%d, %d)", "system", &screen, screen.x, screen.y);
  return (&screen);
}

