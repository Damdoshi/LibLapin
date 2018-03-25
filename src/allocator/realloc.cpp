// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
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

void			*bunny_realloc(void		*ptr,
                         size_t		data)
{
  void			*rel;

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
  if ((rel = realloc(ptr, data)) == NULL)
    scream_error_if(return (NULL), errno, PATTERN, "allocator", ptr, data, rel);
  scream_log_if(PATTERN, "allocator", ptr, data, rel);
  return (rel);
#endif

  if (ptr == NULL)
    return (bunny_malloc(data));
  if (data == 0)
    {
      bunny_free(ptr);
      bunny_errno = 0;
      return (NULL);
    }
  struct memchunk	*chunk;

  /// Get the chunk from the data pointer
  chunk = (struct memchunk*)&((char*)ptr)[-sizeof(struct memchunk)];
  if (chunk->border0 != border0 || chunk->border1 != border1)
    {
      fprintf(stderr, "Bad pointer or altered memory detected while reallocing 0x%p.\n", ptr);
      check_memory_state();
      scream_error_if(dprintf(bunny_get_error_descriptor(), "Sending SIGSEGV"),
		      errno, PATTERN, "allocator", ptr, data, rel);
#ifdef			__linux__
      kill(getpid(), SIGSEGV); /* die Die DIE! */
      while (1);
#else
      exit(EXIT_FAILURE);
#endif
    }

  if ((rel = bunny_malloc(data)) == NULL)
    return (NULL);

  if (data >= chunk->tree->chunk_size)
    memcpy(rel, ptr, chunk->tree->chunk_size);
  else
    memcpy(rel, ptr, data);

  bunny_free(ptr);
  scream_log_if(PATTERN, "allocator", ptr, data, rel);
  return (rel);
}

