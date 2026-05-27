// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

struct			bunny_ressource_to_load
{
  const char		*file;
  void			**target;
  size_t		*subtarget;			// For file size
};


static bool		valid_loading_ressource(struct bunny_ressource_to_load *res)
{
  if (res == NULL || res->file == NULL || res->target == NULL)
    return (false);
  *res->target = NULL;
  return (true);
}

static t_bunny_response	loading_async_response(void				*item,
					       struct bunny_loading_screen *ld)
{
  t_bunny_response	ret;

  ld->busy = false;
  if (ld->failure)
    return (EXIT_ON_ERROR);
  ld->count += 1;
  if (ld->head.subcontext.async_computation)
    {
      if ((ret = ld->head.subcontext.async_computation
	   ((void*)item, (void*)ld->head.main_structure)) != GO_ON)
	return (ret);
    }
  return (GO_ON);
}

static void		load_picture(t_bunny_ressource_to_load		*_res,
				     struct bunny_loading_screen	*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if (valid_loading_ressource(res) == false ||
      (*res->target = (void*)bunny_load_picture(res->file)) == NULL)
    ld->failure = true;
}

static void		load_pixelarray(t_bunny_ressource_to_load	*_res,
					struct bunny_loading_screen	*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if (valid_loading_ressource(res) == false ||
      (*res->target = (void*)bunny_load_pixelarray(res->file)) == NULL)
    ld->failure = true;
}

static void		load_sprite(t_bunny_ressource_to_load		*_res,
				    struct bunny_loading_screen		*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if (valid_loading_ressource(res) == false ||
      (*res->target = (void*)bunny_load_sprite(res->file)) == NULL)
    ld->failure = true;
}

static void		load_music(t_bunny_ressource_to_load		*_res,
				   struct bunny_loading_screen		*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if (valid_loading_ressource(res) == false ||
      (*res->target = (void*)bunny_load_music(res->file)) == NULL)
    ld->failure = true;
}

static void		load_effect(t_bunny_ressource_to_load		*_res,
				    struct bunny_loading_screen		*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if (valid_loading_ressource(res) == false ||
      (*res->target = (void*)bunny_load_effect(res->file)) == NULL)
    ld->failure = true;
}

static void		load_sound_sprite(t_bunny_ressource_to_load	*_res,
					  struct bunny_loading_screen	*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if (valid_loading_ressource(res) == false ||
      (*res->target = (void*)bunny_load_sound_sprite(res->file)) == NULL)
    ld->failure = true;
}

static void		load_text(t_bunny_ressource_to_load		*_res,
				  struct bunny_loading_screen		*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if (valid_loading_ressource(res) == false ||
      (*res->target = (void*)bunny_load_text(res->file)) == NULL)
    ld->failure = true;
}

static void		load_file(t_bunny_ressource_to_load		*_res,
				  struct bunny_loading_screen		*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if (valid_loading_ressource(res) == false ||
      bunny_load_file(res->file, res->target, res->subtarget) == -1)
    ld->failure = true;
}

static void		load_configuration(t_bunny_ressource_to_load	*_res,
					   struct bunny_loading_screen	*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if (valid_loading_ressource(res) == false ||
      (*res->target = (void*)bunny_open_configuration(res->file, NULL)) == NULL)
    ld->failure = true;
}

static void		run_loading_task(t_bunny_loading_task		*task,
					 struct bunny_loading_screen	*ld)
{
  if (task == NULL || task->function == NULL ||
      task->function(task->data) == false)
    ld->failure = true;
}

static bool		push_loading_ressource(struct bunny_loading_screen	*ld,
					       t_bunny_list			**ptr)
{
  t_bunny_function	func;

  if (&ptr[ld->list_cnt] == &ld->pictures)
    func = (t_bunny_function)load_picture;
  else if (&ptr[ld->list_cnt] == &ld->pixelarrays)
    func = (t_bunny_function)load_pixelarray;
  else if (&ptr[ld->list_cnt] == &ld->sprites)
    func = (t_bunny_function)load_sprite;
  else if (&ptr[ld->list_cnt] == &ld->musics)
    func = (t_bunny_function)load_music;
  else if (&ptr[ld->list_cnt] == &ld->effects)
    func = (t_bunny_function)load_effect;
  else if (&ptr[ld->list_cnt] == &ld->sound_sprites)
    func = (t_bunny_function)load_sound_sprite;
  else if (&ptr[ld->list_cnt] == &ld->texts)
    func = (t_bunny_function)load_text;
  else if (&ptr[ld->list_cnt] == &ld->files)
    func = (t_bunny_function)load_file;
  else if (&ptr[ld->list_cnt] == &ld->configurations)
    func = (t_bunny_function)load_configuration;
  else if (&ptr[ld->list_cnt] == &ld->tasks)
    func = (t_bunny_function)run_loading_task;
  else
    return (false);
  return (bunny_async_computation_push(func, ld->node->data));
}

