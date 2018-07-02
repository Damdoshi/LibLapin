/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

/*!
** \file configuration.h
*/

#ifndef			__LAPIN_CONFIGURATION_H__
# define		__LAPIN_CONFIGURATION_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif
# include		<stdarg.h>

typedef enum		e_bunny_configuration_type
  {
    BC_INI,
    BC_DABSIC,
    BC_DABSIC_SEQUENCE,
    BC_DABSIC_FUNCTION,
    BC_DABSIC_EXPRESSION,
    BC_XML,
    BC_LUA,
    BC_CSV,
    BC_JSON,
    BC_LISP,
    //BC_YAML,
    BC_CUSTOM
  }			t_bunny_configuration_type;

typedef void		t_bunny_configuration;

/*!
** Create an empty configuration node.
** \return NULL on error, if no more memory is available.
*/
t_bunny_configuration	*bunny_new_configuration(void);

/*!
** Load a file into a configuration node and its children.
** You can send NULL as config to create a completly new one.
** If it is not NULL, the sent node will be filled with new data and then returned.
**
** \param file The file to load
** \param config An existing config to fill, or NULL to create a new one
*/
# define		bunny_open_configuration(file, config) \
  bunny_load_configuration(bunny_which_format(file), file, config)

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
t_bunny_configuration	*bunny_load_configuration(t_bunny_configuration_type		type,
						  const char				*file,
						  t_bunny_configuration			*config);

/*!
** Save a configuration into a file.
** \param type The configuration format that will be used to export
** \param file The name of the file to save
** \param config The configuration to save
** \return True if everything went well, false on error.
*/
bool			bunny_save_configuration(t_bunny_configuration_type		type,
						 const char				*file,
						 t_bunny_configuration			*config);

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
t_bunny_configuration	*bunny_read_configuration(t_bunny_configuration_type		type,
						  const char				*code,
						  t_bunny_configuration			*config);

/*!
** The type of the function that will be called by bunny_read_configuration if type is
** greater or equal to BC_CUSTOM. Note that config will be allocated by bunny_read_configuration
** if it was NULL. Also note that it will be freed by bunny_read_configuration if you return NULL.
*/
typedef
t_bunny_configuration	*(*t_bunny_my_read_configuration)(t_bunny_configuration_type	t,
							  const char			*code,
							  t_bunny_configuration		*config);

/*!
** The function pointer that will be used by bunny_read_configuration if type is greater or
** equal to BC_CUSTOM. Note that config will be allocated by bunny_read_configuration if it
** was NULL. Also note that it will be freed by bunny_read_configuration if you return NULL.
*/
extern t_bunny_my_read_configuration gl_bunny_my_read_configuration;

/*!
** Convert the sent configuration into a string of type format.
** \param type The configuraton format to write
** \param config The node to convert into string
** \return A string if everything went well, NULL on error.
*/
char			*bunny_write_configuration(t_bunny_configuration_type		type,
						   const t_bunny_configuration		*config);

/*!
** The type of the function that will be called by bunny_write_configuration if type is
** greater or equal to BC_CUSTOM.
*/
typedef char		*(*t_bunny_my_write_configuration)(t_bunny_configuration_type	t,
							   const t_bunny_configuration	*config);

/*!
** The function pointer that will be used by bunny_write_configuration if type is greater or
** equal to BC_CUSTOM.
*/
extern t_bunny_my_write_configuration gl_bunny_my_write_configuration;

/*!
** Delete the sent configuration node. All children will be destroyed as well.
** If the configuration is a child, it will remove itself cleanly from its parent.
** \param config The configuration node to delete.
*/
void			bunny_delete_configuration(t_bunny_configuration		*config);

/*!
** Delete the sent configuration node. All children will be destroyed as well.
** If the configuration is a child, it will remove itself cleanly from its parent.
** \param config The configuration node to delete.
*/
void			bunny_delete_node(t_bunny_configuration				*config,
						   const char				*addr);

/*!
** Set the create mode to on or off. If the create mode is on, every node required to handle
** get child or get case will be created on the fly. On the contrary, functions will return NULL
** if nodes does not exists.
** \param cmode Set or unset the create mode
*/
void			bunny_configuration_create_mode(bool				cmode);

/*!
** Get the parent of the sent configuration node.
** \param config The config we want to parent
** \return A pointer to the parent or NULL if config was a root.
*/
t_bunny_configuration	*bunny_configuration_get_parent(t_bunny_configuration		*config);

/*!
** Get the top parent of the sent configuration node.
** \param config The config tree node we will seek the root
** \return The root node
*/
t_bunny_configuration	*bunny_configuration_get_root(t_bunny_configuration		*config);

/*!
** Get the name of the current node. Note that this name may be different from the one you
** used to fetch it in its parent node, especially if it was a fetch by index: For example,
** an XML node may be inserted in an array, but still have a name.
** \param config The node to fetch the name of
** \return The name of the node. Is always valid.
*/
const char		*bunny_configuration_get_name(const t_bunny_configuration	*config);

