// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p shader, %s vertex_file, %s fragment_file -> %s"


/**
 * @doc
 * @doc-symbol bunny_load_shader
 * @doc-kind function
 * @doc-module shader
 * @doc-order 30
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Loads and compiles shader code from files.
 * @param sha Shader object created by bunny_new_shader.
 * @param vertex_file Optional vertex shader file. May be NULL.
 * @param frag_file Fragment shader file.
 * @return-success Returns true when the shader was loaded and compiled.
 * @return-failure Returns false if parameters are invalid, files cannot be loaded or compilation fails.
 * @log "ressource,graphics"
 * @see bunny_read_shader
 *
 * @doc-lang fr
 * @brief Charge et compile du code shader depuis des fichiers.
 * @param sha Objet shader créé par bunny_new_shader.
 * @param vertex_file Fichier de vertex shader optionnel. Peut être NULL.
 * @param frag_file Fichier de fragment shader.
 * @return-success Renvoie true lorsque le shader a été chargé et compilé.
 * @return-failure Renvoie false si les paramètres sont invalides, si les fichiers ne peuvent pas être chargés ou si la compilation échoue.
 * @log "ressource,graphics"
 * @see bunny_read_shader
 */
bool			bunny_load_shader(t_bunny_shader		*_shader,
					  const char			*vertex,
					  const char			*fragment)
{
  sf::Shader		*shader = (sf::Shader*)_shader;

  if (fragment == NULL)
    scream_error_if(return (false), EINVAL, PATTERN, "ressource,graphics", shader, vertex, fragment, "false");
  if (vertex == NULL)
    {
      if (shader->loadFromFile(fragment, sf::Shader::Type::Fragment) == false)
	scream_error_if(return (false), BE_SYNTAX_ERROR, PATTERN, "ressource,graphics,syntax", shader, vertex, fragment, "false");
      scream_log_if(PATTERN, "ressource,graphics", shader, vertex, fragment, "true");
      return (true);
    }

  if (shader->loadFromFile(vertex, fragment) == false)
    scream_error_if(return (false), BE_SYNTAX_ERROR, PATTERN, "ressource,graphics,syntax", shader, vertex, fragment, "false");
  scream_log_if(PATTERN, "ressource,graphics", shader, vertex, fragment, "true");
  return (true);
}

