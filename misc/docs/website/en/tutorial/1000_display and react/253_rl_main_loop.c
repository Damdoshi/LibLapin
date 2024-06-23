t_bunny_response loop_function(void *d)
{
  t_main_data *data = (t_main_data*)d;

  data->step += 0.05; // Arbitrary pacing of the animation
  return (GO_ON);
}
