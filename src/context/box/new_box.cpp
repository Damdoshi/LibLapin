// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_new_gui_box
 * @doc-kind function
 * @doc-module context
 * @doc-order 490
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Allocates and initializes the common base of a GUI box.
 * @param siz Size of the concrete box structure.
 * @param cnf Configuration node describing the box.
 * @return-success Returns a newly allocated box base.
 * @return-failure Returns $CNULL@ on error.
 * @see t_bunny_box_system
 *
 * @doc-lang fr
 * @brief Alloue et initialise la base commune d’une boîte GUI.
 * @param siz Size of the concrete box structure.
 * @param cnf Configuration node describing the box.
 * @return-success Renvoie une base de boîte nouvellement allouée.
 * @return-failure Renvoie $CNULL@ en cas d’erreur.
 * @see t_bunny_box_system
 */
void			*bunny_new_gui_box(size_t			siz,
					   t_bunny_configuration	*cnf)
{
  t_bunny_gui_box	*nw;
  const char		*s;

  if ((nw = (t_bunny_gui_box*)bunny_calloc(1, siz)) == NULL)
    return (NULL);
  s = bunny_configuration_get_name(cnf);
  if ((nw->id = bunny_strdup(s)) == NULL)
    {
      bunny_free(nw);
      return (NULL);
    }
  if ((nw->children = bunny_new_map(string_map)) == NULL)
    {
      bunny_free((char*)nw->id);
      bunny_free(nw);
      return (NULL);
    }
  return (nw);
}

