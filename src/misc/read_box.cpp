// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_box		*bunny_read_box(const void	*_data,
					off_t		*offset,
					off_t		maxlen)
{
  const char		*data = (const char*)_data;
  t_bunny_box		*tmp = (t_bunny_box*)&data[*offset];
  t_bunny_box		*box;
  size_t		head;
  size_t		i;

  head = sizeof(tmp->key) + sizeof(tmp->box_size);
  if (*offset + head + tmp->box_size >= (size_t)maxlen)
    return (NULL);
  for (i = 0; i < sizeof(tmp->key); ++i)
    if (isalnum(tmp->key[i]) == 0)
      return (NULL);
  if ((box = (t_bunny_box*)bunny_malloc(head + tmp->box_size)) == NULL)
    return (NULL);
  *offset += head;
  memcpy(&box->key[0], &tmp->key[0], sizeof(box->key));
  box->box_size = tmp->box_size;
  memcpy(&box->data[0], &data[*offset], tmp->box_size);
  *offset += tmp->box_size;
  return (box);
}

