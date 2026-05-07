/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/**
 * @doc
 * @doc-symbol plugin
 * @doc-kind module
 * @doc-module plugin
 * @doc-order 0
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Loads dynamic libraries that follow the Bunny plugin convention.
 * @description A bunny plugin is not a simple dynamic library. To be valid, it must implement a __get_function_list function of type t_bunny_get_function_list.
 * @description __get_function_list must return an array of t_bunny_prototype. This array should be statically allocated and must be terminated by a t_bunny_prototype whose function_ptr field is NULL.
 * @description Prototypes described in this array must match the real functions. If a prototype lies about the real ABI of a function, calling it with bunny_plugin_call or bunny_plugin_callv can crash the program.
 * @header lapin/plugin.h
 *
 * @doc-lang fr
 * @brief Charge des bibliothèques dynamiques respectant la convention des plugins Bunny.
 * @description Un plugin bunny n'est pas une simple bibliothèque dynamique. Pour être valide, il doit implémenter une fonction __get_function_list de type t_bunny_get_function_list.
 * @description __get_function_list doit renvoyer un tableau de t_bunny_prototype. Ce tableau devrait être alloué statiquement et doit être terminé par un t_bunny_prototype dont le champ function_ptr vaut NULL.
 * @description Les prototypes décrits dans ce tableau doivent correspondre aux vraies fonctions. Si un prototype ment sur l'ABI réelle d'une fonction, l'appeler avec bunny_plugin_call ou bunny_plugin_callv peut faire planter le programme.
 * @header lapin/plugin.h
 */

#ifndef				__LAPIN_PLUGIN_H__
# define			__LAPIN_PLUGIN_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<stdarg.h>

/**
 * @doc
 * @doc-symbol t_bunny_value_type
 * @doc-kind enum
 * @doc-module plugin
 * @doc-order 100
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Describes how a t_bunny_value must be read.
 * @description t_bunny_value_type is associated with t_bunny_value and t_bunny_prototype. It identifies the runtime type of a parameter or a return value manipulated through the plugin interface.
 * @value BVT_VOID The function returns no value.
 * @value BVT_INTEGER The value is stored in the integer field as an int64_t-compatible integer.
 * @value BVT_DOUBLE The value is stored in the real field as a double.
 * @value BVT_STRING The value is stored in the string field as a const char*.
 * @value BVT_POINTER The value is stored in the any field as a void*.
 * @see t_bunny_value
 * @see t_bunny_prototype
 *
 * @doc-lang fr
 * @brief Décrit comment lire un t_bunny_value.
 * @description t_bunny_value_type est associé à t_bunny_value et à t_bunny_prototype. Il identifie le type d'exécution d'un paramètre ou d'une valeur de retour manipulés à travers l'interface de plugin.
 * @value BVT_VOID La fonction ne renvoie pas de valeur.
 * @value BVT_INTEGER La valeur est stockée dans le champ integer comme entier compatible int64_t.
 * @value BVT_DOUBLE La valeur est stockée dans le champ real comme double.
 * @value BVT_STRING La valeur est stockée dans le champ string comme const char*.
 * @value BVT_POINTER La valeur est stockée dans le champ any comme void*.
 * @see t_bunny_value
 * @see t_bunny_prototype
 */
typedef enum			e_bunny_value_type
  {
    BVT_VOID			= 'v',
    BVT_INTEGER			= 'i', /* int64_t */
    BVT_DOUBLE			= 'd',
    BVT_STRING			= 's', /* const char * */
    BVT_POINTER			= 'p'  /* void * */
  }				t_bunny_value_type;

/**
 * @doc
 * @doc-symbol t_bunny_value
 * @doc-kind union
 * @doc-module plugin
 * @doc-order 120
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Stores one plugin parameter or return value.
 * @description t_bunny_value can contain any value supported by the plugin calling system. It must be interpreted with the associated t_bunny_value_type.
 * @field integer Integer value used with BVT_INTEGER.
 * @field string String pointer used with BVT_STRING.
 * @field any Generic pointer used with BVT_POINTER.
 * @field real Floating-point value used with BVT_DOUBLE.
 * @see t_bunny_value_type
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 *
 * @doc-lang fr
 * @brief Stocke un paramètre ou une valeur de retour de plugin.
 * @description t_bunny_value peut contenir n'importe quelle valeur supportée par le système d'appel de plugin. Il doit être interprété avec le t_bunny_value_type associé.
 * @field integer Valeur entière utilisée avec BVT_INTEGER.
 * @field string Pointeur de chaîne utilisé avec BVT_STRING.
 * @field any Pointeur générique utilisé avec BVT_POINTER.
 * @field real Valeur flottante utilisée avec BVT_DOUBLE.
 * @see t_bunny_value_type
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 */
typedef union			u_bunny_value
{
  int64_t			integer;
  const char			*string;
  void				*any;
  double			real;
}				t_bunny_value;

