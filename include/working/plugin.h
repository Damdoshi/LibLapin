/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file plugin.h
** The plugin module allows you to load dynamic libraries
** design with a specific fashion, imposed by the bunny plugin.
**
** /!\ DOES NOT WORK YET /!\
**
*/

#ifndef				__LAPIN_PLUGIN_H__
# define			__LAPIN_PLUGIN_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<stdarg.h>

typedef enum			e_bunny_value_type
  {
    VOID			= 'v', 
    INTEGER			= 'i', /* int64_t */
    DOUBLE			= 'd',
    STRING			= 's', /* const char * */
    POINTER			= 'p'  /* void * */
  }				t_bunny_value_type;

typedef union			u_bunny_value
{
  ssize_t			integer;
  const char			*string;
  void				*any;
#if				defined(__LP64__) || defined(_WIN64)
  double			real;
#else
  float				real;
#endif
}				t_bunny_value;

typedef struct			s_bunny_prototype
{
  const char *			name;
  const void *			function_ptr;
  t_bunny_value_type		return_value;
  size_t			nbrparam;
  t_bunny_value_type		parameters[2];
}				t_bunny_prototype;

typedef const t_bunny_prototype	*(*t_bunny_get_function_list)(void);

typedef struct			s_bunny_plugin
{
  const char * const		name;
  const void * const		library_handler;
  const size_t			nbr_functions;
# ifndef			__ANSI__
  const t_bunny_prototype	prototypes[0];
# else
  const t_bunny_prototype	prototypes[1];
# endif
}				t_bunny_plugin;

t_bunny_plugin			*bunny_new_plugin(const char			*libfile);
void				bunny_delete_plugin(t_bunny_plugin		*plugin);

void				*bunny_plugin_get_function(const t_bunny_plugin	*plugin,
							   const char		*funcname);

bool				bunny_plugin_call(t_bunny_plugin		*plugin,
						  const char			*funcname,
						  t_bunny_value			*return_value,
						  size_t			arrlen,
						  t_bunny_value			*val);

bool				bunny_plugin_callv(t_bunny_plugin		*plugin,
						   const char			*func,
						   t_bunny_value		*return_value,
						   ...);

#endif	/*			__LAPIN_PLUGIN_H__	*/
