// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bunny Library

#include		"lapin_private.h"

t_bunny_waterbox	*bunny_load_waterbox(const char		*file)
{
  t_bunny_configuration	*cnf;
  t_bunny_waterbox	*wb;

  if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  wb = bunny_read_waterbox(cnf);
  bunny_delete_configuration(cnf);
  return (wb);
}
