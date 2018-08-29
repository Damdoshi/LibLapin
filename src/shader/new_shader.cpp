// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_shader		*bunny_new_shader(void)
{
  t_bunny_shader	*shader;

  try
    {
      shader = (void*)new sf::Shader;
      scream_log_if("%p", "ressource,graphics", shader);
      return (shader);
    }
  catch (...)
    {}
  scream_error_if(return (NULL), ENOMEM, "%p", "ressource,graphics", (void*)NULL);
  return (NULL);
}

