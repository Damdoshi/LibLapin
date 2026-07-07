// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Bibliothèque Lapin

#include			"lapin_private.h"

/**
 * @doc-symbol bunny_update_joysticks
 * @doc-module events
 * @doc-kind function
 * @doc-order 186
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Refreshes the internal joystick information table.
 * @see t_bunny_joystick, bunny_get_joy_info
 *
 * @doc-lang fr
 * @brief Rafraîchit la table interne d'informations sur les joysticks.
 * @see t_bunny_joystick, bunny_get_joy_info
 */
void				bunny_update_joysticks(void)
{
  sf::Joystick::Identification	id;

  sf::Joystick::update();
  for (int i = 0; i < NBRCELL(gl_joystick); ++i)
    if ((gl_joystick[i].connected = sf::Joystick::isConnected(i)))
      {
	id = sf::Joystick::getIdentification(i);
	std::string nam = id.name;
	gl_joystick[i].name = bunny_strdup(nam.c_str());
	gl_joystick[i].vendor = id.vendorId;
	gl_joystick[i].product = id.productId;
	gl_joystick[i].nb_button = sf::Joystick::getButtonCount(i);
	gl_joystick[i].axis = 0;
	for (unsigned int j = 0; j < sf::Joystick::AxisCount; ++j)
	  gl_joystick[i].axis |=
	    (sf::Joystick::hasAxis(i, (sf::Joystick::Axis)j) ? 1 : 0) << j;
      }
    else
      {
	if (gl_joystick[i].name)
	  {
	    bunny_free((char*)gl_joystick[i].name);
	    gl_joystick[i].name = NULL;
	  }
      }
}
