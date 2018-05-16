o/*
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
*/

#ifndef				__LAPIN_PLUGIN_H__
# define			__LAPIN_PLUGIN_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<stdarg.h>

/*!
** This enumeration is associated to the t_bunny_value union
** to indicates in which way it is exploited.
** If the t_bunny_value_type aside the t_bunny_value is INTEGER,
** then the read union field must be the integer one.
*/
typedef enum			e_bunny_value_type
  {
    BVT_VOID			= 'v',
    BVT_INTEGER			= 'i', /* int64_t */
    BVT_DOUBLE			= 'd',
    BVT_STRING			= 's', /* const char * */
    BVT_POINTER			= 'p'  /* void * */
  }				t_bunny_value_type;

/*!
** This union can contains different types and is used
** to store parameter or return value of called functions
** from bunny_plugin.
*/
typedef union			u_bunny_value
{
  int64_t			integer;
  const char			*string;
  void				*any;
  double			real;
}				t_bunny_value;

/*!
** This structure represents a function prototype.
** Having the complete description of the function as available data
** allow script from the outside of the program to manipulate
** represented functions.
** The name field here is the name of the function.
** The function_ptr field here is the real pointer to function.
** The return_value field indicates the type of the value that
** will be returned by the function.
** The nbrparam say how any parameters the function needs.
** The parameters field describe the type of parameters of the
** function.
*/
typedef struct			s_bunny_prototype
{
  const char *			name;
  const void *			function_ptr;
  t_bunny_value_type		return_value;
  size_t			nbrparam;
  t_bunny_value_type		parameters[__ZERO_LENGTH__];
}				t_bunny_prototype;

/*!
** This typedef have the type of the listing function that every
** bunny_plugin must have: the current module will call this function
** to get a complete list of t_bunny_prototype and make all describded
** functions available to the main program.
** Note that unlist functions can be retrieve with the bunny_get_function
** function but you will have to manage them by yourself.
*/
typedef const t_bunny_prototype	*(*t_bunny_get_function_list)(void);

/*!
** The t_bunny_plugin structure represent a single loaded dynamic library.
** The name field is the complete path to the dynamic library file.
** The library_handler field represent the dynamic library in memory.
** The nbr_function field contains the length of the prototypes array.
** The prototypes field is an array of t_bunny_prototype that contains
** every functions retrieved from the dynamic library.
*/
typedef struct			s_bunny_plugin
{
  const char * const		name;
  const void * const		library_handler;
  const size_t			nbr_functions;
  const t_bunny_prototype	prototypes[__ZERO_LENGTH__];
}				t_bunny_plugin;

/*!
** This function open the sent dynamic library file and load every functions
** found inside.
** \param libfile The path of a dynamic library file
** \return A valid pointer on a t_bunny_plugin or NULL on error.
*/
t_bunny_plugin			*bunny_new_plugin(const char			*libfile);

/*!
** Delete the sent plugin and close all associated data.
** \param plugin The plugin to close and delete.
*/
void				bunny_delete_plugin(t_bunny_plugin		*plugin);

/*!
** Get the function pointer associated to the given name in the given plugin.
** The returned function pointer can be a pointer to any function present
** in the dynamic library and exposing a symbol: even functions that are not
** listed inside the list.
** This interface can be use even without any specific bunny_plugin installation
** as an abstraction on dynamic libraries.
** \param plugin A pointer to the loaded dynamic library
** \param funcname The name of the function
** \return The function pointer to cast to the correct type, or NULL
** if the symbol was not found.
*/
void				*bunny_plugin_get_function(const t_bunny_plugin	*plugin,
							   const char		*funcname);

/*!
** Call the function in plugin associated with the sent name.
** Put the function returned value at the specified address.
** Functions parameters are in the sent array which is arrlen elements.
** \param plugin The dynamic library that is suppose to contains the function.
** \param funcname The name of the function to call
** \param return_value The address of the space that will be use to store the
** function returned value.
** \param arrlen The length of the val array.
** \param val The array that contains all parameters to pass to the function.
** \return True if the call was made, false if it was not. Several reasons:
** the function does not exists, the type of parameters is incorrect.
*/
bool				bunny_plugin_call(t_bunny_plugin		*plugin,
						  const char			*funcname,
						  t_bunny_value			*return_value,
						  size_t			arrlen,
						  t_bunny_value			*val);

/*!
** This function wrap the bunny_plugin_call function.
** The array val of the bunny_plugin_call is construct with datas retrieved from the
** va_list of bunny_plugin_callv. The length of this array is retrieved from the
** function prototype in the t_bunny_plugin /!\ So a param list size error might be hidden.
** I recommand to use bunny_plugin_call most of time and keep this one for quickly
** made program.
** \param plugin The dynamic library that is suppose to contains the function.
** \param funcname The name of the function to call
** \param return_value The address of the space that will be use to store the
** \param ... All parameters that will be sent to the function.
** \return True if the call was made, false if it was not. Several reasons:
** the function does not exists, the type of parameters is incorrect.
*/
bool				bunny_plugin_callv(t_bunny_plugin		*plugin,
						   const char			*funcname,
						   t_bunny_value		*return_value,
						   ...);

#endif	/*			__LAPIN_PLUGIN_H__	*/

