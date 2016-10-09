// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			<alloca.h>
#include			"lapin_private.h"

bool				bunny_fill_default_key(const char	*bunny_prog)
{
  const t_bunny_key		*def = bunny_default_key();
  int32_t			buflen = def->length + sizeof(def->length);
  char				*file;
  size_t			siz;
  size_t			i;
  int				fd;
  
  if ((file = bunny_load_file(bunny_prog, &siz)) == NULL)
    return (false);
  for (i = 0; i < siz - buflen; ++i)
    if (memcmp(file, def, buflen) == 0)
      {
	if ((fd = open(bunny_prog, O_WRONLY)) == -1)
	  {
	    bunny_free(file);
	    return (false);
	  }
	lseek(fd, i, SEEK_SET);
	if (write(fd, def, buflen) != buflen)
	  {
	    close(fd);
	    bunny_free(file);
	    return (false);
	  }
	close(fd);
	bunny_free(file);
	return (true);
      }
  bunny_free(file);
  return (false);
}

