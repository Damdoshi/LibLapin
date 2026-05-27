// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_create_mode
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 150
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Enables or disables automatic node creation during accesses.
 * @param cmode $Ctrue@ to create missing nodes automatically, $Cfalse@ to fail on missing nodes.
 * @return-success The global create mode is updated.
 * @log "configuration"
 * @see bunny_configuration_get_create_mode
 *
 * @doc-lang fr
 * @brief Active ou désactive la création automatique de nœuds pendant les accès.
 * @param cmode $Ctrue@ to create missing nodes automatically, $Cfalse@ to fail on missing nodes.
 * @return-success Le mode de création global est mis à jour.
 * @log "configuration"
 * @see bunny_configuration_get_create_mode
 */
void			bunny_configuration_create_mode(bool			cmode)
{
  SmallConf::create_mode = cmode;
  scream_log_if("%s", "configuration", cmode ? "true" : "false");
}

/**
 * @doc
 * @doc-symbol bunny_configuration_get_create_mode
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 151
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the current automatic node creation mode.
 * @return-success Returns $Ctrue@ when create mode is enabled.
 * @log "configuration"
 * @see bunny_configuration_create_mode
 *
 * @doc-lang fr
 * @brief Renvoie le mode courant de création automatique de nœuds.
 * @return-success Renvoie $Ctrue@ quand le mode de création est actif.
 * @log "configuration"
 * @see bunny_configuration_create_mode
 */
bool			bunny_configuration_get_create_mode(void)
{
  return (SmallConf::create_mode);
}

