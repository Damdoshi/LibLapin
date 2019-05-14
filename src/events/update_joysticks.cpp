// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Bibliothèque Lapin

#include			"lapin_private.h"

void				bunny_update_joysticks(void)
{
  sf::Joystick::Identification	id;

  sf::Joystick::update();
  for (int i = 0; i < LAST_BUNNY_JOYSTICK; ++i)
    if ((gl_joystick[i].connected = sf::Joystick::isConnected(i)))
      {
	id = sf::Joystick::getIdentification(i);
	gl_joystick[i].name = bunny_strdup(id.name.toAnsiString().c_str());
	gl_joystick[i].vendor = id.vendorId;
	gl_joystick[i].product = id.productId;
	gl_joystick[i].nb_button = sf::Joystick::getButtonCount(i);
	gl_joystick[i].axis = 0;
	for (int j = 0; j < sf::Joystick::AxisCount; ++j)
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
