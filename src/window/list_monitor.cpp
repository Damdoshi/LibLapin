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
  "xrandr | grep ' connected'"
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

/*
HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
MONITORINFO info;
info.cbSize = sizeof(MONITORINFO);
GetMonitorInfo(monitor, &info);
int monitor_width = info.rcMonitor.right - info.rcMonitor.left;
int monitor_height = info.rcMonitor.bottom - info.rcMonitor.top;
*/

static size_t			read_output(const char		*str,
					    t_bunny_area	*siz,
					    size_t		len)
{
  (void)str;
  (void)siz;
  (void)len;
  return (0);
}

#else

static size_t			read_output(const char		*str,
					    t_bunny_area	*siz,
					    size_t		len)
{
  const char			*p;
  size_t			i;

  for (i = 0, p = str; i < len; ++i)
    {
      if ((p = strstr(p, " connected")) == NULL)
	return (i);
      while (*p && *p != '\n' && !isdigit(*p))
	p += 1;
      if (sscanf(p, "%dx%d+%d+%d (", &siz[i].w, &siz[i].h, &siz[i].x, &siz[i].y) != 4)
	return (i);
      if ((p = strchr(p, '\n')) == NULL)
	return (i);
      p += 1;
    }
  return (i);
}

#endif

const t_bunny_area		*bunny_list_monitors(void)
{
  static t_bunny_area		siz[16]; // Does not support more than 15 monitors
  char				buf[1024 * 32];
  size_t			last;

  if (get_output(&buf[0], sizeof(buf), command) == false)
    return (NULL);
  last = read_output(&buf[0], &siz[0], NBRCELL(siz) - 1);
  siz[last].x = siz[last].y = siz[last].w = siz[last].h = 0;
  return (&siz[0]);
}
