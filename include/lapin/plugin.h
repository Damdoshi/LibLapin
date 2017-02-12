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
    BVT_INTEGER			= 'i',
    BVT_REAL			= 'r',
    BVT_POINTER			= 'p'
  }				t_bunny_value_type;

typedef union			u_bunny_value
{
  ssize_t			integer;
  double			real;
  void				*data;
}				t_bunny_value;

/*!
** The type of function that must be written in plugins to be callable
** by bunny_call* functions.
** Of course, you can get other functions, but it won't bind automaticaly
** with the configuration module.
*/
typedef t_bunny_value		(*t_bunny_plugged_function)(size_t		n,
							    t_bunny_value	*p);


typedef struct			s_bunny_extern_function
{
  const char * const		name;
  const char * const		parameters;
  const char			return_value;
  const t_bunny_plugged_function fptr;
}				t_bunny_extern_function;

typedef struct			s_bunny_plugin
{
  void * const			handler;
  const size_t			nbr_functions;
# ifndef			__ANSI__
  t_bunny_extern_function	functions[0];
# else
  t_bunny_extern_function	functions[1];
# endif
}				t_bunny_plugin;

typedef t_bunny_extern_function	*(*t_bunny_list_plugin_function)(size_t	*nbr_func);

t_bunny_plugin			*bunny_new_plugin(const char		*dyn_lib);
void				bunny_delete_plugin(t_bunny_plugin	*plugin);

void				*bunny_plugin_get_function(t_bunny_plugin *plugin,
							   const char	*str);

bool				bunny_vcall(t_bunny_plugin		*plugin,
					    const char			*func,
					    const char			*param,
					    t_bunny_value		*out,
					    ...);

bool				bunny_call(t_bunny_plugin		*plugin,
					   const char			*func,
					   const char			*paramdesc,
					   t_bunny_value		*out,
					   t_bunny_value		*param);

// array instead of ... ?

#endif	/*			__LAPIN_PLUGIN_H__	*/
