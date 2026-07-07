/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

/**
 * @doc
 * @doc-symbol allocator
 * @doc-kind module
 * @doc-module allocator
 * @doc-order 0
 * @doc-since 2
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Reserves and controls memory through the LibLapin allocator.
 * @description The Bunny Allocator module reserves a specific amount of memory and organizes memory allocations requested by its functions inside this reserved space.
 * @description The Bunny Allocator module helps ensure that a program does not consume too much memory and that the allocated memory remains stable.
 * @header lapin/allocator.h
 *
 * @doc-lang fr
 * @brief Réserve et contrôle la mémoire à travers l'allocateur de la LibLapin.
 * @description Le module Bunny Allocator réserve une quantité précise de mémoire et organise dans cet espace les allocations demandées par ses fonctions.
 * @description Le module Bunny Allocator permet de s'assurer qu'un programme ne consomme pas trop de mémoire et que la mémoire allouée reste stable.
 * @header lapin/allocator.h
 */

#ifndef		__LAPIN_ALLOCATOR_H__
# define	__LAPIN_ALLOCATOR_H__
# if		!defined(__LAPIN_H__)
#  error	You cannot include this file directly.
# endif

void		*bunny_malloc(size_t		size) _BMALLOC();

void		*bunny_calloc(size_t		nmemb,
			      size_t		size) _BMALLOC();

void		*bunny_realloc(void		*ptr,
			       size_t		size) _BMALLOC();

void		bunny_free(void			*data);

/**
 * @doc
 * @doc-symbol bunny_release
 * @doc-kind macro
 * @doc-module allocator
 * @doc-order 130
 * @doc-since 13
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Frees a pointer stored behind another pointer and clears it.
 * @description bunny_release is a small helper around bunny_free. It expects the address of a pointer, frees the pointed memory block, then writes NULL into the pointer variable.
 * @description The macro evaluates its argument more than once. Send the address of a simple pointer variable, not an expression with side effects.
 * @param pointer The address of the pointer to free and reset.
 * @see bunny_free
 *
 * @doc-lang fr
 * @brief Libère un pointeur stocké derrière un autre pointeur et l'efface.
 * @description bunny_release est un petit assistant autour de bunny_free. Il attend l'adresse d'un pointeur, libère le bloc mémoire pointé, puis écrit NULL dans la variable pointeur.
 * @description La macro évalue son argument plus d'une fois. Envoyez l'adresse d'une variable pointeur simple, pas une expression avec effets de bord.
 * @param pointer L'adresse du pointeur à libérer et à remettre à NULL.
 * @see bunny_free
 */
# define	bunny_release(pointer)		\
  do { bunny_free(*pointer); *pointer = NULL; } while (0)

void		bunny_set_memory_check(bool	check);

void		bunny_set_maximum_ram(size_t	bytes);

void		bunny_allocator_reset(void);

void		bunny_malloc_failure(bool	fail);

void		bunny_malloc_fail_after(int	cnt);

/**
 * @doc
 * @doc-symbol BUNNY_ALLOCATOR_OVERLOAD
 * @doc-kind macro
 * @doc-module allocator
 * @doc-order 20
 * @doc-since 11
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Redirects standard allocation calls to the Bunny allocator.
 * @description Define BUNNY_ALLOCATOR_OVERLOAD in your build, usually with the -D compiler option, to transform calls to malloc, calloc, realloc and free into calls to their bunny equivalents without changing your code.
 * @description This is a compile-time option, not a function-like macro to call from your source code.
 * @description This macro is the modern public name. It enables LAPIN_ALLOCATOR_OVERLOAD internally.
 * @see BUNNY_ALLOCATOR_DEACTIVATED, LAPIN_ALLOCATOR_OVERLOAD
 *
 * @doc-lang fr
 * @brief Redirige les appels d'allocation standard vers l'allocateur Bunny.
 * @description Définissez BUNNY_ALLOCATOR_OVERLOAD dans votre compilation, généralement avec l'option -D du compilateur, pour transformer les appels à malloc, calloc, realloc et free en appels vers leurs équivalents bunny sans modifier votre code.
 * @description C'est une option de compilation, pas une macro-fonction à appeler depuis votre code source.
 * @description Cette macro est le nom public moderne. Elle active LAPIN_ALLOCATOR_OVERLOAD en interne.
 * @see BUNNY_ALLOCATOR_DEACTIVATED, LAPIN_ALLOCATOR_OVERLOAD
 */
# ifdef		BUNNY_ALLOCATOR_OVERLOAD
#  define	LAPIN_ALLOCATOR_OVERLOAD
# endif

/**
 * @doc
 * @doc-symbol LAPIN_ALLOCATOR_OVERLOAD
 * @doc-kind macro
 * @doc-module allocator
 * @doc-order 19
 * @doc-since 2
 * @doc-until 10
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Historical name used to redirect standard allocation calls to the Bunny allocator.
 * @description Define LAPIN_ALLOCATOR_OVERLOAD in your build, usually with the -D compiler option, to transform calls to malloc, calloc, realloc and free into calls to their bunny equivalents without changing your code.
 * @description This is a compile-time option, not a function-like macro to call from your source code.
 * @description This is the historical name of BUNNY_ALLOCATOR_OVERLOAD. New code should use BUNNY_ALLOCATOR_OVERLOAD.
 * @see LAPIN_ALLOCATOR_DEACTIVATED, BUNNY_ALLOCATOR_OVERLOAD
 *
 * @doc-lang fr
 * @brief Nom historique utilisé pour rediriger les appels d'allocation standard vers l'allocateur Bunny.
 * @description Définissez LAPIN_ALLOCATOR_OVERLOAD dans votre compilation, généralement avec l'option -D du compilateur, pour transformer les appels à malloc, calloc, realloc et free en appels vers leurs équivalents bunny sans modifier votre code.
 * @description C'est une option de compilation, pas une macro-fonction à appeler depuis votre code source.
 * @description Il s'agit du nom historique de BUNNY_ALLOCATOR_OVERLOAD. Le nouveau code devrait utiliser BUNNY_ALLOCATOR_OVERLOAD.
 * @see LAPIN_ALLOCATOR_DEACTIVATED, BUNNY_ALLOCATOR_OVERLOAD
 */
