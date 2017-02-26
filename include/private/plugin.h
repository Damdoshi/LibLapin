/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_PLUGIN_H__
# define			__LAPIN_PRIVATE_PLUGIN_H__

typedef struct			s_bunny_buttplug
{
   char				*name;
   void				*library_handler;
   size_t			nbr_function;
# ifndef			__ANSI__
   t_bunny_prototype		prototypes[0];
# else
   t_bunny_prototype		prototypes[1];
# endif
}				t_bunny_buttplug;


#endif	/*			__LAPIN_PRIVATE_PLUGIN_H__	*/
