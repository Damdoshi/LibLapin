// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_shader		*bunny_new_shader(void)
{
  return ((void*)new sf::Shader);
}

