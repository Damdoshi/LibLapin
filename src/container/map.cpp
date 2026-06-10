// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdlib.h>
#include		<stdint.h>
#include		"lapin_private.h"

#define			PATTERN		"%p cmp_func, %p dup_func, %p del_func, %p parameter -> %p"

struct                 bunny_map
{
  void                 *data;
  void                 *key;
  size_t               nbr_children;
  struct bunny_map     *up;
  struct bunny_map     *right;
  struct bunny_map     *left;
  t_bunny_map_cmp      cmp;
  t_bunny_map_dup      dup;
  t_bunny_map_del      del;
  void                 *param;
};

/*!
** Create an empty binary map.
**
** The comparison function orders keys. Optional duplication and deletion
** callbacks allow the map to own key storage. The param pointer is forwarded to
** all three callbacks.
**
** \param cmp Key comparator, or NULL to compare raw pointer values.
** \param dup Optional key duplication function.
** \param del Optional key deletion function.
** \param param User parameter sent to cmp, dup and del.
** \return A new map, or NULL on allocation error.
*/
/**
 * @doc
 * @doc-symbol bunny_new_map
 * @doc-kind function
 * @doc-module map
 * @doc-order 180
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates an empty map.
 * @param cmp The optional key comparison callback.
 * @param dup The optional key duplication callback.
 * @param del The optional key deletion callback.
 * @param param The user pointer forwarded to map callbacks.
 * @return-success Returns the newly allocated map.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see string_map, int_map, bunny_delete_map
 *
 * @doc-lang fr
 * @brief Crée une map vide.
 * @param cmp Le callback optionnel de comparaison des clés.
 * @param dup Le callback optionnel de duplication des clés.
 * @param del Le callback optionnel de suppression des clés.
 * @param param Le pointeur utilisateur transmis aux callbacks de map.
 * @return-success Renvoie la map nouvellement allouée.
 * @return-failure Renvoie $CNULL@ si l'allocation échoue.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see string_map, int_map, bunny_delete_map
 */
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

/*!
** Delete a map node and its whole subtree.
**
** Stored data pointers are not freed. Keys are released with the map deletion
** callback when one was provided.
**
** \param _map The map or subtree to destroy.
** \return The number of nodes that were deleted.
*/
/**
 * @doc
 * @doc-symbol bunny_delete_map
 * @doc-kind function
 * @doc-module map
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a map and every map node.
 * @param map The map to delete.
 * @return-success Returns the number of removed entries.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Détruit une map et tous ses nœuds.
 * @param map La map à détruire.
 * @return-success Renvoie le nombre d'entrées retirées.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_map
 */
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

/*!
** Empty a map while keeping its root node usable.
**
** Children are deleted and the root data is cleared. Stored data pointers are
** not freed. Keys are released through the map deletion callback when needed.
**
** \param _map The map to clear.
** \return The number of nodes that were removed or cleared.
*/
/**
 * @doc
 * @doc-symbol bunny_map_clear
 * @doc-kind function
 * @doc-module map
 * @doc-order 210
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Removes every entry from a map while keeping the root.
 * @param map The map to clear.
 * @return-success Returns the number of removed entries.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Retire toutes les entrées d'une map en conservant la racine.
 * @param map La map à vider.
 * @return-success Renvoie le nombre d'entrées retirées.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_map
 */
size_t			bunny_map_clear(t_bunny_map		*_map)
{
  struct bunny_map	*map = (struct bunny_map*)_map;
  size_t		n = map->nbr_children;

  if (map->right)
    bunny_delete_map((t_bunny_map*)map->right);
  if (map->left)
    bunny_delete_map((t_bunny_map*)map->left);
  if (map->del && map->key)
    map->del(map->key, map->param);
  map->data = NULL;
  map->key = NULL;
  map->right = NULL;
  map->left = NULL;
  map->nbr_children = 0;
  return (n);
}

#undef			PATTERN
#define			PATTERN		"%p map, %p key, %s create -> %p"

/*!
** Find or create the node matching a key.
**
** When create is true, missing nodes are allocated and inserted according to
** the map comparator. When create is false, NULL is returned for missing keys.
**
** \param _map The map to browse.
** \param key The key to search.
** \param create Whether a missing node should be created.
** \return The matching node, or NULL on failure or missing key.
*/
/**
 * @doc
 * @doc-symbol bunny_map_get_subtree
 * @doc-kind function
 * @doc-module map
 * @doc-order 260
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Finds or creates the node matching a key.
 * @param map The map to browse.
 * @param key The key to search.
 * @param create Whether a missing node should be created.
 * @return-success Returns the matching node.
 * @return-failure Returns $CNULL@ if the node is missing and not created, or if allocation fails.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Trouve ou crée le nœud correspondant à une clé.
 * @param map La map à parcourir.
 * @param key La clé à chercher.
 * @param create Indique si un nœud manquant doit être créé.
 * @return-success Renvoie le nœud correspondant.
 * @return-failure Renvoie $CNULL@ si le nœud est absent et non créé, ou si une allocation échoue.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_map
 */
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
      if (create == false)
	scream_error_if
	  (return (NULL), BE_CANNOT_FIND_ELEMENT, PATTERN, "container", map, key,
	   create ? "true" : "false", (void*)NULL);
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
      uintptr_t		a = (uintptr_t)map->key;
      uintptr_t		b = (uintptr_t)key;

      if ((res = (a > b) - (a < b)) == 0)
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

