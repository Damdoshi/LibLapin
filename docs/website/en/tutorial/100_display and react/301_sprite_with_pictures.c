#include <math.h> // For abs()
#include <lapin.h>  // For all bunny_ things
#include <stdlib.h> // For EXIT_SUCCESS

typedef struct s_main_data
{
  t_bunny_window *win;
  t_bunny_picture *pic;
  double animation_frame;
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

t_bunny_response wheel_event_response(int wheelid, int delta, void *d)
{
  t_main_data *data = (t_main_data*)d;

  (void)wheelid;
  data->pic->scale.x = (data->pic->scale.y += delta / 5.0);
  return (GO_ON);
}

void set_clip_to_set(t_main_data *data, int animation, int rotation)
{
  data->pic->clip_x_position = ((int)data->animation_frame % 8) * data->pic->clip_width;
  data->pic->clip_y_position = animation * data->pic->clip_height;
  if (rotation % 90 == 0)
    data->pic->rotation = rotation;
  data->animation_frame += 18.0 / bunny_get_frequency();
}

t_bunny_response loop_function(void *d)
{
  t_main_data *data = (t_main_data*)d;

  if (bunny_get_keyboard()[BKS_LEFT])
    {
      set_clip_to_set(data, 1, -90);
      data->pic->position.x -= 100.0 / bunny_get_frequency();
      return (GO_ON);
    }

  if (bunny_get_keyboard()[BKS_RIGHT])
    {
      set_clip_to_set(data, 1, +90);
      data->pic->position.x += 100.0 / bunny_get_frequency();
      return (GO_ON);
    }

  if (bunny_get_keyboard()[BKS_UP])
    {
      set_clip_to_set(data, 1, 0);
      data->pic->position.y -= 100.0 / bunny_get_frequency();
      return (GO_ON);
    }

  if (bunny_get_keyboard()[BKS_DOWN])
    {
      set_clip_to_set(data, 1, 180);
      data->pic->position.y += 100.0 / bunny_get_frequency();
      return (GO_ON);
    }

  data->animation_frame = 0;
  set_clip_to_set(data, 0, 45);
  return (GO_ON);
}

t_bunny_response display_function(void *d)
{
  t_main_data *data = (t_main_data*)d;

  // Clear the whole screen with opaque black
  bunny_fill(&data->win->buffer, BLACK);

  // Draw the sprite on window at a position specified in itself
  bunny_blit(&data->win->buffer, data->pic, NULL);

  // Refresh the window display
  bunny_display(data->win);
  return (GO_ON);
}

int main(void)
{
  t_main_data main_data;

  main_data.win = bunny_start(800, 600, false, "Animate a sprite with pictures");

  main_data.pic = bunny_load_picture("./sprite.png");
  main_data.pic->clip_width = 107;
  main_data.pic->clip_height = 100;
  main_data.pic->origin.x = main_data.pic->clip_width / 2;
  main_data.pic->origin.y = main_data.pic->clip_height / 2;
  main_data.pic->position.x = main_data.win->buffer.width / 2;
  main_data.pic->position.y = main_data.win->buffer.height / 2;

  main_data.animation_frame = 0;

  // key_event_response will be called on key pressed and key released events
  bunny_set_key_response(key_event_response);

  // wheel_event_response will be called on wheel scroll, both direction
  bunny_set_wheel_response(wheel_event_response);

  // loop_function will be called regulary at 25Hz (see bunny_loop call)
  bunny_set_loop_main_function(loop_function);

  // display_function will be called when the program need to refresh the display
  bunny_set_display_function(display_function);

  // The third parameter will be sent as last parameter of every functions called by bunny_loop.
  bunny_loop(main_data.win, 25, &main_data);

  // Destroy the picture
  bunny_delete_clipable(main_data.pic);

  // When getting out of bunny_loop, close the window
  bunny_stop(main_data.win);
  return (EXIT_SUCCESS);
}
