// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_load_binary_box
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 560
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Loads one binary box from a file descriptor.
 * @param fd The file descriptor to read from.
 * @return-case success A newly allocated binary box, or NULL on failure.
 * @see t_bunny_binary_box
 *
 * @doc-lang fr
 * @brief Charge une boîte binaire depuis un descripteur de fichier.
 * @param fd Le descripteur de fichier à lire.
 * @return-case success Une boîte binaire nouvellement allouée, ou NULL en cas d'échec.
 * @see t_bunny_binary_box
 */

t_bunny_binary_box	*bunny_load_binary_box(int			fd)
{
  t_bunny_binary_box	tmp;
  t_bunny_binary_box	*box;
  size_t		headsize;

  headsize = sizeof(tmp.key) + sizeof(tmp.box_size);
  if (bunny_read_until_it_is_full(fd, &tmp, headsize) != headsize)
    return (NULL);
  if ((box = (t_bunny_binary_box*)bunny_malloc(headsize + tmp.box_size)) == NULL)
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

