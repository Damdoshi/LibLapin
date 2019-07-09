// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_parallax	*bunny_load_parallax(const char		*file)
{
  t_bunny_configuration	*cnf;

  if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  auto p = bunny_read_parallax(cnf);
  bunny_delete_configuration(cnf);
  return (p);
}

t_bunny_parallax	*bunny_load_parallax_wh(const char	*file,
						unsigned int	width,
						unsigned int	height)
{
  t_bunny_configuration	*cnf;

  if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  auto p = bunny_read_parallax_wh(cnf, width, height);
  bunny_delete_configuration(cnf);
  return (p);
}

