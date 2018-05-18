// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include		<stdlib.h>
#include		"lapin_private.h"

#define			PATTERN		"%p cmp_func, %p dup_func, %p del_func, %p parameter -> %p"

t_bunny_map		*bunny_new_map(t_bunny_map_cmp		cmp,
				       t_bunny_map_dup		dup,
				       t_bunny_map_del		del,
				       void			*param)
{
  struct bunny_map	*map;

  if ((map = (struct bunny_map*)bunny_malloc(sizeof(*map))) == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "container",
       cmp, dup, del, param, (void*)NULL);
  map->data = NULL;
  map->key = NULL;
  map->nbr_children = 0;
  map->up = NULL;
  map->right = NULL;
  map->left = NULL;
  map->cmp = cmp;
  map->dup = dup;
  map->del = del;
  map->param = param;
  scream_log_if(PATTERN, "container", cmp, dup, del, param, map);
  return ((t_bunny_map*)map);
}

size_t			bunny_delete_map(t_bunny_map		*_map)
{
  struct bunny_map	*map = (struct bunny_map*)_map;
  size_t		n = map->nbr_children;

  if (map->right)
    bunny_delete_map((t_bunny_map*)map->right);
  if (map->left)
    bunny_delete_map((t_bunny_map*)map->left);
  if (map->up)
    {
      map->up->nbr_children -= n;
      if (map->up->right == map)
	map->up->right = NULL;
      if (map->up->left == map)
	map->up->left = NULL;
    }
  if (map->del)
    map->del(map->key, map->param);
  bunny_free(map);
  scream_log_if("%p -> %zu", "container", _map, n);
  return (n);
}

size_t			bunny_map_clear(t_bunny_map		*_map)
{
  struct bunny_map	*map = (struct bunny_map*)_map;
  size_t		n = map->nbr_children;

  if (map->right)
    bunny_delete_map((t_bunny_map*)map->right);
  if (map->left)
    bunny_delete_map((t_bunny_map*)map->left);
  map->nbr_children = 0;
  return (n);
}

#undef			PATTERN
#define			PATTERN		"%p map, %p key, %s create -> %p"

t_bunny_map		*bunny_map_get_subtree(t_bunny_map	*_map,
					       void		*key,
					       bool		create)
{
  t_bunny_map		*tmp;
  struct bunny_map	*map = (struct bunny_map*)_map;
  struct bunny_map	*nw;
  int			res;

  if (map->key == NULL)
    {
      if (map->dup)
	{
	  if ((map->key = map->dup(key, map->param)) == NULL)
	    scream_error_if
	      (return (NULL), BE_CANNOT_DUPLICATE, PATTERN, "container", map, key,
	       create ? "true" : "false", (void*)NULL);
	}
      else
	map->key = key;
      for (nw = map; nw != NULL; nw = nw->up)
	nw->nbr_children += 1;
      scream_log_if(PATTERN, "container", map, key, create ? "true" : "false", _map);
      return (_map);
    }

  if (map->cmp)
    {
      if ((res = map->cmp(map->key, key, map->param)) == 0)
	{
	  scream_log_if(PATTERN, "container", map, key, create ? "true" : "false", _map);
	  return (_map);
	}
    }
  else
    {
      if ((res = (ssize_t)map->key - (ssize_t)key) == 0)
	{
	  scream_log_if(PATTERN, "container", map, key, create ? "true" : "false", _map);
	  return (_map);
	}
    }

  if (res > 0)
    {
      if (map->left == NULL)
	{
	  if (create == false)
	    scream_error_if
	      (return (NULL), BE_CANNOT_FIND_ELEMENT, PATTERN, "container",
	       map, key, create ? "true" : "false", (void*)NULL);
	  if ((map->left = (struct bunny_map*)bunny_new_map
	       (map->cmp, map->dup, map->del, map->param)) == NULL)
	    scream_error_if
	      (return (NULL), bunny_errno, PATTERN, "container",
	       map, key, create ? "true" : "false", (void*)NULL);
	  map->left->up = map;
	}
      if ((tmp = bunny_map_get_subtree((t_bunny_map*)map->left, key, create)) == NULL)
	scream_error_if
	  (return (NULL), BE_CANNOT_DUPLICATE, PATTERN, "container",
	   map, key, create ? "true" : "false", tmp);
      scream_log_if(PATTERN, "container", map, key, create ? "true" : "false", tmp);
      return (tmp);
    }

  if (map->right == NULL)
    {
      if (create == false)
	scream_error_if
	  (return (NULL), BE_CANNOT_FIND_ELEMENT, PATTERN, "container",
	   map, key, create ? "true" : "false", (void*)NULL);
      if ((map->right = (struct bunny_map*)bunny_new_map
	   (map->cmp, map->dup, map->del, map->param)) == NULL)
	scream_error_if
	  (return (NULL), bunny_errno, PATTERN, "container",
	   map, key, create ? "true" : "false", (void*)NULL);
      map->right->up = map;
    }
  if ((tmp = bunny_map_get_subtree((t_bunny_map*)map->right, key, create)) == NULL)
    scream_error_if
      (return (NULL), BE_CANNOT_DUPLICATE, PATTERN, "container",
       map, key, create ? "true" : "false", tmp);
  scream_log_if(PATTERN, "container", map, key, create ? "true" : "false", tmp);
  return (tmp);
}

