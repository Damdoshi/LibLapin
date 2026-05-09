// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_declarativef
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 813
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Tests declarative boolean presence through a formatted path.
 * @param c Configuration tree to inspect.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Returns $Ctrue@ when the declaration is considered active.
 * @return-failure Returns $Cfalse@ otherwise.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Teste une présence booléenne déclarative via un chemin formaté.
 * @param c Configuration tree to inspect.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Renvoie $Ctrue@ quand la déclaration est considérée active.
 * @return-failure Renvoie $Cfalse@ sinon.
 * @log "configuration"
 */
bool			bunny_configuration_declarativef(t_bunny_configuration		*cnf,
							 const char			*fmt,
							 ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *nod;
  va_list	lst;
  int		x;

  va_start(lst, fmt);
  vsnprintf(&buffer[0], sizeof(buffer), fmt, lst);
  if ((nod = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    return (false);
  if (bunny_configuration_get_int(nod, &x) == false)
    return (true);
  return (!!x);
}

