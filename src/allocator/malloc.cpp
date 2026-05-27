// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<errno.h>
#include		<signal.h>
#include		<string.h>
#include		<unistd.h>
#include		"lapin_private.h"

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
# undef			bunny_malloc
# undef			bunny_calloc
# undef			bunny_realloc
# undef			bunny_free
#endif

#define			PATTERN				"%zu size -> %p"

typedef void		*(*t_sysmalloc)(size_t);
typedef void		(*t_sysfree)(void*);

static size_t		heap_size = 20 * 1024 * 1024;
int			memory_check = 0;
size_t			border0;
size_t			border1;

void			check_memory_state(void);

struct memhead		*memory_head(bool	reset)
{
  static struct memhead	*head = NULL;

  if (head == NULL || reset)
    {
      t_sysmalloc	sysmalloc = malloc;
      size_t		s = heap_size + sizeof(*head);

      memset(&border0, 0x42, sizeof(border0));	// Because size_t size is quite volatile...
      memset(&border1, 0x84, sizeof(border1));
      if (head == NULL)
	{
	  if ((head = (struct memhead*)sysmalloc(s)) == NULL)
	    {
	      fprintf(stderr, "Initial memory allocation failed. Exiting right now. Sorry.\n");
	      exit(EXIT_FAILURE);
	    }
	  atexit(check_memory_state);
	}
      else
	memset(head, 0, s);
      head->alloc_count = 0;
      head->total_count = 0;
      head->alloc = 0;
      head->total = 0;
      head->first = NULL;
      head->limit = &(((char*)head)[s]);
      head->last_position = &(((char*)head)[sizeof(*head)]);
    }
  return (head);
}

/**
 * @doc
 * @doc-symbol bunny_allocator_reset
 * @doc-kind function
 * @doc-module allocator
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Erases the Bunny allocator space.
 * @description This function resets the allocator internal state and makes every pointer previously returned by the Bunny allocator obsolete.
 * @description Use with caution. Existing pointers become invalid immediately after the reset.
 * @see bunny_set_memory_check, bunny_set_maximum_ram, bunny_malloc_failure
 *
 * @doc-lang fr
 * @brief Efface l'espace de l'allocateur Bunny.
 * @description Cette fonction réinitialise l'état interne de l'allocateur et rend obsolète tout pointeur précédemment renvoyé par l'allocateur Bunny.
 * @description Utilisez-la avec prudence. Les pointeurs existants deviennent invalides immédiatement après la réinitialisation.
 * @see bunny_set_memory_check, bunny_set_maximum_ram, bunny_malloc_failure
 */
void			bunny_allocator_reset(void)
{
  memory_head(true);
}

/**
 * @doc
 * @doc-symbol bunny_set_maximum_ram
 * @doc-kind function
 * @doc-module allocator
 * @doc-order 190
 * @doc-since 9
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Sets the maximum amount of memory managed by the Bunny allocator.
 * @description This function is only effective before any allocation made by the Bunny allocator. It defines the maximum size of the reserved allocator heap.
 * @description When the allocated memory reaches this size, allocation functions managed by the Bunny allocator start to fail. By default, the limit is 20 MB.
 * @param bytes The maximum size of the allocator heap, in bytes.
 * @see bunny_set_memory_check, bunny_allocator_reset, bunny_malloc_failure, set_max_heap_size
 *
 * @doc-lang fr
 * @brief Définit la quantité maximale de mémoire gérée par l'allocateur Bunny.
 * @description Cette fonction n'est efficace qu'avant toute allocation réalisée par l'allocateur Bunny. Elle définit la taille maximale du tas réservé à l'allocateur.
 * @description Lorsque la mémoire allouée atteint cette taille, les fonctions d'allocation gérées par l'allocateur Bunny commencent à échouer. Par défaut, la limite est de 20 Mo.
 * @param bytes La taille maximale du tas de l'allocateur, en octets.
 * @see bunny_set_memory_check, bunny_allocator_reset, bunny_malloc_failure, set_max_heap_size
 */
void			bunny_set_maximum_ram(size_t	byt)
{
  static int		edited;

  if (!edited)
    heap_size = byt;
  edited = 1;
}

