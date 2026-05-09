/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file error.h
** Bunny error handling and error handling
*/

#ifndef				__LAPIN_ERROR_H__
# define			__LAPIN_ERROR_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<errno.h>


/**
 * @doc
 * @doc-symbol error
 * @doc-kind module
 * @doc-module error
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Exposes LibLapin error codes, errno access and log configuration.
 * @description The error module centralizes LibLapin-specific error values and provides helpers to configure where error and log messages are written.
 * @header lapin/error.h
 *
 * @doc-lang fr
 * @brief Expose les codes d'erreur LibLapin, l'accès à errno et la configuration des logs.
 * @description Le module error centralise les valeurs d'erreur propres à LibLapin et fournit des aides pour configurer où les messages d'erreur et de log sont écrits.
 * @header lapin/error.h
 */



/**
 * @doc
 * @doc-symbol BUNNY_DEBUG
 * @doc-kind macro
 * @doc-module error
 * @doc-order 50
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Includes code only when BUNNY_DEBUG was defined before including LibLapin.
 * @description BUNNY_DEBUG(code) expands to code in debug builds and to nothing otherwise. It is a convenience macro for user-side debug instrumentation.
 * @param code Code fragment to include only in debug mode.
 * @see BUNNY_LOG
 *
 * @doc-lang fr
 * @brief Inclut du code seulement si BUNNY_DEBUG a été défini avant d'inclure LibLapin.
 * @description BUNNY_DEBUG(code) s'étend en code dans les builds de debug et en rien sinon. C'est une macro de confort pour l'instrumentation de debug côté utilisateur.
 * @param code Fragment de code à inclure uniquement en mode debug.
 * @see BUNNY_LOG
 */
# ifdef				BUNNY_DEBUG
#  undef			BUNNY_DEBUG
#  define			BUNNY_DEBUG(code)			code
# else
#  define			BUNNY_DEBUG(code)
# endif


/**
 * @doc
 * @doc-symbol BUNNY_LOG
 * @doc-kind macro
 * @doc-module error
 * @doc-order 75
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Includes code only when BUNNY_LOG was defined before including LibLapin.
 * @description BUNNY_LOG(code) expands to code in logging builds and to nothing otherwise.
 * @param code Code fragment to include only when logs are enabled.
 * @see BUNNY_DEBUG
 *
 * @doc-lang fr
 * @brief Inclut du code seulement si BUNNY_LOG a été défini avant d'inclure LibLapin.
 * @description BUNNY_LOG(code) s'étend en code dans les builds avec logs et en rien sinon.
 * @param code Fragment de code à inclure uniquement lorsque les logs sont activés.
 * @see BUNNY_DEBUG
 */
# ifdef				BUNNY_LOG
#  undef			BUNNY_LOG
#  define			BUNNY_LOG(code)				code
# else
#  define			BUNNY_LOG(code)
# endif



/**
 * @doc
 * @doc-symbol t_bunny_error
 * @doc-kind enum
 * @doc-module error
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Lists LibLapin-specific error codes stored in bunny_errno.
 * @description t_bunny_error values extend standard errno values for errors that are specific to LibLapin subsystems.
 * @enum BE_CANT_GENERATE_RESSOURCE A resource could not be generated.
 * @enum BE_SYNTAX_ERROR A parsed text or shader contains a syntax error.
 * @enum BE_BAD_ADDRESS An address or path is invalid.
 * @enum BE_TYPE_ERROR A value does not have the expected type.
 * @enum BE_CONTAINER_IS_EMPTY A container operation requires a non-empty container.
 * @enum BE_CANNOT_DUPLICATE A duplication operation failed.
 * @enum BE_CANNOT_FIND_ELEMENT An expected element was not found.
 * @enum BE_CANNOT_FIND_EMBEDDED_KEY A nested key was not found.
 * @enum BE_UNKNOWN_DISPLAY_DEVICE The requested display device is unknown.
 * @enum BE_CONFIGURED_FUNCTION_NOT_FOUND A function referenced by configuration was not found.
 * @enum BE_TOO_MANY_PARAMETERS Too many parameters were provided.
 * @enum BE_MISSING_CONTEXT A required context is missing.
 * @enum BE_PEER_IS_A_SERVER A network peer operation was attempted on a server peer.
 * @enum LAST_ERROR Sentinel value.
 * @see bunny_errno, bunny_strerror
 *
 * @doc-lang fr
 * @brief Liste les codes d'erreur propres à LibLapin stockés dans bunny_errno.
 * @description Les valeurs t_bunny_error complètent errno pour les erreurs spécifiques aux sous-systèmes de LibLapin.
 * @enum BE_CANT_GENERATE_RESSOURCE Une ressource n'a pas pu être générée.
 * @enum BE_SYNTAX_ERROR Un texte ou shader analysé contient une erreur de syntaxe.
 * @enum BE_BAD_ADDRESS Une adresse ou un chemin est invalide.
 * @enum BE_TYPE_ERROR Une valeur n'a pas le type attendu.
 * @enum BE_CONTAINER_IS_EMPTY Une opération de conteneur exige un conteneur non vide.
 * @enum BE_CANNOT_DUPLICATE Une duplication a échoué.
 * @enum BE_CANNOT_FIND_ELEMENT Un élément attendu est introuvable.
 * @enum BE_CANNOT_FIND_EMBEDDED_KEY Une clé imbriquée est introuvable.
 * @enum BE_UNKNOWN_DISPLAY_DEVICE Le périphérique d'affichage demandé est inconnu.
 * @enum BE_CONFIGURED_FUNCTION_NOT_FOUND Une fonction référencée par configuration est introuvable.
 * @enum BE_TOO_MANY_PARAMETERS Trop de paramètres ont été fournis.
 * @enum BE_MISSING_CONTEXT Un contexte requis est manquant.
 * @enum BE_PEER_IS_A_SERVER Une opération de pair réseau a été tentée sur un pair serveur.
 * @enum LAST_ERROR Valeur sentinelle.
 * @see bunny_errno, bunny_strerror
 */
