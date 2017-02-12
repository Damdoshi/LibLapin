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
    BC_CUSTOM
  }				t_bunny_configuration_type;

typedef void			t_bunny_configuration;

/*!
** Create an empty configuration node.
** \return NULL on error, if no more memory is available.
*/
t_bunny_configuration		*bunny_new_configuration(void);

/*!
** Load a file into a configuration node and its children.
** You can send NULL as config to create a completly new one. If it is not NULL, the sent
** node will be filled with new data and then returned.
** Some fields may be overwritten.
** \param type The configuration format to load and read
** \param file The file to load
** \param config An existing config to fill, or NULL to create a new one
** \return config if it is not NULL else a new node if everything went well, NULL on error.
*/
t_bunny_configuration		*bunny_load_configuration(t_bunny_configuration_type	type,
							  const char			*file,
							  t_bunny_configuration		*config);

/*!
** Save a configuration into a file.
** \param type The configuration format that will be used to export
** \param file The name of the file to save
** \param config The configuration to save
** \return True if everything went well, false on error.
*/
bool				bunny_save_configuration(t_bunny_configuration_type	type,
							 const char			*file,
							 t_bunny_configuration		*config);

/*!
** Read the content of the string and convert it to a configuration node.
** You can send NULL as config to generate a new one. If it is not NULL, the sent
** node will be filled with new data and then returned.
** Some fields may be overwritten.
** \param type The configuration format to read
** \param code The string to parse
** \param config An existing config to fill or NULL to create a new one.
** \return config if it is not NULL else a new node if everything went well, NULL on error.
*/
t_bunny_configuration		*bunny_read_configuration(t_bunny_configuration_type	type,
							  const char			*code,
							  t_bunny_configuration		*config);

/*!
** The type of the function that will be called by bunny_read_configuration if type is
** greater or equal to BC_CUSTOM. Note that config will be allocated by bunny_read_configuration
** if it was NULL. Also note that it will be freed by bunny_read_configuration if you return NULL.
*/
typedef t_bunny_configuration	*(*t_bunny_my_read_configuration)(t_bunny_configuration_type t,
								  const char		*code,
								  t_bunny_configuration	*config);

/*!
** The function pointer that will be used by bunny_read_configuration if type is greater or
** equal to BC_CUSTOM. Note that config will be allocated by bunny_read_configuration if it
** was NULL. Also note that it will be freed by bunny_read_configuration if you return NULL.
*/
extern
t_bunny_my_read_configuration	gl_bunny_my_read_configuration;

/*!
** Convert the sent configuration into a string of type format.
** \param type The configuraton format to write
** \param config The node to convert into string
** \return A string if everything went well, NULL on error.
*/
char				*bunny_write_configuration(t_bunny_configuration_type	type,
							   const t_bunny_configuration	*config);

/*!
** The type of the function that will be called by bunny_write_configuration if type is
** greater or equal to BC_CUSTOM.
*/
typedef char			*(*t_bunny_my_write_configuration)(t_bunny_configuration_type t,
								   const t_bunny_configuration *config);

/*!
** The function pointer that will be used by bunny_write_configuration if type is greater or
** equal to BC_CUSTOM.
*/
extern
t_bunny_my_write_configuration	gl_bunny_my_write_configuration;

/*!
** Delete the sent configuration node. All children will be destroyed as well.
** If the configuration is a child, it will remove itself cleanly from its parent.
** \param config The configuration node to delete.
*/
void				bunny_delete_configuration(t_bunny_configuration	*config);

/*!
** Get the parent of the sent configuration node.
** \param config The config we want to parent
** \return A pointer to the parent or NULL if config was a root.
*/
t_bunny_configuration		*bunny_configuration_get_parent(t_bunny_configuration	*config);

/*!
** Get the children of the sent config that match the sent name.
** If create mode is true (It is not by default), the child will be created if it does
** not exists.
** \param config The configuration to search in
** \param child The child name to fetch
** \return A pointer to the child, NULL if there is no child with this name and create_mode
** is false, NULL if create_mode is true but there is no more memory.
*/
t_bunny_configuration		*bunny_configuration_get_child(t_bunny_configuration	*config,
							       const char		*child);

