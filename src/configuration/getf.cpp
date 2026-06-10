// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_vgetf_node
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 630
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path using a $tva_list@ helper that reads a node.
 * @param config Configuration tree to inspect or modify.
 * @param data Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui lit un(e) node.
 * @param config Configuration tree to inspect or modify.
 * @param data Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_vgetf_node(t_bunny_configuration	*cnf,
					       t_bunny_configuration	**data,
					       const char		*pat,
					       va_list			lst)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    return (false);
  if (data)
    *data = got;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_getf_node
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 620
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path helper that reads a node.
 * @param config Configuration tree to inspect or modify.
 * @param data Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui lit un(e) node.
 * @param config Configuration tree to inspect or modify.
 * @param data Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_getf_node(t_bunny_configuration	*cnf,
					      t_bunny_configuration	**data,
					      const char		*pat,
					      ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vgetf_node(cnf, data, pat, lst));
}

/**
 * @doc
 * @doc-symbol bunny_configuration_vgetf_string
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 631
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path using a $tva_list@ helper that reads a string.
 * @param config Configuration tree to inspect or modify.
 * @param string Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui lit un(e) string.
 * @param config Configuration tree to inspect or modify.
 * @param string Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_vgetf_string(t_bunny_configuration	*cnf,
						 const char		**data,
						 const char		*pat,
						 va_list		lst)
{
  const char	*got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if (bunny_configuration_go_get_string(cnf, &got, &buffer[0]) == false)
    return (false);
  if (data)
    *data = got;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_getf_string
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 621
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path helper that reads a string.
 * @param config Configuration tree to inspect or modify.
 * @param string Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui lit un(e) string.
 * @param config Configuration tree to inspect or modify.
 * @param string Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_getf_string(t_bunny_configuration	*cnf,
						const char		**data,
						const char		*pat,
						...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vgetf_string(cnf, data, pat, lst));
}

/**
 * @doc
 * @doc-symbol bunny_configuration_vgetf_int
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 632
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path using a $tva_list@ helper that reads a integer.
 * @param config Configuration tree to inspect or modify.
 * @param integer Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui lit un(e) integer.
 * @param config Configuration tree to inspect or modify.
 * @param integer Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_vgetf_int(t_bunny_configuration	*cnf,
					      int			*data,
					      const char		*pat,
					      va_list			lst)
{
  int		got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if (bunny_configuration_go_get_int(cnf, &got, &buffer[0]) == false)
    return (false);
  if (data)
    *data = got;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_getf_int
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 622
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path helper that reads a integer.
 * @param config Configuration tree to inspect or modify.
 * @param integer Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui lit un(e) integer.
 * @param config Configuration tree to inspect or modify.
 * @param integer Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_getf_int(t_bunny_configuration	*cnf,
					     int			*data,
					     const char			*pat,
					     ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vgetf_int(cnf, data, pat, lst));
}

/**
 * @doc
 * @doc-symbol bunny_configuration_vgetf_bool
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 633
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path using a $tva_list@ helper that reads a boolean.
 * @param config Configuration tree to inspect or modify.
 * @param boolean Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui lit un(e) boolean.
 * @param config Configuration tree to inspect or modify.
 * @param boolean Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_vgetf_bool(t_bunny_configuration	*cnf,
					       bool			*data,
					       const char		*pat,
					       va_list			lst)
{
  int		got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if (bunny_configuration_go_get_int(cnf, &got, &buffer[0]) == false)
    return (false);
  if (data)
    *data = !!got;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_getf_bool
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 623
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path helper that reads a boolean.
 * @param config Configuration tree to inspect or modify.
 * @param boolean Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui lit un(e) boolean.
 * @param config Configuration tree to inspect or modify.
 * @param boolean Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_getf_bool(t_bunny_configuration	*cnf,
					      bool			*data,
					      const char		*pat,
					      ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vgetf_bool(cnf, data, pat, lst));
}

/**
 * @doc
 * @doc-symbol bunny_configuration_vgetf_double
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 634
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path using a $tva_list@ helper that reads a double.
 * @param config Configuration tree to inspect or modify.
 * @param dbl Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui lit un(e) double.
 * @param config Configuration tree to inspect or modify.
 * @param dbl Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_vgetf_double(t_bunny_configuration	*cnf,
						 double			*data,
						 const char		*pat,
						 va_list		lst)
{
  double	got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if (bunny_configuration_go_get_double(cnf, &got, &buffer[0]) == false)
    return (false);
  if (data)
    *data = got;
  return (true);
}


/**
 * @doc
 * @doc-symbol bunny_configuration_getf_double
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 624
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path helper that reads a double.
 * @param config Configuration tree to inspect or modify.
 * @param dbl Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui lit un(e) double.
 * @param config Configuration tree to inspect or modify.
 * @param dbl Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_getf_double(t_bunny_configuration	*cnf,
						 double			*data,
						 const char		*pat,
						 ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vgetf_double(cnf, data, pat, lst));
}
