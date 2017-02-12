// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_delete_shader(t_bunny_shader	*_shader)
{
  sf::Shader		*shader = (sf::Shader*)_shader;

  delete shader;
}

