/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_ALLOCATOR_H__
# define			__LAPIN_PRIVATE_ALLOCATOR_H__

# define			MEMORY_CHUNK_SIZE			64

struct				memtree;
struct				memchunk
{
  size_t			border0;
  struct memtree		*tree;
  struct memchunk		*prev;
  struct memchunk		*next;
  char				*data;
  size_t			real_size;
  size_t			border1;
};

struct				memtree
{
  size_t			chunk_size;
  struct memchunk		*allocated;
  struct memchunk		*freed;
  struct memtree		*greater;
  struct memtree		*lesser;
};

struct				memhead
{
  size_t			alloc_count;
  size_t			total_count;
  size_t			alloc;
  size_t			total;
  struct memtree		*first;
  void				*limit;
  char				*last_position;
};

struct memchunk			*get_node(struct memhead		*head,
					  size_t			data);

#endif	/*			__LAPIN_PRIVATE_ALLOCATOR_H__	*/

