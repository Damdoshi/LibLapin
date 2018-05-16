/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_PLUGIN_H__
# define			__LAPIN_PRIVATE_PLUGIN_H__
# if				_WIN32 || __WIN32__
#  include			<Windows.h>
# else
#  include			<dlfcn.h>
# endif

typedef struct			s_bunny_buttplug
{
  char				*name;
  void				*library_handler;
  size_t			nbr_function;
  t_bunny_prototype		prototypes[__ZERO_LENGTH__];
}				t_bunny_buttplug;

#endif	/*			__LAPIN_PRIVATE_PLUGIN_H__	*/
