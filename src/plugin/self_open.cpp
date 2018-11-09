// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			*bunny_plugin_self_open(void)
{
  static bool		opened = false;
  static void		*self_handler;

  if (opened == false)
    {
      if ((self_handler = dlopen(NULL, RTLD_NOW)) == NULL)
	return (NULL);
      opened = true;
    }
  return (self_handler);
}

void			*bunny_plugin_get_self_function(const char	*n)
{
  void			*x = bunny_plugin_self_open();

  if (!x)
    return (x);
  return (dlsym(x, n));
}

