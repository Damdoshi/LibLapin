// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_create_binary_box
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 580
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Allocates a binary box with a payload of the requested size.
 * @param len Payload size in bytes.
 * @return-case success A newly allocated binary box, or NULL on allocation failure.
 * @see t_bunny_binary_box
 *
 * @doc-lang fr
 * @brief Alloue une boîte binaire avec une charge utile de la taille demandée.
 * @param len Taille de la charge utile en octets.
 * @return-case success Une boîte binaire nouvellement allouée, ou NULL en cas d'échec d'allocation.
 * @see t_bunny_binary_box
 */

t_bunny_binary_box	*bunny_create_binary_box(size_t		len)
{
  t_bunny_binary_box	*box;

  if ((box = (t_bunny_binary_box*)bunny_calloc(sizeof(box->key) + sizeof(box->box_size) + len, 1))
      == NULL)
    return (NULL);
  box->box_size = len;
  return (box);
}