/*!
** Get the children of the sent config that match the sent index.
** If create mode is true (It is not by default), the child will be created if it does
** not exists.
** \param config The configuration to search in
** \param child The child index to fetch
** \return A pointer to the child, NULL if there is no child at this index and create_mode
** false, NULL if create_mode is true but here is no more memory.
*/
t_bunny_configuration		*bunny_configuration_get_case(t_bunny_configuration	*config,
							      size_t			i);

/*!
** Get the name of the current node. Note that this name may be different from the one you
** used to fetch it in its parent node, especially if it was a fetch by index: For example,
** an XML node may be inserted in an array, but still have a name.
** \param config The node to fetch the name of
** \return The name of the node. Is always valid.
*/
const char			*bunny_configuration_get_name(const t_bunny_configuration *config);

/*!
** Set the create mode to on or off. If the create mode is on, every node required to handle
** get child or get case will be created on the fly. On the contrary, functions will return NULL
** if nodes does not exists.
** \param cmode Set or unset the create mode
*/
void				bunny_configuration_create_mode(bool			cmode);

/*!
** Set the value inside the node to a string.
** \param config The node to set
** \param str The value to set
*/
void				bunny_configuration_set_string(t_bunny_configuration	*config,
							       const char		*str);

/*!
** Set the value inside the node to a double.
** \param config The node to set
** \param val The value to set
*/
void				bunny_configuration_set_double(t_bunny_configuration	*config,
							       double			val);

/*!
** Set the value inside the node to an integer.
** \param config The node to set
** \param val The value to set
*/
void				bunny_configuration_set_int(t_bunny_configuration	*config,
							    int				val);

/*!
** Get the value inside the node as a string.
** \param config The node to read
** \param str A pointer to the space that will be used to contain the value
** \return True if the value was set. Can fail if no value was ever set.
*/
bool				bunny_configuration_get_string(const t_bunny_configuration *config,
							       const char		**str);

/*!
** Get the value inside the node as a double.
** \param config The node to read
** \param val A pointer to the space that will be used to contain the value
** \return True if the value was set. Can fail if no value was ever set or if
** the value cannot be converted into a double.
*/
bool				bunny_configuration_get_double(const t_bunny_configuration *config,
							       double			*val);

/*!
** Get the value inside the node as an integer.
** \param config The node to read
** \param val A pointer to the space that will be used to contain the value
** \return True if the value was set. Can fail if no value was ever set or if
** the value cannot be converted into an integer.
*/
bool				bunny_configuration_get_int(const t_bunny_configuration	*config,
							    int				*val);

/*!
** Return the first children of the sent node.
** \param The node to browse
** \return The first chil. Return NULL ("bunny_configuration_end") if there is no child.
*/
t_bunny_configuration		*bunny_configuration_first(t_bunny_configuration	*config);

/*!
** Return the next children of config->father, directly after config.
** \param The node that have a father we want the next child.
** \param The next child. Return NULL ("bunny_configuration_end"() if it was the last.
*/
t_bunny_configuration		*bunny_configuration_next(t_bunny_configuration		*config);

/*!
** Return a recognizable element that is after the last children of config (NULL...)
** \param The node that we want the children terminating symbol.
** \return Always NULL.
*/
t_bunny_configuration		*bunny_configuration_end(t_bunny_configuration		*config);

/*!
** Get the requested node from config.
** \param config The configuration to browse.
** \param nbr The number of fieldname and integers you sent.
** \param ... nbr parameters that can be strings or integers. All integers must be
** negative or 0.
** \return The matching node
*/
t_bunny_configuration		*bunny_configuration_get_node_va(t_bunny_configuration	*config,
								 size_t			nbr,
								 ...);

#endif	/*			__LAPIN_CONFIGURATION_H__	*/

