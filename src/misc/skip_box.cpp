// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

off_t			bunny_skip_box(const void	*_data,
				       off_t		offset,
				       off_t		maxlen)
{
  const char		*data = (const char*)_data;
  t_bunny_box		*tmp = (t_bunny_box*)&data[offset];
  size_t		head;

  head = sizeof(tmp->key) + sizeof(tmp->box_size);
  if (offset + head + tmp->box_size >= (size_t)maxlen)
    return (0);
  offset += head + tmp->box_size;
  return (offset);
}