typedef enum			e_bunny_error
  {
    BE_CANT_GENERATE_RESSOURCE	= 10000,
    BE_SYNTAX_ERROR,
    BE_BAD_ADDRESS,
    BE_TYPE_ERROR,
    BE_CONTAINER_IS_EMPTY,
    BE_CANNOT_DUPLICATE,
    BE_CANNOT_FIND_ELEMENT,
    BE_CANNOT_FIND_EMBEDDED_KEY,
    BE_UNKNOWN_DISPLAY_DEVICE,
    BE_CONFIGURED_FUNCTION_NOT_FOUND,
    BE_TOO_MANY_PARAMETERS,
    BE_MISSING_CONTEXT,
    BE_PEER_IS_A_SERVER,
    LAST_ERROR
  }				t_bunny_error;

/*!
** The last error that occurs.
*/


/**
 * @doc
 * @doc-symbol bunny_errno
 * @doc-kind macro
 * @doc-module error
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Gives access to the last LibLapin or system error code.
 * @description bunny_errno is currently an alias to errno. LibLapin functions set it either to a standard errno value or to a t_bunny_error value.
 * @see t_bunny_error, bunny_strerror, bunny_perror
 *
 * @doc-lang fr
 * @brief Donne accès au dernier code d'erreur système ou LibLapin.
 * @description bunny_errno est actuellement un alias vers errno. Les fonctions LibLapin le renseignent soit avec une valeur errno standard, soit avec une valeur t_bunny_error.
 * @see t_bunny_error, bunny_strerror, bunny_perror
 */
# define			bunny_errno				errno

/*!
** Return a string that contains the description of the sent error number in
** an human readable fashion. Works the same way as strerror(3).
**
** /!\ This function is not implemented yet
**
** \param An error number
*/
const char			*bunny_strerror(int			errorcode);

/*!
** Print the sent string followed by ": " if the string is not NULL and if the
** first byte is not '\0', followed by the last error description.
** Works the same way as perror(3), it writes on stderr.
**
** /!\ This function is not implemented yet
**
** \param A prefix to write before the error description. __FUNC__ or
** __PRETTY_FUNCTION__ may be a good idea, or the concatenation of __FILE__ and
** __LINE__... Or the name of the function that provokes the error.
*/
void				bunny_perror(const char			*str);

/*!
** Set the file descriptor used for error logging.
** This file descriptor can be negative to disable error logging.
** By default, is is STDERR_FILENO.
** \param fd The file descriptor for error logging
*/
void				bunny_set_error_descriptor(int		fd);

/*!
** Get the file descriptor used to log errors.
** This file descriptor can be negative: no logs are printed.
** By default, is is STDERR_FILENO.
** \return The file descriptor used for error logs.
*/
int				bunny_get_error_descriptor(void);

/*!
** Set the file descriptor used for normal logging.
** This file descriptor can be negative to disable logging.
** By default, is is STDOUT_FILENO.
** \param fd The file descriptor for logging
*/
void				bunny_set_log_descriptor(int		fd);

/*!
** Get the file descriptor used to log normal messages.
** This file descriptor can be negative: no logs are printed.
** By default, is is STDOUT_FILENO.
** \return The file descriptor used for logs.
*/
int				bunny_get_log_descriptor(void);

/*!
** Only print logs that contains label precised by parameter.
** Labels must be separated by ',' comma without any whitespace.
** LibLapin labels are:
**
**   system, ressource, graphics, sound, configuration, security,
**   unix, syntax, network, hardware
**
** \param label A string containing comma separated labels.
*/
void				bunny_set_log_filter(const char		*label);

/*!
** Set a complete or incomplete log mode.
** The complete log mode looks like:
** FAILURE/LOG [tags][timestamp][file:line][Error type][Detailed message]
** The incomplete log mode looks like:
** Error type - Detailed message, if the log is an error
** Or:
** Detailed message, if is a simple log
*/
void				bunny_set_log_mode(bool			complete);

#endif	/*			__LAPIN_ERROR_H__	*/
