// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			<fcntl.h>
#include			<string.h>
#include			"lapin_private.h"

#define				PATTERN		"%s program, %p key -> %s"

bool				bunny_fill_default_key(const char	*bunny_prog,
						       const t_bunny_cipher_key *key)
{
  int32_t			buflen;
  const t_bunny_cipher_key	*def;
  char				*file;
  size_t			siz;
  size_t			i;
  int				fd;

  def = bunny_default_key();
  buflen = def->length + sizeof(def->length);

  if (bunny_load_file(bunny_prog, (void**)&file, &siz) == false)
    scream_error_if(return (false), bunny_errno, PATTERN, "security", bunny_prog, key, "false");
  for (i = 0; i < siz - buflen; ++i)
    if (memcmp(file, def, buflen) == 0)
      {
	if ((fd = open(bunny_prog, O_WRONLY)) == -1)
	  {
	    i = errno;
	    bunny_delete_file(file, bunny_prog);
	    scream_error_if(return (false), i, PATTERN, "security", bunny_prog, key, "false");
	  }
	lseek(fd, i, SEEK_SET);
	if (write(fd, key, key->length + sizeof(key->length)) != buflen)
	  {
	    i = errno;
	    close(fd);
	    bunny_free(file);
	    scream_error_if(return (false), i, PATTERN, "security", bunny_prog, key, "false");
	  }
	close(fd);
	bunny_delete_file(file, bunny_prog);
	scream_log_if(PATTERN, "security", bunny_prog, key, "true");
	return (true);
      }
  bunny_delete_file(file, bunny_prog);
  scream_error_if(return (false), BE_CANNOT_FIND_EMBEDDED_KEY, PATTERN, "security", bunny_prog, key, "false");
  return (false);
}

