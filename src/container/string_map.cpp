// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdlib.h>
#include		"lapin_private.h"

/*!
** Retrieve a string value from a string map.
**
** The map must have been created with the string_map helper callbacks. The
** returned string belongs to the map and must not be freed by the caller.
**
** \param map The string map to browse.
** \param key The string key to search.
** \return The stored string, or NULL if absent or if map is not a string map.
*/
/**
 * @doc
 * @doc-symbol bunny_string_map_get
 * @doc-kind function
 * @doc-module map
 * @doc-order 460
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the string value associated with a string key.
 * @param map The string map to browse.
 * @param key The key to search.
 * @return-success Returns the stored string.
 * @return-failure Returns $CNULL@ if the key is missing.
 * @see string_map, bunny_string_map_set
 *
 * @doc-lang fr
 * @brief Renvoie la valeur chaîne associée à une clé chaîne.
 * @param map La string map à parcourir.
 * @param key La clé à chercher.
 * @return-success Renvoie la chaîne stockée.
 * @return-failure Renvoie $CNULL@ si la clé est absente.
 * @see string_map, bunny_string_map_set
 */
const char		*bunny_string_map_get(t_bunny_map	*map,
					      const char	*key)
{
  if (map == NULL || (void*)map->cmp != (void*)strcmp)
    return (NULL);
  return (bunny_map_get_data(map, key, const char*));
}

/*!
** Store, replace or remove a string value in a string map.
**
** The map must have been created with the string_map helper callbacks. The
** value is duplicated before being stored. Passing NULL as val removes the key.
**
** \param map The string map to edit.
** \param key The string key to store.
** \param val The string value to duplicate and store, or NULL to remove.
** \return The previous value according to bunny_map_set_data semantics, or NULL on removal/error.
*/
/**
 * @doc
 * @doc-symbol bunny_string_map_set
 * @doc-kind function
 * @doc-module map
 * @doc-order 480
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Associates a duplicated string value with a string key.
 * @param map The string map to edit.
 * @param key The key to associate.
 * @param val The string to duplicate and store, or $CNULL@ to clear it.
 * @return-success Returns the newly stored string, or $CNULL@ when clearing.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @see string_map, bunny_string_map_get
 *
 * @doc-lang fr
 * @brief Associe une valeur chaîne dupliquée à une clé chaîne.
 * @param map La string map à modifier.
 * @param key La clé à associer.
 * @param val La chaîne à dupliquer et stocker, ou $CNULL@ pour la vider.
 * @return-success Renvoie la chaîne nouvellement stockée, ou $CNULL@ lors de la suppression.
 * @return-failure Renvoie $CNULL@ si une allocation échoue.
 * @see string_map, bunny_string_map_get
 */
const char		*bunny_string_map_set(t_bunny_map	*map,
					      const char	*key,
					      const char	*val)
{
  const char		*dup;
  const char		*old;

  if (val == NULL)
    {
      if ((map = bunny_map_get_subtree(map, (char*)key, false)))
	{
	  if (bunny_map_data(map, char*))
	    bunny_free(bunny_map_data(map, char*));
	  *(void**)&map->data = NULL;
	}
      return (NULL);
    }
  if ((dup = bunny_strdup(val)) == NULL)
    return (NULL);
  if ((old = (const char*)bunny_map_set_data(map, key, dup, const char*)) == NULL)
    {
      bunny_free((char*)dup);
      return (NULL);
    }
  if (old != dup)
    bunny_free((char*)old);
  return (dup);
}