# ifdef		LAPIN_ALLOCATOR_OVERLOAD
#  define	malloc(a)			bunny_malloc(a)
#  define	calloc(a, b)			bunny_calloc(a, b)
#  define	realloc(a, b)			bunny_realloc(a, b)
#  define	free(a)				bunny_free(a)
# endif

/**
 * @doc
 * @doc-symbol BUNNY_ALLOCATOR_DEACTIVATED
 * @doc-kind macro
 * @doc-module allocator
 * @doc-order 40
 * @doc-since 11
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Disables or bypasses the Bunny allocator.
 * @description This macro can be used in two different ways. At library compile time, it disables internal use of the Bunny allocator and binds the allocator functions to the system allocator. At application compile time, it transforms calls to bunny_malloc, bunny_calloc, bunny_realloc and bunny_free into calls to the regular allocator functions.
 * @description This is a compile-time option, not a function-like macro to call from your source code.
 * @description This is useful while debugging with tools such as valgrind, which cannot inspect the Bunny allocator internal heap like it inspects the system allocator.
 * @description This macro is the modern public name. It enables LAPIN_ALLOCATOR_DEACTIVATED internally.
 * @see BUNNY_ALLOCATOR_OVERLOAD, LAPIN_ALLOCATOR_DEACTIVATED
 *
 * @doc-lang fr
 * @brief Désactive ou contourne l'allocateur Bunny.
 * @description Cette macro peut être utilisée de deux manières. À la compilation de la bibliothèque, elle désactive l'utilisation interne de l'allocateur Bunny et relie les fonctions d'allocation à l'allocateur système. À la compilation de l'application, elle transforme les appels à bunny_malloc, bunny_calloc, bunny_realloc et bunny_free en appels aux fonctions d'allocation classiques.
 * @description C'est une option de compilation, pas une macro-fonction à appeler depuis votre code source.
 * @description C'est utile pendant le débogage avec des outils comme valgrind, qui ne peuvent pas inspecter le tas interne de l'allocateur Bunny comme ils inspectent l'allocateur système.
 * @description Cette macro est le nom public moderne. Elle active LAPIN_ALLOCATOR_DEACTIVATED en interne.
 * @see BUNNY_ALLOCATOR_OVERLOAD, LAPIN_ALLOCATOR_DEACTIVATED
 */
# ifdef		BUNNY_ALLOCATOR_DEACTIVATED
#  define	LAPIN_ALLOCATOR_DEACTIVATED
# endif

/**
 * @doc
 * @doc-symbol LAPIN_ALLOCATOR_DEACTIVATED
 * @doc-kind macro
 * @doc-module allocator
 * @doc-order 39
 * @doc-since 2
 * @doc-until 10
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Historical name used to disable or bypass the Bunny allocator.
 * @description This macro can be used in two different ways. At library compile time, it disables internal use of the Bunny allocator and binds the allocator functions to the system allocator. At application compile time, it transforms calls to bunny_malloc, bunny_calloc, bunny_realloc and bunny_free into calls to the regular allocator functions.
 * @description This is a compile-time option, not a function-like macro to call from your source code.
 * @description This is the historical name of BUNNY_ALLOCATOR_DEACTIVATED. New code should use BUNNY_ALLOCATOR_DEACTIVATED.
 * @see LAPIN_ALLOCATOR_OVERLOAD, BUNNY_ALLOCATOR_DEACTIVATED
 *
 * @doc-lang fr
 * @brief Nom historique utilisé pour désactiver ou contourner l'allocateur Bunny.
 * @description Cette macro peut être utilisée de deux manières. À la compilation de la bibliothèque, elle désactive l'utilisation interne de l'allocateur Bunny et relie les fonctions d'allocation à l'allocateur système. À la compilation de l'application, elle transforme les appels à bunny_malloc, bunny_calloc, bunny_realloc et bunny_free en appels aux fonctions d'allocation classiques.
 * @description C'est une option de compilation, pas une macro-fonction à appeler depuis votre code source.
 * @description Il s'agit du nom historique de BUNNY_ALLOCATOR_DEACTIVATED. Le nouveau code devrait utiliser BUNNY_ALLOCATOR_DEACTIVATED.
 * @see LAPIN_ALLOCATOR_OVERLOAD, BUNNY_ALLOCATOR_DEACTIVATED
 */
# ifdef		LAPIN_ALLOCATOR_DEACTIVATED
#  define	bunny_malloc(a)			malloc(a)
#  define	bunny_calloc(a, b)		calloc(a, b)
#  define	bunny_realloc(a, b)		realloc(a, b)
#  define	bunny_free(a)			free(a)
# endif

#endif	/*	__LAPIN_ALLOCATOR_H__		*/
