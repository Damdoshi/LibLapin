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

int			main(void)
{
  char			buffer[1024];
  int			pip[2];
  int			len;

  assert(pipe(pip) == 0);

  /* ****************************************************************** */
  /* Test strerror */

  assert(strcmp(bunny_strerror(-1), "Unknown error -1") == 0);
  assert(strcmp(bunny_strerror(ENOMEM), strerror(ENOMEM)) == 0);
  assert(strcmp(bunny_strerror(BE_SYNTAX_ERROR), "Syntax error") == 0);

  /* ****************************************************************** */
  /* Test perror */

  const char		*ref =
    "Syntax error\n"
    "Syntax error\n"
    "Label: Syntax error\n"
    ;
  int			outstd;

  assert((outstd = dup(2)) == 5);
  assert(close(2) == 0);
  assert(dup(pip[1]) == 2);

  bunny_errno = BE_SYNTAX_ERROR;
  bunny_perror(NULL);
  bunny_perror("");
  bunny_perror("Label");
  assert((len = read(pip[0], &buffer[0], sizeof(buffer) - 1)) != -1);
  buffer[len] = '\0';
  assert(strcmp(ref, buffer) == 0);

  assert(close(2) == 0);
  assert(dup(outstd) == 2);
  assert(close(outstd) == 0);

  /* ****************************************************************** */

  return (EXIT_SUCCESS);
}

