// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_load_box
 * @doc-kind function
 * @doc-module context
 * @doc-order 500
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Loads a GUI box system from a configuration file.
 * @param bs Box system to fill.
 * @param file Configuration file to load.
 * @param env Optional existing environment configuration.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @see t_bunny_box_system
 *
 * @doc-lang fr
 * @brief Charge un système de boîtes GUI depuis un fichier de configuration.
 * @param bs Box system to fill.
 * @param file Configuration file to load.
 * @param env Optional existing environment configuration.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @see t_bunny_box_system
 */
bool			bunny_load_box(t_bunny_box_system	*bs,
				       const char		*file,
				       t_bunny_configuration	*env)
{
  t_bunny_configuration	*cnf;
  bool			ret;

  if ((cnf = bunny_open_configuration(file, env)) == NULL)
    return (false);
  ret = bunny_read_box(bs, cnf);
  if (!env)
    bunny_delete_configuration(cnf);
  return (ret);
}

