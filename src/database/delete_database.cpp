// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_delete_database(t_bunny_database	*db)
{
  // close db
  if (db->url)
    free(db->url);
  if (db->login)
    free(db->login);
  if (db->password)
    free(db->password);
  bunny_free(db);
}
