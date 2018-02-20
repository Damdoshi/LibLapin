#include <lapin.h>  // For all bunny_ things.o
#include <stdlib.h> // For EXIT_SUCCESS

// Setting this response function will enable bunny_get_mouse_position
t_bunny_response move_event_response(const t_bunny_position *relative, void *data)
{
  t_bunny_window *win = (t_bunny_window*)data;
  const t_bunny_position *position;
  bool is_down;

  // We do not need the relative movement
  (void)relative;

  // Get the current mouse position
  position = bunny_get_mouse_position();
  // Get the status of the left button
  is_down = bunny_get_mouse_button()[BMB_LEFT];

  // If the left button is down, draw
  if (is_down)
    {
      bunny_set_pixel(&win->buffer, *position, WHITE);
      bunny_display(win);
    }
  return (GO_ON);
}

// Setting this response function will enable bunny_get_mouse_button
t_bunny_response click_event_response(t_bunny_event_state state, t_bunny_mouse_button button, void *data)
{
  // We do not need the window right now
  (void)data;

  // We do not care if the button is going up or down
  (void)state;

  // Clicking with the right mouse button
  if (button == BMB_RIGHT)
    return (EXIT_ON_SUCCESS); // Exiting the program successfuly.
  return (GO_ON);
}

int main(void)
{
  t_bunny_window *win = bunny_start(800, 600, false, "Draw pixels tutorial");

  // move_event_response will be called if the mouse moved
  bunny_set_move_response(move_event_response);
  // click_event_response will be called if a mouse button is pressed or released
  bunny_set_click_response(click_event_response);

  // Display the default content of the window
  bunny_display(win);

  // The third parameter will be sent as last parameter of every functions called by bunny_loop.
  bunny_loop(win, 25, win);

  // When getting out of bunny_loop, close the window
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
