// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<fcntl.h>
#include		"lapin_private.h"

#define			PATTERN		"%s file, %p data, %zu data length -> %s"

bool			bunny_save_file(const char		*file,
					const void		*data,
					size_t			len)
{
  int			fd;

  if ((fd = open(file, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, 0644)) == -1)
    scream_error_if(return (false), bunny_errno, PATTERN, "ressource,file", file, data, len, "false");
#warning Does adding O_BINARY allow to compare against sk on mingw again?
  if (write(fd, data, len) == -1)
    {
      close(fd);
      scream_error_if(return (false), bunny_errno, PATTERN, "ressource,file", file, data, len, "false");
    }
  close(fd);
  scream_log_if(PATTERN, "ressource,file", file, data, len, "true");
  return (true);
}

