// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p shader, %s vertex_file, %s fragment_file -> %s"


/**
 * @doc
 * @doc-symbol bunny_read_shader
 * @doc-kind function
 * @doc-module shader
 * @doc-order 35
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Compiles shader code from strings.
 * @param sha Shader object created by bunny_new_shader.
 * @param vrt Optional vertex shader source. May be NULL.
 * @param frg Fragment shader source.
 * @return-success Returns true when the shader was compiled.
 * @return-failure Returns false if parameters are invalid or compilation fails.
 * @log "ressource,graphics"
 * @see bunny_load_shader
 *
 * @doc-lang fr
 * @brief Compile du code shader depuis des chaînes.
 * @param sha Objet shader créé par bunny_new_shader.
 * @param vrt Source de vertex shader optionnelle. Peut être NULL.
 * @param frg Source de fragment shader.
 * @return-success Renvoie true lorsque le shader a été compilé.
 * @return-failure Renvoie false si les paramètres sont invalides ou si la compilation échoue.
 * @log "ressource,graphics"
 * @see bunny_load_shader
 */
bool			bunny_read_shader(t_bunny_shader		*_shader,
					  const char			*vertex,
					  const char			*fragment)
{
  sf::Shader		*shader = (sf::Shader*)_shader;

  if (fragment == NULL)
    scream_error_if(return (false), EINVAL, PATTERN, "ressource,graphics", shader, vertex, fragment, "false");
  if (vertex == NULL)
    {
      if (shader->loadFromMemory(fragment, sf::Shader::Type::Fragment) == false)
	scream_error_if(return (false), BE_SYNTAX_ERROR, PATTERN, "ressource,graphics,syntax", shader, vertex, fragment, "false");
      scream_log_if(PATTERN, "ressource,graphics", shader, vertex, fragment, "true");
      return (true);
    }

  if (shader->loadFromMemory(vertex, fragment) == false)
    scream_error_if(return (false), BE_SYNTAX_ERROR, PATTERN, "ressource,graphics,syntax", shader, vertex, fragment, "false");
  scream_log_if(PATTERN, "ressource,graphics", shader, vertex, fragment, "true");
  return (true);
}

