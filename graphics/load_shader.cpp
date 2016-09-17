// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_load_shader(t_bunny_shader		*_shader,
					  const char			*vertex,
					  const char			*fragment)
{
  sf::Shader		*shader = (sf::Shader*)_shader;

  if (fragment == NULL)
    return (false);
  if (vertex == NULL)
    return (shader->loadFromFile(fragment, sf::Shader::Fragment));
  return (shader->loadFromFile(vertex, fragment));
}

