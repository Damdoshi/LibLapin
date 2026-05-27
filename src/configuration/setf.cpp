// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_vsetf_node
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 640
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path using a $tva_list@ helper that writes a node.
 * @param config Configuration tree to inspect or modify.
 * @param node Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui écrit un(e) node.
 * @param config Configuration tree to inspect or modify.
 * @param node Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_vsetf_node(t_bunny_configuration	*cnf,
					       const t_bunny_configuration *data,
					       const char		*pat,
					       va_list			lst)
{
  bool		cmode = bunny_configuration_get_create_mode();
  t_bunny_configuration *got;
  char		buffer[1024 * 4];

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  bunny_configuration_create_mode(true);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      bunny_configuration_create_mode(cmode);
      return (false);
    }
  if (data == NULL)
    {
      bunny_configuration_create_mode(cmode);
      bunny_delete_configuration(got);
      return (true);
    }
  SmallConf	*a;
  const SmallConf *b;

  a = (SmallConf*)got;
  b = (const SmallConf*)data;
  SmallConf::RecursiveAssign(*a, *b, true, true);
  bunny_configuration_create_mode(cmode);
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_setf_node
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 630
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path helper that writes a node.
 * @param config Configuration tree to inspect or modify.
 * @param node Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui écrit un(e) node.
 * @param config Configuration tree to inspect or modify.
 * @param node Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_setf_node(t_bunny_configuration	*cnf,
					      const t_bunny_configuration *data,
					      const char		*pat,
					      ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vsetf_node(cnf, data, pat, lst));
}

/**
 * @doc
 * @doc-symbol bunny_configuration_vsetf_string
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 641
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path using a $tva_list@ helper that writes a string.
 * @param config Configuration tree to inspect or modify.
 * @param string Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui écrit un(e) string.
 * @param config Configuration tree to inspect or modify.
 * @param string Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_vsetf_string(t_bunny_configuration	*cnf,
						 const char		*data,
						 const char		*pat,
						 va_list		lst)
{
  bool		cmode = bunny_configuration_get_create_mode();
  char		buffer[1024 * 4];
  bool		ret;

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  bunny_configuration_create_mode(true);
  ret = (bunny_configuration_go_set_string(cnf, data, &buffer[0]));
  bunny_configuration_create_mode(cmode);
  return (ret);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_setf_string
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 631
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path helper that writes a string.
 * @param config Configuration tree to inspect or modify.
 * @param string Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui écrit un(e) string.
 * @param config Configuration tree to inspect or modify.
 * @param string Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_setf_string(t_bunny_configuration	*cnf,
						const char		*data,
						const char		*pat,
						...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vsetf_string(cnf, data, pat, lst));
}

/**
 * @doc
 * @doc-symbol bunny_configuration_vsetf_int
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 642
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path using a $tva_list@ helper that writes a integer.
 * @param config Configuration tree to inspect or modify.
 * @param int Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui écrit un(e) integer.
 * @param config Configuration tree to inspect or modify.
 * @param int Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_vsetf_int(t_bunny_configuration	*cnf,
					      int			data,
					      const char		*pat,
					      va_list			lst)
{
  bool		cmode = bunny_configuration_get_create_mode();
  char		buffer[1024 * 4];
  bool		ret;

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  bunny_configuration_create_mode(true);
  ret = (bunny_configuration_go_set_int(cnf, data, &buffer[0]));
  bunny_configuration_create_mode(cmode);
  return (ret);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_setf_int
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 632
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path helper that writes a integer.
 * @param config Configuration tree to inspect or modify.
 * @param int Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui écrit un(e) integer.
 * @param config Configuration tree to inspect or modify.
 * @param int Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_setf_int(t_bunny_configuration	*cnf,
					     int			data,
					     const char			*pat,
					     ...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vsetf_int(cnf, data, pat, lst));
}

/**
 * @doc
 * @doc-symbol bunny_configuration_vsetf_double
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 644
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path using a $tva_list@ helper that writes a double.
 * @param config Configuration tree to inspect or modify.
 * @param double Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui écrit un(e) double.
 * @param config Configuration tree to inspect or modify.
 * @param double Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param lst Argument list consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_vsetf_double(t_bunny_configuration	*cnf,
						 double			data,
						 const char		*pat,
						 va_list		lst)
{
  bool		cmode = bunny_configuration_get_create_mode();
  char		buffer[1024 * 4];
  bool		ret;

  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  bunny_configuration_create_mode(true);
  ret = (bunny_configuration_go_set_double(cnf, data, &buffer[0]));
  bunny_configuration_create_mode(cmode);
  return (ret);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_setf_double
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 634
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Formatted path helper that writes a double.
 * @param config Configuration tree to inspect or modify.
 * @param double Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Aide de chemin formaté qui écrit un(e) double.
 * @param config Configuration tree to inspect or modify.
 * @param double Typed value or output storage.
 * @param format Printf-like address pattern.
 * @param ... Values consumed by $Sformat@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_setf_double(t_bunny_configuration	*cnf,
						double			data,
						const char		*pat,
						...)
{
  va_list	lst;

  va_start(lst, pat);
  return (bunny_configuration_vsetf_double(cnf, data, pat, lst));
}

