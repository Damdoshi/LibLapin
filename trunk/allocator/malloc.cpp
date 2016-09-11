// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<signal.h>
#include		<string.h>
#include		<unistd.h>
#include		"lapin_private.h"

typedef void		*(*t_sysmalloc)(size_t);
typedef void		(*t_sysfree)(void*);

static size_t		heap_size = 20 * 1024 * 1024;
int			memory_check = 0;
size_t			border0;
size_t			border1;

void			check_memory_state(void);

struct memhead		*memory_head(void)
{
  static struct memhead	*head = NULL;

  if (head == NULL)
    {
      t_sysmalloc	sysmalloc = malloc;
      size_t		s = heap_size + sizeof(*head);

      memset(&border0, 0x42, sizeof(border0));	// Because size_t size is quite volatile...
      memset(&border1, 0x84, sizeof(border1));
      if ((head = (struct memhead*)sysmalloc(s)) == NULL)
	{
	  fprintf(stderr, "Initial memory allocation failed. Exiting right now. Sorry.\n");
	  exit(EXIT_FAILURE);
	}
      head->alloc_count = 0;
      head->total_count = 0;
      head->alloc = 0;
      head->total = 0;
      head->first = NULL;
      head->limit = &(((char*)head)[s]);
      head->last_position = &(((char*)head)[sizeof(*head)]);
      atexit(check_memory_state);
    }
  return (head);
}

void			bunny_set_maximum_ram(size_t	byt)
{
  static int		edited;

  if (!edited)
    heap_size = byt;
  edited = 1;
}

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
      kill(getpid(), SIGSEGV);
      usleep(2e6);
      exit(EXIT_FAILURE);
    }
}

void			*bunny_malloc(size_t		data)
{
  struct memhead	*head;
  struct memchunk	*node;
  size_t		jam;

  jam = data;
  if (data % MEMORY_CHUNK_SIZE)
    data += MEMORY_CHUNK_SIZE - (data % MEMORY_CHUNK_SIZE);
  head = memory_head();
  if ((node = get_node(head, data)) == NULL)
    return (NULL);
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
  return (node->data);
}

