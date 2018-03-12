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
