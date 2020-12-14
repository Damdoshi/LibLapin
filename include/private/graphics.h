/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_GRAPHICS_H__
# define			__LAPIN_PRIVATE_GRAPHICS_H__
# include			<SFML/Graphics.hpp>

/*
typedef void			(*method_delete)(void			*clp);
typedef void			(*method_blit)(void			*target,
					       const t_bunny_clipable	*origin,
					       const t_bunny_position	*pos);
typedef void			(*method_draw)(void			*pic);
typedef void			(*method_pixel)(void			*target,
						t_bunny_position	pos,
						unsigned int		col);
typedef void			(*method_circle)(void			*target,
						 t_bunny_position	pos,
						 t_bunny_position	rad,
						 unsigned int		color);
typedef void			(*method_line)(void			*target,
					       const t_bunny_position	*pos,
					       const unsigned int	*col);
typedef void			(*method_polygon)(void			*target,
						  const t_bunny_position *pos,
						  const unsigned int	*col);
typedef void			(*method_fill)(void			*target,
					       unsigned int		color);
typedef void			(*method_clear)(void			*target,
						unsigned int		color);
typedef void			(*method_geometry)(void			*target,
						   t_bunny_geometry	geom,
						   t_bunny_vertex_array	*array,
						   t_bunny_clipable	*texture);

struct				bunny_method
{
  method_delete			delete_clipable;
  method_blit			blit;
  method_draw			draw;
  method_pixel			pixel;
  method_circle			circle;
  method_line			line;
  method_polygon		polygon;
  method_fill			fill;
  method_clear			clear;
  method_geometry		geometry;
};
*/
enum				_buffer_type
  {
    WINDOW			= 0,
    GRAPHIC_RAM			= 1,
    SYSTEM_RAM			= 2,
    GRAPHIC_TEXT		= 3,
    TTF_TEXT			= 4,
    SPRITE			= 5,
    DRESSED_SPRITE		= 6,
    TILEMAP			= 7,
    PARALLAX			= 8,
    LAST_BUFFER_TYPE
  };

//extern const bunny_method	gl_bunny_method[LAST_BUFFER_TYPE];

typedef void			*(*t_copy_on_write_gfx)(const void	*res);

struct				bunny_window
{
  size_t			type;
  sf::RenderWindow		*window;
  size_t			unused;
  ssize_t			width;
  ssize_t			height;
  t_bunny_extended_data		data[BUNNY_EXTENDED_DATA_LENGTH];
  const char			*window_name;
  t_bunny_window_style		style;
};

# ifdef				__MINGW32__
#  pragma			pack(1)
# endif

struct				bunny_picture
{
  size_t			type;
  sf::RenderTexture		*texture;
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

  size_t			res_id;
  const sf::Texture		*tex;
  sf::Sprite			*sprite;
};

struct				bunny_pixelarray
{
  size_t			type;
  size_t			unused;
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
  unsigned int			*rawpixels;

  size_t			res_id;
  sf::Image			*image;
  sf::Texture			*tex;
  sf::Sprite			*sprite;
};

struct				bunny_gfx_font
{
  size_t			type;
  sf::RenderTexture		*texture;
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

  size_t			res_id;
  const sf::Texture		*tex;
  sf::Sprite			*sprite;

  const char			*string;
  size_t			string_offset;
  size_t			string_len;
  t_bunny_align			halign;
  t_bunny_align			valign;
  unsigned int			color;
  unsigned int			outline_color;
  double			outline_size;
  t_bunny_position		offset;
  t_bunny_position		glyph_size;
  t_bunny_position		interglyph_space;

  // Private
  char				*conf_string;

  // Private, specific to gfx font
  t_bunny_picture		*gfx;
};

struct				bunny_ttf_font
{
  size_t			type;
  sf::RenderTexture		*texture;
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

  size_t			res_id;
  const sf::Texture		*tex;
  sf::Sprite			*sprite;

  const char			*string;
  size_t			string_offset;
  size_t			string_len;
  t_bunny_align			halign;
  t_bunny_align			valign;
  unsigned int			color;
  unsigned int			outline_color;
  double			outline_size;
  t_bunny_position		offset;
  t_bunny_position		glyph_size;
  t_bunny_position		interglyph_space;

  // Private
  char				*conf_string;

  // Private, specific to ttf font
  sf::Font			*font;
  sf::Text			*text;
};

struct				bunny_sprite
{
  size_t			type;
  sf::RenderTexture		*texture;
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

  size_t			res_id;
  const sf::Texture		*tex;
  sf::Sprite			*sprite;

  t_bunny_animation		*animation;
  size_t			nbr_animation;
  t_bunny_map			*hashname_id;
  t_bunny_collision_shapes	*collision_shapes;
  int32_t			nbr_collision;
  uint64_t			current_animation_hash;
  int32_t			current_animation;
  uint32_t			current_frame_repeat;
  int32_t			current_repeat;
  uint32_t			current_frame;
  double			current_time;
  bool				stop_repeat;
  bool				draw_collision_shape;
  t_bunny_collision		working_collision; // private
};