static t_bunny_response	loading_loop(struct bunny_loading_screen	*ld)
{
  t_bunny_list		**ptr = &ld->pictures;
  t_bunny_list		**end = &(&ld->tasks)[1];
  t_bunny_response	ret;
  double		step;

  if (ld->failure && ld->busy == false)
    return (EXIT_ON_ERROR);

  if (ld->total_ressources <= 0)
    {
      ld->smooth_cursor = 1.0;
      ld->terminated = true;
    }
  else if (ld->busy == false)
    {
      if (ld->node)
	{
	  if (push_loading_ressource(ld, ptr) == false)
	    {
	      ld->failure = true;
	      return (EXIT_ON_ERROR);
	    }
	  ld->busy = true;
	  ld->node = bunny_list_next(ld->node);
	}
      else if (&ptr[ld->list_cnt + 1] < end)
	{
	  ld->list_cnt += 1;
	  ld->node = bunny_list_begin(ptr[ld->list_cnt]);
	}
      else
	ld->node = NULL;
    }

  if (ld->total_ressources > 0)
    {
      step = 0.3 * (((double)ld->count / ld->total_ressources) - ld->smooth_cursor);
      ld->smooth_cursor += step;
      if (ld->count >= ld->total_ressources && ld->smooth_cursor > 0.999)
	{
	  ld->smooth_cursor = 1.0;
	  ld->terminated = true;
	}
    }

  if (ld->head.subcontext.loop)
    {
      if ((ret = ld->head.subcontext.loop(ld->head.main_structure)) != GO_ON)
	return (ret);
    }
  if (ld->terminated)
    return (SWITCH_CONTEXT);
  return (GO_ON);
}

static t_bunny_response	loading_entering(struct bunny_loading_screen	*ld)
{
  t_bunny_list		**ptr = &ld->pictures;
  t_bunny_list		**end = &(&ld->tasks)[1];
  t_bunny_response	ret;
  int			i;

  if (gl_bunny_loop_threadpool == NULL)
    {
      if (bunny_set_async_computation(1) == false)
	return (EXIT_ON_ERROR);
      ld->local_threadpool = true;
    }
  else
    ld->local_threadpool = false;

  ld->terminated = false;
  ld->failure = false;
  ld->smooth_cursor = 0;
  ld->count = 0;
  ld->total_ressources = 0;
  ld->busy = false;
  ld->list_cnt = 0;
  ld->node = bunny_list_begin(*ptr);
  for (i = 0; &ptr[i] != end; ++i)
    ld->total_ressources += bunny_list_size(ptr[i]);

  if (ld->head.subcontext.entering_context)
    {
      if ((ret = ld->head.subcontext.entering_context
	   ((void*)ld->head.main_structure)) != GO_ON)
	return (ret);
    }

  return (GO_ON);
}

static void		loading_leaving(t_bunny_response		res,
					struct bunny_loading_screen	*ld)
{
  if (ld->local_threadpool)
    bunny_set_async_computation(0);
  if (ld->failure)
    bunny_clear_all_loaded_ressources((t_bunny_loading_screen*)ld);
  if (ld->head.subcontext.leaving_context)
    ld->head.subcontext.leaving_context(res, ld->head.main_structure);
}