/*!
** Get the address of the current node.
** \param config The node to fetch the name of
** \return The address of the node. Is always valid.
** "" is returned if the node is the root.
*/
const char		*bunny_configuration_get_address(const t_bunny_configuration	*config);

bool			bunny_configuration_getf_node(t_bunny_configuration		*config,
						      t_bunny_configuration		**node,
						      const char			*format,
						      ...) _BFMT(3, 4);

bool			bunny_configuration_getf_string(t_bunny_configuration		*config,
							const char			**string,
							const char			*format,
							...) _BFMT(3, 4);

bool			bunny_configuration_getf_double(t_bunny_configuration		*config,
							double				*dbl,
							const char			*format,
						      ...) _BFMT(3, 4);

bool			bunny_configuration_getf_int(t_bunny_configuration		*config,
						     int				*integer,
						     const char				*format,
						     ...) _BFMT(3, 4);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Get a value inside the configuration. Its type will match of the type of val.
** \param cnf The configuration to browse
** \param val A pointer to the space that will be written to get the value.
** \return True if the value was get
*/
#  define		bunny_configuration_getf(cnf, data, fmt, ...)			\
  _Generic((data),									\
	   void*: bunny_configuration_getf_node, \
	   const t_bunny_configuration**: bunny_configuration_getf_node,		\
	   t_bunny_configuration**: bunny_configuration_getf_node,			\
	   const char**: bunny_configuration_getf_string,				\
	   double*: bunny_configuration_getf_double,					\
	   int*: bunny_configuration_getf_int)(cnf, data, fmt, ##__VA_ARGS__)
# endif

bool			bunny_configuration_setf_node(t_bunny_configuration		*config,
						      const t_bunny_configuration	*node,
						      const char			*format,
						      ...) _BFMT(3, 4);

bool			bunny_configuration_setf_string(t_bunny_configuration		*config,
							const char			*string,
							const char			*format,
							...) _BFMT(3, 4);

bool			bunny_configuration_setf_double(t_bunny_configuration		*config,
							double				dbl,
							const char			*format,
						      ...) _BFMT(3, 4);

bool			bunny_configuration_setf_int(t_bunny_configuration		*config,
						     int				integer,
						     const char				*format,
						     ...) _BFMT(3, 4);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Get a value inside the configuration. Its type will match of the type of val.
** \param cnf The configuration to browse
** \param val A pointer to the space that will be written to get the value.
** \return True if the value was get
*/
#  define		bunny_configuration_setf(cnf, data, fmt, ...)			\
  _Generic((data),									\
	   const t_bunny_configuration*: bunny_configuration_setf_node,			\
	   t_bunny_configuration*: bunny_configuration_setf_node,			\
	   const char*: bunny_configuration_setf_string,				\
	   char*: bunny_configuration_setf_string,					\
	   double: bunny_configuration_setf_double,					\
	   int: bunny_configuration_setf_int)(cnf, data, fmt, ##__VA_ARGS__)
# endif

ssize_t			bunny_configuration_childrenf(const t_bunny_configuration	*c,
						      const char			*pat,
						      ...) _BFMT(2, 3);
ssize_t			bunny_configuration_casesf(const t_bunny_configuration		*c,
						   const char				*pat,
						   ...) _BFMT(2, 3);

bool			bunny_configuration_executef(t_bunny_configuration		*config,
						     bool				rec,
						     t_bunny_configuration		*parameters,
						     const char				*pattern,
						     ...) _BFMT(4, 5);

/*!
** Return the first children of the sent node.
** \param The node to browse
** \return The first chil. Return NULL ("bunny_configuration_end") if there is no child.
*/
t_bunny_configuration	*bunny_configuration_first(t_bunny_configuration		*config);

/*!
** Return the next children of config->father, directly after config.
** \param The node that have a father we want the next child.
** \param The next child. Return NULL ("bunny_configuration_end"() if it was the last.
*/
t_bunny_configuration	*bunny_configuration_next(t_bunny_configuration			*config);

/*!
** Return a recognizable element that is after the last children of config (NULL...)
** \param The node that we want the children terminating symbol.
** \return Always NULL.
*/
t_bunny_configuration	*bunny_configuration_end(t_bunny_configuration			*config);

/*!
** Return if the sent configuration node is the last children of its local tree.
** \param config The node to test
** \return True if it is the last.
*/
bool			bunny_configuration_is_last(t_bunny_configuration		*config);

/*!
** Return the format which is supposed to be used in file thanks to its extension.
** \param file The filename/path
** \return The file format, accordingly to its extension. BC_CUSTOM if there is no
** matching built-in type.
*/
t_bunny_configuration_type bunny_which_format(const char				*file);

/*!
**
*/
void			bunny_configuration_push_path(const char			*file);

/*!
**
*/
void			bunny_configuration_pop_path(void);

# include			"compat/configuration.h"
#endif	/*			__LAPIN_CONFIGURATION_H__				*/

