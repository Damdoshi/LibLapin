// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<sys/stat.h>
#include		"lapin_private.h"

bool			bunny_file_exists(const char		*file)
{
  return (access(file, F_OK) == 0);
}

