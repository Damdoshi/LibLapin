// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_delete_key(t_bunny_cipher_key	*key)
{
  bunny_free(key);
}

