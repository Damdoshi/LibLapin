/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file configuration.h
** The configuration module give you a INI file parser.
** A INI file data structure is defined like this:
** #here, we are in DEFAULT_SCOPE
** [scopename]
** #here, we are in scopename
** fieldname=index0,index1,index2,index3 #this is the field fieldname in scopename
*/

#ifndef				__LAPIN_CONFIGURATION_H__
# define			__LAPIN_CONFIGURATION_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** A t_bunny_ini is a completly private type that contains a configuration tree
** that may be managed throught ini functions.
** Because it is fully private, you can only move a pointer on it and cannot make
** a copy directly.
*/
typedef void			t_bunny_ini;

/*!
** The DEFAULT_SCOPE symbolic constant is useful to get fields from INI file
** that was defined before any scope was defined.
** Use it like this: bunny_ini_get_field(ini, DEFAULT_SCOPE, "fieldname", index)
*/
extern const char		*DEFAULT_SCOPE;

/*!
** The REMOVE_SCOPE symbolic constant is useful to remove a scope from a INI configuration.
** Use it like this: bunny_ini_set_field(ini, "scopename", REMOVE_SCOPE)
*/
# define			REMOVE_SCOPE					NULL, 0, NULL

/*!
** The REMOVE_FIELD symbolic constant is useful to remove a field from a INI configuration
** in a specific scope.
** Use it like this: bunny_ini_set_field(ini, "scopename", "fieldname", REMOVE_FIELD)
*/
# define			REMOVE_FIELD					(unsigned int)-1, NULL

/*!
** The REMOVE_INDEX symbolic constant is useful to remove a value from a field at a given
** address in a INI configuration.
** Use it like this: bunny_ini_set_field(ini, "scopename", "fieldname", index, REMOVE_INDEX)
*/
# define			REMOVE_INDEX					NULL

/*!
** Create an INI configuration.
** \return Return a t_bunny_ini pointer or NULL on error.
*/
t_bunny_ini			*bunny_new_ini(void);

/*!
** The bunny_load_ini function open and read a file that is supposed to be a INI file.
** \param file The INI file.
** \return The loaded INI configuration or NULL if an error happened.
*/
t_bunny_ini			*bunny_load_ini(const char			*file);

/*!
** The bunny_ini_get_error return a description of the last error encountered by
** the bunny_load_ini function. It will help you to know why it returned NULL.
** \return The last encountered error, NULL if no error was encountered.
*/
const char			*bunny_ini_get_error(void);

/*!
** The bunny_save_ini function save the content of the sent t_bunny_ini in the specified
** file in the INI file format.
** \param ini The INI configuration to save.
** \param file The file where to save the configuration
** \return True if everything went well. False on error.
*/
bool				bunny_save_ini(t_bunny_ini			*ini,
					       const char			*file);

/*!
** The bunny_ini_get_field function returns a value stored in a specific point in
** the INI configuration, if it exists.
** \param ini The INI configuration
** \param scope The scope name where is the data you need. Use DEFAULT_SCOPE to
** access to the fields that were written before any scope was precised in your INI file.
** \param field The field name where is the data you need.
** \param index The index in the field you want to read
** \return Return a constant string (You have to duplicate it if you wanna keep it
** after closing the INI configuration) if the data exists, else it returns NULL.
*/
const char			*bunny_ini_get_field(const t_bunny_ini		*ini,
						     const char			*scope,
						     const char			*field,
						     unsigned int		index);

/*!
** The bunny_ini_set_field function write a data inside a specific point in the INI
** configuration.
** \param ini The INI configuration
** \param scope The scope name in which you wanna write. Use DEFAULT_SCOPE to
** access to the fields that were written before any scope was precised in your INI file.
** \param field The field name in which you wanna write.
** \param index The index in the field you wanna write in.
** \param value The value that will be inserted into the INI configuration. Send
** REMOVE_INDEX to remove the data instead of writing a new one.
*/
void				bunny_ini_set_field(t_bunny_ini			*ini,
						    const char			*scope,
						    const char			*field,
						    unsigned int		index,
						    const char			*value);

/*!
** The bunny_delete_ini destroy an INI configuration.
** All strings returned by INI function for this INI configuration should be trashed,
** or your program may crash.
** \param ini The INI configuration to delete.
*/
void				bunny_delete_ini(t_bunny_ini			*ini);

/*!
** The t_bunny_ini_scope is a fully private element that is useful to browse scopes
** stored inside a INI configuration.
** This is how you browse scopes inside a INI configuration:
** void				browse(t_bunny_ini				*cnf)
** {
**   t_bunny_ini_scope		*scp;
**
**   for (scp = bunny_ini_first_scope(cnf); scp != LAST_SCOPE; scp = bunny_ini_next_scope(cnf, scp))
**   {}
** }
*/
typedef void			t_bunny_ini_scope;

/*!
** A symbolic constant to compare with the value returned by bunny_ini_next_scope
** in order to know if the browse loop reached its end.
*/
# define			LAST_SCOPE					NULL

