/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#include			<unistd.h>
#include			<fcntl.h>
#include			<assert.h>
#include			<lapin.h>
#include			<string.h>
#include			<stdlib.h>
#include			<stdio.h>

int				main(void)
{
  t_bunny_configuration		*cnf;
  const char			*str;
  int				tmp;

  assert(cnf = bunny_load_configuration(BC_CSV, "./base.csv", NULL));

  assert(bunny_configuration_go_get(cnf, &tmp, "[0][0]"));
  assert(tmp == 1);
  assert(bunny_configuration_go_get(cnf, &tmp, "[0][1]"));
  assert(tmp == 2);
  assert(bunny_configuration_go_get(cnf, &tmp, "[0][2]"));
  assert(tmp == 3);

  assert(bunny_configuration_go_get(cnf, &tmp, "[1][0]"));
  assert(tmp == 4);
  // inserted 
  assert(bunny_configuration_go_get(cnf, &tmp, "[1][2]"));
  assert(tmp == 6);

  assert(bunny_configuration_go_get(cnf, &tmp, "[2][0]"));
  assert(tmp == 7);
  assert(bunny_configuration_go_get(cnf, &tmp, "[2][1]"));
  assert(tmp == 8);
  assert(bunny_configuration_go_get(cnf, &tmp, "[2][2]"));
  assert(tmp == 9);

  ///////////////////////////////////////////////////////////

  assert(bunny_configuration_go_get(cnf, &str, "[1][1][0][0]"));
  assert(*str == 'a');
  assert(bunny_configuration_go_get(cnf, &str, "[1][1][0][1]"));
  assert(*str == 'b');
  assert(bunny_configuration_go_get(cnf, &str, "[1][1][0][2]"));
  assert(*str == 'c');

  assert(bunny_configuration_go_get(cnf, &str, "[1][1][1][0]"));
  assert(*str == 'd');
  assert(bunny_configuration_go_get(cnf, &str, "[1][1][1][1]"));
  assert(*str == 'e');
  assert(bunny_configuration_go_get(cnf, &str, "[1][1][1][2]"));
  assert(*str == 'f');

  assert(bunny_configuration_go_get(cnf, &str, "[1][1][2][0]"));
  assert(*str == 'g');
  assert(bunny_configuration_go_get(cnf, &str, "[1][1][2][1]"));
  assert(*str == 'h');
  assert(bunny_configuration_go_get(cnf, &str, "[1][1][2][2]"));
  assert(*str == 'i');

  bunny_save_configuration(BC_CSV, "/dev/stdout", cnf);

  bunny_delete_configuration(cnf);
  return (EXIT_SUCCESS);
}

