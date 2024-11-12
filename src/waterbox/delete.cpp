// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bunny Library

#include		"lapin_private.h"

void			bunny_delete_waterbox(t_bunny_waterbox	*wb)
{
  bunny_delete_bitfield(wb->boxes[0]);
  bunny_delete_bitfield(wb->boxes[1]);
  delete wb;
}

