/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

/**
 * @doc
 * @doc-symbol monitor
 * @doc-kind module
 * @doc-module monitor
 * @doc-order 0
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Provides a small debugging monitor for live variables.
 * @description The Monitor module registers variable addresses and later displays or prints their current value. Registered values are not copied: the monitor stores the sent name and pointer.
 * @description The module can also store previous values in a short history, then display the history followed by the current value.
 * @header lapin/monitor.h
 *
 * @doc-lang fr
 * @brief Fournit un petit moniteur de débogage pour des variables vivantes.
 * @description Le module Monitor enregistre des adresses de variables afin d'afficher ou d'imprimer leur valeur courante plus tard. Les valeurs enregistrées ne sont pas copiées : le moniteur stocke le nom et le pointeur envoyés.
 * @description Le module peut aussi stocker les valeurs précédentes dans un court historique, puis afficher cet historique suivi de la valeur courante.
 * @header lapin/monitor.h
 */

#ifndef			__LAPIN_MONITOR_H__
# define		__LAPIN_MONITOR_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

/**
 * @doc
 * @doc-symbol t_bunny_monitored_type
 * @doc-kind enum
 * @doc-module monitor
 * @doc-order 100
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Identifies the runtime type of a monitored pointer.
 * @description t_bunny_monitored_type is used by _bunny_add_monitored_value and transparently by bunny_add_monitored_value to know how the pointed value must be read and displayed.
 * @value BMT_STRING The monitored pointer is a string pointer.
 * @value BMT_INTEGER The monitored pointer is an int pointer.
 * @value BMT_DOUBLE The monitored pointer is a double pointer.
 * @see bunny_add_monitored_value
 * @see _bunny_add_monitored_value
 *
 * @doc-lang fr
 * @brief Identifie le type d'exécution d'un pointeur surveillé.
 * @description t_bunny_monitored_type est utilisé par _bunny_add_monitored_value, et de manière transparente par bunny_add_monitored_value, pour savoir comment la valeur pointée doit être lue et affichée.
 * @value BMT_STRING Le pointeur surveillé est un pointeur vers une chaîne.
 * @value BMT_INTEGER Le pointeur surveillé est un pointeur vers un int.
 * @value BMT_DOUBLE Le pointeur surveillé est un pointeur vers un double.
 * @see bunny_add_monitored_value
 * @see _bunny_add_monitored_value
 */
typedef enum		e_bunny_monitored_type
  {
    BMT_STRING,
    BMT_INTEGER,
    BMT_DOUBLE
  }			t_bunny_monitored_type;

bool			_bunny_add_monitored_value(const char		*name,
						   t_bunny_monitored_type type,
						   const void		*ptr);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
/**
 * @doc
 * @doc-symbol bunny_add_monitored_value
 * @doc-kind macro
 * @doc-module monitor
 * @doc-order 120
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Registers a value in the debug monitor.
 * @description bunny_add_monitored_value is a C11-only macro. It uses _Generic to select the monitored type and forwards the call to _bunny_add_monitored_value.
 * @description No copy is made, neither for name nor for ptr. The pointed variable must remain alive as long as it is registered.
 * @param name The name of the monitored value.
 * @param ptr The pointer to monitor. Supported types are char*, int* and double*.
 * @return-case success On $Bsuccess@, returns true.
 * @return-case failure On $Bfailure@, returns false.
 * @error ENOMEM Historically documented for allocation failure while registering the value. The current implementation returns false when the C++ map insertion throws, without explicitly setting bunny_errno.
 * @section Details This macro is only available in C11 and is not available in C++. Code that cannot use the macro can call _bunny_add_monitored_value directly.
 * @see _bunny_add_monitored_value
 * @see bunny_remove_monitored_value
 * @see bunny_display_monitored_value
 * @see bunny_print_monitored_value
 *
 * @doc-lang fr
 * @brief Enregistre une valeur dans le moniteur de débogage.
 * @description bunny_add_monitored_value est une macro disponible uniquement en C11. Elle utilise _Generic pour sélectionner le type surveillé et transmet l'appel à _bunny_add_monitored_value.
 * @description Aucune copie n'est faite, ni pour name ni pour ptr. La variable pointée doit rester vivante tant qu'elle est enregistrée.
 * @param name Le nom de la valeur surveillée.
 * @param ptr Le pointeur à surveiller. Les types supportés sont char*, int* et double*.
 * @return-case success En cas de $Bsuccès@, renvoie true.
 * @return-case failure En cas d'$Béchec@, renvoie false.
 * @error ENOMEM Historiquement documenté pour un échec d'allocation lors de l'enregistrement de la valeur. L'implémentation courante renvoie false lorsque l'insertion dans la map C++ lève une exception, sans renseigner explicitement bunny_errno.
 * @section Details Cette macro est disponible uniquement en C11 et n'est pas disponible en C++. Le code qui ne peut pas utiliser la macro peut appeler _bunny_add_monitored_value directement.
 * @see _bunny_add_monitored_value
 * @see bunny_remove_monitored_value
 * @see bunny_display_monitored_value
 * @see bunny_print_monitored_value
 */

#  define		bunny_add_monitored_value(name, ptr)		\
  _Generic								\
  ((ptr),								\
   char*: _bunny_add_monitored_value(name, BMT_STRING, ptr),		\
   int*: _bunny_add_monitored_value(name, BMT_INTEGER, ptr),		\
   double*: _bunny_add_monitored_value(name, BMT_DOUBLE, ptr)		\
   )
# endif

bool			bunny_remove_monitored_value(const char		*name);

void			bunny_store_monitored_value(void);
void			bunny_reset_stored_monitored_value(void);

void			bunny_display_monitored_value(t_bunny_font	*textarea,
						      const char	*n);

ssize_t			bunny_print_monitored_value(int			fd,
						    const char		*n);

#endif	/*		__LAPIN_MONITOR_H__			*/
