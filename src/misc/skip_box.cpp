// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_skip_binary_box
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 530
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Skips one binary box and returns the next offset.
 * @param data The binary data to inspect.
 * @param offset Offset of the box to skip.
 * @param maxlen Total length of data.
 * @return-case success The offset immediately after the box, or 0 if the box is invalid or truncated.
 * @see t_bunny_binary_box
 *
 * @doc-lang fr
 * @brief Saute une boîte binaire et renvoie l'offset suivant.
 * @param data Les données binaires à inspecter.
 * @param offset Offset de la boîte à sauter.
 * @param maxlen Longueur totale de data.
 * @return-case success L'offset situé immédiatement après la boîte, ou 0 si la boîte est invalide ou tronquée.
 * @see t_bunny_binary_box
 */

off_t			bunny_skip_binary_box(const void	*_data,
					      off_t		offset,
					      off_t		maxlen)
{
  const char		*data = (const char*)_data;
  t_bunny_binary_box	*tmp = (t_bunny_binary_box*)&data[offset];
  size_t		head;

  head = sizeof(tmp->key) + sizeof(tmp->box_size);
  if (offset + head + tmp->box_size >= (size_t)maxlen)
    return (0);
  offset += head + tmp->box_size;
  return (offset);
}

