/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<lapin.h>

static bool		load_save_test(const char		*original,
				       const char		*dump1,
				       const char		*dump2)
{
  char			buffer[256];
  t_bunny_ini		*ini;
  size_t		i;

  snprintf(&buffer[0], sizeof(buffer), "diff %s %s", dump1, dump2);
  if ((ini = bunny_load_ini(original)) == NULL)
    return (false);
  for (i = 0; i < 10; ++i)
    if (i % 2 == 0)
      {
	bunny_save_ini(ini, dump2);
	bunny_delete_ini(ini);
	if ((ini = bunny_load_ini(dump2)) == NULL)
	  return (false);
      }
    else
      {
	bunny_save_ini(ini, dump1);
	bunny_delete_ini(ini);
	if ((ini = bunny_load_ini(dump1)) == NULL)
	  return (false);
	if (system(&buffer[0]) != 0)
	  return (false);
	fprintf(stderr, "Round %zu ok.\n", i / 2);
      }
  bunny_delete_ini(ini);
  return (true);
}

int			main(void)
{
  const char		*file = "./file.ini";
  t_bunny_ini		*ini;

  fprintf(stderr, "Trying to load and reload the same file and check consistancy.\n");
  assert(load_save_test(file, "./tmp1.ini~", "./tmp2.ini~"));
  system("rm *~");
  assert(ini = bunny_load_ini(file));
  assert(bunny_save_ini(ini, "/dev/stdout"));
  assert(strcmp("Damdoshi", bunny_ini_get_field(ini, DEFAULT_SCOPE, "Name", 0)) == 0);
  assert(strcmp("Jason", bunny_ini_get_field(ini, DEFAULT_SCOPE, "Name", 1)) == 0);
  assert(strcmp("C", bunny_ini_get_field(ini, "Mental", "Language", 1)) == 0);
  assert(strcmp("Fat", bunny_ini_get_field(ini, "Body", "Status", 0)) == 0);
  assert(bunny_ini_get_field(ini, "Body", "Status", 42) == NULL);
  bunny_delete_configuration(ini);
  return (EXIT_SUCCESS);
}

