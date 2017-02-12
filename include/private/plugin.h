/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_PLUGIN_H__
# define			__LAPIN_PRIVATE_PLUGIN_H__

struct				bunny_plugin
{
  void				*handler;
  size_t			nbr_functions;
  t_bunny_extern_function	functions[0];
};

#endif	/*			__LAPIN_PRIVATE_PLUGIN_H__	*/
