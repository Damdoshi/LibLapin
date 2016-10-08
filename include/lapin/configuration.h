/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file configuration.h

*/

#ifndef				__LAPIN_CONFIGURATION_H__
# define			__LAPIN_CONFIGURATION_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<stdarg.h>

typedef enum			e_bunny_configuration_type
  {
    BC_INI,
    BC_DABSIC,
    BC_XML,
    BC_LUA,
    BC_CRUNCH,			/* binary file format */
    BC_CARROT_SQL,
    BC_CUSTOM
  }				t_bunny_configuration_type;

typedef struct			s_bunny_configuration
{
  const char			_private[6 * sizeof(size_t)];
  const char * const		name;
  const char * const		value;
}				t_bunny_configuration;

/*!
** Depending of the type, may takes parameters (sql... logins)
**
*/
t_bunny_configuration		*bunny_new_configuration(t_bunny_configuration_type	type,
							 ...);
t_bunny_configuration		*bunny_load_configuration(t_bunny_configuration_type	type,
							  t_bunny_configuration		*config,
							  bool				overwrite,
							  ...);
typedef t_bunny_configuration	*(*t_bunny_my_load_configuration)(t_bunny_configuration_type t,
								  t_bunny_configuration	*config,
								  bool			overwrite,
								  va_list		params);
extern
t_bunny_my_load_configuration	gl_bunny_my_load_configuration;

bool				bunny_save_configuration(t_bunny_configuration_type	type,
							 t_bunny_configuration		*config,
							 ...);
typedef t_bunny_configuration	(*t_bunny_my_save_configuration)(t_bunny_configuration_type t,
								 t_bunny_configuration	*config,
								 va_list		params);
extern
t_bunny_my_save_configuration	gl_bunny_my_save_configuration;


void				bunny_delete_configuration(t_bunny_configuration	*config);

extern const char		bunny_root;
extern const char		bunny_parent;

t_bunny_configuration		*bunny_configuration_get_node(t_bunny_configuration	*config,
							      const char		*addr);

bool				bunny_configuration_set_value(t_bunny_configuration	*config,
							      const char		*addr,
							      const char		*value);
# define			bunny_configuration_remove_value(cnf, addr) \
  bunny_configuration_set_value(cnf, addr, NULL)

t_bunny_configuration		*bunny_configuration_first(t_bunny_configuration	*config);

t_bunny_configuration		*bunny_configuration_next(t_bunny_configuration		*config);

# define			bunny_configuration_end(config)				NULL

#endif	/*			__LAPIN_CONFIGURATION_H__	*/
