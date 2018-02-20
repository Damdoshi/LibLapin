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

