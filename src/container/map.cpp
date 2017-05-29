// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include		<stdlib.h>
#include		<alloca.h>
#include		"lapin_private.h"

struct			bunny_map
{
  void			*data;
  void			*key;
  size_t		nbr_children;
  struct bunny_map	*up;
  struct bunny_map	*right;
  struct bunny_map	*left;
  t_bunny_map_cmp	cmp;
  t_bunny_map_dup	dup;
  t_bunny_map_del	del;
  void			*param;
};

t_bunny_map		*bunny_new_map(t_bunny_map_cmp		cmp,
				       t_bunny_map_dup		dup,
				       t_bunny_map_del		del,
				       void			*param)
{
  struct bunny_map	*map;

  if ((map = (struct bunny_map*)bunny_malloc(sizeof(*map))) == NULL)
    return (NULL);
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
  return (n);
}

t_bunny_map		*bunny_map_get_subtree(t_bunny_map	*_map,
					       void		*key,
					       bool		create)
{
  struct bunny_map	*map = (struct bunny_map*)_map;
  struct bunny_map	*nw;
  int			res;

  if (map->key == NULL)
    {
      if (map->dup)
	{
	  if ((map->key = map->dup(key, map->param)) == NULL)
	    return (NULL);
	}
      else
	map->key = key;
      for (nw = map; nw != NULL; nw = nw->up)
	nw->nbr_children += 1;
      return (_map);
    }

  if (map->cmp)
    {
      if ((res = map->cmp(map->key, key, map->param)) == 0)
	return (_map);
    }
  else
    {
      if ((res = (ssize_t)map->key - (ssize_t)key) == 0)
	return (_map);
    }

  if (res > 0)
    {
      if (map->left == NULL)
	{
	  if (create == false)
	    return (NULL);
	  if ((map->left = (struct bunny_map*)bunny_new_map
	       (map->cmp, map->dup, map->del, map->param)) == NULL)
	    return (NULL);
	  map->left->up = map;
	}
      return (bunny_map_get_subtree((t_bunny_map*)map->left, key, create));
    }

  if (map->right == NULL)
    {
      if (create == false)
	return (NULL);
      if ((map->right = (struct bunny_map*)bunny_new_map
	   (map->cmp, map->dup, map->del, map->param)) == NULL)
	return (NULL);
      map->right->up = map;
    }
  return (bunny_map_get_subtree((t_bunny_map*)map->right, key, create));
}

void			*_bunny_map_get_data(t_bunny_map	*map,
					     void		*key)
{
  struct bunny_map	*tree;

  if ((tree = (struct bunny_map*)bunny_map_get_subtree(map, key, false)) == NULL)
    return (NULL);
  return (tree->data);
}

void			*_bunny_map_set_data(t_bunny_map	*map,
					     void		*key,
					     void		*data)
{
  struct bunny_map	*tree;
  void			*old;

  if ((tree = (struct bunny_map*)bunny_map_get_subtree(map, key, true)) == NULL)
    return (NULL);
  old = tree->data;
  tree->data = data;
  if (old)
    return (old);
  return (data);
}

void			bunny_map_foreach(t_bunny_map		*map,
					  void			(*func)
					  (void			*nod,
					   void			*param),
					  void			*param)
{
  struct bunny_map	*nod = (struct bunny_map*)map;

  if (nod == NULL)
    return ;
  if (nod->left)
    bunny_map_foreach((t_bunny_map*)nod->left, func, param);
  if (nod->data != NULL)
    func(nod->data, param);
  if (nod->right)
    bunny_map_foreach((t_bunny_map*)nod->right, func, param);
}

bool			bunny_map_fast_foreach(t_bunny_threadpool *pol,
					       t_bunny_map	*map,
					       void		(*func)
					       (void		*nod,
						const void	*param),
					       const void	*param)
{
  struct bunny_map	*nod = (struct bunny_map*)map;
  bool			ok;

  ok = (pol != NULL);
  if (nod == NULL)
    return (true);

  if (nod->left)
    ok = ok && bunny_map_fast_foreach(pol, (t_bunny_map*)nod->left, func, param);

  if (pol == NULL || ok == false)
    func(nod->data, param);
  else
    if (bunny_thread_push(pol, func, nod->data, param) == false)
      {
	func(nod->data, param);
	ok = false;
	pol = NULL;
      }

  if (nod->right)
    ok = ok && bunny_map_fast_foreach(pol, (t_bunny_map*)nod->right, func, param);
  return (ok);
}


