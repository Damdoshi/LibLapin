// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p shader, %s vertex_file, %s fragment_file -> %s"

bool			bunny_read_shader(t_bunny_shader		*_shader,
					  const char			*vertex,
					  const char			*fragment)
{
  sf::Shader		*shader = (sf::Shader*)_shader;

  if (fragment == NULL)
    scream_error_if(return (false), EINVAL, PATTERN, "ressource,graphics", shader, vertex, fragment, "false");
  if (vertex == NULL)
    {
      if (shader->loadFromMemory(fragment, sf::Shader::Fragment) == false)
	scream_error_if(return (false), BE_SYNTAX_ERROR, PATTERN, "ressource,graphics,syntax", shader, vertex, fragment, "false");
      scream_log_if(PATTERN, "ressource,graphics", shader, vertex, fragment, "true");
      return (true);
    }

  if (shader->loadFromMemory(vertex, fragment) == false)
    scream_error_if(return (false), BE_SYNTAX_ERROR, PATTERN, "ressource,graphics,syntax", shader, vertex, fragment, "false");
  scream_log_if(PATTERN, "ressource,graphics", shader, vertex, fragment, "true");
  return (true);
}

