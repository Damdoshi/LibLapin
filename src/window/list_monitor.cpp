// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include			"lapin_private.h"
#if				_WIN32 || __WIN32__
# define			popen				_popen
# define			command				\
  ""
#else
# define			command				\
  "xrandr | grep '^Screen'"
#endif

static bool			get_output(char			*buf,
					   size_t		buflen,
					   const char		*cmd)
{
  FILE				*fil;
  size_t			l;

  if ((fil = popen(cmd, "r")) == NULL)
    return (NULL);
  l = 0;
  do
    {
      l += fread(&buf[l], 1, buflen - l - 1, fil);
      if (ferror(fil))
	{
	  pclose(fil);
	  return (false);
	}
    }
  while (feof(fil) == 0 && l < buflen - 1);
  buf[l] = '\0';
  return (true);
}

#if				_WIN32 || __WIN32__

size_t				read_output(const char		*str,
					    t_bunny_size	*siz,
					    size_t		len)
{
  (void)str;
  (void)siz;
  (void)len;
  return (0);
}

#else

size_t				read_output(const char		*str,
					    t_bunny_size	*siz,
					    size_t		len)
{
  const char			*p;
  size_t			i;

  for (i = 0, p = str; i < len; ++i)
    {
      if ((p = strstr(p, "current")) == NULL)
	return (i);
      if (sscanf(p, "current %d x %d,", &siz[i].x, &siz[i].y) != 2)
	return (i);
      if ((p = strchr(p, '\n')) == NULL)
	return (i);
      p += 1;
    }
  return (i);
}

#endif

const t_bunny_size		*bunny_list_monitors(void)
{
  static t_bunny_size		siz[16]; // Does not support more than 16 monitors
  char				buf[1024 * 32];
  size_t			last;

  if (get_output(&buf[0], sizeof(buf), command) == false)
    return (NULL);
  last = read_output(&buf[0], &siz[0], sizeof(siz) - 1);
  siz[last].x = siz[last].y = 0;
  return (&siz[0]);
}
