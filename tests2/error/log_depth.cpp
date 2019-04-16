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
#include		<time.h>
#include		<unistd.h>
#include		"private2/logs.hpp"

int			main(void)
{
  char			buffer[4096];
  int			pip[2];
  int			len;

  assert(pipe(pip) == 0);

  /* ****************************************************************** */
  /* Test depth handling log system and that LOG is dropped. */

  const char		*refall =
    "CRIT main Surface message\n"
    "  FAIL main Middle surface message\n"
    "    FAIL main Middle deep message\n"
    "      CRIT main Deeper message\n"
    ;

  bunny_set_log_verbosity((t_bunny_log_verbosity)(BLV_DISPLAY_CRITICAL | BLV_DISPLAY_FAILURE));
  assert(bunny_get_log_verbosity() == (t_bunny_log_verbosity)(BLV_DISPLAY_CRITICAL | BLV_DISPLAY_FAILURE));

  bunny_set_message_descriptors(pip[1], pip[1], pip[1]);
  assert(bunny_get_log_descriptor() == pip[1]);

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
  /* Test a lower verbosity */

  const char		*refcritical =
    "CRIT main Surface message\n"
    "  CRIT main Deeper message\n"
    ;

  bunny_set_log_verbosity(BLV_DISPLAY_CRITICAL);
  bunny_log(BLT_CRITICAL, "test", "Deeper message");
  bunny_log(BLT_FAILED, "test", "Middle deep message");
  bunny_log(BLT_FAILED, "test", "Middle surface message");
  bunny_log(BLT_LOG, "test", "This will not be stacked");
  bunny_log(BLT_CRITICAL, "test", "Surface message");
  bunny_flush();
  assert((len = read(pip[0], &buffer[0], sizeof(buffer))) != -1);
  buffer[len] = '\0';
  assert(strcmp(refcritical, &buffer[0]) == 0);

  /* ****************************************************************** */
  /* Test label log length */

  bunny_set_log_length(BLL_LABELED_LOG);
  assert(bunny_get_log_length() == BLL_LABELED_LOG);
  bunny_log(BLT_CRITICAL, "test,test2", "Labeled log");
  bunny_flush();
  assert((len = read(pip[0], &buffer[0], sizeof(buffer))) != -1);
  buffer[len] = '\0';
  assert(strcmp("CRIT main [test test2] Labeled log\n", &buffer[0]) == 0);

  /* ****************************************************************** */
  /* Test full log length */

  char			buildref[4096];

  bunny_set_log_length(BLL_FULL_LOG);
  assert(bunny_get_log_length() == BLL_FULL_LOG);
  snprintf(buildref, sizeof(buildref),
	   "CRIT main [test] %ld ./error/log_depth.cpp:92 int main() Complete log\n",
	   time(NULL));
  bunny_log(BLT_CRITICAL, "test", "Complete log"); // /!\ Pay attention to the line!
  bunny_flush();
  assert((len = read(pip[0], &buffer[0], sizeof(buffer))) != -1);
  buffer[len] = '\0';
  assert(strcmp(buildref, &buffer[0]) == 0);

  /* ****************************************************************** */
  /* Parameters */

  snprintf(buildref, sizeof(buildref),
	   "CRIT main [test] %ld ./error/log_depth.cpp:4242 "
	   "int main() parameter1 parameter2 -> return msg\n",
	   time(NULL));
  bunny::Log
    (BLV_DISPLAY_CRITICAL,
     "int main()", "main",
     BLT_CRITICAL,
     {"test"},
     "msg",
     __FILE__, 4242,
     "return", "parameter1", "parameter2"
     );
  bunny_flush();
  assert((len = read(pip[0], &buffer[0], sizeof(buffer))) != -1);
  buffer[len] = '\0';
  assert(strcmp(buildref, &buffer[0]) == 0);

  /* ****************************************************************** */
  /* Filter labels */

  const char		*reffilter =
    "FAIL main EEE\n"
    "  FAIL main CCC\n"
    "    FAIL main BBB\n"
    "      FAIL main AAA\n"
    ;

  bunny_set_log_length(BLL_SHORT_LOG);
  bunny_filter_label("aaa,bbb,ccc");
  bunny_set_message_descriptors(pip[1], pip[1], pip[1]);
  bunny_set_log_verbosity(BLV_DISPLAY_FAILURE);

  bunny_log(BLT_FAILED, "ddd", "DDD");
  bunny_log(BLT_FAILED, "aaa", "AAA");
  bunny_log(BLT_FAILED, "bbb", "BBB");
  bunny_log(BLT_FAILED, "ccc", "CCC");
  bunny_log(BLT_FAILED, "ddd,ccc", "EEE");
  bunny_flush();
  assert((len = read(pip[0], &buffer[0], sizeof(buffer))) != -1);
  buffer[len] = '\0';
  assert(strcmp(reffilter, &buffer[0]) == 0);

  /* ****************************************************************** */
  /* Test bad descriptors (or any kind of wrong call to write) and log output */

  int			errout;

  bunny_filter_label(NULL);
  bunny_set_log_length(BLL_SHORT_LOG);
  bunny_set_log_verbosity((t_bunny_log_verbosity)(BLV_DISPLAY_CRITICAL | BLV_DISPLAY_FAILURE | BLV_DISPLAY_POSTLOG | BLV_DISPLAY_PRELOG));

  // Transform pipe into stderr.
  assert((errout = dup(2)) == 5);
  assert(close(2) == 0);
  assert(dup(pip[1]) == 2);

  bunny_set_log_descriptor(42); // Bad fd
  bunny_log(BLT_LOG, "test", "Bad log descriptor."); // Will be flushed immediatly on 2
  assert((len = read(pip[0], &buffer[0], sizeof(buffer))) != -1);
  buffer[len] = '\0';
  assert(strcmp("Failed to log : LOGG main Bad log descriptor.\n", &buffer[0]) == 0);

  bunny_set_critical_descriptor(42); // Bad fd
  bunny_errno = BE_SYNTAX_ERROR;
  bunny_log(BLT_CRITICAL, "test", "");
  bunny_flush(); // Flush previous log on 2
  assert((len = read(pip[0], &buffer[0], sizeof(buffer))) != -1);
  buffer[len] = '\0';
  assert(strcmp("Failed to log : CRIT main (Error code 10001: Syntax error)\n", &buffer[0]) == 0);

  // Restore stderr
  assert(close(2) == 0);
  assert(dup(errout) == 2);
  assert(close(errout) == 0);

  /* ****************************************************************** */

  return (EXIT_SUCCESS);
}
