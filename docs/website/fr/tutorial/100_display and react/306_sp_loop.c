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
