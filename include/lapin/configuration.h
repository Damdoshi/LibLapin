/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
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

/**
 * @doc
 * @doc-symbol configuration
 * @doc-kind module
 * @doc-module configuration
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Loads, builds, edits and saves structured configuration trees.
 * @description The configuration module is the central tree API used by Dabsic, INI, XML, Lua, JSON, CSV, Lisp, raw data and text-based resource loaders. It provides direct children/case access, formatted path access, execution of Dabsic nodes and helpers for resource loading.
 * @header lapin/configuration.h
 *
 * @doc-lang fr
 * @brief Charge, construit, modifie et sauvegarde des arbres de configuration structurés.
 * @description Le module configuration est l’API centrale d’arbre utilisée par Dabsic, INI, XML, Lua, JSON, CSV, Lisp, les données brutes et les chargeurs de ressources textuels. Il fournit les accès enfants/cases, les chemins formatés, l’exécution de nœuds Dabsic et des aides de chargement de ressources.
 * @header lapin/configuration.h
 */

/**
 * @doc
 * @doc-symbol t_bunny_configuration_type
 * @doc-kind enum
 * @doc-module configuration
 * @doc-order 10
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Lists the configuration grammars supported by LibLapin.
 * @field BC_INI INI-like format.
 * @field BC_DABSIC Dabsic block structured format.
 * @field BC_DABSIC_SEQUENCE Dabsic sequence.
 * @field BC_DABSIC_FUNCTION Dabsic function.
 * @field BC_DABSIC_EXPRESSION Dabsic expression.
 * @field BC_XML XML format.
 * @field BC_LUA Lua table-like format.
 * @field BC_CSV CSV format.
 * @field BC_JSON JSON format.
 * @field BC_LISP Lisp-like format.
 * @field BC_TEXT Text container format.
 * @field BC_DATA Raw binary data format.
 * @field BC_CUSTOM First value reserved for user-provided formats.
 * @see bunny_load_configuration
 * @see bunny_read_configuration
 * @see bunny_write_configuration
 * @see bunny_which_format
 *
 * @doc-lang fr
 * @brief Liste les grammaires de configuration supportées par la LibLapin.
 * @field BC_INI INI-like format.
 * @field BC_DABSIC Dabsic block structured format.
 * @field BC_DABSIC_SEQUENCE Dabsic sequence.
 * @field BC_DABSIC_FUNCTION Dabsic function.
 * @field BC_DABSIC_EXPRESSION Dabsic expression.
 * @field BC_XML XML format.
 * @field BC_LUA Lua table-like format.
 * @field BC_CSV CSV format.
 * @field BC_JSON JSON format.
 * @field BC_LISP Lisp-like format.
 * @field BC_TEXT Text container format.
 * @field BC_DATA Raw binary data format.
 * @field BC_CUSTOM First value reserved for user-provided formats.
 * @see bunny_load_configuration
 * @see bunny_read_configuration
 * @see bunny_write_configuration
 * @see bunny_which_format
 */
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
    BC_TEXT,
    BC_DATA,
    //BC_YAML, Il faudra bien finir par le faire.
    BC_CUSTOM
  }			t_bunny_configuration_type;

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
/**
 * @doc
 * @doc-symbol bunny_open_configuration
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 40
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Loads a configuration file after guessing its format from its extension.
 * @param file Path of the file to load.
 * @param config Existing node to fill, or $CNULL@ to allocate a new tree.
 * @param ... Optional arguments used by text configuration loading.
 * @return-success Returns $Sconfig@ when it is not $CNULL@, otherwise returns a newly allocated $Tt_bunny_configuration@.
 * @return-failure Returns $CNULL@ on error.
 * @log "ressource,configuration"
 * @see bunny_which_format
 * @see bunny_load_configuration
 *
 * @doc-lang fr
 * @brief Charge un fichier de configuration après avoir deviné son format depuis son extension.
 * @param file Path of the file to load.
 * @param config Existing node to fill, or $CNULL@ to allocate a new tree.
 * @param ... Optional arguments used by text configuration loading.
 * @return-success Renvoie $Sconfig@ s’il n’est pas $CNULL@, sinon renvoie un $Tt_bunny_configuration@ nouvellement alloué.
 * @return-failure Renvoie $CNULL@ en cas d’erreur.
 * @log "ressource,configuration"
 * @see bunny_which_format
 * @see bunny_load_configuration
 */
