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
  assert(strcmp(bunny_strerror(-1), "Unknown error -1") == 0);
  assert(strcmp(bunny_strerror(ENOMEM), strerror(ENOMEM)) == 0);
  assert(strcmp(bunny_strerror(BE_SYNTAX_ERROR), "Syntax error") == 0);
  return (EXIT_SUCCESS);
}

