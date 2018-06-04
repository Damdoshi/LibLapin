// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

struct			bunny_ressource_to_load
{
  const char		*file;
  void			**target;
  size_t		*subtarget;			// For file size
};

static pthread_mutex_t	gl_loading_lock = PTHREAD_MUTEX_INITIALIZER;

static t_bunny_response	loading_async_response(t_bunny_ressource_to_load *_res,
					       struct bunny_loading_screen *ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;
  t_bunny_response	ret;

  (void)res;
  if (ld->failure)
    return (EXIT_ON_ERROR);
  ld->count++;
  pthread_mutex_unlock(&gl_loading_lock);
  if (ld->head.subcontext.async_computation_response)
    {
      if ((ret = ld->head.subcontext.async_computation_response
	   ((void*)_res, (void*)ld->head.main_structure)) != GO_ON)
	return (ret);
    }
  return (GO_ON);
}

static void		load_picture(t_bunny_ressource_to_load		*_res,
				     struct bunny_loading_screen	*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if ((*res->target = (void*)bunny_load_picture(res->file)) == NULL)
    ld->failure = true;
}

static void		load_pixelarray(t_bunny_ressource_to_load	*_res,
					struct bunny_loading_screen	*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if ((*res->target = (void*)bunny_load_pixelarray(res->file)) == NULL)
    ld->failure = true;
}

static void		load_sprite(t_bunny_ressource_to_load		*_res,
				    struct bunny_loading_screen		*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if ((*res->target = (void*)bunny_load_sprite(res->file)) == NULL)
    ld->failure = true;
}

static void		load_music(t_bunny_ressource_to_load		*_res,
				   struct bunny_loading_screen		*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if ((*res->target = (void*)bunny_load_music(res->file)) == NULL)
    ld->failure = true;
}

static void		load_effect(t_bunny_ressource_to_load		*_res,
				    struct bunny_loading_screen		*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if ((*res->target = (void*)bunny_load_effect(res->file)) == NULL)
    ld->failure = true;
}

static void		load_sound_sprite(t_bunny_ressource_to_load	*_res,
					  struct bunny_loading_screen	*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if ((*res->target = (void*)bunny_load_sound_sprite(res->file))
      == NULL)
    ld->failure = true;
}

static void		load_text(t_bunny_ressource_to_load		*_res,
				  struct bunny_loading_screen		*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if ((*res->target = (void*)bunny_load_text(res->file)) == NULL)
    ld->failure = true;
}

static void		load_file(t_bunny_ressource_to_load		*_res,
				  struct bunny_loading_screen		*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if (bunny_load_file(res->file, res->target, res->subtarget) == -1)
    ld->failure = true;
}

static void		load_configuration(t_bunny_ressource_to_load	*_res,
					   struct bunny_loading_screen	*ld)
{
  struct bunny_ressource_to_load *res = (struct bunny_ressource_to_load*)_res;

  if ((*res->target = (void*)bunny_open_configuration(res->file, NULL)) == NULL)
    ld->failure = true;
}

static t_bunny_response	loading_loop(struct bunny_loading_screen	*ld)
{
  t_bunny_list		**ptr = &ld->pictures;
  t_bunny_list		**end = &(&ld->configurations)[1];
  t_bunny_response	ret;
  double		step;

  if (ld->failure)
    return (EXIT_ON_ERROR);

  if (pthread_mutex_trylock(&gl_loading_lock) == 0)
    {
      if (ld->node)
	{
	  if (&ptr[ld->list_cnt] == &ld->pictures)
	    bunny_async_computation_push((t_bunny_function)load_picture, ld->node->data);
	  else if (&ptr[ld->list_cnt] == &ld->pixelarrays)
	    bunny_async_computation_push((t_bunny_function)load_pixelarray, ld->node->data);
	  else if (&ptr[ld->list_cnt] == &ld->sprites)
	    bunny_async_computation_push((t_bunny_function)load_sprite, ld->node->data);
	  else if (&ptr[ld->list_cnt] == &ld->musics)
	    bunny_async_computation_push((t_bunny_function)load_music, ld->node->data);
	  else if (&ptr[ld->list_cnt] == &ld->effects)
	    bunny_async_computation_push((t_bunny_function)load_effect, ld->node->data);
	  else if (&ptr[ld->list_cnt] == &ld->sound_sprites)
	    bunny_async_computation_push((t_bunny_function)load_sound_sprite, ld->node->data);
	  else if (&ptr[ld->list_cnt] == &ld->texts)
	    bunny_async_computation_push((t_bunny_function)load_text, ld->node->data);
	  else if (&ptr[ld->list_cnt] == &ld->files)
	    bunny_async_computation_push((t_bunny_function)load_file, ld->node->data);
	  else if (&ptr[ld->list_cnt] == &ld->configurations)
	    bunny_async_computation_push((t_bunny_function)load_configuration, ld->node->data);

	  ld->node = bunny_list_next(ld->node);
	}
      else if (&ptr[ld->list_cnt + 1] < end)
	{
	  ld->list_cnt += 1;
	  ld->node = bunny_list_begin(ptr[ld->list_cnt]);
	  pthread_mutex_unlock(&gl_loading_lock);
	}
      else
	{
	  ld->node = NULL;
	  pthread_mutex_unlock(&gl_loading_lock);
	}

    }

  step = 0.3 * (((double)ld->count / ld->total_ressources) - ld->smooth_cursor);
  ld->smooth_cursor += step;

  if (ld->count >= ld->total_ressources && ld->smooth_cursor > 0.999)
    {
      ld->smooth_cursor = 1.0;
      ld->terminated = true;
    }

  if (ld->head.subcontext.loop)
    {
      if ((ret = ld->head.subcontext.loop(ld->head.main_structure)) != GO_ON)
	return (ret);
    }
  else if (ld->terminated)
    return (SWITCH_CONTEXT);

  return (GO_ON);
}