# define		bunny_open_configuration(file, config, ...)	\
  bunny_load_configuration(bunny_which_format(file), file, config, #__VA_ARGS__)

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
						  t_bunny_configuration			*config,
						  ...);

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
/**
 * @doc
 * @doc-symbol t_bunny_my_read_configuration
 * @doc-kind typedef
 * @doc-module configuration
 * @doc-order 80
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type used to read custom configuration formats.
 * @param t Custom configuration type, usually greater or equal to $CBC_CUSTOM@.
 * @param code String to parse.
 * @param config Configuration node to fill.
 * @return-success Returns the filled configuration node.
 * @return-failure Returns $CNULL@ on error.
 * @see gl_bunny_my_read_configuration
 * @see bunny_read_configuration
 *
 * @doc-lang fr
 * @brief Type de callback utilisé pour lire des formats de configuration personnalisés.
 * @param t Custom configuration type, usually greater or equal to $CBC_CUSTOM@.
 * @param code String to parse.
 * @param config Configuration node to fill.
 * @return-success Renvoie le nœud de configuration rempli.
 * @return-failure Renvoie $CNULL@ en cas d’erreur.
 * @see gl_bunny_my_read_configuration
 * @see bunny_read_configuration
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
/**
 * @doc
 * @doc-symbol t_bunny_my_write_configuration
 * @doc-kind typedef
 * @doc-module configuration
 * @doc-order 110
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type used to write custom configuration formats.
 * @param t Custom configuration type.
 * @param config Configuration tree to serialize.
 * @return-success Returns a newly allocated serialized string.
 * @return-failure Returns $CNULL@ on error.
 * @see gl_bunny_my_write_configuration
 * @see bunny_write_configuration
 *
 * @doc-lang fr
 * @brief Type de callback utilisé pour écrire des formats de configuration personnalisés.
 * @param t Custom configuration type.
 * @param config Configuration tree to serialize.
 * @return-success Renvoie une chaîne sérialisée nouvellement allouée.
 * @return-failure Renvoie $CNULL@ en cas d’erreur.
 * @see gl_bunny_my_write_configuration
 * @see bunny_write_configuration
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

// Destroy all children and remove value.
void			bunny_clear_configuration(t_bunny_configuration			*config);

/*!
** Delete the sent configuration node. All children will be destroyed as well.
** If the configuration is a child, it will remove itself cleanly from its parent.
** \param config The configuration node to delete.
*/
void			bunny_delete_node(t_bunny_configuration				*config,
					  const char					*addr);

/*!
** Set the create mode to on or off. If the create mode is on, every node required to handle
** get child or get case will be created on the fly. On the contrary, functions will return NULL
** if nodes does not exists.
** \param cmode Set or unset the create mode
*/
void			bunny_configuration_create_mode(bool				cmode);

bool			bunny_configuration_get_create_mode(void);

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
bool			bunny_configuration_addressf(t_bunny_configuration		*config,
						     const char				**addr,
						     const char				*format,
						     ...) _BFMT(3, 4);

// The retrieving parameter can be NULL, so the function can be used only to check if the type is correct.
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

bool			bunny_configuration_getf_bool(t_bunny_configuration		*config,
						      bool				*boolean,
						      const char			*format,
						      ...) _BFMT(3, 4);

bool			bunny_configuration_vgetf_node(t_bunny_configuration		*config,
						       t_bunny_configuration		**node,
						       const char			*format,
						       va_list				lst);

bool			bunny_configuration_vgetf_string(t_bunny_configuration		*config,
							 const char			**string,
							 const char			*format,
							 va_list			lst);

bool			bunny_configuration_vgetf_double(t_bunny_configuration		*config,
							 double				*dbl,
							 const char			*format,
							 va_list			lst);

bool			bunny_configuration_vgetf_int(t_bunny_configuration		*config,
						      int				*integer,
						      const char			*format,
						      va_list				lst);

bool			bunny_configuration_vgetf_bool(t_bunny_configuration		*config,
						       bool				*boolean,
						       const char			*format,
						       va_list				lst);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
