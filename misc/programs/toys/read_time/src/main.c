
/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

int			main(void)
{
  t_bunny_configuration	*cnf;
  double		res;

  if ((cnf = bunny_open_configuration("time.dab", NULL)) == NULL)
    goto End;
  bunny_save_configuration(BC_DABSIC, "/dev/stdout", cnf);
  if (bunny_configuration_read_time(cnf, "Seconds", &res) == false)
    goto End;
  assert(res - 4.2 < 0.01);
  if (bunny_configuration_read_time(cnf, "Minutes", &res) == false)
    goto End;
  assert(res - (60 + 4.2) < 0.01);
  if (bunny_configuration_read_time(cnf, "Hours", &res) == false)
    goto End;
  assert(res - (90 * 60 + 4.2) < 0.01);
  bunny_printl("Success\n");
  return (EXIT_SUCCESS);
 End:
  bunny_perror(NULL);
  return (EXIT_FAILURE);
}

