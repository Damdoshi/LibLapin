// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Bibliothèque Lapin

#ifndef				__LAPIN_PRIVATE_CINEMATIC_HPP__
# define			__LAPIN_PRIVATE_CINEMATIC_HPP__

struct				bunny_cinematic
{
  size_t			type;
  sf::RenderTexture		*texture;
  size_t			glactive;
  t_copy_on_write_gfx		duplicate;
  ssize_t			width;
  ssize_t			height;
  t_bunny_extended_data		data[BUNNY_EXTENDED_DATA_LENGTH];
  t_bunny_area			rect;
  t_bunny_accurate_position	position;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;
  bool				smooth;
  bool				mosaic;

  bunny_cinematic() {}
  ~bunny_cinematic() {}
  
  // Private fields of t_bunny_clipable
  size_t			res_id;
  const sf::Texture		*tex;
  sf::Sprite			*sprite;
  t_bunny_configuration		*configuration;

  ////////////////////////////////////
  // Public fields of t_bunny_cinematic
  struct {
    double			music;
    double			voice;
    double			effect;
  }				volumes;

  union {
    t_bunny_map			*maps[7];
    struct {
      t_bunny_map		*pictures;
      t_bunny_map		*effects;
      t_bunny_map		*musics;
      t_bunny_map		*voices;
      t_bunny_map		*fonts;
      t_bunny_map		*texts;
      t_bunny_map		*commands;
    };
  };

  bool				repeat;
  t_bunny_configuration		*program;
  size_t			current_command;
  void				*stack_frame;
  char				extended_data[512];

  // Champs privés
  int				return_position[128];
  char				command_data[128][128];
  int				stack_top;

  t_bunny_color			background_color;
  t_bunny_color			foreground_color;
};

struct				cinematic_text
{
  bool				init;
  t_bunny_font			*fnt;
  t_bunny_sprite		*fac;
  t_bunny_sound_sprite		*voi;
  const char			*tex;
  int				speed;
};

void				__bunny_draw_cinematic(struct bunny_cinematic *cin);

#endif	//			__LAPIN_PRIVATE_CINEMATIC_HPP__
