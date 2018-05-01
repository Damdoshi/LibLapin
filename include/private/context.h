/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_CONTEXT_H__
# define			__LAPIN_PRIVATE_CONTEXT_H__
# include			<SFML/Graphics.hpp>

struct				bunny_splash_screen
{
  t_bunny_context_runtime_info	head;
  char				*bunny_picture_file;
  char				*rope_picture_file;
  char				*title_picture_file;
  char				*jingle_sound_file;
  char				*boom_sound_file;
  char				*outch_sound_file;
  char				*falling_sound_file;

  //

  size_t			animation_step;
  double			time_counter;
  double			middle_of_screen;
  double			bunny_fall_speed;
  double			rope_wave_length;
  double			rope_amplitude;
  double			shake_amplitude;
  double			up_speed;
  bool				jingle_played;

  t_bunny_picture		*bunny;
  t_bunny_picture		*rope;
  t_bunny_picture		*title;
  t_bunny_effect		*jingle;
  t_bunny_effect		*boom;
  t_bunny_effect		*outch;
  t_bunny_effect		*falling;
};

struct				depth_layer
{
  std::vector<t_bunny_picture*>	color_layers;
  std::vector<t_bunny_picture*>	normal_layers;
  std::vector<int>		tile;
  int				height;

  depth_layer(void)
  {}
  ~depth_layer(void)
  {
    for (size_t i = 0; i < color_layers.size(); ++i)
      if (color_layers[i])
	bunny_delete_clipable(color_layers[i]);
    for (size_t i = 0; i < normal_layers.size(); ++i)
      if (color_layers[i])
	bunny_delete_clipable(normal_layers[i]);
  }
};

struct				bunny_depth_engine
{
  t_bunny_context_runtime_info	head;
  const char			*configuration_file;
  const char			*shader_file;

  bool				shadows;
  t_bunny_color			back_color;
  t_bunny_color			light_color;
  t_bunny_position		camera;
  int				camera_height;
  double			camera_angle;

  //

  SmallConf			configuration;
  t_bunny_picture		*final_screen;
  t_bunny_shader		*normal_shader;
  t_bunny_position		screen_tile_size;
  t_bunny_position		screen_pixel_size;
  t_bunny_position		screen_configured_size;

  t_bunny_picture		*color_screen;
  t_bunny_picture		*normal_screen;

  t_bunny_position		pixel_map_size;
  t_bunny_position		tile_map_size;
  std::vector<depth_layer>	map_layers;

  const char			*color_tileset_file;
  const char			*normal_tileset_file;
  t_bunny_picture		*color_tileset;
  t_bunny_picture		*normal_tileset;
  t_bunny_position		tileset_size;
  t_bunny_position		tile_size;
};

bool				depth_load_levels(struct bunny_depth_engine &eng);
bool				depth_load_configuration(struct bunny_depth_engine &eng);
bool				depth_load_shader(struct bunny_depth_engine &eng);
bool				depth_load_tilesets(struct bunny_depth_engine &eng);
t_bunny_response		depth_entering(struct bunny_depth_engine &eng);
void				depth_leaving(t_bunny_response		resp,
					      struct bunny_depth_engine	&eng);
t_bunny_response		depth_display(struct bunny_depth_engine	&eng);
t_bunny_response		depth_loop(struct bunny_depth_engine	&eng);
void				display_single_tile(struct bunny_depth_engine &eng,
						    struct depth_layer	&layer,
						    t_bunny_position	&pos,
						    int			height);

#endif	/*			__LAPIN_PRIVATE_CONTEXT_H__		*/
