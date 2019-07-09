// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_window		*bunny_begin_configuration(t_bunny_configuration	*cnf)
{
  int			style = 0;
  int			width;
  int			height;
  const char		*name;
  const char		*stl;
  int			i;

  if (bunny_configuration_getf_int(cnf, &width, "Size[0]"))
    {
      if (!bunny_configuration_getf_int(cnf, &height, "Size[1]"))
	return (NULL);
    }
  else
    {
      if (!bunny_configuration_getf_int(cnf, &width, "Width"))
	return (NULL);
      if (!bunny_configuration_getf_int(cnf, &height, "Height"))
	return (NULL);
    }

  if (!bunny_configuration_getf_string(cnf, &name, "Name"))
    name = "LibLapin";

  for (i = 0; bunny_configuration_getf_string(cnf, &stl, "Style[%d]", i); ++i)
    if (!strcmp(stl, "Simple"))
      style |= NO_BORDER;
    else if (!strcmp(stl, "Titlebar"))
      style |= TITLEBAR;
    else if (!strcmp(stl, "ResizeButton"))
      style |= RESIZE_BUTTON;
    else if (!strcmp(stl, "CloseButton"))
      style |= CLOSE_BUTTON;
    else if (!strcmp(stl, "Fullscreen"))
      style |= FULLSCREEN;
    else if (!strcmp(stl, "Default"))
      style |= DEFAULT_WIN_STYLE;
    else if (!strcmp(stl, "Antialiasing"))
      style |= ANTIALIASING;
    else
      return (NULL);
  if (i == 0)
    style = DEFAULT_WIN_STYLE;

  return (bunny_start_style(width, height, (t_bunny_window_style)style, name));
}

t_bunny_window		*bunny_begin(const char					*file)
{
  t_bunny_configuration	*cnf;

  if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  auto r = bunny_begin_configuration(cnf);
  bunny_delete_configuration(cnf);
  return (r);
}
