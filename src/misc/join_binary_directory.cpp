// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include	<string.h>
#include	<libgen.h>
#include	"lapin_private.h"

#ifdef		__GNUC__
# include	<unistd.h>
# define	change_directory	chdir
#else
# define	change_directory	_chdir
#endif

bool		bunny_join_binary_directory(const char	*argv0)
{
  char		buf[strlen(argv0) + 1];
  char		*dir;

  memcpy(&buf[0], argv0, sizeof(buf));
  dir = dirname(&buf[0]);

  return (change_directory(dir) != -1);
}
