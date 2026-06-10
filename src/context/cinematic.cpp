// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
// EFRITS 2022-2026
// Pentacle Technologie 2008-2026
//
// Bibliotheque Lapin

#include			<ctype.h>
#include			<string.h>
#include			"lapin_private.h"

static t_bunny_response		call_subcontext(t_bunny_response		ret)
{
  if (ret == LEAVE_EVENT)
    return (GO_ON);
  return (ret);
}

static size_t			get_nbr_screen(t_bunny_cinematic_screen		*cin)
{
  size_t			i;

  if (cin->head.nbr_screen)
    return (cin->head.nbr_screen);
  if (cin->head.screens == NULL)
    return (0);
  for (i = 0; cin->head.screens[i]; ++i)
    {}
  cin->head.nbr_screen = i;
  return (i);
}

static const char		*get_language(t_bunny_cinematic_screen		*cin,
					      char				*buffer,
					      size_t				bufsiz)
{
  const char			*language = cin->language ? cin->language : "";
  size_t			i;

  if (bufsiz == 0)
    return (language);
  for (i = 0; language[i] && i + 1 < bufsiz; ++i)
    buffer[i] = toupper((unsigned char)language[i]);
  buffer[i] = '\0';
  return (&buffer[0]);
}

static t_bunny_cinematic_event	get_validation_event(t_bunny_cinematic_screen	*cin)
{
  if (cin->validation_event == BCE_NO_EVENT)
    return (BCE_TERMINATE_EVENT);
  return (cin->validation_event);
}

static t_bunny_response		cinematic_key(t_bunny_event_state		state,
					      t_bunny_keysym			sym,
					      t_bunny_cinematic_screen		*cin)
{
  t_bunny_response		ret;

  if (cin->head.subcontext.key)
    if ((ret = cin->head.subcontext.key(state, sym, cin)) != GO_ON)
      return (call_subcontext(ret));
  if (state == GO_UP)
    return (GO_ON);
  if (sym == BKS_ESCAPE)
    return (SWITCH_CONTEXT);
  if (sym == BKS_SPACE || sym == BKS_RETURN)
    cin->pending_event = get_validation_event(cin);
  return (GO_ON);
}

static t_bunny_response		cinematic_click(t_bunny_event_state		state,
						t_bunny_mouse_button		button,
						t_bunny_cinematic_screen	*cin)
{
  t_bunny_response		ret;

  if (cin->head.subcontext.click)
    if ((ret = cin->head.subcontext.click(state, button, cin)) != GO_ON)
      return (call_subcontext(ret));
  (void)button;
  if (state == GO_DOWN)
    cin->pending_event = get_validation_event(cin);
  return (GO_ON);
}

static t_bunny_response		cinematic_joy_button(t_bunny_event_state	state,
						     int			joyid,
						     int			button,
						     t_bunny_cinematic_screen	*cin)
{
  t_bunny_response		ret;

  if (cin->head.subcontext.joy_button)
    if ((ret = cin->head.subcontext.joy_button(state, joyid, button, cin)) != GO_ON)
      return (call_subcontext(ret));
  (void)joyid;
  if (state == GO_UP)
    return (GO_ON);
  if (button == 6)
    return (SWITCH_CONTEXT);
  cin->pending_event = get_validation_event(cin);
  return (GO_ON);
}

static t_bunny_response		cinematic_loop(t_bunny_cinematic_screen		*cin)
{
  t_bunny_cinematic_event	event;
  t_bunny_response		ret;
  double			now;

  if (cin->cinematic == NULL)
    return (EXIT_ON_ERROR);
  event = cin->pending_event;
  cin->pending_event = BCE_NO_EVENT;
  now = bunny_get_current_time();
  ret = bunny_cinematic(cin->cinematic, event, now - cin->last_action);
  cin->last_action = now;
  if (ret == EXIT_ON_SUCCESS)
    return (SWITCH_CONTEXT);
  if (ret != GO_ON)
    return (ret);
  if (cin->head.subcontext.loop)
    if ((ret = cin->head.subcontext.loop(cin)) != GO_ON)
      return (call_subcontext(ret));
  return (GO_ON);
}