/**
 * @doc
 * @doc-symbol set_max_heap_size
 * @doc-kind function
 * @doc-module allocator
 * @doc-order 189
 * @doc-since 2
 * @doc-until 8
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Historical function used to set the maximum Bunny allocator heap size.
 * @description This function is only effective before any allocation made by the Bunny allocator. It defines the maximum size of the reserved allocator heap, in megabytes.
 * @description When the allocated memory reaches this size, allocation functions managed by the Bunny allocator start to fail. By default, the limit is 20 MB.
 * @param megabytes The maximum size of the allocator heap, in megabytes.
 * @see bunny_set_memory_check, bunny_allocator_reset, bunny_malloc_failure, bunny_set_maximum_ram
 *
 * @doc-lang fr
 * @brief Fonction historique utilisée pour définir la taille maximale du tas de l'allocateur Bunny.
 * @description Cette fonction n'est efficace qu'avant toute allocation réalisée par l'allocateur Bunny. Elle définit la taille maximale du tas réservé à l'allocateur, en mégaoctets.
 * @description Lorsque la mémoire allouée atteint cette taille, les fonctions d'allocation gérées par l'allocateur Bunny commencent à échouer. Par défaut, la limite est de 20 Mo.
 * @param megabytes La taille maximale du tas de l'allocateur, en mégaoctets.
 * @see bunny_set_memory_check, bunny_allocator_reset, bunny_malloc_failure, bunny_set_maximum_ram
 */
extern "C" void		set_max_heap_size(size_t	data)
{
  bunny_set_maximum_ram(data * 1024 * 1024);
}

extern "C" size_t	get_max_heap_size(void)
{
  return (heap_size);
}

extern "C" size_t	get_nb_alloc(void)
{
  struct memhead	*head;

  head = memory_head();
  return (head->alloc);
}

static int		check_list(struct memchunk	*chunk)
{
  if (chunk == NULL)
    return (0);
  struct memchunk	*ch;
  size_t		j;
  int			i;

  i = 0;
  ch = chunk;
  do
    {
      if (ch->border0 != border0 || ch->border1 != border1)
	{
	  fprintf(stderr, "Altered chunk found: %p\n", ch->data);
	  i += 1;
	}
      else
	{
	  j = chunk->real_size;
	  while (j < chunk->tree->chunk_size && chunk->data[j] == 0x21)
	    j += 1;
	  if (j != chunk->tree->chunk_size)
	    i += 1;
	}
      ch = ch->next;
    }
  while (ch != chunk);
  return (i);
}

static int		check_tree(struct memtree	*tree)
{
  if (tree == NULL)
    return (0);
  int			i;

  i = check_list(tree->allocated);
  i += check_list(tree->freed);
  i += check_tree(tree->lesser);
  i += check_tree(tree->greater);
  return (i);
}

void			check_memory_state(void)
{
  t_sysfree		sysfree = free; /* (t_sysfree)dlsym(RTLD_NEXT, "free"); */

  if (memory_check == 0)
    {
      sysfree(memory_head());
      return ;
    }
  struct memhead	*head;
  int			i;

  head = memory_head();
  fprintf(stderr, "Call to malloc: %zu\n", head->alloc_count);
  fprintf(stderr, "Sum of all byte requested: %zu\n", head->total_count);
  fprintf(stderr, "Allocated chunks at the end of the program: %zu\n", head->alloc);
  fprintf(stderr, "Allocated bytes at the end of the program: %zu\n", head->total);
  i = check_tree(head->first);
  fprintf(stderr, "Altered chunks: %d\n", i);
  sysfree(memory_head());
  if (i)
    {
#ifdef			__linux__
      kill(getpid(), SIGSEGV);
#endif
      bunny_usleep(2e6);
      exit(EXIT_FAILURE);
    }
}

static bool		malloc_failure = false;

/**
 * @doc
 * @doc-symbol bunny_malloc_failure
 * @doc-kind function
 * @doc-module allocator
 * @doc-order 220
 * @doc-since 11
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Forces Bunny allocation functions to fail.
 * @description When enabled, any call to bunny_malloc, bunny_calloc or bunny_realloc fails and returns NULL.
 * @description This function is mainly useful for tests that need to exercise allocation failure paths. Use with caution.
 * @param fail Send true to make allocations fail, false to restore normal allocation behavior.
 * @see bunny_malloc, bunny_calloc, bunny_realloc
 *
 * @doc-lang fr
 * @brief Force l'échec des fonctions d'allocation Bunny.
 * @description Lorsque ce mode est activé, tout appel à bunny_malloc, bunny_calloc ou bunny_realloc échoue et renvoie NULL.
 * @description Cette fonction est surtout utile pour tester les chemins d'échec d'allocation. Utilisez-la avec prudence.
 * @param fail Envoyez true pour faire échouer les allocations, false pour restaurer le comportement normal.
 * @see bunny_malloc, bunny_calloc, bunny_realloc
 */
