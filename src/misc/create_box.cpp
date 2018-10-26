// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_binary_box	*bunny_create_binary_box(size_t		len)
{
  t_bunny_binary_box	*box;

  if ((box = (t_bunny_binary_box*)bunny_calloc(sizeof(box->key) + sizeof(box->box_size) + len, 1))
      == NULL)
    return (NULL);
  box->box_size = len;
  return (box);
}

