// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static int		get_style(t_bunny_configuration				*cnf)
{
  const char		*stl;
  int			style = 0;
  int			i;

  for (i = 0; bunny_configuration_getf_string(cnf, &stl, "Style[%d]", i); ++i)
    {
      if (!bunny_strcasecmp(stl, "Simple"))
	style |= NO_BORDER;
      else if (!bunny_strcasecmp(stl, "Titlebar"))
	style |= TITLEBAR;
      else if (!bunny_strcasecmp(stl, "ResizeButton"))
	style |= RESIZE_BUTTON;
      else if (!bunny_strcasecmp(stl, "CloseButton"))
	style |= CLOSE_BUTTON;
      else if (!bunny_strcasecmp(stl, "Fullscreen"))
	style |= FULLSCREEN;
      else if (!bunny_strcasecmp(stl, "Default"))
	style |= DEFAULT_WIN_STYLE;
      else if (!bunny_strcasecmp(stl, "Antialiasing"))
	style |= ANTIALIASING;
      else
	return (-2);
    }
  if (i == 0)
    return (-1);
  return (style);
}

static t_bunny_window	**mono_fullscreen(t_bunny_configuration			*cnf)
{
  const char		*name;
  t_bunny_window	**wins;

  if (!bunny_configuration_getf_string(cnf, &name, "Name"))
    name = "LibLapin";
  if ((wins = (t_bunny_window**)bunny_malloc(sizeof(*wins) * 2)) == NULL)
    return (NULL);
  if ((wins[0] = bunny_single_fullscreen(name)) == NULL)
    {
      bunny_free(wins);
      return (NULL);
    }
  wins[1] = NULL;
  return (wins);
}

static t_bunny_window	**full_fullscreen(t_bunny_configuration			*cnf)
{
  const char		*name;

  if (!bunny_configuration_getf_string(cnf, &name, "Name"))
      name = "LibLapin";
  return (bunny_all_fullscreen(name));
}

static t_bunny_window	*open_single_window(t_bunny_configuration		*cnf,
					    t_bunny_configuration		*root)
{
  int			style = 0;
  t_bunny_position	size;
  const char		*name;

  if (bunny_position_configuration("Size", &size, cnf) != BD_OK)
    if (bunny_position_configuration("Size", &size, root) != BD_OK)
      if (bunny_configuration_getf_int(cnf, &size.x, "Width") == false ||
	  bunny_configuration_getf_int(cnf, &size.y, "Height") == false)
	return (NULL);
  if (!bunny_configuration_getf_string(cnf, &name, "Name"))
    if (!bunny_configuration_getf_string(root, &name, "Name"))
      name = "LibLapin";

  if ((style = get_style(cnf)) == -2)
    return (NULL);
  if (style == -1)
    if ((style = get_style(root)) == -2)
      return (NULL);
  if (style == -1)
    style = DEFAULT_WIN_STYLE;

  t_bunny_window	*win;
  t_bunny_position	position;

  if ((win = bunny_start_style(size.x, size.y, (t_bunny_window_style)style, name)) == NULL)
    return (NULL);
  if (bunny_position_configuration("Position", &position, cnf) == BD_OK ||
      bunny_position_configuration("Position", &position, root) == BD_OK)
    bunny_move_window(win, position);
  return (win);
}

/**
 * @doc
 * @doc-symbol bunny_begin_configuration
 * @doc-kind function
 * @doc-module window
 * @doc-order 420
 * @doc-since 13
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Opens windows described by a configuration node.
 * @description The configuration may describe a single window directly or a Windows node containing several window descriptions. Shared properties can be placed at the root and overridden by each window node.
 * @param cnf The configuration node describing the window or windows to open.
 * @return-case success A NULL-terminated array of opened t_bunny_window pointers.
 * @return-case failure NULL if the configuration is invalid or if a window cannot be opened.
 * @see bunny_begin, bunny_beginc, bunny_end
 *
 * @doc-lang fr
 * @brief Ouvre les fenêtres décrites par un noeud de configuration.
 * @description La configuration peut décrire directement une fenêtre unique ou un noeud Windows contenant plusieurs descriptions de fenêtres. Les propriétés partagées peuvent être placées à la racine et surchargées par chaque noeud de fenêtre.
 * @param cnf Le noeud de configuration décrivant la ou les fenêtres à ouvrir.
 * @return-case success Un tableau terminé par NULL de pointeurs vers les t_bunny_window ouvertes.
 * @return-case failure NULL si la configuration est invalide ou si une fenêtre ne peut pas être ouverte.
 * @see bunny_begin, bunny_beginc, bunny_end
 */
