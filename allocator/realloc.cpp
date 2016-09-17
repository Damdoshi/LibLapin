// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<signal.h>
#include		<unistd.h>
#include		<string.h>
#include		"lapin_private.h"

void			check_memory_state(void);

extern size_t		border0;
extern size_t		border1;

void			*bunny_realloc(void		*ptr,
				       size_t		data)
{
  if (ptr == NULL)
    return (bunny_malloc(data));
  if (data == 0)
    {
      bunny_free(ptr);
      return (NULL);
    }
  struct memchunk	*chunk;
  void			*rel;

  /// Get the chunk from the data pointer
  chunk = (struct memchunk*)&((char*)ptr)[-sizeof(struct memchunk)];
  if (chunk->border0 != border0 || chunk->border1 != border1)
    {
      fprintf(stderr, "Bad pointer or altered memory detected while reallocing 0x%p.\n", ptr);
      check_memory_state();
      kill(getpid(), SIGSEGV); /* die Die DIE! */
      while (1);
    }
  if ((rel = bunny_malloc(data)) == NULL)
    return (NULL);
  if (data >= chunk->tree->chunk_size)
    memcpy(rel, ptr, chunk->tree->chunk_size);
  else
    memcpy(rel, ptr, data);
  bunny_free(ptr);
  return (rel);
}

