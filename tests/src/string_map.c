/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2026
** Pentacle Technologie 2008-2026
** EFRITS 2022-2026
**
** Bibliothèque Lapin
*/

#include		<assert.h>
#include		<stdlib.h>
#include		<string.h>
#include		"lapin.h"

static void		test_empty_and_wrong_map(void)
{
  t_bunny_map		*strings;
  t_bunny_map		*ints;

  assert(bunny_string_map_get(NULL, "missing") == NULL);
  assert((strings = bunny_new_map(string_map)) != NULL);
  assert(bunny_string_map_get(strings, "missing") == NULL);
  assert(bunny_map_size(strings) == 0);
  assert((ints = bunny_new_map(int_map)) != NULL);
  assert(bunny_string_map_get(ints, "missing") == NULL);
  bunny_delete_map(ints);
  bunny_delete_string_map(strings);
}

static void		test_set_get_replace_and_clear(void)
{
  t_bunny_map		*map;
  const char		*alpha;
  const char		*beta;

  assert((map = bunny_new_map(string_map)) != NULL);
  alpha = bunny_string_map_set(map, "alpha", "one");
  beta = bunny_string_map_set(map, "beta", "two");
  assert(alpha != NULL);
  assert(beta != NULL);
  assert(strcmp(alpha, "one") == 0);
  assert(strcmp(beta, "two") == 0);
  assert(strcmp(bunny_string_map_get(map, "alpha"), "one") == 0);
  assert(strcmp(bunny_string_map_get(map, "beta"), "two") == 0);
  assert(bunny_map_size(map) == 2);

  alpha = bunny_string_map_set(map, "alpha", "uno");
  assert(alpha != NULL);
  assert(strcmp(alpha, "uno") == 0);
  assert(strcmp(bunny_string_map_get(map, "alpha"), "uno") == 0);
  assert(bunny_map_size(map) == 2);

  assert(bunny_string_map_clear(map, "beta") == NULL);
  assert(bunny_string_map_get(map, "beta") == NULL);
  beta = bunny_string_map_set(map, "beta", "deux");
  assert(beta != NULL);
  assert(strcmp(bunny_string_map_get(map, "beta"), "deux") == 0);
  assert(bunny_string_map_clear(map, "missing") == NULL);
  assert(strcmp(bunny_string_map_get(map, "alpha"), "uno") == 0);
  assert(strcmp(bunny_string_map_get(map, "beta"), "deux") == 0);
  bunny_delete_string_map(map);
}

static void		test_allocation_failure(void)
{
  t_bunny_map		*map;

  assert((map = bunny_new_map(string_map)) != NULL);
  bunny_malloc_failure(true);
  assert(bunny_string_map_set(map, "alpha", "one") == NULL);
  bunny_malloc_failure(false);
  assert(bunny_map_size(map) == 0);
  assert(bunny_string_map_get(map, "alpha") == NULL);
  bunny_delete_string_map(map);
}

int			main(void)
{
  test_empty_and_wrong_map();
  test_set_get_replace_and_clear();
  test_allocation_failure();
  return (EXIT_SUCCESS);
}
