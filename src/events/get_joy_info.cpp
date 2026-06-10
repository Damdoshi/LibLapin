// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_get_joy_info
 * @doc-module events
 * @doc-kind function
 * @doc-order 185
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns information about a joystick slot.
 * @param id The joystick slot identifier.
 * @return-success A pointer to the requested t_bunny_joystick information structure.
 * @return-failure NULL if id is outside the supported joystick range.
 * @see t_bunny_joystick, bunny_update_joysticks
 *
 * @doc-lang fr
 * @brief Renvoie les informations d'un emplacement de joystick.
 * @param id L'identifiant de l'emplacement de joystick.
 * @return-success Un pointeur vers la structure d'informations t_bunny_joystick demandée.
 * @return-failure NULL si id est hors de l'intervalle des joysticks pris en charge.
 * @see t_bunny_joystick, bunny_update_joysticks
 */
const t_bunny_joystick	*bunny_get_joy_info(int		id)
{
  if (id >= NBRCELL(gl_joystick) || id < 0)
    return (NULL);
  return (&gl_joystick[id]);
}

