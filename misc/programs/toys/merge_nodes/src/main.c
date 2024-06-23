/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2022
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

int			main(void)
{
  t_bunny_configuration	*cnf;
  t_bunny_configuration	*c[3];

  assert((cnf = bunny_open_configuration("test.dab", NULL)));
  bunny_configuration_getf(cnf, &c[0], "NodeA");
  bunny_configuration_getf(cnf, &c[1], "NodeB");
  bunny_configuration_getf(cnf, &c[2], "NodeC");
  bunny_configuration_merge(2, c[0], c[1], c[2]);
  bunny_save_configuration(BC_DABSIC, "/dev/stdout", cnf);
  return (0);
}

