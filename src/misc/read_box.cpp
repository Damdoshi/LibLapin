// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_read_binary_box
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 540
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Reads and copies one binary box from memory.
 * @param data The binary data to inspect.
 * @param offset Input/output offset. On success, it is advanced after the copied box.
 * @param maxlen Total length of data.
 * @return-case success A newly allocated binary box, or NULL on failure.
 * @see t_bunny_binary_box
 *
 * @doc-lang fr
 * @brief Lit et copie une boîte binaire depuis la mémoire.
 * @param data Les données binaires à inspecter.
 * @param offset Offset d'entrée/sortie. En cas de succès, il est avancé après la boîte copiée.
 * @param maxlen Longueur totale de data.
 * @return-case success Une boîte binaire nouvellement allouée, ou NULL en cas d'échec.
 * @see t_bunny_binary_box
 */

t_bunny_binary_box	*bunny_read_binary_box(const void	*_data,
					       off_t		*offset,
					       off_t		maxlen)
{
  const char		*data = (const char*)_data;
  t_bunny_binary_box	*tmp = (t_bunny_binary_box*)&data[*offset];
  t_bunny_binary_box	*box;
  size_t		head;
  size_t		i;

  head = sizeof(tmp->key) + sizeof(tmp->box_size);
  if (*offset + head + tmp->box_size >= (size_t)maxlen)
    return (NULL);
  for (i = 0; i < sizeof(tmp->key); ++i)
    if (isalnum(tmp->key[i]) == 0)
      return (NULL);
  if ((box = (t_bunny_binary_box*)bunny_malloc(head + tmp->box_size)) == NULL)
    return (NULL);
  *offset += head;
  memcpy(&box->key[0], &tmp->key[0], sizeof(box->key));
  box->box_size = tmp->box_size;
  memcpy(&box->data[0], &data[*offset], tmp->box_size);
  *offset += tmp->box_size;
  return (box);
}

