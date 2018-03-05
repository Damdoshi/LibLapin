void set_clip_to_set(t_main_data *data, int animation, int rotation)
{
  data->pic->clip_x_position = (data->animation_frame % 8) * data->pic->clip_width;
  data->pic->clip_y_position = animation * data->pic->clip_height;
  if (rotation % 90 == 0)
    data->pic->rotation = rotation;
  data->animation_frame += 18.0 / bunny_get_frequency();
}

