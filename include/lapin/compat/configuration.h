/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_CONFIGURATION_COMPAT_H__
# define		__LAPIN_CONFIGURATION_COMPAT_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Cover bunny_configuration_get_child and bunny_configuration_get_case with the same
** symbol.
** \param cnf The configuration to browse
** \param id A string or an integer to browse the configuration
** \return A t_bunny_configuration
*/
#  define		bunny_configuration_access(cnf, id)				\
  _Generic((id),									\
	   const char*: bunny_configuration_go_get_node,				\
	   char*: bunny_configuration_go_get_node,					\
	   size_t: bunny_configuration_get_case,					\
	   int: bunny_configuration_get_case						\
	   )(cnf, id)
# endif

/*!
** Get the children of the sent config that match the sent name.
** If create mode is true (It is not by default), the child will be created if it does
** not exists.
** \param config The configuration to search in
** \param child The child name to fetch
** \return A pointer to the child, NULL if there is no child with this name and create_mode
** is false, NULL if create_mode is true but there is no more memory.
*/
t_bunny_configuration	*bunny_configuration_get_child(t_bunny_configuration		*config,
						       const char			*child);


/*!
** Get the children of the sent config that match the sent index.
** If create mode is true (It is not by default), the child will be created if it does
** not exists.
** \param config The configuration to search in
** \param child The child index to fetch
** \return A pointer to the child, NULL if there is no child at this index and create_mode
** false, NULL if create_mode is true but here is no more memory.
*/
t_bunny_configuration	*bunny_configuration_get_case(t_bunny_configuration		*config,
						      size_t				i);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Get a value inside the configuration. Its type will match of the type of val.
** \param cnf The configuration to browse
** \param val A pointer to the space that will be written to get the value.
** \return True if the value was get
*/
#  define		bunny_configuration_get(cnf, val)				\
  _Generic((val),									\
	   const char**: bunny_configuration_get_string,				\
	   char**: bunny_configuration_get_string,					\
	   double*: bunny_configuration_get_double,					\
	   int*: bunny_configuration_get_int)(cnf, val)
# endif

/*!
** Get the value inside the node as a string.
** \param config The node to read
** \param str A pointer to the space that will be used to contain the value
** \return True if the value was get. Can fail if no value was ever set.
*/
bool			bunny_configuration_get_string(const t_bunny_configuration	*config,
						       const char			**str);

/*!
** Get the value inside the node as a double.
** \param config The node to read
** \param val A pointer to the space that will be used to contain the value
** \return True if the value was get. Can fail if no value was ever set or if
** the value cannot be converted into a double.
*/
bool			bunny_configuration_get_double(const t_bunny_configuration	*config,
						       double				*val);

/*!
** Get the value inside the node as an integer.
** \param config The node to read
** \param val A pointer to the space that will be used to contain the value
** \return True if the value was get. Can fail if no value was ever set or if
** the value cannot be converted into an integer.
*/
bool			bunny_configuration_get_int(const t_bunny_configuration		*config,
							    int				*val);

/*!
** Get the requested node from config.
** \param config The configuration to browse.
** \param nbr The number of fieldname and integers you sent as variadic parameters.
** \param ... nbr parameters that can be strings or integers. All integers must be
** negative or 0 or they will be considered as pointers.
** \return The matching node
*/
t_bunny_configuration	*bunny_configuration_go_get_node_va(t_bunny_configuration	*config,
							    size_t			nbr,
							    ...);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Get a value inside the configuration. Its type will match of the type of val.
** \param cnf The configuration to browse
** \param val A pointer to the space that will be written to get the value.
** \pram nbr How many variadic parameter there is
** \param ... nbr parameters that can be strings or integers. All integers must be negative
** or 0 or they will be considered as pointers.
** \return True if the value was get
*/
#  define		bunny_configuration_go_get_va(cnf, val, nbr, ...)		\
  _Generic((val),									\
	   const char**: bunny_configuration_go_get_string_va,				\
	   double*: bunny_configuration_go_get_double_va,				\
	   int*: bunny_configuration_go_get_int_va)(cnf, val, nbr, __VA_ARGS__)
# endif

