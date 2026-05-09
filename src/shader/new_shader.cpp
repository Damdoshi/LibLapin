// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_new_shader
 * @doc-kind function
 * @doc-module shader
 * @doc-order 25
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Creates an empty shader object.
 * @return-success Returns a new shader object.
 * @return-failure Returns NULL on allocation failure.
 * @log "ressource,graphics"
 * @see bunny_load_shader, bunny_read_shader, bunny_delete_shader
 *
 * @doc-lang fr
 * @brief Crée un objet shader vide.
 * @return-success Renvoie un nouvel objet shader.
 * @return-failure Renvoie NULL en cas d’échec d’allocation.
 * @log "ressource,graphics"
 * @see bunny_load_shader, bunny_read_shader, bunny_delete_shader
 */
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

