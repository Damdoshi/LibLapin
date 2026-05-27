// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_delete_shader
 * @doc-kind function
 * @doc-module shader
 * @doc-order 50
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Destroys a shader object.
 * @param shader Shader created by bunny_new_shader.
 * @log "ressource,graphics"
 * @see bunny_new_shader
 *
 * @doc-lang fr
 * @brief Détruit un objet shader.
 * @param shader Shader créé par bunny_new_shader.
 * @log "ressource,graphics"
 * @see bunny_new_shader
 */
void			bunny_delete_shader(t_bunny_shader	*_shader)
{
  sf::Shader		*shader = (sf::Shader*)_shader;

  delete shader;
  scream_log_if("%p", "ressource,graphics", shader);
}

