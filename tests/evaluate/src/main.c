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

int			main(void)
{
  t_bunny_configuration	*cnf;
  double		dec;
  const char		*str;

  assert(cnf = bunny_load_configuration(BC_INI, "./simple.ini", NULL));
  assert(bunny_configuration_go_get(cnf, &str, "Operation"));
  dec = bunny_evaluate(str, cnf);
  assert(!isnan(dec));
  assert(dec - 12 < 0.1);
  printf("I confirme that : %s\nWith the following environment:\n", str);
  bunny_delete_node(cnf, "Operation");
  bunny_save_configuration(BC_INI, "/dev/stdout", cnf);
  printf("Is equal to %f.", dec);

  printf("Fully done!\n");
  return (EXIT_SUCCESS);
}

