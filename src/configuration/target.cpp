// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		<stdarg.h>
#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_target
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 805
 * @doc-since 0
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Makes one configuration node target another one.
 * @param from Source configuration node.
 * @param to Target configuration node.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Fait cibler un nœud de configuration vers un autre.
 * @param from Source configuration node.
 * @param to Target configuration node.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool			bunny_configuration_target(t_bunny_configuration	*_f,
						   t_bunny_configuration	*_t)
{
  SmallConf		*f = (SmallConf*)_f;
  SmallConf		*t = (SmallConf*)_t;

  f->last_type = SmallConf::RAWSTRING;
  f->have_value = true;
  f->original_value = t->address;
  return (true);
}


/**
 * @doc
 * @doc-symbol bunny_configuration_targetf
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 806
 * @doc-since 0
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Makes a formatted path in a configuration target another node.
 * @param _f Configuration tree to modify.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Fait cibler un chemin formaté dans une configuration vers un autre nœud.
 * @param _f Configuration tree to modify.
 * @param pattern Printf-like address pattern.
 * @param ... Values consumed by $Spattern@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool			bunny_configuration_targetf(t_bunny_configuration	*_f,
						    const char			*pattern,
						    ...)
{
  char			buffer[4096];
  va_list		lst;
  t_bunny_configuration	*cnf;

  va_start(lst, pattern);
  if ((vsnprintf(buffer, sizeof(buffer), pattern, lst)) >= (int)sizeof(buffer))
    return (false);
  if (bunny_configuration_getf_node(_f, &cnf, buffer) == false)
    return (false);
  return (bunny_configuration_target(_f, cnf));
}
