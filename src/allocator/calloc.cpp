// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
# undef			bunny_malloc
# undef			bunny_calloc
# undef			bunny_realloc
# undef			bunny_free
#endif

#define			PATTERN				"%zu nmemb, %zu size -> %p"

/**
 * @doc
 * @doc-symbol bunny_calloc
 * @doc-kind function
 * @doc-module allocator
 * @doc-order 140
 * @doc-since 2
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Allocates and clears an array with the Bunny allocator.
 * @description Reserves memory for an array of nmemb elements of size bytes each and returns a pointer to the first byte of the allocated memory block.
 * @description The allocated memory is set to zero. If there is not enough memory available, the function returns NULL.
 * @description The returned memory block must be freed with bunny_free.
 * @param nmemb The number of elements to reserve.
 * @param size The size, in bytes, of a single element.
 * @return-case success The address of the first byte of the allocated memory block.
 * @return-case failure NULL.
 * @error ENOMEM Out of memory. If BUNNY_ALLOCATOR_DEACTIVATED was not set at library compile time, this means the prereserved memory space is exhausted. See bunny_set_maximum_ram for more information about this prereserved memory space.
 * @log "allocator"
 * @section Additional informations When BUNNY_ALLOCATOR_DEACTIVATED is set at library compile time, bunny_calloc becomes a wrapper around calloc with additional log output.
 * @section Additional informations When BUNNY_ALLOCATOR_DEACTIVATED is not set at library compile time, bunny_calloc allocates memory inside a special space with a delimited size.
 * @see bunny_set_maximum_ram, bunny_free
 *
 * @doc-lang fr
 * @brief Alloue et remet à zéro un tableau avec l'allocateur Bunny.
 * @description Réserve la mémoire nécessaire à un tableau de nmemb éléments de size octets chacun et renvoie un pointeur vers le premier octet du bloc mémoire alloué.
 * @description La mémoire allouée est mise à zéro. S'il n'y a pas assez de mémoire disponible, la fonction renvoie NULL.
 * @description Le bloc mémoire renvoyé doit être libéré avec bunny_free.
 * @param nmemb Le nombre d'éléments à réserver.
 * @param size La taille, en octets, d'un seul élément.
 * @return-case success L'adresse du premier octet du bloc mémoire alloué.
 * @return-case failure NULL.
 * @error ENOMEM Mémoire insuffisante. Si BUNNY_ALLOCATOR_DEACTIVATED n'a pas été défini à la compilation de la bibliothèque, cela signifie que l'espace mémoire préréservé est épuisé. Consultez bunny_set_maximum_ram pour plus d'informations sur cet espace mémoire préréservé.
 * @log "allocator"
 * @section Informations supplémentaires Lorsque BUNNY_ALLOCATOR_DEACTIVATED est défini à la compilation de la bibliothèque, bunny_calloc devient un emballage autour de calloc avec une sortie de log supplémentaire.
 * @section Informations supplémentaires Lorsque BUNNY_ALLOCATOR_DEACTIVATED n'est pas défini à la compilation de la bibliothèque, bunny_calloc alloue la mémoire dans un espace spécial de taille limitée.
 * @see bunny_set_maximum_ram, bunny_free
 */
void			*bunny_calloc(size_t		nmemb,
				      size_t		data)
{
  size_t		i;
  void			*ptr;

  // To ensure a precise behaviour everywhere
  if (!nmemb || !data)
    return (NULL);
# if			defined (__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
  if (!ckd_mul(&i, nmemb, data))
    return (NULL);
#else
  i = nmemb * data;
#endif

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
  if ((ptr = calloc(nmemb, data)) == NULL)
    scream_error_if(return (NULL), errno, PATTERN, "allocator", nmemb, data, ptr);
  scream_log_if(PATTERN, "allocator", nmemb, data, ptr);
  return (ptr);
#endif
  if ((ptr = bunny_malloc(i)) == NULL)
    scream_error_if(return (NULL), errno, PATTERN, "allocator", nmemb, data, ptr);
  scream_log_if(PATTERN, "allocator", nmemb, data, ptr);
  return (memset(ptr, 0, i));
}

