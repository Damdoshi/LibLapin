// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			<fcntl.h>
#include			<alloca.h>
#include			<string.h>
#include			"lapin_private.h"

bool				bunny_fill_default_key(const char	*bunny_prog,
						       t_bunny_cipher_key *key)
{
  int32_t			buflen;
  const t_bunny_cipher_key	*def;
  char				*file;
  size_t			siz;
  size_t			i;
  int				fd;

  if (key == NULL)
    def = bunny_default_key();
  else
    def = key;
  buflen = def->length + sizeof(def->length);
  if (bunny_load_file(bunny_prog, &file, &siz) == false)
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

