// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdlib.h>
#include		"lapin_private.h"

const char		*bunny_string_map_get(t_bunny_map	*map,
					      const char	*key)
{
  if ((void*)map->cmp != (void*)strcmp)
    return (NULL);
  return (bunny_map_get_data(map, key, const char*));
}

const char		*bunny_string_map_set(t_bunny_map	*map,
					      const char	*key,
					      const char	*val)
{
  if (val == NULL)
    {
      if ((map = bunny_map_get_subtree(map, (char*)key, false)))
	{
	  if (bunny_map_data(map, char*))
	    bunny_free(bunny_map_data(map, char*));
	  bunny_delete_map(map);
	}
      return (NULL);
    }
  if ((val = bunny_strdup(val)) == NULL)
    return (NULL);
  if ((key = (char*)bunny_map_set_data(map, key, val, const char*)) == NULL)
    bunny_free((char*)val);
  return (key);
}

