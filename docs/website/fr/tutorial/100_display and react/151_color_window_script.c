#include <lapin.h>  // For all bunny_ things.o
#include <stdlib.h> // For EXIT_SUCCESS

// data is the third parameter of bunny_loop
t_bunny_response key_event_response(t_bunny_event_state state, t_bunny_keysym keycode,void *data)
{
  if (state == GO_UP) // If a key is released
    return (GO_ON); // Do nothing, stay in bunny loop

  // If we are here, it means a key pressed event occured

  if (keycode == BKS_ESCAPE) // The escape key was pressed
    return (EXIT_ON_SUCCESS); // Get out of bunny loop, program successful

  // The "data" parameter is the third parameter of bunny_loop, so it is the window
  t_bunny_window *win = (t_bunny_window*)data;

  // Fill the window with a random opaque color
  bunny_fill(&win->buffer, rand() | BLACK);
  bunny_display(win);

  // Do nothing more, stay in bunny loop
  return (GO_ON);
}

int main(void)
{
  t_bunny_window *win = bunny_start(800, 600, false, "Blink window tutorial");

  // key_event_response will be called on key pressed and key released events
  bunny_set_key_response(key_event_response);

  // Display the default content of the window
  bunny_display(win);

  // The third parameter will be sent as last parameter of every functions called by bunny_loop.
  bunny_loop(win, 25, win);

  // When getting out of bunny_loop, close the window
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