static t_bunny_response		cinematic_display(t_bunny_cinematic_screen	*cin)
{
  t_bunny_clipable		*clip;
  t_bunny_response		ret;
  size_t			nbr;

  if (cin->cinematic == NULL)
    return (EXIT_ON_ERROR);
  clip = &cin->cinematic->clipable;
  bunny_draw(clip);
  nbr = get_nbr_screen(cin);
  for (size_t i = 0; i < nbr; ++i)
    {
      t_bunny_position		pos;

      if (cin->head.screens[i] == NULL)
        continue ;
      pos.x = 0;
      pos.y = 0;
      if (cin->clear_screen)
        bunny_clear(cin->head.screens[i], BLACK);
      if (cin->centered)
        {
          pos.x = ((int)cin->head.screens[i]->width - (int)clip->buffer.width) / 2;
          pos.y = ((int)cin->head.screens[i]->height - (int)clip->buffer.height) / 2;
        }
      bunny_blit(cin->head.screens[i], clip, &pos);
    }
  if (cin->head.subcontext.display)
    if ((ret = cin->head.subcontext.display(cin)) != GO_ON)
      return (call_subcontext(ret));
  if (cin->head.subcontext.display == NULL)
    for (size_t i = 0; i < nbr; ++i)
      if (cin->head.screens[i])
        bunny_display((t_bunny_window*)cin->head.screens[i]);
  return (GO_ON);
}

static t_bunny_response		cinematic_entering(t_bunny_cinematic_screen	*cin)
{
  t_bunny_response		ret;
  char				language[128];

  if (cin->cinematic == NULL)
    {
      if (cin->cinematic_file == NULL)
        return (EXIT_ON_ERROR);
      get_language(cin, &language[0], sizeof(language));
      if (cin->width && cin->height)
        cin->cinematic = bunny_load_cinematic_wh
          (cin->cinematic_file, cin->width, cin->height, &language[0]);
      else if (get_nbr_screen(cin) >= 1 && cin->head.screens[0])
        cin->cinematic = bunny_load_cinematic_wh
          (cin->cinematic_file,
           cin->head.screens[0]->width,
           cin->head.screens[0]->height,
           &language[0]);
      else
        cin->cinematic = bunny_load_cinematic(cin->cinematic_file, &language[0]);
      if (cin->cinematic == NULL)
        return (EXIT_ON_ERROR);
      cin->delete_cinematic_on_leave = true;
    }
  bunny_reset_cinematic(cin->cinematic);
  bunny_clear(&cin->cinematic->clipable.buffer, BLACK);
  cin->pending_event = BCE_NO_EVENT;
  cin->last_action = bunny_get_current_time();
  if (cin->head.subcontext.entering_context)
    if ((ret = cin->head.subcontext.entering_context(cin)) != GO_ON)
      return (call_subcontext(ret));
  return (GO_ON);
}

static void			cinematic_leaving(t_bunny_response		res,
						  t_bunny_cinematic_screen	*cin)
{
  if (cin->head.subcontext.leaving_context)
    cin->head.subcontext.leaving_context(res, cin);
  if (cin->cinematic)
    {
      bunny_cinematic_stop(cin->cinematic);
      if (cin->delete_cinematic_on_leave)
        {
          bunny_delete_clipable(&cin->cinematic->clipable);
          cin->cinematic = NULL;
          cin->delete_cinematic_on_leave = false;
        }
    }
}

const t_bunny_context		gl_bunny_cinematic_context =
  {
    (t_bunny_key)cinematic_key,
    bunny_context_type,
    (t_bunny_click)cinematic_click,
    bunny_context_move,
    bunny_context_wheel,
    bunny_context_joy_connect,
    (t_bunny_joy_button)cinematic_joy_button,
    bunny_context_joy_axis,
    bunny_context_get_focus,
    bunny_context_lost_focus,
    bunny_context_resize,
    (t_bunny_loop)cinematic_loop,
    (t_bunny_display)cinematic_display,
    bunny_context_close,
    bunny_context_message,
    bunny_context_connect,
    (t_bunny_loop)cinematic_entering,
    (t_bunny_leaving_context)cinematic_leaving,
    bunny_context_async_computation,
    bunny_context_event_response
  };
