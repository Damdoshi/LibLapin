// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_box		*bunny_load_box(int			fd)
{
  t_bunny_box		tmp;
  t_bunny_box		*box;
  size_t		headsize;

  headsize = sizeof(tmp.key) + sizeof(tmp.box_size);
  if (bunny_read_until_it_is_full(fd, &tmp, headsize) != headsize)
    return (NULL);
  if ((box = (t_bunny_box*)bunny_malloc(headsize + tmp.box_size)) == NULL)
    return (NULL);
  memcpy(&box->key[0], &tmp.key[0], sizeof(box->key));
  box->box_size = tmp.box_size;

  if (bunny_read_until_it_is_full(fd, &box->data[0], box->box_size) != box->box_size)
    {
      bunny_free(box);
      return (NULL);
    }
  return (box);
}

