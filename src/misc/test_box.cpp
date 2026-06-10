// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_test_binary_box
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 520
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Tests whether a binary box at an offset has a given four-byte key.
 * @param data The binary data to inspect.
 * @param offset Offset of the box to test.
 * @param maxlen Total length of data.
 * @param str Four-byte key to compare.
 * @return-case success true if the key matches.
 * @see t_bunny_binary_box
 *
 * @doc-lang fr
 * @brief Teste si une boîte binaire située à un offset possède une clé de quatre octets donnée.
 * @param data Les données binaires à inspecter.
 * @param offset Offset de la boîte à tester.
 * @param maxlen Longueur totale de data.
 * @param str Clé de quatre octets à comparer.
 * @return-case success true si la clé correspond.
 * @see t_bunny_binary_box
 */

bool			bunny_test_binary_box(const void	*_data,
					      off_t		offset,
					      off_t		maxlen,
					      const char	*str)
{
  const char		*data = (const char*)_data;

  if (offset + 4 >= maxlen)
    return (false);
  if (bunny_strnlen(str, 4) != 4)
    return (false);
  return (strncmp(&data[offset], str, 4) == 0);
}

