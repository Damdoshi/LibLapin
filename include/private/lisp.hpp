/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_PRIVATE_LISP_HPP__
# define		__LAPIN_PRIVATE_LISP_HPP__

t_bunny_configuration	*_bunny_read_lisp(const char			*code,
					  t_bunny_configuration		*config);
char			*_bunny_write_lisp(const t_bunny_configuration	*config);

#endif	/*		__LAPIN_PRIVATE_LISP_HPP__			*/
