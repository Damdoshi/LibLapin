// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"PVM110N.hpp"
#include		"lapin.h"

void			bunny_delete_hardware(t_bunny_hardware		*hdr)
{
  delete (hbs::PVM110N*)hdr->_private;
  bunny_free(hdr);
}