struct				bunny_dressed_sprite
{
  size_t			type;
  sf::RenderTexture		*texture;
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

  size_t			res_id;
  const sf::Texture		*tex;
  sf::Sprite			*sprite;

  t_bunny_animation		*animation;
  size_t			nbr_animation;
  t_bunny_map			*hashname_id;
  t_bunny_collision_shapes	*collision_shapes;
  int32_t			nbr_collision;
  uint64_t			current_animation_hash;
  int32_t			current_animation;
  uint32_t			current_frame_repeat;
  int32_t			current_repeat;
  uint32_t			current_frame;
  double			current_time;
  bool				stop_repeat;
  bool				draw_collision_shape;
  t_bunny_collision		working_collision; // private

  t_bunny_map			*closets; // [hash -> t_bunny_closet*]
  t_bunny_map			*clothes; // [hash -> t_bunny_sprite*]
  bool				have_wardrobe;
};

struct				bunny_tilemap
{
  size_t			type;
  sf::RenderTexture		*texture;
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

  // Private fields of t_bunny_clipable
  size_t			res_id;
  const sf::Texture		*tex; // Displayed shape
  sf::Sprite			*sprite;

  ////////////////////////////////////
  // Public fields of t_bunny_tilemap

  bool				normal_map;
  t_bunny_tilemap_projection	projection;
  t_bunny_tilemap_method	method;

  t_bunny_size			tile_size;
  t_bunny_size			map_size;

  // Tilesets
  t_bunny_tileset		*tilesets;
  int				nbr_tilesets;

  t_bunny_tile_layer		*layers;
  int				nbr_layers;

  int				layer_clip[2];

  t_bunny_accurate_zposition	camera;
  t_bunny_accurate_position	zoom;
  double			tile_rotation;
  bool				lock_borders;
  bool				loop[2];
  t_bunny_map			*properties; // map[string] = string

  /////////////////////////////////////
  // Private fields of t_bunny_tilemap
  // final stacking:
  t_bunny_picture		*working;
  t_bunny_position		working_target_diff;
  double			last_step;
  bool				duplicated_tilemap;

  // Layer stacking
  bool				rendered;
  t_bunny_zposition		animated_tiles[1024 * 16];
  int				nbr_animated_tiles;
  t_bunny_zposition		changed_tiles[1024];
  int				nbr_changed_tiles;
};

void				__bunny_tilemap_lock_borders(t_bunny_accurate_position	&tilsiz,
							     t_bunny_accurate_position	&tlcam,
							     struct bunny_tilemap	*tmap,
							     double			left,
							     double			right,
							     double			top,
							     double			bot);
void				bunny_delete_tileset(t_bunny_tileset			*ts);
void				bunny_delete_layer(t_bunny_tile_layer			*ts);

void				__bunny_set_square(sf::VertexArray			&vertex,
						   t_bunny_picture			*clip,
						   double				tleft,
						   double				ttop,
						   double				rleft,
						   double				rtop,
						   int					&last_vx);


struct				bunny_parallax
{
  size_t			type;
  sf::RenderTexture		*texture;
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

  // Private fields of t_bunny_clipable
  size_t			res_id;
  const sf::Texture		*tex; // Displayed shape
  sf::Sprite			*sprite;

  t_bunny_parallax_layer	*layers;
  size_t			nbr_layers;
  t_bunny_size			inside_size;
  t_bunny_accurate_position	viewpoint;
  bool				lock_viewpoint;
};


struct bunny_sprite		*_bunny_new_sprite(void);

t_bunny_tilemap			*__bunny_load_dabsic_tilemap(t_bunny_configuration *,
							     struct bunny_tilemap *);
t_bunny_tilemap			*__bunny_load_tmx_tilemap(t_bunny_configuration *,
							  struct bunny_tilemap *);
bool				__bunny_draw_tilemap(struct bunny_tilemap *);
void				__bunny_blit_tilemap(struct bunny_tilemap *tmap,
						     const t_bunny_clipable *pic,
						     const t_bunny_position *pos,
						     const t_bunny_shader *shader);
void				__bunny_draw_parallax(struct bunny_parallax *px);

# pragma			pack()

t_bunny_font			*__bunny_load_ttf(unsigned int		width,
						  unsigned int		height,
						  const char		*file,
						  const t_bunny_position *size);

t_bunny_font			*__bunny_load_gfx(unsigned int		width,
						  unsigned int		height,
						  const char		*file,
						  const t_bunny_position *size);

void				_bunny_draw_text(t_bunny_font			*font);

sf::Color			bunny_color_to_sf_color(unsigned int		i);
unsigned int			sf_color_to_bunny_color(const sf::Color		&clr);

struct SmallConf;
bool				_bunny_set_sprite_attribute(struct bunny_sprite &sprite,
							    SmallConf &config);

#endif	/*			__LAPIN_PRIVATE_GRAPHICS_H__			*/
