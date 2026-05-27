// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<math.h>
#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_get_string
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 260
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reads the node scalar value as a string.
 * @param config Node to read.
 * @param str Output pointer receiving the internal string pointer.
 * @return-success Returns $Ctrue@ and stores the string pointer.
 * @return-failure Returns $Cfalse@ if no value is available.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Lit la valeur scalaire du nœud sous forme de chaîne.
 * @param config Node to read.
 * @param str Output pointer receiving the internal string pointer.
 * @return-success Renvoie $Ctrue@ et stocke le pointeur de chaîne.
 * @return-failure Renvoie $Cfalse@ si aucune valeur n’est disponible.
 * @log "configuration"
 */
bool			bunny_configuration_get_string(const t_bunny_configuration *config,
						       const char		**str)
{
  SmallConf		*conf = (SmallConf*)config;
  bool			ret;

  ret = conf->GetString(str);
  scream_log_if
    ("%p conf, %p target  -> %s (%s)", "configuration",
     config, str, ret ? "true" : "false", ret ? *str : "");
  return (ret);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_get_double
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 270
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reads the node scalar value as a double.
 * @param config Node to read.
 * @param val Output double pointer.
 * @return-success Returns $Ctrue@ and stores the value.
 * @return-failure Returns $Cfalse@ if no value is available or conversion fails.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Lit la valeur scalaire du nœud sous forme de double.
 * @param config Node to read.
 * @param val Output double pointer.
 * @return-success Renvoie $Ctrue@ et stocke la valeur.
 * @return-failure Renvoie $Cfalse@ si aucune valeur n’est disponible ou si la conversion échoue.
 * @log "configuration"
 */
bool			bunny_configuration_get_double(const t_bunny_configuration *config,
						       double			*val)
{
  SmallConf		*conf = (SmallConf*)config;
  bool			ret;

  ret = conf->GetDouble(val);
  scream_log_if
    ("%p conf, %p target  -> %s (%f)", "configuration",
     config, val, ret ? "true" : "false", ret ? *val : nan(""));
  return (ret);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_get_int
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 280
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reads the node scalar value as an integer.
 * @param config Node to read.
 * @param val Output integer pointer.
 * @return-success Returns $Ctrue@ and stores the value.
 * @return-failure Returns $Cfalse@ if no value is available or conversion fails.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Lit la valeur scalaire du nœud sous forme d’entier.
 * @param config Node to read.
 * @param val Output integer pointer.
 * @return-success Renvoie $Ctrue@ et stocke la valeur.
 * @return-failure Renvoie $Cfalse@ si aucune valeur n’est disponible ou si la conversion échoue.
 * @log "configuration"
 */
bool			bunny_configuration_get_int(const t_bunny_configuration	*config,
						    int				*val)
{
  SmallConf		*conf = (SmallConf*)config;
  bool			ret;

  ret = conf->GetInt(val);
  scream_log_if
    ("%p conf, %p target  -> %s (%d)", "configuration",
     config, val, ret ? "true" : "false", ret ? *val : 0);
  return (ret);
}