t_bunny_window		**bunny_begin_configuration(t_bunny_configuration	*cnf)
{
  t_bunny_window	**wins;
  t_bunny_configuration	*root = cnf;
  t_bunny_configuration	*sub;
  int			len;
  int			i;

  if (bunny_configuration_getf_int(cnf, NULL, "Size[0]") ||
      bunny_configuration_getf_int(cnf, NULL, "Width"))
    {
      if ((wins = (t_bunny_window**)bunny_malloc(sizeof(*wins) * 2)) == NULL)
	return (NULL);
      wins[1] = NULL;
      if ((wins[0] = open_single_window(cnf, root)) == NULL)
	goto FreeWindows;
      return (wins);
    }
  if (!bunny_configuration_getf_node(cnf, &sub, "Windows"))
    sub = cnf;
  if ((len = bunny_configuration_casesf(sub, ".")) <= 0)
    return (NULL);
  if ((wins = (t_bunny_window**)bunny_malloc(sizeof(*wins) * (len + 1))) == NULL)
    return (NULL);
  wins[len] = NULL;
  for (i = 0; i < len; ++i)
    {
      wins[i] = NULL;
      if (!bunny_configuration_getf_node(sub, &cnf, "[%d]", i))
	goto FreeWindows;
      if ((wins[i] = open_single_window(cnf, root)) == NULL)
	goto FreeWindows;
    }
  return (wins);
 FreeWindows:
  for (i = 0; wins[i]; ++i)
    bunny_stop(wins[i]);
  bunny_free(wins);
  return (NULL);
}

/**
 * @doc
 * @doc-symbol bunny_beginc
 * @doc-kind function
 * @doc-module window
 * @doc-order 410
 * @doc-since 13
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Opens windows from a configuration file and returns their count.
 * @description This function loads a configuration file, opens windows from it and optionally writes the number of created windows into nbr_win. It supports regular window lists and fullscreen helper modes.
 * @param file The configuration file to load.
 * @param nbr_win If not NULL, receives the number of opened windows.
 * @return-case success A NULL-terminated array of opened t_bunny_window pointers.
 * @return-case failure NULL if the configuration file cannot be loaded, is invalid, or if a window cannot be opened.
 * @see bunny_begin, bunny_begin_configuration, bunny_end
 *
 * @doc-lang fr
 * @brief Ouvre des fenêtres depuis un fichier de configuration et renvoie leur nombre.
 * @description Cette fonction charge un fichier de configuration, ouvre les fenêtres décrites et écrit éventuellement le nombre de fenêtres créées dans nbr_win. Elle supporte les listes de fenêtres classiques et les modes utilitaires plein écran.
 * @param file Le fichier de configuration à charger.
 * @param nbr_win Si ce paramètre n'est pas NULL, reçoit le nombre de fenêtres ouvertes.
 * @return-case success Un tableau terminé par NULL de pointeurs vers les t_bunny_window ouvertes.
 * @return-case failure NULL si le fichier de configuration ne peut pas être chargé, s'il est invalide ou si une fenêtre ne peut pas être ouverte.
 * @see bunny_begin, bunny_begin_configuration, bunny_end
 */
t_bunny_window		**bunny_beginc(const char			*file,
				       size_t				*nbr)
{
  t_bunny_configuration	*cnf;
  const char		*str;

  if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  t_bunny_window	**r;

  if (bunny_configuration_getf_string(cnf, &str, "Mode"))
    {
      if (bunny_strcasecmp(str, "Fullscreen") == 0 ||
	  bunny_strcasecmp(str, "MonoFullscreen") == 0)
	r = mono_fullscreen(cnf);
      else if (bunny_strcasecmp(str, "AllFullscreen") == 0)
	r = full_fullscreen(cnf);
      else
	r = NULL;
    }
  else
    r = bunny_begin_configuration(cnf);
  bunny_delete_configuration(cnf);
  if (nbr && r)
    for (*nbr = 0; r[*nbr] != NULL; ++(*nbr));
  return (r);
}

/**
 * @doc
 * @doc-symbol bunny_begin
 * @doc-kind function
 * @doc-module window
 * @doc-order 400
 * @doc-since 13
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Opens windows from a configuration file.
 * @description This helper calls bunny_beginc without requesting the number of opened windows.
 * @param file The configuration file to load.
 * @return-case success A NULL-terminated array of opened t_bunny_window pointers.
 * @return-case failure NULL if the configuration file cannot be loaded, is invalid, or if a window cannot be opened.
 * @see bunny_beginc, bunny_begin_configuration, bunny_end
 *
 * @doc-lang fr
 * @brief Ouvre des fenêtres depuis un fichier de configuration.
 * @description Cet utilitaire appelle bunny_beginc sans demander le nombre de fenêtres ouvertes.
 * @param file Le fichier de configuration à charger.
 * @return-case success Un tableau terminé par NULL de pointeurs vers les t_bunny_window ouvertes.
 * @return-case failure NULL si le fichier de configuration ne peut pas être chargé, s'il est invalide ou si une fenêtre ne peut pas être ouverte.
 * @see bunny_beginc, bunny_begin_configuration, bunny_end
 */
t_bunny_window			**bunny_begin(const char			*cnf)
{
  return (bunny_beginc(cnf, NULL));
}
