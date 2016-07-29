// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// LibLapin

#include		"lapin_private.h"

static struct memchunk	*pf2a(struct memtree			*tree) // push freed to allocated
{
  struct memchunk	*ch = tree->freed;

  /// If the elemen inside the freed list is the last, remove it and set to null
  if (tree->freed == tree->freed->next)
    tree->freed = NULL;
  /// Else, the next is now the first
  else
    {
      tree->freed->next->prev = tree->freed->prev;
      tree->freed->prev->next = tree->freed->next;
      tree->freed = tree->freed->next;
    }

  /// If the former freed space is the first one to be reallocated, create a loop
  if ((ch->next = tree->allocated) == NULL)
    {
      ch->prev = ch;
      ch->next = ch;
    }
  /// If there is already several
  else
    {
      ch->prev = ch->next->prev;
      ch->next->prev = ch;
      ch->prev->next = ch;
    }
  tree->allocated = ch;
  return (ch);
}

static struct memtree	*create_new_tree(struct memhead		*head,
					 size_t			data)
{
  struct memtree	*tree;

  tree = (struct memtree*)head->last_position;
  if (((size_t)head->last_position + sizeof(*tree)) > (size_t)head->limit)
    return (NULL);
  head->last_position += sizeof(*tree);
  tree->chunk_size = data;
  tree->allocated = NULL;
  tree->freed = NULL;
  tree->greater = NULL;
  tree->lesser = NULL;
  return (tree);
}

static struct memchunk	*add_to_tree(struct memhead		*head,
				     struct memtree		*tree)
{
  struct memchunk	*ch;

  ch = (struct memchunk*)head->last_position;
  if (((size_t)head->last_position + sizeof(*ch) + tree->chunk_size) > (size_t)head->limit)
    return (NULL);
  head->last_position += sizeof(*ch) + tree->chunk_size;

  /// insert into double linked list
  if (tree->allocated == NULL)
    {
      ch->next = ch;
      ch->prev = ch;
    }
  else
    {
      ch->next = tree->allocated;
      ch->prev = tree->allocated->prev;
      ch->next->prev = ch;
      ch->prev->next = ch;
    }

  tree->allocated = ch;
  ch->tree = tree;
  return (ch);
}

static struct memchunk	*treef(struct memhead			*head,
			       struct memtree			**slot,
			       struct memtree			*tree,
			       size_t				data)
{
  /// If there is no tree
  if (tree == NULL)
    {
      if ((*slot = create_new_tree(head, data)) == NULL)
	return (NULL);
      tree = *slot;
    }
  /// If I am on the right node
  if (tree->chunk_size == data)
    {
      if (tree->freed != NULL)
	return (pf2a(tree));
      return (add_to_tree(head, tree));
    }
  /// If the current node data is to low
  if (tree->chunk_size < data)
    return (treef(head, &tree->greater, tree->greater, data));
  /// If the current node data is to high
  return (treef(head, &tree->lesser, tree->lesser, data));
}

struct memchunk		*get_node(struct memhead		*head,
				  size_t			data)
{
  return (treef(head, &head->first, head->first, data));
}
