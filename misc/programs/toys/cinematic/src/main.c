// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Cinematic test program

#include		<lapin.h>
#include		<assert.h>
#include		<stdlib.h>

typedef struct		s_program
{
  t_bunny_window	*win;
  t_bunny_cinematic	*cin;
  double		last_date;
}			t_program;

t_bunny_response	event(const t_bunny_event *event,
			      void		*_prog)
{
  t_program		*prog = _prog;
  double		now;

  now = bunny_get_current_time();
  if (bunny_cinematic(prog->cin, event, now) == false)
    return (EXIT_ON_SUCCESS);
  prog->last_date = now;
  return (GO_ON);
}

t_bunny_response	loop(void		*_prog)
{
  t_program		*prog = _prog;
  double		now;

  now = bunny_get_current_time();
  if (bunny_cinematic(prog->cin, NULL, now) == false)
    return (EXIT_ON_SUCCESS);
  prog->last_date = now;
  return (GO_ON);
}

t_bunny_response	display(void		*_prog)
{
  t_program		*prog = _prog;

  bunny_draw(&prog->cin->clipable);
  bunny_blit(&prog->win->buffer, &prog->cin->clipable, NULL);
  bunny_display(prog->win);
  return (GO_ON);
}

int			main(void)
{
  // bunny_set_error_descriptor(2);
  t_program		prog = {
    .win = bunny_start(1024, 768, false, "Name"),
    .cin = bunny_load_cinematic("./cinematic.dab", "FR")
  };

  // bunny_consistancy();
  if (!prog.cin)
    {
      fprintf(stderr, "Failed to load cinematic.dab and its dependencies.\n");
      return (EXIT_FAILURE);
    }
  bunny_enable_full_blit(true);
  bunny_set_loop_main_function(loop);
  bunny_set_display_function(display);
  bunny_set_event_response(event);
  prog.last_date = bunny_get_current_time();
  bunny_loop(prog.win, 50, &prog);  
  bunny_delete_cinematic(prog.cin); // a remplacer par delete clipable
  bunny_stop(prog.win);
  return (EXIT_SUCCESS);
}
