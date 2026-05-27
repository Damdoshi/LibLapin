// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_is_shader_available
 * @doc-kind function
 * @doc-module shader
 * @doc-order 20
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Reports whether the shader backend is available.
 * @return-success Returns true if shaders can be used.
 * @return-failure Returns false when shaders are unavailable.
 *
 * @doc-lang fr
 * @brief Indique si le backend de shaders est disponible.
 * @return-success Renvoie true si les shaders peuvent être utilisés.
 * @return-failure Renvoie false lorsque les shaders sont indisponibles.
 */
bool			bunny_is_shader_available(void)
{
  return (sf::Shader::isAvailable());
}

