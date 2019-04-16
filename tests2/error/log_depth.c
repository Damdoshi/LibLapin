/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** LibLapin 2
*/

#include		<assert.h>
#include		<lapin2.h>
#include		<stdio.h>
#include		<stdlib.h>
#include		<string.h>
#include		<unistd.h>

int			main(void)
{
  char			buffer[4096];
  int			pip[2];
  int			len;

  assert(pipe(pip) == 0);

  /* ****************************************************************** */

  const char		*refall =
    "CRIT main Surface message\n"
    "  FAIL main Middle surface message\n"
    "    FAIL main Middle deep message\n"
    "      CRIT main Deeper message\n"
    ;

  bunny_set_log_verbosity(BLV_DISPLAY_CRITICAL | BLV_DISPLAY_FAILURE);
  bunny_set_message_descriptors(pip[1], pip[1], pip[1]);

  bunny_log(BLT_CRITICAL, "test", "Deeper message");
  bunny_log(BLT_FAILED, "test", "Middle deep message");
  bunny_log(BLT_FAILED, "test", "Middle surface message");
  bunny_log(BLT_LOG, "test", "This will not be stacked");
  bunny_log(BLT_CRITICAL, "test", "Surface message");
  bunny_flush();

  assert((len = read(pip[0], &buffer[0], sizeof(buffer))) != -1);
  buffer[len] = '\0';
  assert(strcmp(refall, &buffer[0]) == 0);

  /* ****************************************************************** */

  const char		*refcritical =
    "CRIT main Surface message\n"
    "  CRIT main Deeper message\n"
    ;

  bunny_set_log_verbosity(BLV_DISPLAY_CRITICAL);
  bunny_log(BLT_CRITICAL, "test", "Deeper message");
  bunny_log(BLT_FAILED, "test", "Middle deep message");
  bunny_log(BLT_FAILED, "test", "Middle surface message");
  bunny_log(BLT_FAILED, "test", "This will not be stacked");
  bunny_log(BLT_CRITICAL, "test", "Surface message");
  bunny_flush();
  assert((len = read(pip[0], &buffer[0], sizeof(buffer))) != -1);
  buffer[len] = '\0';
  assert(strcmp(refcritical, &buffer[0]) == 0);

  /* ****************************************************************** */

  return (EXIT_SUCCESS);
}