/**
 * @doc
 * @doc-symbol t_bunny_prototype
 * @doc-kind struct
 * @doc-module plugin
 * @doc-order 130
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Describes a callable function exported by a bunny plugin.
 * @description t_bunny_prototype represents one function exposed by the plugin interface. bunny_plugin_call and bunny_plugin_callv use this description to prepare the call.
 * @field name The name of the represented function.
 * @field function_ptr The real pointer to the represented function.
 * @field return_value The type of the value returned by the represented function.
 * @field nbr_parameters The number of parameters expected by the represented function and the number of meaningful entries in parameters.
 * @field parameters The type of each parameter expected by the represented function. A bunny plugin prototype can describe up to 16 parameters.
 * @see t_bunny_value_type
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 *
 * @doc-lang fr
 * @brief Décrit une fonction appelable exportée par un plugin bunny.
 * @description t_bunny_prototype représente une fonction exposée par l'interface de plugin. bunny_plugin_call et bunny_plugin_callv utilisent cette description pour préparer l'appel.
 * @field name Le nom de la fonction représentée.
 * @field function_ptr Le vrai pointeur vers la fonction représentée.
 * @field return_value Le type de la valeur renvoyée par la fonction représentée.
 * @field nbr_parameters Le nombre de paramètres attendus par la fonction représentée et le nombre d'entrées significatives dans parameters.
 * @field parameters Le type de chaque paramètre attendu par la fonction représentée. Un prototype de plugin bunny peut décrire jusqu'à 16 paramètres.
 * @see t_bunny_value_type
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 */
typedef struct			s_bunny_prototype
{
  const char *			name;
  const void *			function_ptr;
  t_bunny_value_type		return_value;
  size_t			nbr_parameters;
  t_bunny_value_type		parameters[16];
}				t_bunny_prototype;

/**
 * @doc
 * @doc-symbol t_bunny_get_function_list
 * @doc-kind callback
 * @doc-module plugin
 * @doc-order 135
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Is the type of the mandatory __get_function_list plugin entry point.
 * @description Every bunny plugin must export a __get_function_list function compatible with t_bunny_get_function_list. bunny_new_plugin calls it to retrieve the list of functions exposed through the plugin interface.
 * @return-case success On $Bsuccess@, returns an array of t_bunny_prototype terminated by an entry whose function_ptr field is NULL.
 * @return-case failure On $Bfailure@, returning NULL makes bunny_new_plugin reject the plugin.
 * @see t_bunny_prototype
 * @see bunny_new_plugin
 *
 * @doc-lang fr
 * @brief Est le type du point d'entrée obligatoire __get_function_list d'un plugin.
 * @description Chaque plugin bunny doit exporter une fonction __get_function_list compatible avec t_bunny_get_function_list. bunny_new_plugin l'appelle pour récupérer la liste des fonctions exposées par l'interface de plugin.
 * @return-case success En cas de $Bsuccès@, renvoie un tableau de t_bunny_prototype terminé par une entrée dont le champ function_ptr vaut NULL.
 * @return-case failure En cas d'$Béchec@, renvoyer NULL fait rejeter le plugin par bunny_new_plugin.
 * @see t_bunny_prototype
 * @see bunny_new_plugin
 */
typedef const t_bunny_prototype	*(*t_bunny_get_function_list)(void);

/**
 * @doc
 * @doc-symbol t_bunny_plugin
 * @doc-kind struct
 * @doc-module plugin
 * @doc-order 140
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Represents a loaded dynamic library matching the bunny plugin format.
 * @description t_bunny_plugin stores the handle of the loaded dynamic library and the array of functions returned by the bunny plugin interface.
 * @field name The complete path of the loaded dynamic library file.
 * @field library_handler The dynamic library handle loaded in memory.
 * @field nbr_functions The number of entries in prototypes.
 * @field prototypes The functions retrieved from the dynamic library through __get_function_list.
 * @see bunny_new_plugin
 * @see bunny_delete_plugin
 * @see bunny_plugin_get_function
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 *
 * @doc-lang fr
 * @brief Représente une bibliothèque dynamique chargée respectant le format de plugin bunny.
 * @description t_bunny_plugin stocke le handle de la bibliothèque dynamique chargée et le tableau de fonctions renvoyé par l'interface de plugin bunny.
 * @field name Le chemin complet du fichier de bibliothèque dynamique chargé.
 * @field library_handler Le handle de la bibliothèque dynamique chargée en mémoire.
 * @field nbr_functions Le nombre d'entrées dans prototypes.
 * @field prototypes Les fonctions récupérées depuis la bibliothèque dynamique via __get_function_list.
 * @see bunny_new_plugin
 * @see bunny_delete_plugin
 * @see bunny_plugin_get_function
 * @see bunny_plugin_call
 * @see bunny_plugin_callv
 */
typedef struct			s_bunny_plugin
{
  const char * const		name;
  const void * const		library_handler;
  const size_t			nbr_functions;
  const t_bunny_prototype	prototypes[__ZERO_LENGTH__];
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
						   const char			*funcname,
						   t_bunny_value		*return_value,
						   ...);

void				*bunny_plugin_self_open(void);
void				*bunny_plugin_get_self_function(const char	*n);

#endif	/*			__LAPIN_PLUGIN_H__	*/