static t_bunny_response	loading_entering(struct bunny_loading_screen	*ld)
{
  t_bunny_list		**ptr = &ld->pictures;
  t_bunny_list		**end = &(&ld->configurations)[1];
  t_bunny_response	ret;
  int			i;

  if (gl_bunny_loop_threadpool == NULL)
    {
      bunny_set_async_computation(1);
      ld->local_threadpool = true;
    }
  else
    ld->local_threadpool = false;

  ld->terminated = false;
  ld->failure = false;
  ld->smooth_cursor = 0;
  ld->count = 0;
  ld->total_ressources = 0;
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

  (void)res;
  if (ld->local_threadpool)
    bunny_set_async_computation(0);
  if (ld->failure)
    bunny_clear_all_loaded_ressources((t_bunny_loading_screen*)ld);
  if (ld->head.subcontext.leaving_context)
    ld->head.subcontext.leaving_context(res, ld->head.main_structure);
}

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
    NULL,
    bunny_context_message,
    bunny_context_connect,
    (t_bunny_loop)loading_entering,
    (t_bunny_leaving_context)loading_leaving,
    (t_bunny_async_computation_response)loading_async_response
  };

bool			bunny_init_loading_context(t_bunny_loading_screen *_ld)
{
  struct bunny_loading_screen *ld = (struct bunny_loading_screen*)_ld;
  t_bunny_list		**ptr = &ld->pictures;
  t_bunny_list		**end = &(&ld->configurations)[1];
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

void			bunny_terminate_loading_context(t_bunny_loading_screen *_ld)
{
  struct bunny_loading_screen *ld = (struct bunny_loading_screen*)_ld;
  t_bunny_list		**ptr = &ld->pictures;
  t_bunny_list		**end = &(&ld->configurations)[1];
  t_bunny_node		*nod;
  int			i;

  for (i = 0; &ptr[i] != end; ++i)
    {
      for (bunny_list_all(ptr[i], nod))
	bunny_delete_ressource_hook((t_bunny_ressource_to_load*)nod->data);
      bunny_delete_list(ptr[i]);
    }
}

void			bunny_clear_all_loaded_ressources(t_bunny_loading_screen *_ld)
{
  struct bunny_ressource_to_load *res;
  struct bunny_loading_screen *ld = (struct bunny_loading_screen*)_ld;
  t_bunny_list		**ptr = &ld->pictures;
  t_bunny_list		**end = &(&ld->configurations)[1];
  t_bunny_node		*nod;
  int			i;

  for (i = 0; &ptr[i] != end; ++i)
    if (ptr[i])
      for (bunny_list_all(ptr[i], nod))
	{
	  if ((res = bunny_list_data(nod, struct bunny_ressource_to_load*)) == NULL)
	    continue ;

	  if (&ptr[ld->list_cnt] == &ld->pictures)
	    bunny_delete_clipable((t_bunny_clipable*)*res->target);
	  else if (&ptr[ld->list_cnt] == &ld->pixelarrays)
	    bunny_delete_clipable((t_bunny_clipable*)*res->target);
	  else if (&ptr[ld->list_cnt] == &ld->sprites)
	    bunny_delete_clipable((t_bunny_clipable*)*res->target);
	  else if (&ptr[ld->list_cnt] == &ld->musics)
	    bunny_delete_sound((t_bunny_sound*)*res->target);
	  else if (&ptr[ld->list_cnt] == &ld->effects)
	    bunny_delete_sound((t_bunny_sound*)*res->target);
	  else if (&ptr[ld->list_cnt] == &ld->sound_sprites)
	    bunny_delete_sound((t_bunny_sound*)*res->target);
	  else if (&ptr[ld->list_cnt] == &ld->texts)
	    bunny_delete_clipable((t_bunny_clipable*)*res->target);
	  else if (&ptr[ld->list_cnt] == &ld->files)
	    bunny_delete_file(*res->target, res->file);
	  else if (&ptr[ld->list_cnt] == &ld->configurations)
	    bunny_delete_configuration((t_bunny_configuration*)*res->target);
	}
}

t_bunny_ressource_to_load *bunny_new_ressource_hook(void)
{
  return ((t_bunny_ressource_to_load*)bunny_malloc(sizeof(t_bunny_ressource_to_load)));
}

void			bunny_delete_ressource_hook(t_bunny_ressource_to_load *ld)
{
  bunny_free(ld);
}

bool			bunny_add_to_ressource_list(t_bunny_list		*lst,
						    t_bunny_ressource_to_load	*ld,
						    size_t			len)
{
  int			i;

  for (i = 0; i < (int)len; ++i)
    if (bunny_list_push_back(lst, &ld[i]) == false)
      {
	bunny_list_clear(lst);
	return (false);
      }
  return (true);
}

