// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			*bunny_new_gui_box(size_t			siz,
					   t_bunny_configuration	*cnf)
{
  t_bunny_gui_box	*nw;
  const char		*s;

  if ((nw = (t_bunny_gui_box*)bunny_calloc(siz, 1)) == NULL)
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