/*!
** Go to the describded node and get its value as a string.
** \param config The configuration to browse
** \param val A pointer where to store the string you want t get
** \param nbr The number of fieldname and integers you sent as variadic parameters.
** \param ... nbr parameters that can be strings or integers. All integers must be negative
** or 0 or they will be considered as pointers.
** \return True if the output value was set.
*/
bool			bunny_configuration_go_get_string_va(const t_bunny_configuration *config,
							     const char			**val,
							     size_t			nbr,
							     ...);

/*!
** Go to the describded node and get its value as a double
** \param config The configuration to browse
** \param val A pointer where to store the double you want t get
** \param nbr The number of fieldname and integers you sent as variadic parameters.
** \param ... nbr parameters that can be strings or integers. All integers must be negative
** or 0 or they will be considered as pointers.
** \return True if the output value was set.
*/
bool			bunny_configuration_go_get_double_va(const t_bunny_configuration *config,
							     double			*val,
							     size_t			nbr,
							     ...);

/*!
** Go to the describded node and get its value as an integer.
** \param config The configuration to browse
** \param val A pointer where to store the integer you want to get
** \param nbr The number of fieldname and integers you sent as variadic parameters.
** \param ... nbr parameters that can be strings or integers. All integers must be negative
** or 0 or they will be considered as pointers.
** \return True if the output value was set.
*/
bool			bunny_configuration_go_get_int_va(const t_bunny_configuration	*config,
							  int				*val,
							  size_t			nbr,
							  ...);

/*!
** Get the requested node from config.
** \param config The configuration to browseg.
** \param addr An address in the C fashion, for example: "varname[index][index2]->pointed.attribute"
** The '*' operator is not supported yet. Parenthesis are not supported yet.
** \return The matching node
*/
t_bunny_configuration	*bunny_configuration_go_get_node(t_bunny_configuration		*config,
							 const char			*addr);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Get a value inside the configuration. Its type will match of the type of val.
** \param cnf The configuration to browse
** \param val A pointer to the space that will be written to get the value.
** \param addr An address in the C fashion, for example: "varname[index][index2]->pointed.attribute"
** The '*' operator is not supported yet. Parenthesis are not supported yet.
** \return True if the value was get
*/
#  define		bunny_configuration_go_get(cnf, val, addr)			\
  _Generic((val),									\
	   const char**: bunny_configuration_go_get_string,				\
	   double*: bunny_configuration_go_get_double,					\
	   int*: bunny_configuration_go_get_int)(cnf, val, addr)
# endif

/*!
** Go to the describded node and get its value as a string.
** \param config The configuration to browse
** \param val A pointer where to store the string you want t get
** \param addr An address in the C fashion, for example: "varname[index][index2]->pointed.attribute"
** The '*' operator is not supported yet. Parenthesis are not supported yet.
** \return True if the output value was set.
*/
bool			bunny_configuration_go_get_string(t_bunny_configuration		*config,
							  const char			**val,
							  const char			*addr);

/*!
** Go to the describded node and get its value as a double.
** \param config The configuration to browse
** \param val A pointer where to store the double you want t get
** \param addr An address in the C fashion, for example: "varname[index][index2]->pointed.attribute"
** The '*' operator is not supported yet. Parenthesis are not supported yet.
** \return True if the output value was set.
*/
bool			bunny_configuration_go_get_double(t_bunny_configuration		*config,
							  double			*val,
							  const char			*addr);

/*!
** Go to the describded node and get its value as an integer
** \param config The configuration to browse
** \param val A pointer where to store the integer you want t get
** \param addr An address in the C fashion, for example: "varname[index][index2]->pointed.attribute"
** The '*' operator is not supported yet. Parenthesis are not supported yet.
** \return True if the output value was set.
*/
bool			bunny_configuration_go_get_int(t_bunny_configuration		*config,
						       int				*val,
						       const char			*addr);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Set a value inside the configuration. Its type will match of the type of val.
** \param cnf The configuration to editr
** \param val The value to write
** \return True if the value was set
*/
#  define		bunny_configuration_set(cnf, val)				\
  _Generic((val),									\
	   const char*: bunny_configuration_set_string,					\
	   char*: bunny_configuration_set_string,					\
	   double: bunny_configuration_set_double,					\
	   int: bunny_configuration_set_int)(cnf, val)
# endif

/*!
** Set the value inside the node to a string.
** \param config The node to set
** \param str The value to set
*/
void			bunny_configuration_set_string(t_bunny_configuration		*config,
						       const char			*str);

