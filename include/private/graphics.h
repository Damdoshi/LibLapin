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
# ifdef				__WIN32
#  pragma			packed
# endif
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
  const char			*window_name;
};

struct				bunny_picture
{
  size_t			type;
  sf::RenderTexture		*texture;
  t_copy_on_write_gfx		duplicate;
  ssize_t			width;
  ssize_t			height;
  t_bunny_area			rect;
  t_bunny_accurate_position	position;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;

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
  t_bunny_area			rect;
  t_bunny_accurate_position	position;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;
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
  t_bunny_area			rect;
  t_bunny_accurate_position	position;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;

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

  t_bunny_picture		*gfx;
};

struct				bunny_ttf_font
{
  size_t			type;
  sf::RenderTexture		*texture;
  t_copy_on_write_gfx		duplicate;
  ssize_t			width;
  ssize_t			height;
  t_bunny_area			rect;
  t_bunny_accurate_position	position;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;

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

  sf::Font			*font;
  sf::Text			*text;
};

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

#endif	/*			__LAPIN_PRIVATE_GRAPHICS_H__			*/
