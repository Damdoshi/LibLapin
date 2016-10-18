// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_database	*bunny_new_database(const char		*url,
					    const char		*login,
					    const char		*password)
{
  t_bunny_database	*n;

  if ((n = bunny_calloc(1, sizeof(*n))) == NULL)
    return (NULL);
  n->url = strdup(url);
  n->login = strdup(login);
  n->password = strdup(password);
  if (!n->url || !n->login || !n->password)
    {
      bunny_delete_database(n);
      return (NULL);
    }
  // open db
  return (n);
}