/*!
** Set the value inside the node to a double.
** \param config The node to set
** \param val The value to set
*/
void			bunny_configuration_set_double(t_bunny_configuration		*config,
						       double				val);

/*!
** Set the value inside the node to an integer.
** \param config The node to set
** \param val The value to set
*/
void			bunny_configuration_set_int(t_bunny_configuration		*config,
						    int					val);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Go to the describded node and set its value.
** \param config The configuration to browse
** \param val The value to set
** \param nbr The number of fieldname and integers you sent as variadic parameters.
** \param ... nbr parameters that can be strings or integers. All integers must be negative
** or 0 or they will be considered as pointers.
** \return True if the value was set.
*/
#  define		bunny_configuration_go_set_va(cnf, val, nbr, ...)		\
  _Generic((val),									\
	   const char*: bunny_configuration_go_set_string_va,				\
	   char*: bunny_configuration_go_set_string_va,					\
	   double: bunny_configuration_go_set_double_va,				\
	   int: bunny_configuration_go_set_int_va)(cnf, val, nbr, __VA_ARGS__)
# endif

/*!
** Go to the describded node and set its value to a string.
** \param config The configuration to browse
** \param val The value to set
** \param nbr The number of fieldname and integers you sent as variadic parameters.
** \param ... nbr parameters that can be strings or integers. All integers must be negative
** or 0 or they will be considered as pointers.
** \return True if the value was set.
*/
bool			bunny_configuration_go_set_string_va(const t_bunny_configuration *config,
							     const char			*val,
							     size_t			nbr,
							     ...);

/*!
** Go to the describded node and set its value to a double.
** \param config The configuration to browse
** \param val The value to set
** \param nbr The number of fieldname and integers you sent as variadic parameters.
** \param ... nbr parameters that can be strings or integers. All integers must be negative
** or 0 or they will be considered as pointers.
** \return True if the value was set.
*/
bool			bunny_configuration_go_set_double_va(const t_bunny_configuration *config,
							     double			val,
							     size_t			nbr,
							     ...);

/*!
** Go to the describded node and set its value to an integer.
** \param config THe configuration to browse
** \param val The value to set
** \param nbr The number of fieldname and integers you sent as variadic parameters.
** \param ... nbr parameters that can be strings or integers. All integers must be negative
** or 0 or they will be considered as pointers.
** \return True if the output value was set.
*/
bool			bunny_configuration_go_set_int_va(const t_bunny_configuration	*config,
							  int				val,
							  size_t			nbr,
							  ...);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Go to the describded node and set its value.
** \param config The configuration to browse
** \param val The value to set
** \param addr An address in the C fashion, for example: "varname[index][index2]->pointed.attribute"
** The '*' operator is not supported yet. Parenthesis are not supported yet.
** \return True if the value was set.
*/
#  define		bunny_configuration_go_set(cnf, val, addr)			\
  _Generic((val),									\
	   const char*: bunny_configuration_go_set_string,				\
	   char*: bunny_configuration_go_set_string,					\
	   double: bunny_configuration_go_set_double,					\
	   int: bunny_configuration_go_set_int)(cnf, val, addr)
# endif

/*!
** Go to the describded node and set its value to a string.
** \param config The configuration to browse
** \param val A pointer where to store the string you want to set
** \param addr An address in the C fashion, for example: "varname[index][index2]->pointed.attribute"
** The '*' operator is not supported yet. Parenthesis are not supported yet.
** \return True if the value was set.
*/
bool			bunny_configuration_go_set_string(t_bunny_configuration		*config,
							  const char			*val,
							  const char			*addr);

/*!
** Go to the describded node and set its value to a double
** \param config The configuration to browse
** \param val The value to set
** \param addr An address in the C fashion, for example: "varname[index][index2]->pointed.attribute"
** The '*' operator is not supported yet. Parenthesis are not supported yet.
** \return True if the value was set.
*/
bool			bunny_configuration_go_set_double(t_bunny_configuration		*config,
							  double			val,
							  const char			*addr);

/*!
** Go to the describded node and set its value to an integer
** \param config The configuration to browse
** \param val The value to set
** \param addr An address in the C fashion, for example: "varname[index][index2]->pointed.attribute"
** The '*' operator is not supported yet. Parenthesis are not supported yet.
** \return True if the value was set.
*/
bool			bunny_configuration_go_set_int(t_bunny_configuration		*config,
						       int				val,
						       const char			*addr);


#endif
