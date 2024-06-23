t_bunny_response wheel_event_response(int wheelid, int delta, void *d)
{
  t_main_data *data = (t_main_data*)d;

  (void)wheelid;
  data->pic->scale.x = (data->pic->scale.y += delta / 5.0);
  return (GO_ON);
}