/*!
** Retrieve the data associated with a key.
**
** This is the typed implementation behind the bunny_map_get_data macro.
**
** \param map The map to browse.
** \param key The key to search.
** \return The stored data pointer, or NULL if the key is absent.
*/
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

/*!
** Store a data pointer at the node matching a key.
**
** Missing nodes are created. If a node already stored data, the previous data
** pointer is returned. The previous data is not freed by the map.
**
** \param map The map to edit.
** \param key The key to search or create.
** \param data The data pointer to store.
** \return The previous data pointer, the new data pointer for an empty node, or NULL on error.
*/
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

/*!
** Apply a function to every node of a map.
**
** Nodes are visited recursively. The callback receives the t_bunny_map node,
** not directly the stored data.
**
** \param map The map to browse.
** \param func The function to call on each node.
** \param param User parameter sent to func.
*/
/**
 * @doc
 * @doc-symbol bunny_map_foreach
 * @doc-kind function
 * @doc-module map
 * @doc-order 340
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Applies a callback to every node of a map.
 * @param map The map to traverse.
 * @param func The callback to call.
 * @param param The user pointer forwarded to $Sfunc@.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see t_bunny_map
 *
 * @doc-lang fr
 * @brief Applique un callback à chaque nœud d'une map.
 * @param map La map à parcourir.
 * @param func Le callback à appeler.
 * @param param Le pointeur utilisateur transmis à $Sfunc@.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see t_bunny_map
 */
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

/*!
** Apply a function to every node of a map using a thread pool.
**
** If the thread pool cannot accept all tasks, remaining nodes are processed by
** the caller thread before waiting for completion.
**
** \param pol The thread pool used to schedule callbacks.
** \param map The map to browse.
** \param func The function to call on each node.
** \param param User parameter sent to func.
** \return True if all work was scheduled normally, false if a fallback happened.
*/
/**
 * @doc
 * @doc-symbol bunny_map_fast_foreach
 * @doc-kind function
 * @doc-module map
 * @doc-order 360
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Applies a callback to every map node using a thread pool.
 * @param pool The thread pool used to distribute work.
 * @param map The map to traverse.
 * @param func The callback to call.
 * @param param The user pointer forwarded to $Sfunc@.
 * @return-success Returns $Ctrue@ if every task could be scheduled normally.
 * @return-failure Returns $Cfalse@ if some work had to be done by the main thread.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see bunny_thread_wait_completion
 *
 * @doc-lang fr
 * @brief Applique un callback à chaque nœud d'une map avec un pool de threads.
 * @param pool Le pool de threads utilisé pour répartir le travail.
 * @param map La map à parcourir.
 * @param func Le callback à appeler.
 * @param param Le pointeur utilisateur transmis à $Sfunc@.
 * @return-success Renvoie $Ctrue@ si toutes les tâches ont pu être planifiées normalement.
 * @return-failure Renvoie $Cfalse@ si une partie du travail a dû être faite par le thread principal.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see bunny_thread_wait_completion
 */
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

  if (nod->left && bunny_map_fast_foreach(pol, (t_bunny_map*)nod->left, func, param) == false)
    {
      if (errorcode == -1)
	errorcode = bunny_errno;
      ok = false;
      pol = NULL;
    }

  if (nod->data != NULL)
    {
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
    }

  if (nod->right && bunny_map_fast_foreach(pol, (t_bunny_map*)nod->right, func, param) == false)
    {
      if (errorcode == -1)
	errorcode = bunny_errno;
      ok = false;
      pol = NULL;
    }

  if (errorcode == -1)
    errorcode = 0;

  bunny_thread_wait_completion(pol);
  if (ok == false)
    scream_error_if
      (return (false), errorcode, PATTERN, "container", pol, map, func, param, "false");

  scream_log_if(PATTERN, "container", pol, map, func, param, "true");
  return (true);
}

typedef struct		s_bunny_io
{
  size_t		index;
  t_bunny_map		**map;
}			t_bunny_io;

static void		stack_map(t_bunny_map			*map,
				  void				*_x)
{
  t_bunny_io		*x = (t_bunny_io*)_x;

  x->map[x->index++] = map;
}

/*!
** Build an iterator array for a map.
**
** The public bunny_map_begin macro allocates a temporary buffer with alloca and
** calls this function. The resulting array is terminated by NULL and can be
** browsed with bunny_map_next.
**
** \param map The map to flatten into an iterator array.
** \param buf Storage for bunny_map_size(map) + 1 node pointers.
** \return buf filled with map nodes and terminated by NULL.
*/
t_bunny_map		**_bunny_map_begin(t_bunny_map		*map,
					   void			*buf)
{
  t_bunny_io		io = {0, (t_bunny_map**)buf};

  bunny_map_foreach(map, stack_map, &io);
  io.map[io.index] = NULL;
  return ((t_bunny_map**)buf);
}

