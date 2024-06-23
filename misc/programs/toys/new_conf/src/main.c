/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<string.h>
#include		<lapin.h>

int			main(void)
{
  t_bunny_configuration	*cnf = bunny_open_configuration("./file.dab", NULL);
  t_bunny_configuration *prv;
  double doubl;
  int integer;
  const char *string;

  assert(cnf);

  bunny_configuration_create_mode(true);

  assert(bunny_configuration_getf(cnf, &prv, "Source"));
  assert(bunny_configuration_setf(cnf, prv, "Destination"));

  assert(bunny_configuration_setf(cnf, 42, "Scope42.Field42[%d]", 0));
  assert(bunny_configuration_setf(cnf, "42", "Scope42.Field42[%d]", 1));
  assert(bunny_configuration_setf(cnf, 0.42, "Scope42.Field42[%d]", 2));

  assert(bunny_configuration_setf(cnf, "The", "%s.%s", "The", "Scope"));

  assert(bunny_configuration_getf(cnf, &integer, "Integer"));
  assert(bunny_configuration_getf(cnf, &doubl, "Double"));
  assert(bunny_configuration_getf(cnf, &string, "String"));

  assert(integer == 128);
  assert(doubl - 75.5 < 0.1);
  assert(strcmp(string, "This is the string") == 0);

  assert(bunny_configuration_getf(cnf, &string, "BadField") == false);

  bunny_save_configuration(BC_DABSIC, "/dev/stdout", cnf);

  bunny_delete_configuration(cnf);
  return (EXIT_SUCCESS);
}

