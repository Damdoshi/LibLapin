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

struct				bunny_loading_screen
{
  t_bunny_context_runtime_info	head;
  t_bunny_list			*pictures;
  t_bunny_list			*pixelarrays;
  t_bunny_list			*sprites;
  t_bunny_list			*musics;
  t_bunny_list			*effects;
  t_bunny_list			*sound_sprites;
  t_bunny_list			*texts;
  t_bunny_list			*files;
  t_bunny_list			*configurations;
  double			smooth_cursor; // fake percentage with smooth
  bool				terminated;
  int				count;
  int				total_ressources;
  bool				local_threadpool;
  int				list_cnt;
  t_bunny_node			*node;
  bool				failure;
};

///////////////////////

struct				bunny_depth_engine
{
  t_bunny_context_runtime_info	head;

  ////////////////////////////
  // PROVIDED CONFIGURATION //
  ///////////////////////////

  t_bunny_configuration		*configuration;

  ////////////////////
  // RUNTIME STATUS //
  ////////////////////

  t_bunny_accurate_position	camera;
  double			zindex;
  t_bunny_accurate_position	zoom;
  double			rotation;

  // Pool on t_bunny_clipable*
  t_bunny_pool			*sprites;

  /////////////////////////////
  // EXTRACTED CONFIGURATION //
  /////////////////////////////

  // Is there any normal mapping?
  bool				normal_map;
  // Is there any raytraced shadows?
  bool				raytraced_shadows;
  // How many layer there is for a single level
  int				depth_layer_count;
  // How strong is the zoom between two layers
  double			depth_ratio;
  // The map node
  t_bunny_configuration		*levels;

  //////////////////////////
  // PERMANENT RESSOURCES //
  //////////////////////////

  // NULL means no normal map
  // If there is a normal map, it is used both as render target (to generated the depthed
  // normal map) and as normal map (when rendering the final result)
  t_bunny_normal_map		*normal_map_renderer;

  // The collide map is used for raytraced shadows (black mean collide)
  // But can also  have other purpose (currently, I don't have any precise idea.)
  t_bunny_picture		*collide_map_renderer;

  // The tilemap to draw. It is not a standard tilemap, it has to respect
  // the depth tilemap format which is described in formats/ and in documentation.
  // Any amount of tilemap can be loaded (defined by configuration), depending on
  // the level you have loaded. (Only interesting tilemaps are really rendered)
  t_bunny_tilemap		**tilemap_color_renderer;
  t_bunny_tilemap		**tilemap_normal_renderer;
  t_bunny_tilemap		**tilemap_collide_renderer;

  // TODO:
  // Intermediate raytraced shadow tileset
  // RAYTRACED SHADOW SHOULD HAVE A LEVEL, SO A CHARACTER PROJECTED SHADOW IS NOT ONY
  // ON FLOOR AND NOT FULL WALL EITHER
};

#endif	/*			__LAPIN_PRIVATE_CONTEXT_H__		*/