/**
 * @doc
 * @doc-symbol gl_bunny_loading_context
 * @doc-kind variable
 * @doc-module context
 * @doc-order 620
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Built-in context that loads resources and custom tasks while a subcontext animates the screen.
 * @description The loading context pushes one resource or custom task at a time to the bunny_loop asynchronous computation pool and updates $Spercent_completion@ smoothly while $Ssubcontext.loop@ and $Ssubcontext.display@ keep the loading screen alive.
 * @description $Ssubcontext.async_computation@ is called from the bunny_loop thread after each completed resource or custom task. It is the right place to perform main-thread integration work such as binding a loaded configuration to application structures.
 * @see t_bunny_loading_screen
 *
 * @doc-lang fr
 * @brief Contexte intégré chargeant des ressources et des tâches personnalisées pendant qu'un sous-contexte anime l'écran.
 * @description Le contexte de chargement pousse une ressource ou une tâche personnalisée à la fois vers la réserve de calcul asynchrone de bunny_loop et met à jour $Spercent_completion@ de manière lissée pendant que $Ssubcontext.loop@ et $Ssubcontext.display@ gardent l'écran de chargement vivant.
 * @description $Ssubcontext.async_computation@ est appelé depuis le thread de bunny_loop après chaque ressource ou tâche personnalisée terminée. C'est l'endroit adapté pour réaliser l'intégration côté thread principal, par exemple binder une configuration chargée vers les structures de l'application.
 * @see t_bunny_loading_screen
 */
const t_bunny_context	gl_bunny_loading_context =
  {
    bunny_context_key,
    bunny_context_type,
    bunny_context_click,
    bunny_context_move,
    bunny_context_wheel,
    bunny_context_joy_connect,
    bunny_context_joy_button,
    bunny_context_joy_axis,
    bunny_context_get_focus,
    bunny_context_lost_focus,
    bunny_context_resize,
    (t_bunny_loop)loading_loop,
    bunny_context_display,
    bunny_context_close,
    bunny_context_message,
    bunny_context_connect,
    (t_bunny_loop)loading_entering,
    (t_bunny_leaving_context)loading_leaving,
    (t_bunny_async_computation_response)loading_async_response,
    bunny_context_event_response
  };

/**
 * @doc
 * @doc-symbol bunny_init_loading_context
 * @doc-kind function
 * @doc-module context
 * @doc-order 630
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Initializes a loading-screen runtime structure.
 * @param screen Loading screen to initialize.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on allocation error.
 * @see t_bunny_loading_screen
 *
 * @doc-lang fr
 * @brief Initialise une structure d’exécution de loading screen.
 * @param screen Loading screen to initialize.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur d’allocation.
 * @see t_bunny_loading_screen
 */
