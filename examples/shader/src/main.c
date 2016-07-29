/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** 
*/

#include		<stdio.h>
#include		<assert.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_picture		*color;
t_bunny_picture		*normal;
t_bunny_picture		*specular;
t_bunny_shader		*shader;

t_bunny_response	key(t_bunny_event_state			state,
			    t_bunny_keysym			sym,
			    void				*data)
{
  (void)state;
  (void)data;
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	move(const t_bunny_position		*relative,
			     void				*dat)
{
  (void)relative;
  (void)dat;
  return (GO_ON);
}

t_bunny_response	loop(void				*dat)
{
  (void)dat;
  bunny_shader_set_variable
    (shader, "LightPos", BVT_3_FLOAT,
     (double)bunny_get_mouse_position()->x,
     (double)bunny_get_mouse_position()->y,
     1.0);
  bunny_clear(&win->buffer, BLACK);
  bunny_blit_shader(&win->buffer, color, NULL, shader);
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{
  assert(bunny_is_shader_available());
  assert(shader = bunny_new_shader());
  assert(bunny_load_shader(shader, NULL, "scene.frag"));
  assert(win = bunny_start(1024, 1024, false, "Shiny things are shiny"));
  assert(color = bunny_load_picture("color.png"));
  assert(normal = bunny_load_picture("normal.png"));
  assert(specular = bunny_load_picture("specular.png"));

  bunny_shader_set_variable(shader, "OriginalTexture", BVT_CURRENT_TEXTURE_TYPE);
  bunny_shader_set_variable(shader, "OriginalNMap", BVT_PICTURE, normal);
  bunny_shader_set_variable(shader, "SpecularMap", BVT_PICTURE, specular);

  bunny_shader_set_variable
    (shader, "WindowSize", BVT_2_FLOAT,
     (double)win->buffer.width, (double)win->buffer.height);
  bunny_shader_set_variable
    (shader, "LightPos", BVT_3_FLOAT, 0.0, 0.0, 0.1);
  bunny_shader_set_variable
    (shader, "LightColor", BVT_FULL_COLOR, WHITE);
  bunny_shader_set_variable
    (shader, "AmbientColor", BVT_FULL_COLOR, WHITE);
  bunny_shader_set_variable
    (shader, "AmbientIntensity", BVT_1_FLOAT, 0.0);
  bunny_shader_set_variable
    (shader, "LightSpecularColor", BVT_FULL_COLOR, WHITE);
  bunny_shader_set_variable
    (shader, "Falloff", BVT_3_FLOAT, 0.25, 0.25, 0.25);

  color->scale.x = (double)win->buffer.width / color->buffer.width;
  color->scale.y = (double)win->buffer.height / color->buffer.height;
  
  bunny_set_key_response(key);
  bunny_set_move_response(move);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 20, NULL);
  bunny_delete_clipable(color);
  bunny_delete_clipable(normal);
  bunny_delete_clipable(specular);
  bunny_delete_shader(shader);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