/*!
** Get a value inside the configuration. Its type will match of the type of val.
** \param cnf The configuration to browse
** \param val A pointer to the space that will be written to get the value.
** \return True if the value was get
*/
/**
 * @doc
 * @doc-symbol bunny_configuration_getf
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 620
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief C11 generic macro that reads a node or scalar value at a formatted address.
 * @param cnf Configuration tree to inspect.
 * @param data Typed output pointer.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_getf_node
 * @see bunny_configuration_getf_string
 * @see bunny_configuration_getf_double
 * @see bunny_configuration_getf_int
 * @see bunny_configuration_getf_bool
 *
 * @doc-lang fr
 * @brief Macro générique C11 qui lit un nœud ou une valeur scalaire à une adresse formatée.
 * @param cnf Configuration tree to inspect.
 * @param data Typed output pointer.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_getf_node
 * @see bunny_configuration_getf_string
 * @see bunny_configuration_getf_double
 * @see bunny_configuration_getf_int
 * @see bunny_configuration_getf_bool
 */
#  define		bunny_configuration_getf(cnf, data, fmt, ...)			\
  _Generic((data),									\
	   void*: bunny_configuration_getf_node,					\
	   const t_bunny_configuration**: bunny_configuration_getf_node,		\
	   t_bunny_configuration**: bunny_configuration_getf_node,			\
	   const char**: bunny_configuration_getf_string,				\
	   double*: bunny_configuration_getf_double,					\
	   bool*: bunny_configuration_getf_bool,					\
	   int*: bunny_configuration_getf_int)(cnf, data, fmt, ##__VA_ARGS__)
/**
 * @doc
 * @doc-symbol bunny_configuration_vgetf
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 625
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Reads a node or scalar value at a formatted address using a $Tva_list@.
 * @param cnf Configuration tree to inspect.
 * @param data Typed output pointer.
 * @param fmt Printf-like address pattern.
 * @param va Argument list consumed by $Sfmt@.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_getf
 *
 * @doc-lang fr
 * @brief Lit un nœud ou une valeur scalaire à une adresse formatée avec une $Tva_list@.
 * @param cnf Configuration tree to inspect.
 * @param data Typed output pointer.
 * @param fmt Printf-like address pattern.
 * @param va Argument list consumed by $Sfmt@.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_getf
 */
#  define		bunny_configuration_vgetf(cnf, data, fmt, va)			\
  _Generic((data),									\
	   void*: bunny_configuration_vgetf_node,					\
	   const t_bunny_configuration**: bunny_configuration_vgetf_node,		\
	   t_bunny_configuration**: bunny_configuration_vgetf_node,			\
	   const char**: bunny_configuration_vgetf_string,				\
	   double*: bunny_configuration_vgetf_double,					\
	   bool*: bunny_configuration_vgetf_bool,					\
	   int*: bunny_configuration_vgetf_int)(cnf, data, fmt, va)
# endif

/**
 * @doc
 * @doc-symbol bunny_configuration_existsf
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 626
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Tests whether a formatted configuration address exists.
 * @param cnf Configuration tree to inspect.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_getf_node
 *
 * @doc-lang fr
 * @brief Teste si une adresse de configuration formatée existe.
 * @param cnf Configuration tree to inspect.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_getf_node
 */
#  define		bunny_configuration_existsf(cnf, fmt, ...)			\
  bunny_configuration_getf_node(cnf, NULL, fmt, ##__VA_ARGS__)

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

bool			bunny_configuration_vsetf_node(t_bunny_configuration		*config,
						       const t_bunny_configuration	*node,
						       const char			*format,
						       va_list				lst);

bool			bunny_configuration_vsetf_string(t_bunny_configuration		*config,
							 const char			*string,
							 const char			*format,
							 va_list			lst);

bool			bunny_configuration_vsetf_double(t_bunny_configuration		*config,
							 double				dbl,
							 const char			*format,
							 va_list			lst);

bool			bunny_configuration_vsetf_int(t_bunny_configuration		*config,
						      int				integer,
						      const char			*format,
						      va_list				lst);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
/*!
** Get a value inside the configuration. Its type will match of the type of val.
** \param cnf The configuration to browse
** \param val A pointer to the space that will be written to get the value.
** \return True if the value was get
*/
/**
 * @doc
 * @doc-symbol bunny_configuration_setf
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 630
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief C11 generic macro that writes a node or scalar value at a formatted address.
 * @param cnf Configuration tree to modify.
 * @param data Value or node to store.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_setf_node
 * @see bunny_configuration_setf_string
 * @see bunny_configuration_setf_double
 * @see bunny_configuration_setf_int
 *
 * @doc-lang fr
 * @brief Macro générique C11 qui écrit un nœud ou une valeur scalaire à une adresse formatée.
 * @param cnf Configuration tree to modify.
 * @param data Value or node to store.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_setf_node
 * @see bunny_configuration_setf_string
 * @see bunny_configuration_setf_double
 * @see bunny_configuration_setf_int
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
bool			bunny_configuration_get_case_named(t_bunny_configuration	*cnf,
							   t_bunny_configuration	**out,
							   const char			*pat,
							   ...) _BFMT(3, 4);

bool			bunny_configuration_executef_node(t_bunny_configuration		*config,
							  t_bunny_configuration		**data,
							  t_bunny_configuration		*parameters,
							  const char			*pattern,
							  ...) _BFMT(4, 5);
bool			bunny_configuration_executef_string(t_bunny_configuration	*config,
							    const char			**data,
							    t_bunny_configuration	*parameters,
							    const char			*pattern,
							    ...) _BFMT(4, 5);
bool			bunny_configuration_executef_double(t_bunny_configuration	*config,
							    double			*data,
							    t_bunny_configuration	*parameters,
							    const char			*pattern,
							    ...) _BFMT(4, 5);
bool			bunny_configuration_executef_int(t_bunny_configuration		*config,
							 int				*data,
							 t_bunny_configuration		*parameters,
							 const char			*pattern,
							 ...) _BFMT(4, 5);
bool			bunny_configuration_executef_bool(t_bunny_configuration		*config,
							  bool				*data,
							  t_bunny_configuration		*parameters,
							  const char			*pattern,
							  ...) _BFMT(4, 5);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/**
 * @doc
 * @doc-symbol bunny_configuration_executef
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 660
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief C11 generic macro that executes a Dabsic node selected by a formatted address and retrieves its typed result.
 * @param cnf Configuration tree to inspect.
 * @param data Typed output pointer.
 * @param rec Execution context.
 * @param params Parameters passed to the execution.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_execute
 *
 * @doc-lang fr
 * @brief Macro générique C11 qui exécute un nœud Dabsic sélectionné par adresse formatée et récupère son résultat typé.
 * @param cnf Configuration tree to inspect.
 * @param data Typed output pointer.
 * @param rec Execution context.
 * @param params Parameters passed to the execution.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_execute
 */
#  define		bunny_configuration_executef(cnf, data, rec, params, fmt, ...)	\
  _Generic((data),									\
	   void*: bunny_configuration_executef_node,					\
	   const t_bunny_configuration**: bunny_configuration_executef_node,		\
	   t_bunny_configuration**: bunny_configuration_executef_node,			\
	   const char**: bunny_configuration_executef_string,				\
	   double*: bunny_configuration_executef_double,				\
    	   bool*: bunny_configuration_executef_bool,					\
	   int*: bunny_configuration_executef_int)(cnf, data, rec, params, fmt, ##__VA_ARGS__)
# endif

bool			bunny_configuration_target(t_bunny_configuration		*from,
						   t_bunny_configuration		*to);
bool			bunny_configuration_targetf(t_bunny_configuration	*_f,
						    const char			*pattern,
						    ...);

bool			bunny_configuration_bindf_int(t_bunny_configuration		*c,
						      int				*i,
						      const char			*pat,
						      ...) _BFMT(3, 4);
bool			bunny_configuration_bindf_char(t_bunny_configuration		*c,
						       char				*i,
						       const char			*pat,
						       ...) _BFMT(3, 4);
bool			bunny_configuration_bindf_bool(t_bunny_configuration		*c,
						       bool				*i,
						       const char			*pat,
						       ...) _BFMT(3, 4);
bool			bunny_configuration_bindf_double(t_bunny_configuration		*c,
							 double				*i,
							 const char			*pat,
							 ...) _BFMT(3, 4);
bool			bunny_configuration_bindf_string(t_bunny_configuration		*c,
							 char				**i,
							 const char			*pat,
							 ...) _BFMT(3, 4);
/**
 * @doc
 * @doc-symbol bunny_configuration_bindf
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 690
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Binds a C variable to a configuration field selected by a formatted address.
 * @param cnf Configuration tree to modify.
 * @param data Address of the C variable to bind.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_unbindf
 *
 * @doc-lang fr
 * @brief Lie une variable C à un champ de configuration sélectionné par adresse formatée.
 * @param cnf Configuration tree to modify.
 * @param data Address of the C variable to bind.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_unbindf
 */
#  define		bunny_configuration_bindf(cnf, data, fmt, ...)			\
  _Generic((data),									\
	   char**: bunny_configuration_bindf_string,					\
	   char*: bunny_configuration_bindf_char,					\
	   bool*: bunny_configuration_bindf_bool,					\
	   double*: bunny_configuration_bindf_double,					\
	   int*: bunny_configuration_bindf_int)(cnf, data, fmt, ##__VA_ARGS__)

bool			bunny_configuration_unbindf(t_bunny_configuration		*c,
						    const char				*fmt,
						    ...) _BFMT(2, 3);

bool			bunny_configuration_declarativef(t_bunny_configuration		*c,
							 const char			*fmt,
							 ...) _BFMT(2, 3);

/*
** Turn expression into field that contains their result
*/
bool			bunny_configuration_resolve(t_bunny_configuration		*cnf);

/*!
** c[fmt] become a link on c.
*/
bool			bunny_configuration_linkf(t_bunny_configuration			*c,
						  const char				*fmt,
						  ...) _BFMT(2, 3);
/*!
** ori->dst
*/
void			bunny_configuration_link(t_bunny_configuration			*dst,
						 t_bunny_configuration			*ori);

/*!
** Return the first children of the sent node.
** \param The node to browse
** \return The first chil. Return NULL ("bunny_configuration_end") if there is no child.
*/
t_bunny_configuration	*bunny_configuration_first(t_bunny_configuration		*config);
t_bunny_configuration	*bunny_configuration_firstf(t_bunny_configuration		*config,
						    const char				*pattern,
						    ...) _BFMT(2, 3);

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

/**
 * @doc
 * @doc-symbol bunny_configuration_all_children
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 760
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Initializes a $Kfor@ loop over every child of a configuration node.
 * @param conf Configuration node to iterate.
 * @param node Loop variable receiving each child.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_first
 * @see bunny_configuration_next
 *
 * @doc-lang fr
 * @brief Initialise une boucle $Kfor@ sur tous les enfants d’un nœud de configuration.
 * @param conf Configuration node to iterate.
 * @param node Loop variable receiving each child.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_first
 * @see bunny_configuration_next
 */
# define		bunny_configuration_all_children(conf, node)			\
  node = bunny_configuration_firstf(conf, ".");						\
  node != bunny_configuration_end(conf);						\
  node = bunny_configuration_next(node)
/**
 * @doc
 * @doc-symbol bunny_configuration_all_childrenf
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 761
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Initializes a $Kfor@ loop over every child of a node selected by a formatted address.
 * @param conf Configuration tree to inspect.
 * @param node Loop variable receiving each child.
 * @param addr Printf-like address pattern.
 * @param ... Values consumed by $Saddr@.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_firstf
 *
 * @doc-lang fr
 * @brief Initialise une boucle $Kfor@ sur tous les enfants d’un nœud sélectionné par adresse formatée.
 * @param conf Configuration tree to inspect.
 * @param node Loop variable receiving each child.
 * @param addr Printf-like address pattern.
 * @param ... Values consumed by $Saddr@.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_firstf
 */
# define		bunny_configuration_all_childrenf(conf, node, addr, ...)	\
  node = bunny_configuration_firstf(conf, addr, ##__VA_ARGS__)		;		\
  node != bunny_configuration_end(conf);						\
  node = bunny_configuration_next(node)

/**
 * @doc
 * @doc-symbol bunny_configuration_all_casesf
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 763
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Initializes a $Kfor@ loop over every indexed case of a node selected by a formatted address.
 * @param conf Configuration tree to inspect.
 * @param i Loop index variable.
 * @param addr Printf-like address pattern.
 * @param ... Values consumed by $Saddr@.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_casesf
 *
 * @doc-lang fr
 * @brief Initialise une boucle $Kfor@ sur toutes les cases indexées d’un nœud sélectionné par adresse formatée.
 * @param conf Configuration tree to inspect.
 * @param i Loop index variable.
 * @param addr Printf-like address pattern.
 * @param ... Values consumed by $Saddr@.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_casesf
 */
# define		bunny_configuration_all_casesf(conf, i, addr, ...)		\
  i = 0; i < bunny_configuration_casesf(conf, addr, ##__VA_ARGS__); ++i
/**
 * @doc
 * @doc-symbol bunny_configuration_all_cases
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 762
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Initializes a $Kfor@ loop over every indexed case of a configuration node.
 * @param conf Configuration node to inspect.
 * @param i Loop index variable.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_casesf
 *
 * @doc-lang fr
 * @brief Initialise une boucle $Kfor@ sur toutes les cases indexées d’un nœud de configuration.
 * @param conf Configuration node to inspect.
 * @param i Loop index variable.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_casesf
 */
# define		bunny_configuration_all_cases(conf, i)				\
  i = 0; i < bunny_configuration_casesf(conf, "."); ++i

/**
 * @doc
 * @doc-symbol bunny_configuration_all
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 764
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief C11 helper selecting child or case iteration according to the loop variable type.
 * @param conf Configuration node to inspect.
 * @param node Either a $Tt_bunny_configuration@* child variable or an integer index variable.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_all_children
 * @see bunny_configuration_all_cases
 *
 * @doc-lang fr
 * @brief Aide C11 sélectionnant l’itération enfant ou case selon le type de la variable de boucle.
 * @param conf Configuration node to inspect.
 * @param node Either a $Tt_bunny_configuration@* child variable or an integer index variable.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_all_children
 * @see bunny_configuration_all_cases
 */
# define		bunny_configuration_all(conf, node)				\
  _Generic((node),									\
	   t_bunny_configuration*: bunny_configuration_all_children(conf, node),	\
           default: bunny_configuration_all_cases(conf, node)				\
	   )

/*!
** Return if the sent configuration node is the last children of its local tree.
** \param config The node to test
** \return True if it is the last.
*/
bool			bunny_configuration_is_last(t_bunny_configuration		*config);

/*!
** Merge all sents configurations into the first one
*/
bool			bunny_configuration_merge(int					cnt,
						  t_bunny_configuration			*target,
						  ...);

/*!
** Return the format which is supposed to be used in file thanks to its extension.
** \param file The filename/path
** \return The file format, accordingly to its extension. BC_CUSTOM if there is no
** matching built-in type.
*/
t_bunny_configuration_type bunny_which_format(const char				*file);

void			bunny_configuration_push_path(const char			*file);
void			bunny_configuration_pop_path(void);
bool			bunny_configuration_resolve_path(const char			*str,
							 char				*buffer,
							 int				size_buffer);

bool			bunny_configuration_read_time(const t_bunny_configuration	*cnf,
						      const char			*fld,
						      double				*secs);

// I think this is broken. Having to specifiy a type + increase a pointer... ?
// So it is full void* or char* and specified explicitly
// Let's think again.
/**
 * @doc
 * @doc-symbol bunny_configuration_get_and_go
 * @doc-kind macro
 * @doc-module configuration
 * @doc-order 820
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Reads a value and advances a byte pointer when the read succeeds.
 * @param cnf Configuration tree to inspect.
 * @param ptr Pointer advanced by the size of $Styp@ on success.
 * @param typ C type to read.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Expands to a value depending on the wrapped helper.
 * @return-failure Expands to $Cfalse@ or an equivalent failure value when the wrapped helper fails.
 * @see bunny_configuration_getf
 *
 * @doc-lang fr
 * @brief Lit une valeur et avance un pointeur d’octets quand la lecture réussit.
 * @param cnf Configuration tree to inspect.
 * @param ptr Pointer advanced by the size of $Styp@ on success.
 * @param typ C type to read.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Produit une valeur dépendant de l’aide enveloppée.
 * @return-failure Produit $Cfalse@ ou une valeur d’échec équivalente quand l’aide enveloppée échoue.
 * @see bunny_configuration_getf
 */
# define		bunny_configuration_get_and_go(cnf, ptr, typ, fmt, ...) \
  bunny_configuration_getf(cnf, (typ*)ptr, fmt, ##__VA_ARGS__) ? (bool)(ptr += sizeof(typ)) : 0

/*
** To avoid having plenty of tmp variable of differentes types when fetching inside
** a configuration sequentially
*/
/**
 * @doc
 * @doc-symbol t_bunny_temporary_data
 * @doc-kind union
 * @doc-module configuration
 * @doc-order 830
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Temporary typed storage convenient when reading sequential configuration values.
 * @field configuration Configuration node storage.
 * @field integer Integer storage.
 * @field real Floating point storage.
 * @field string String pointer storage.
 *
 * @doc-lang fr
 * @brief Stockage typé temporaire pratique lors de lectures séquentielles de configuration.
 * @field configuration Configuration node storage.
 * @field integer Integer storage.
 * @field real Floating point storage.
 * @field string String pointer storage.
 */
typedef union		u_bunny_temporary_data
{
  t_bunny_configuration	*configuration;
  int			integer;
  double		real;
  const char		*string;
}			t_bunny_temporary_data;

// Ces champs peuvent se combiner.
/**
 * @doc
 * @doc-symbol t_flexible_load_mode
 * @doc-kind enum
 * @doc-module configuration
 * @doc-order 840
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Selects which shapes $Sbunny_configuration_flexible_load@ accepts.
 * @field FLM_LOAD_FIELD Accept a single field.
 * @field FLM_LOAD_ARRAY Accept an array.
 * @field FLM_LOAD_HASHMAP Accept a named set/hash map.
 * @field FLM_KEEP_CONFIGURATION Keep loaded configuration nodes registered in the original tree.
 * @see bunny_configuration_flexible_load
 *
 * @doc-lang fr
 * @brief Sélectionne les formes acceptées par $Sbunny_configuration_flexible_load@.
 * @field FLM_LOAD_FIELD Accept a single field.
 * @field FLM_LOAD_ARRAY Accept an array.
 * @field FLM_LOAD_HASHMAP Accept a named set/hash map.
 * @field FLM_KEEP_CONFIGURATION Keep loaded configuration nodes registered in the original tree.
 * @see bunny_configuration_flexible_load
 */
typedef enum		e_flexible_load_mode
  {
   FLM_LOAD_FIELD	= 1, // 0 or 1.
   FLM_LOAD_ARRAY	= 2,
   FLM_LOAD_HASHMAP	= 4,
   FLM_KEEP_CONFIGURATION = 8 // Register loaded configuration inside the initial conf tree
  }			t_flexible_load_mode;

/*
** Recoit la configuration dont il faut extraire les informations directement.
** Si la configuration est un seul champ, alors le noeud est ce champ.
*/
/**
 * @doc
 * @doc-symbol t_flexible_load
 * @doc-kind typedef
 * @doc-module configuration
 * @doc-order 850
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type used to transform one configuration node into a loaded resource.
 * @param cnf Configuration node to convert.
 * @return-success Returns the loaded object.
 * @return-failure Returns $CNULL@ on error.
 * @see bunny_configuration_flexible_load
 *
 * @doc-lang fr
 * @brief Type de callback utilisé pour transformer un nœud de configuration en ressource chargée.
 * @param cnf Configuration node to convert.
 * @return-success Renvoie l’objet chargé.
 * @return-failure Renvoie $CNULL@ en cas d’erreur.
 * @see bunny_configuration_flexible_load
 */
typedef void		*(*t_flexible_load)(t_bunny_configuration			*cnf);

/*
** Permet de charger un champ pouvant contenir une valeur, un tableau ou une table de hash.
** La valeur peut etre un noeud avec des valeurs a charger, ou un fichier.
** void **pointeur;
** int nbr = bunny_configuration_flexible_load(cnf, FLM_..., function, &pointeur, "...", ...)
** nbr est la taille du tableau qui a été alloué par flexible_load.
** free(pointeur);
*/
int			bunny_configuration_flexible_load(t_bunny_configuration		*cnf,
							  t_flexible_load_mode		mode,
							  t_flexible_load		load,
							  void				***ptr,
							  const char			*pattern,
							  ...);
# include		"compat/configuration.h"
#endif	/*		__LAPIN_CONFIGURATION_H__					*/

