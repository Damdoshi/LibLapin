// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// LibLapin

#include		<stddef.h>
#include		<signal.h>
#include		<unistd.h>
#include		"lapin_private.h"

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
# undef			bunny_malloc
# undef			bunny_calloc
# undef			bunny_realloc
# undef			bunny_free
#endif

void			check_memory_state(void);
extern size_t		border0;
extern size_t		border1;

/**
 * @doc
 * @doc-symbol bunny_free
 * @doc-kind function
 * @doc-module allocator
 * @doc-order 120
 * @doc-since 2
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Releases a memory block allocated by the Bunny allocator.
 * @description Releases the sent memory block so it can be made available for a later allocation.
 * @description The pointer must come from bunny_malloc, bunny_calloc or bunny_realloc. Sending NULL is accepted and does nothing.
 * @param data A memory block allocated with bunny_malloc, bunny_calloc or bunny_realloc.
 * @log "allocator"
 * @section Error and logs If the sent address is invalid and the Bunny allocator is active, the program reports the altered memory state and deliberately raises a SIGSEGV-like failure.
 * @section Additional informations When BUNNY_ALLOCATOR_DEACTIVATED is set at library compile time, bunny_free becomes a wrapper around free with additional log output.
 * @see bunny_set_maximum_ram, bunny_malloc
 *
 * @doc-lang fr
 * @brief Libère un bloc mémoire alloué par l'allocateur Bunny.
 * @description Libère le bloc mémoire envoyé afin qu'il puisse être réutilisé par une allocation ultérieure.
 * @description Le pointeur doit provenir de bunny_malloc, bunny_calloc ou bunny_realloc. Envoyer NULL est accepté et ne fait rien.
 * @param data Un bloc mémoire alloué avec bunny_malloc, bunny_calloc ou bunny_realloc.
 * @log "allocator"
 * @section Erreurs et logs Si l'adresse envoyée est invalide et que l'allocateur Bunny est actif, le programme signale l'altération de l'état mémoire et provoque volontairement un échec de type SIGSEGV.
 * @section Informations supplémentaires Lorsque BUNNY_ALLOCATOR_DEACTIVATED est défini à la compilation de la bibliothèque, bunny_free devient un emballage autour de free avec une sortie de log supplémentaire.
 * @see bunny_set_maximum_ram, bunny_malloc
 */
void			bunny_free(void		*data)
{
  // To ensure a precise behaviour everywhere
  if (data == NULL)
    return ;
#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
  scream_log_if("%p", "allocator", data);
  free(data);
  return ;
#endif
  struct memchunk	*chunk;
  bool			bad;
  size_t		i;

  /// Get the chunk from the data pointer
  chunk = (struct memchunk*)&((char*)data)[-sizeof(struct memchunk)];
  for (i = chunk->real_size, bad = false; i < chunk->tree->chunk_size && bad == false; ++i)
    bad = (chunk->data[i] != 0x21);
  if (bad || chunk->border0 != border0 || chunk->border1 != border1)
    {
      fprintf(stderr, "Bad pointer or altered memory detected while freeing 0x%p.\n", data);
      check_memory_state();
      freexit(getpid(), SIGSEGV); /* die Die DIE! (my darling) */
      bunny_usleep(2e6);
      exit(EXIT_FAILURE);
    }
  struct memtree	*tree;

  tree = chunk->tree;
  /// Remove from the allocated list
  if (chunk->prev == chunk->next)
    tree->allocated = NULL;
  else
    {
      chunk->prev->next = chunk->next;
      chunk->next->prev = chunk->prev;
      if (tree->allocated == chunk)
	tree->allocated = chunk->next;
    }

  /// Add inside the freed list
  if (tree->freed == NULL)
    {
      chunk->next = chunk;
      chunk->prev = chunk;
    }
  else
    {
      chunk->next = tree->freed;
      chunk->prev = tree->freed->prev;
      chunk->prev->next = chunk;
      chunk->next->prev = chunk;
    }
  tree->freed = chunk;

  /// Stats
  struct memhead	*head;

  head = memory_head();
  head->alloc -= 1;
  head->total -= tree->chunk_size;

  scream_log_if("%p", "allocator", data);
}

// avec un prev, l'action de retirer serait plus rapide
