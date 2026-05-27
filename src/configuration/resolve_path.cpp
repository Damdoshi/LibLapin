// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<unistd.h>
#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_resolve_path
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 612
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Resolves a configuration resource path using the current search stack.
 * @param str Path to resolve.
 * @param buffer Destination buffer.
 * @param size_buffer Destination buffer size.
 * @return-success Returns $Ctrue@ and writes the resolved path.
 * @return-failure Returns $Cfalse@ if the path cannot be resolved or does not fit.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Résout un chemin de ressource de configuration avec la pile de recherche courante.
 * @param str Path to resolve.
 * @param buffer Destination buffer.
 * @param size_buffer Destination buffer size.
 * @return-success Renvoie $Ctrue@ et écrit le chemin résolu.
 * @return-failure Renvoie $Cfalse@ si le chemin ne peut pas être résolu ou ne tient pas.
 * @log "configuration"
 */
bool			bunny_configuration_resolve_path(const char	*file,
							 char		*buffer,
							 int		size_buffer)
{
  std::list<std::string>::reverse_iterator it;

  for (it = SmallConf::file_path.rbegin(); it != SmallConf::file_path.rend(); ++it)
    {
      size_t		siz;

      if (*it != "")
	siz = snprintf(&buffer[0], size_buffer, "%s/%s", it->c_str(), file);
      else
	siz = snprintf(&buffer[0], size_buffer, "%s", file);
      if (siz == (size_t)size_buffer)
	continue ;
      if (access(&buffer[0], R_OK) == 0)
	return (true);
    }
  return (false);
}