void			bunny_malloc_failure(bool	f)
{
  malloc_failure = f;
}

/**
 * @doc
 * @doc-symbol bunny_malloc
 * @doc-kind function
 * @doc-module allocator
 * @doc-order 100
 * @doc-since 2
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Allocates a memory block with the Bunny allocator.
 * @description Reserves the requested amount of bytes and returns a pointer to the first byte of the allocated memory block. If there is not enough memory available, the function returns NULL.
 * @description The returned memory block must be freed with bunny_free.
 * @param size The amount of bytes to reserve.
 * @return-case success The address of the first byte of the allocated memory block.
 * @return-case failure NULL.
 * @error ENOMEM Out of memory. If BUNNY_ALLOCATOR_DEACTIVATED was not set at library compile time, this means the prereserved memory space is exhausted. See bunny_set_maximum_ram for more information about this prereserved memory space.
 * @log "allocator"
 * @section Additional informations When BUNNY_ALLOCATOR_DEACTIVATED is set at library compile time, bunny_malloc becomes a wrapper around malloc with additional log output.
 * @section Additional informations When BUNNY_ALLOCATOR_DEACTIVATED is not set at library compile time, bunny_malloc allocates memory inside a special space with a delimited size.
 * @see bunny_set_maximum_ram, bunny_free
 *
 * @doc-lang fr
 * @brief Alloue un bloc mémoire avec l'allocateur Bunny.
 * @description Réserve la quantité demandée d'octets et renvoie un pointeur vers le premier octet du bloc mémoire alloué. S'il n'y a pas assez de mémoire disponible, la fonction renvoie NULL.
 * @description Le bloc mémoire renvoyé doit être libéré avec bunny_free.
 * @param size La quantité d'octets à réserver.
 * @return-case success L'adresse du premier octet du bloc mémoire alloué.
 * @return-case failure NULL.
 * @error ENOMEM Mémoire insuffisante. Si BUNNY_ALLOCATOR_DEACTIVATED n'a pas été défini à la compilation de la bibliothèque, cela signifie que l'espace mémoire préréservé est épuisé. Consultez bunny_set_maximum_ram pour plus d'informations sur cet espace mémoire préréservé.
 * @log "allocator"
 * @section Informations supplémentaires Lorsque BUNNY_ALLOCATOR_DEACTIVATED est défini à la compilation de la bibliothèque, bunny_malloc devient un emballage autour de malloc avec une sortie de log supplémentaire.
 * @section Informations supplémentaires Lorsque BUNNY_ALLOCATOR_DEACTIVATED n'est pas défini à la compilation de la bibliothèque, bunny_malloc alloue la mémoire dans un espace spécial de taille limitée.
 * @see bunny_set_maximum_ram, bunny_free
 */
void			*bunny_malloc(size_t		data)
{
  if (malloc_failure)
    return (NULL);
  // To ensure a precise behaviour everywhere
  if (data == 0)
    return (NULL);

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
  void			*ptr;

  if ((ptr = malloc(data)) == NULL)
    scream_error_if(return (NULL), errno, PATTERN, "allocator", data, ptr);
  scream_log_if(PATTERN, "allocator", data, ptr);
  return (ptr);
#endif

  struct memhead	*head;
  struct memchunk	*node;
  size_t		jam;

  jam = data;
  if (data % MEMORY_CHUNK_SIZE)
    data += MEMORY_CHUNK_SIZE - (data % MEMORY_CHUNK_SIZE);
  head = memory_head();
  if ((node = get_node(head, data)) == NULL)
    scream_error_if(return (NULL), ENOMEM, PATTERN, "allocator", data, node);
  head->alloc_count += 1;
  head->total_count += data;
  head->alloc += 1;
  head->total += data;
  node->border0 = border0;
  node->border1 = border1;
  node->data = &((char*)node)[sizeof(struct memchunk)];
  node->real_size = jam;
  for (; jam < data; ++jam)
    node->data[jam] = 0x21;
  scream_log_if(PATTERN, "allocator", data, node->data);
  return (node->data);
}

