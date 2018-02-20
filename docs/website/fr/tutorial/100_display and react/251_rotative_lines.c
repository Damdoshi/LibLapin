#include <lapin.h>  // For all bunny_ things.o
#include <stdlib.h> // For EXIT_SUCCESS

typedef struct s_main_data
{
  t_bunny_window *win;
  double step;
} t_main_data;

// data is the third parameter of bunny_loop
t_bunny_response key_event_response(t_bunny_event_state state, t_bunny_keysym keycode, void *data)
{
  // We do not need the main data right now
  (void)data;

  if (state == GO_DOWN && keycode == BKS_ESCAPE) // If we press escape
    return (EXIT_ON_SUCCESS); // We exit successfully
  return (GO_ON); // Or we go on
}

t_bunny_response loop_function(void *d)
{
  t_main_data *data = (t_main_data*)d;

  data->step += 0.05; // Arbitrary pacing of the animation
  return (GO_ON);
}

t_bunny_response display_function(void *d)
{
  t_main_data *data = (t_main_data*)d;

  bunny_fill(&data->win->buffer, ALPHA(64, BLACK));

  t_bunny_position circle_position;
  t_bunny_position circle_size;

  circle_position.x = data->win->buffer.width / 2;
  circle_position.y = data->win->buffer.height / 2;
  circle_size.x = cos(data->step) * data->win->buffer.width / 2;
  circle_size.y = sin(data->step) * data->win->buffer.height / 2;

  bunny_set_circle(&data->win->buffer, circle_position, circle_size, RED);

  unsigned int col[2] = {BLACK, RED};
  t_bunny_position pos[2];
  double additional_step;

  pos[0].x = circle_position.x;
  pos[0].y = circle_position.y;

  for (additional_step = 0; additional_step < 1; additional_step += 0.05)
    {
      pos[1].x = pos[0].x + cos(2.3 * data->step + additional_step) * circle_size.x * (1 - additional_step);
      pos[1].y = pos[0].y + sin(2.3 *data->step + additional_step) * circle_size.y * (1 - additional_step);

      bunny_set_line(&data->win->buffer, &pos[0], &col[0]);

      pos[1].x = pos[0].x - cos(2.3 * data->step + additional_step) * circle_size.x * (1 - additional_step);
      pos[1].y = pos[0].y - sin(2.3 * data->step + additional_step) * circle_size.y * (1 - additional_step);

      bunny_set_line(&data->win->buffer, &pos[0], &col[0]);
    }

  bunny_display(data->win);
  return (GO_ON);
}

int main(void)
{
  t_main_data main_data;

  main_data.win = bunny_start(600, 600, false, "Dancing lines and circles");
  main_data.step = 1.0;

  // key_event_response will be called on key pressed and key released events
  bunny_set_key_response(key_event_response);

  // loop_function will be called regulary at 25Hz (see bunny_loop call)
  bunny_set_loop_main_function(loop_function);

  // display_function will be called when the program need to refresh the display
  bunny_set_display_function(display_function);

  // The third parameter will be sent as last parameter of every functions called by bunny_loop.
  bunny_loop(main_data.win, 25, &main_data);

  // When getting out of bunny_loop, close the window
  bunny_stop(main_data.win);
  return (EXIT_SUCCESS);
}
