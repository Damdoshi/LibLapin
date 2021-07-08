/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

void			*load(t_bunny_configuration	*c)
{
  const char		*s;

  if (bunny_configuration_getf(c, &s, ".") == false)
    return (NULL);
  return (bunny_strdup(s));
}

int			main(void)
{
  t_bunny_configuration	*cnf;
  char			**data;
  int			len;

  assert(cnf = bunny_open_configuration("root.dab", NULL));
  len = bunny_configuration_flexible_load
    (cnf, FLM_LOAD_FIELD | FLM_LOAD_ARRAY | FLM_LOAD_HASHMAP, load, (void***)&data, "Root");
  assert(len == 8);
  assert(strcmp(data[0], "aaa") == 0);
  assert(strcmp(data[1], "bbb") == 0);
  assert(strcmp(data[2], "ccc") == 0);
  assert(strcmp(data[3], "ddd") == 0);
  assert(strcmp(data[4], "eee") == 0);
  assert(strcmp(data[5], "fff") == 0);
  assert(strcmp(data[6], "ggg") == 0);
  assert(strcmp(data[7], "hhh") == 0);
  for (int i = 0; i < len; ++i)
    puts(data[i]);
  bunny_save_configuration(BC_DABSIC, "/dev/stdout", cnf);
  len = bunny_configuration_flexible_load
    (cnf, FLM_LOAD_FIELD | FLM_LOAD_ARRAY | FLM_LOAD_HASHMAP | FLM_KEEP_CONFIGURATION, load, (void***)&data, "Root");
  bunny_save_configuration(BC_DABSIC, "/dev/stdout", cnf);
  bunny_delete_configuration(cnf);
  return (EXIT_SUCCESS);
}
