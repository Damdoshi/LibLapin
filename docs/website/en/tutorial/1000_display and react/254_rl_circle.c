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