#undef			PATTERN
#define			PATTERN		"%p map, %p key -> %p"

void			*_bunny_map_get_data(t_bunny_map	*map,
					     void		*key)
{
  struct bunny_map	*tree;

  if ((tree = (struct bunny_map*)bunny_map_get_subtree(map, key, false)) == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "container", map, key, tree);
  scream_log_if(PATTERN, "container", map, key, tree->data);
  return (tree->data);
}

#undef			PATTERN
#define			PATTERN		"%p map, %p key, %p data -> %p"

void			*_bunny_map_set_data(t_bunny_map	*map,
					     void		*key,
					     void		*data)
{
  struct bunny_map	*tree;
  void			*old;

  if ((tree = (struct bunny_map*)bunny_map_get_subtree(map, key, true)) == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "container", map, key, data, tree);
  old = tree->data;
  tree->data = data;
  if (old)
    {
      scream_log_if(PATTERN, "container", map, key, data, old);
      return (old);
    }
  scream_log_if(PATTERN, "container", map, key, data, data);
  return (data);
}

void			bunny_map_foreach(t_bunny_map		*map,
					  void			(*func)
					  (t_bunny_map		*map,
					   void			*param),
					  void			*param)
{
  struct bunny_map	*nod = (struct bunny_map*)map;

  if (nod == NULL)
    {
      scream_log_if("%p map, %p func, %p param", "container", map, func, param);
      return ;
    }
  if (nod->left)
    bunny_map_foreach((t_bunny_map*)nod->left, func, param);
  if (nod->data != NULL)
    func((t_bunny_map*)nod, param);
  if (nod->right)
    bunny_map_foreach((t_bunny_map*)nod->right, func, param);
  scream_log_if("%p map, %p func, %p param", "container", map, func, param);
}

#undef			PATTERN
#define			PATTERN	"%p threadpool, %p map, %p func, %p param -> %s"

bool			bunny_map_fast_foreach(t_bunny_threadpool *pol,
					       t_bunny_map	*map,
					       void		(*func)
					       (t_bunny_map	*map,
						void		*param),
					       void		*param)
{
  struct bunny_map	*nod = (struct bunny_map*)map;
  int			errorcode = -1;
  bool			ok;

  if ((ok = (pol != NULL)) == false)
    errorcode = 0;
  if (nod == NULL)
    {
      scream_log_if(PATTERN, "container", pol, map, func, param, "true");
      bunny_thread_wait_completion(pol);
      return (true);
    }

  if (nod->left)
    ok = ok && bunny_map_fast_foreach(pol, (t_bunny_map*)nod->left, func, param);
  if (ok == false && errorcode == -1)
    errorcode = bunny_errno;

  if (pol == NULL || ok == false)
    func((t_bunny_map*)nod, param);
  else
    if (bunny_thread_push(pol, (void (*)(void*,void*))func, (t_bunny_map*)nod, param) == false)
      {
	if (errorcode == -1)
	  errorcode = bunny_errno;
      	func((t_bunny_map*)nod, param);
	ok = false;
	pol = NULL;
      }

  if (nod->right)
    ok = ok && bunny_map_fast_foreach(pol, (t_bunny_map*)nod->right, func, param);
  if (ok == false && errorcode == -1)
    errorcode = bunny_errno;

  if (errorcode == -1)
    errorcode = 0;

  bunny_thread_wait_completion(pol);
  if (ok == false)
    scream_error_if
      (return (false), errorcode, PATTERN, "container", pol, map, func, param, "false");

  scream_log_if(PATTERN, "container", pol, map, func, param, "true");
  return (true);
}


