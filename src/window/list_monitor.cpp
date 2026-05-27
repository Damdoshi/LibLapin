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

static t_bunny_position		gl_monitor_origin = {0, 0};

/**
 * @doc
 * @doc-symbol bunny_get_monitors_origin
 * @doc-kind function
 * @doc-module window
 * @doc-order 460
 * @doc-since 13
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Returns the desktop origin of the primary monitor.
 * @description The value is updated while reading monitor information. It is useful on multi-monitor desktops where the primary monitor is not located at coordinates 0,0.
 * @return-case success A t_bunny_position containing the desktop origin of the primary monitor.
 * @see bunny_list_monitors, bunny_list_autonomous_monitors
 *
 * @doc-lang fr
 * @brief Renvoie l'origine du moniteur principal sur le bureau.
 * @description La valeur est mise à jour lors de la lecture des informations sur les moniteurs. Elle est utile sur les bureaux multi-écrans lorsque le moniteur principal n'est pas placé aux coordonnées 0,0.
 * @return-case success Une t_bunny_position contenant l'origine du moniteur principal sur le bureau.
 * @see bunny_list_monitors, bunny_list_autonomous_monitors
 */
t_bunny_position		bunny_get_monitors_origin(void)
{
  return (gl_monitor_origin);
}

static bool			get_output(char			*buf,
					   size_t		buflen,
					   const char		*cmd)
{
  FILE				*fil;
  size_t			l;

  if ((fil = popen(cmd, "r")) == NULL)
    return (false);
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
      bool			primary = false;

      if ((p = strstr(p, " connected")) == NULL)
	return (i);
      if (strncmp(p + 10, " primary", 8) == 0)
	primary = true;
      while (*p && *p != '\n' && !isdigit(*p))
	p += 1;
      if (sscanf(p, "%dx%d+%d+%d (", &siz[i].w, &siz[i].h, &siz[i].x, &siz[i].y) != 4)
	return (i);
      if (primary)
	{
	  gl_monitor_origin.x = siz[i].x;
	  gl_monitor_origin.y = siz[i].y;
	}
      if ((p = strchr(p, '\n')) == NULL)
	return (i);
      p += 1;
    }
  return (i);
}

#endif

///////////////////////// IL FAUT QUE LES ECRANS CLONEES NE SOIENT PAS MONTRES !!!!!

/**
 * @doc
 * @doc-symbol bunny_list_monitors
 * @doc-kind function
 * @doc-module window
 * @doc-order 470
 * @doc-since 13
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Lists the monitors reported by the system.
 * @description The returned static array is terminated by an area filled with zero. On Linux, the current implementation reads xrandr output. Cloned monitors may appear in this list.
 * @return-case success A pointer to a zero-terminated array of t_bunny_area.
 * @return-case failure NULL if the monitor list cannot be retrieved.
 * @see bunny_list_autonomous_monitors, bunny_get_monitors_origin
 *
 * @doc-lang fr
 * @brief Liste les moniteurs rapportés par le système.
 * @description Le tableau statique renvoyé se termine par une zone remplie avec zéro. Sous Linux, l'implémentation courante lit la sortie de xrandr. Les moniteurs clonés peuvent apparaître dans cette liste.
 * @return-case success Un pointeur vers un tableau de t_bunny_area terminé par une entrée nulle.
 * @return-case failure NULL si la liste des moniteurs ne peut pas être récupérée.
 * @see bunny_list_autonomous_monitors, bunny_get_monitors_origin
 */
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

/**
 * @doc
 * @doc-symbol bunny_list_autonomous_monitors
 * @doc-kind function
 * @doc-module window
 * @doc-order 480
 * @doc-since 13
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Lists monitors while removing cloned screen entries.
 * @description This function starts from bunny_list_monitors and keeps a single entry for monitors sharing the same desktop position. The returned array is terminated by an area filled with zero.
 * @return-case success A pointer to a zero-terminated array of autonomous monitor areas.
 * @return-case failure NULL if the monitor list cannot be retrieved.
 * @see bunny_list_monitors, bunny_single_fullscreen, bunny_all_fullscreen
 *
 * @doc-lang fr
 * @brief Liste les moniteurs en retirant les entrées d'écrans clonés.
 * @description Cette fonction part de bunny_list_monitors et conserve une seule entrée pour les moniteurs partageant la même position sur le bureau. Le tableau renvoyé est terminé par une zone remplie avec zéro.
 * @return-case success Un pointeur vers un tableau de zones de moniteurs autonomes terminé par une entrée nulle.
 * @return-case failure NULL si la liste des moniteurs ne peut pas être récupérée.
 * @see bunny_list_monitors, bunny_single_fullscreen, bunny_all_fullscreen
 */
const t_bunny_area		*bunny_list_autonomous_monitors(void)
{
  t_bunny_area			*screens = (t_bunny_area*)bunny_list_monitors();
  int				i, j, count;

  for (i = 0, count = 0; screens[i].w && screens[i].h; ++i)
    {
      // Search for previously encountered screens with the same position
      for (j = i - 1; j >= 0; --j)
	if (screens[j].x == screens[i].x && screens[j].y == screens[i].y)
	  break ;
      // If one is found, then skip it
      if (j >= 0)
	continue ;
      // If no one is found, store it.
      screens[count] = screens[i];
      count += 1;
    }
  screens[count].x = 0;
  screens[count].y = 0;
  screens[count].w = 0;
  screens[count].h = 0;
  return (screens);
}

