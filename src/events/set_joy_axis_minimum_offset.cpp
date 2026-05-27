// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

/**
 * @doc-symbol bunny_set_joy_axis_minimum_offset
 * @doc-module events
 * @doc-kind function
 * @doc-order 210
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Sets the minimum axis delta required to trigger a joystick axis callback.
 * @param axis The joystick axis concerned by the threshold.
 * @param off The minimum value difference required to trigger the callback.
 * @see t_bunny_joy_axis, bunny_set_joy_axis_response, bunny_get_joy_axis
 *
 * @doc-lang fr
 * @brief Règle l'écart minimal d'axe nécessaire pour déclencher un callback d'axe de joystick.
 * @param axis L'axe de joystick concerné par le seuil.
 * @param off La différence minimale de valeur nécessaire pour déclencher le callback.
 * @see t_bunny_joy_axis, bunny_set_joy_axis_response, bunny_get_joy_axis
 */
void		bunny_set_joy_axis_minimum_offset(t_bunny_axis		_axis,
						  float			off)
{
  int		axis = _axis;
  int		i;

  for (i = 0; i < LAST_BUNNY_AXIS && (axis & 0x1) == 0; ++i)
    axis >>= 1;
  if (i == LAST_BUNNY_AXIS)
    return ;
  gl_axis_offset[i] = off;
}

