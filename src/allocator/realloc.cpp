// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<errno.h>
#include		<signal.h>
#include		<unistd.h>
#include		<string.h>
#include		"lapin_private.h"

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
# undef			bunny_malloc
# undef			bunny_calloc
# undef			bunny_realloc
# undef			bunny_free
#endif

#define			PATTERN				"%p ptr, %zu size -> %p"

void			check_memory_state(void);

extern size_t		border0;
extern size_t		border1;

/**
 * @doc
 * @doc-symbol bunny_realloc
 * @doc-kind function
 * @doc-module allocator
 * @doc-order 160
 * @doc-since 2
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Resizes a memory block allocated by the Bunny allocator.
 * @description Changes the size of the memory block pointed to by ptr to size bytes.
 * @description If ptr is NULL and size is not zero, the function behaves like bunny_malloc. If size is zero, the sent pointer is freed and NULL is returned.
 * @description There is no guarantee that the returned address will be identical to the sent address, even when the new size is smaller than the old one.
 * @description The returned memory block must be freed with bunny_free.
 * @param ptr The memory block to resize.
 * @param size The new size of the memory block, in bytes.
 * @return-case success The address of the first byte of the resized memory block.
 * @return-case failure NULL. The sent memory block is left untouched.
 * @error ENOMEM Out of memory. If BUNNY_ALLOCATOR_DEACTIVATED was not set at library compile time, this means the prereserved memory space is exhausted. See bunny_set_maximum_ram for more information about this prereserved memory space.
 * @log "allocator"
 * @section Error and logs If the sent address is invalid and the Bunny allocator is active, the program reports the altered memory state and deliberately raises a SIGSEGV-like failure.
 * @section Additional informations When BUNNY_ALLOCATOR_DEACTIVATED is set at library compile time, bunny_realloc becomes a wrapper around realloc with additional log output.
 * @section Additional informations When BUNNY_ALLOCATOR_DEACTIVATED is not set at library compile time, bunny_realloc allocates memory inside a special space with a delimited size.
 * @see bunny_set_maximum_ram, bunny_free
 *
 * @doc-lang fr
 * @brief Redimensionne un bloc mémoire alloué par l'allocateur Bunny.
 * @description Modifie la taille du bloc mémoire pointé par ptr pour qu'elle devienne size octets.
 * @description Si ptr vaut NULL et que size n'est pas nul, la fonction se comporte comme bunny_malloc. Si size vaut zéro, le pointeur envoyé est libéré et NULL est renvoyé.
 * @description Rien ne garantit que l'adresse renvoyée sera identique à l'adresse envoyée, même lorsque la nouvelle taille est inférieure à l'ancienne.
 * @description Le bloc mémoire renvoyé doit être libéré avec bunny_free.
 * @param ptr Le bloc mémoire à redimensionner.
 * @param size La nouvelle taille du bloc mémoire, en octets.
 * @return-case success L'adresse du premier octet du bloc mémoire redimensionné.
 * @return-case failure NULL. Le bloc mémoire envoyé n'est pas modifié.
 * @error ENOMEM Mémoire insuffisante. Si BUNNY_ALLOCATOR_DEACTIVATED n'a pas été défini à la compilation de la bibliothèque, cela signifie que l'espace mémoire préréservé est épuisé. Consultez bunny_set_maximum_ram pour plus d'informations sur cet espace mémoire préréservé.
 * @log "allocator"
 * @section Erreurs et logs Si l'adresse envoyée est invalide et que l'allocateur Bunny est actif, le programme signale l'altération de l'état mémoire et provoque volontairement un échec de type SIGSEGV.
 * @section Informations supplémentaires Lorsque BUNNY_ALLOCATOR_DEACTIVATED est défini à la compilation de la bibliothèque, bunny_realloc devient un emballage autour de realloc avec une sortie de log supplémentaire.
 * @section Informations supplémentaires Lorsque BUNNY_ALLOCATOR_DEACTIVATED n'est pas défini à la compilation de la bibliothèque, bunny_realloc alloue la mémoire dans un espace spécial de taille limitée.
 * @see bunny_set_maximum_ram, bunny_free
 */
void			*bunny_realloc(void		*ptr,
				       size_t		data_size)
{
  size_t		ptrv = (size_t)ptr;
  void			*rel = NULL;

  // To ensure a precise behaviour everywhere
  if (ptr == NULL)
    return (bunny_malloc(data_size));
  if (data_size == 0)
    {
      bunny_free(ptr);
      bunny_errno = 0;
      return (NULL);
    }

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
  if ((rel = realloc(ptr, data_size)) == NULL)
    scream_error_if(return (NULL), errno, PATTERN, "allocator", (void*)ptrv, data_size, rel);
  scream_log_if(PATTERN, "allocator", (void*)ptrv, data_size, rel);
  return (rel);
#endif

  
  struct memchunk	*chunk;

  /// Get the chunk from the data pointer
  chunk = (struct memchunk*)&((char*)ptr)[-sizeof(struct memchunk)];
  if (chunk->border0 != border0 || chunk->border1 != border1)
    {
      fprintf(stderr, "Bad pointer or altered memory detected while reallocing 0x%zu.\n", ptrv);
      check_memory_state();
      scream_error_if(dprintf(bunny_get_error_descriptor(), "Sending SIGSEGV"),
		      errno, PATTERN, "allocator", ptr, data_size, rel);
#ifdef			__linux__
      kill(getpid(), SIGSEGV); /* die Die DIE! */
      while (1);
#else
      exit(EXIT_FAILURE);
#endif
    }

  if ((rel = bunny_malloc(data_size)) == NULL)
    return (NULL);

  if (data_size >= chunk->tree->chunk_size)
    memcpy(rel, ptr, chunk->tree->chunk_size);
  else
    memcpy(rel, ptr, data_size);

  bunny_free(ptr);
  scream_log_if(PATTERN, "allocator", (size_t)ptrv, data_size, rel);
  return (rel);
}