bool			bunny_init_loading_context(t_bunny_loading_screen *_ld)
{
  struct bunny_loading_screen *ld = (struct bunny_loading_screen*)_ld;
  t_bunny_list		**ptr = &ld->pictures;
  t_bunny_list		**end = &(&ld->tasks)[1];
  int			i;

  for (i = 0; &ptr[i] != end; ++i)
    if ((ptr[i] = bunny_new_list()) == NULL)
      {
	while (--i >= 0)
	  bunny_delete_list(ptr[i]);
	return (false);
      }
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_delete_ressource_hook
 * @doc-kind function
 * @doc-module context
 * @doc-order 670
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Deletes a loading-resource hook.
 * @param hook Hook to delete.
 * @return-success The hook is released.
 * @see t_bunny_loading_screen
 *
 * @doc-lang fr
 * @brief Détruit un hook de ressource à charger.
 * @param hook Hook to delete.
 * @return-success Le hook est libéré.
 * @see t_bunny_loading_screen
 */
void			bunny_delete_ressource_hook(t_bunny_ressource_to_load *ld)
{
  bunny_free(ld);
}

/**
 * @doc
 * @doc-symbol bunny_terminate_loading_context
 * @doc-kind function
 * @doc-module context
 * @doc-order 640
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Releases the lists owned by a loading-screen runtime structure.
 * @param screen Loading screen to terminate.
 * @return-success The loading lists and hooks are released.
 * @see t_bunny_loading_screen
 *
 * @doc-lang fr
 * @brief Libère les listes possédées par une structure de loading screen.
 * @param screen Loading screen to terminate.
 * @return-success Les listes de chargement et hooks sont libérés.
 * @see t_bunny_loading_screen
 */
void			bunny_terminate_loading_context(t_bunny_loading_screen *_ld)
{
  struct bunny_loading_screen *ld = (struct bunny_loading_screen*)_ld;
  t_bunny_list		**ptr = &ld->pictures;
  t_bunny_list		**end = &(&ld->tasks)[1];
  t_bunny_node		*nod;
  int			i;

  for (i = 0; &ptr[i] != end; ++i)
    {
      for (bunny_list_all(ptr[i], nod))
	{
	  if (&ptr[i] == &ld->tasks)
	    bunny_delete_loading_task((t_bunny_loading_task*)nod->data);
	  else
	    bunny_delete_ressource_hook((t_bunny_ressource_to_load*)nod->data);
	}
      bunny_delete_list(ptr[i]);
    }
}

/**
 * @doc
 * @doc-symbol bunny_clear_all_loaded_ressources
 * @doc-kind function
 * @doc-module context
 * @doc-order 650
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Deletes every resource already loaded by a loading context.
 * @param screen Loading screen whose resources must be cleared.
 * @return-success All tracked loaded resources are deleted.
 * @see t_bunny_loading_screen
 *
 * @doc-lang fr
 * @brief Détruit toutes les ressources déjà chargées par un contexte de chargement.
 * @param screen Loading screen whose resources must be cleared.
 * @return-success Toutes les ressources chargées suivies sont détruites.
 * @see t_bunny_loading_screen
 */
void			bunny_clear_all_loaded_ressources(t_bunny_loading_screen *_ld)
{
  struct bunny_ressource_to_load *res;
  struct bunny_loading_screen *ld = (struct bunny_loading_screen*)_ld;
  t_bunny_list		**ptr = &ld->pictures;
  t_bunny_list		**end = &(&ld->tasks)[1];
  t_bunny_node		*nod;
  int			i;

  for (i = 0; &ptr[i] != end; ++i)
    if (ptr[i])
      for (bunny_list_all(ptr[i], nod))
	{
	  if (&ptr[i] == &ld->tasks)
	    continue ;
	  if ((res = bunny_list_data(nod, struct bunny_ressource_to_load*)) == NULL ||
	      res->target == NULL || *res->target == NULL)
	    continue ;

	  if (&ptr[i] == &ld->pictures)
	    bunny_delete_clipable((t_bunny_clipable*)*res->target);
	  else if (&ptr[i] == &ld->pixelarrays)
	    bunny_delete_clipable((t_bunny_clipable*)*res->target);
	  else if (&ptr[i] == &ld->sprites)
	    bunny_delete_clipable((t_bunny_clipable*)*res->target);
	  else if (&ptr[i] == &ld->musics)
	    bunny_delete_sound((t_bunny_sound*)*res->target);
	  else if (&ptr[i] == &ld->effects)
	    bunny_delete_sound((t_bunny_sound*)*res->target);
	  else if (&ptr[i] == &ld->sound_sprites)
	    bunny_delete_sound((t_bunny_sound*)*res->target);
	  else if (&ptr[i] == &ld->texts)
	    bunny_delete_clipable((t_bunny_clipable*)*res->target);
	  else if (&ptr[i] == &ld->files)
	    bunny_delete_file(*res->target, res->file);
	  else if (&ptr[i] == &ld->configurations)
	    bunny_delete_configuration((t_bunny_configuration*)*res->target);
	  *res->target = NULL;
	}
}

/**
 * @doc
 * @doc-symbol bunny_new_ressource_hook
 * @doc-kind function
 * @doc-module context
 * @doc-order 660
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Allocates an empty loading-resource hook.
 * @return-success Returns a newly allocated hook.
 * @return-failure Returns $CNULL@ on allocation error.
 * @see t_bunny_loading_screen
 *
 * @doc-lang fr
 * @brief Alloue un hook de ressource à charger vide.
 * @return-success Renvoie un hook nouvellement alloué.
 * @return-failure Renvoie $CNULL@ en cas d’erreur d’allocation.
 * @see t_bunny_loading_screen
 */
t_bunny_ressource_to_load *bunny_new_ressource_hook(void)
{
  t_bunny_ressource_to_load *hook;

  if ((hook = (t_bunny_ressource_to_load*)bunny_malloc(sizeof(*hook))) == NULL)
    return (NULL);
  hook->file = NULL;
  hook->target = NULL;
  hook->subtarget = NULL;
  return (hook);
}

/**
 * @doc
 * @doc-symbol bunny_new_loading_task
 * @doc-kind function
 * @doc-module context
 * @doc-order 682
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Allocates an empty custom loading task.
 * @return-success Returns a newly allocated loading task.
 * @return-failure Returns $CNULL@ on allocation error.
 * @see t_bunny_loading_task
 *
 * @doc-lang fr
 * @brief Alloue une tâche personnalisée de chargement vide.
 * @return-success Renvoie une tâche de chargement nouvellement allouée.
 * @return-failure Renvoie $CNULL@ en cas d’erreur d’allocation.
 * @see t_bunny_loading_task
 */
t_bunny_loading_task	*bunny_new_loading_task(void)
{
  t_bunny_loading_task *task;

  if ((task = (t_bunny_loading_task*)bunny_malloc(sizeof(*task))) == NULL)
    return (NULL);
  task->function = NULL;
  task->data = NULL;
  return (task);
}

/**
 * @doc
 * @doc-symbol bunny_delete_loading_task
 * @doc-kind function
 * @doc-module context
 * @doc-order 683
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Deletes a custom loading task.
 * @param task Task to delete.
 * @return-success The task is released.
 * @see t_bunny_loading_task
 *
 * @doc-lang fr
 * @brief Détruit une tâche personnalisée de chargement.
 * @param task Tâche à détruire.
 * @return-success La tâche est libérée.
 * @see t_bunny_loading_task
 */
void			bunny_delete_loading_task(t_bunny_loading_task *task)
{
  bunny_free(task);
}

/**
 * @doc
 * @doc-symbol bunny_add_to_ressource_list
 * @doc-kind function
 * @doc-module context
 * @doc-order 680
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Appends several loading hooks to a loading list.
 * @param lst Destination list.
 * @param ld Array of hooks to append.
 * @param len Number of hooks in $Sld@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on insertion error.
 * @description Hooks are copied into the loading context. The caller keeps ownership of $Sld@ and may store it on the stack, in static storage or free it after this call.
 * @see t_bunny_loading_screen
 *
 * @doc-lang fr
 * @brief Ajoute plusieurs hooks de chargement à une liste.
 * @param lst Destination list.
 * @param ld Array of hooks to append.
 * @param len Number of hooks in $Sld@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur d’insertion.
 * @description Les hooks sont copiés dans le contexte de chargement. L'appelant garde la propriété de $Sld@ et peut le stocker sur la pile, en statique ou le libérer après cet appel.
 * @see t_bunny_loading_screen
 */
bool			bunny_add_to_ressource_list(t_bunny_list		*lst,
					    t_bunny_ressource_to_load	*ld,
					    size_t			len)
{
  t_bunny_ressource_to_load *copy;
  size_t		i;

  for (i = 0; i < len; ++i)
    {
      if ((copy = bunny_new_ressource_hook()) == NULL)
	return (false);
      *copy = ld[i];
      if (bunny_list_push_back(lst, copy) == false)
	{
	  bunny_delete_ressource_hook(copy);
	  return (false);
	}
    }
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_add_to_loading_task_list
 * @doc-kind function
 * @doc-module context
 * @doc-order 684
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Appends several custom tasks to a loading list.
 * @param lst Destination task list.
 * @param tasks Array of tasks to append.
 * @param len Number of tasks in $Stasks@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on allocation or insertion error.
 * @description Tasks are copied into the loading context. The caller keeps ownership of $Stasks@ and may store it on the stack, in static storage or free it after this call.
 * @see t_bunny_loading_task
 * @see t_bunny_loading_screen
 *
 * @doc-lang fr
 * @brief Ajoute plusieurs tâches personnalisées à une liste de chargement.
 * @param lst Liste de tâches destination.
 * @param tasks Tableau de tâches à ajouter.
 * @param len Nombre de tâches dans $Stasks@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur d’allocation ou d’insertion.
 * @description Les tâches sont copiées dans le contexte de chargement. L'appelant garde la propriété de $Stasks@ et peut le stocker sur la pile, en statique ou le libérer après cet appel.
 * @see t_bunny_loading_task
 * @see t_bunny_loading_screen
 */
bool			bunny_add_to_loading_task_list(t_bunny_list		*lst,
				       t_bunny_loading_task	*tasks,
				       size_t			len)
{
  t_bunny_loading_task *copy;
  size_t		i;

  for (i = 0; i < len; ++i)
    {
      if ((copy = bunny_new_loading_task()) == NULL)
	return (false);
      *copy = tasks[i];
      if (bunny_list_push_back(lst, copy) == false)
	{
	  bunny_delete_loading_task(copy);
	  return (false);
	}
    }
  return (true);
}