/*!
** Get the first scope inside the INI configuration. The first scope should be
** DEFAULT_SCOPE.
** \param ini The INI configuration to browse.
** \return The first scope in the INI configuration. NULL if there is no scope.
*/
t_bunny_ini_scope		*bunny_ini_first_scope(t_bunny_ini		*ini);

/*!
** Get the next scope inside the INI configuration.
** \param ini The INI configuration
** \param scope The current scope, which will become the previous one.
** \return Return the scope after the given one. LAST_SCOPE if it was the last one.
*/
t_bunny_ini_scope		*bunny_ini_next_scope(t_bunny_ini		*ini,
						      t_bunny_ini_scope		*scope);

/*!
** Get the name of the sent scope. DEFAULT_SCOPE's name is "".
** \param ini The INI configuration
** \param scope The scope you wanna get the name from
** \return The name of the scope.
*/
const char			*bunny_ini_scope_name(const t_bunny_ini		*ini,
						      const t_bunny_ini_scope	*scope);

/*!
** The bunny_ini_scope_get_field returns a value stored in a specific point in
** the INI configuration, if it exists. The scope name does not need to be precised,
** because the function takes a t_bunny_ini_scope and the search is already limited
** to it.
** \param scope The scope where is the data you need.
** \param field The field name where is the data you need.
** \param index The index in the field you want to read
** \return Return a constant string (You have to duplicate it if you wanna keep it
** after closing the INI configuration) if the data exists, else it returns NULL.
*/
const char			*bunny_ini_scope_get_field(const t_bunny_ini_scope *scope,
							   const char		*field,
							   unsigned int		index);

/*!
** The bunny_ini_set_field function write a data inside a specific point in the INI
** configuration. The scope is precised thanks to a t_bunny_ini_scope pointer instead
** of its name.
** \param scope The scope in which you wanna write.
** \param field The field in which you wanna write.
** \param index The index in the field you wanna write in.
** \param value The value that will be inserted into the INI configuration. Send
** REMOVE_INDEX to remove the data instead of writing a new one.
*/
void				bunny_ini_scope_set_field(t_bunny_ini_scope	*scope,
							  const char		*field,
							  unsigned int		index,
							  const char		*value);

/*!
** Get a t_bunny_ini_scope by name instead of browsing throught the INI configuration.
** \param ini The INI configuration
** \param scope The name of the scope you wanna get
** \return The requested t_bunny_ini_scope. NULL if it does not exist.
*/
t_bunny_ini_scope		*bunny_ini_get_scope(t_bunny_ini		*ini,
						     const char			*scope);

/*!
** The t_bunny_ini_field is a fully private element that is useful to browse fields
** of a scope stored inside a INI configuration.
** This is how you browse fields inside a scope:
** void				browse(t_bunny_ini_scope			*scp)
** {
**   t_bunny_ini_field		*fld;
**
**   for (fld = bunny_ini_first_field(scp); fld != LAST_FIELD; fld = bunny_ini_next_field(scp, fdl))
**   {}
** }
*/
typedef void			t_bunny_ini_field;

/*!
** A symbolic constant to compare with the value return by bunny_ini_next_field
** in order to know if the browse loop reached its end.
*/
# define			LAST_FIELD					NULL

/*!
** Get the first field inside a scope in a INI configuration.
** \param scope The scope to browse inside a INI configuration.
** \return The first field in the scope. NULL if there is no scope.
*/
t_bunny_ini_field		*bunny_ini_first_field(t_bunny_ini_scope	*scope);

/*!
** Get the next field inside the given scope from an INI configuration.
** \param scope The scope to browse
** \param field The current field, which will become the previous one.
** \return Return the field after the given one, LAST_FIELD if it was the last one.
*/
t_bunny_ini_field		*bunny_ini_next_field(t_bunny_ini_scope		*scope,
						      t_bunny_ini_field		*field);

/*!
** Get the name of the sent field.
** \param scope The scope that own the field
** \param field The field you wanna get to name from
** \return The name of the field
*/
const char			*bunny_ini_field_name(const t_bunny_ini_scope	*scope,
						      const t_bunny_ini_field	*field);

/*!
** The bunny_ini_field_get_value returns a value stored in a specific point in the
** INI configuration, if it exists. The field name does not need to be precised, neither
** the scope because the function takes a t_bunny_ini_field and the search is already
** limited to it.
** \param field The field where is the data you need
** \param index The index in the field you want to read
** \return Return a constant string (You have to duplicate it if you wanna keep it
** after closing the INI configuration) if the data exists, else it returns NULL.
*/
const char			*bunny_ini_field_get_value(const t_bunny_ini_field *field,
							   unsigned int		index);

/*!
** The bunny_ini_field_set_value function write a data inside a specific point in
** the INI configuration. The field and scope are precised thanks to a t_bunny_ini_field
** pointer instead of names.
** \param field The field in which you wanna write.
** \param index The index in the field you wanna write in.
** \param value The value that will be inserted into the INI configuration. Send
** REMOVE_INDEX to remove the data instead of writing a new one.
*/
void				bunny_ini_field_set_value(t_bunny_ini_field	*field,
							  unsigned int		index,
							  const char		*value);

#endif	/*			__LAPIN_CONFIGURATION_H__	*/
