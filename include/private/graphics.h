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

enum				_buffer_type
  {
    WINDOW,
    GRAPHIC_RAM,
    SYSTEM_RAM,
    GRAPHIC_TEXT,
    TTF_TEXT
  };

struct				bunny_window
{
  size_t			type;
  sf::RenderWindow		*window;
  ssize_t			width;
  ssize_t			height;
  const char			*window_name;
};

struct				bunny_picture
{
  size_t			type;
  sf::RenderTexture		*texture;
  ssize_t			width;
  ssize_t			height;
  t_bunny_area			rect;
  t_bunny_accurate_position	position;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;

  const sf::Texture		*tex;
  sf::Sprite			*sprite;
};

struct				bunny_pixelarray
{
  size_t			type;
  size_t			unused;
  ssize_t			width;
  ssize_t			height;
  t_bunny_area			rect;
  t_bunny_accurate_position	position;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;
  unsigned int			*rawpixels;

  sf::Image			image;
  sf::Texture			tex;
  sf::Sprite			sprite;
};

struct				bunny_gfx_font
{
  size_t			type;
  sf::RenderTexture		*texture;
  ssize_t			width;
  ssize_t			height;
  t_bunny_area			rect;
  t_bunny_accurate_position	position;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;
  const sf::Texture		*tex;
  sf::Sprite			*sprite;

  const char			*string;
  t_bunny_align			halign;
  t_bunny_align			valign;
  unsigned int			color;
  unsigned int			outline_color;
  double			outline_size;
  t_bunny_position		offset;
  t_bunny_position		glyph_size;

  t_bunny_picture		*gfx;
};

struct				bunny_ttf_font
{
  size_t			type;
  sf::RenderTexture		*texture;
  ssize_t			width;
  ssize_t			height;
  t_bunny_area			rect;
  t_bunny_accurate_position	position;
  t_bunny_accurate_position	origin;
  t_bunny_accurate_position	scale;
  double			rotation;
  t_bunny_color			color_mask;
  const sf::Texture		*tex;
  sf::Sprite			*sprite;

  const char			*string;
  t_bunny_align			halign;
  t_bunny_align			valign;
  unsigned int			color;
  unsigned int			outline_color;
  double			outline_size;
  t_bunny_position		offset;
  t_bunny_position		glyph_size;

  sf::Font			font;
  sf::Text			text;
};

void				_bunny_draw_text(t_bunny_font			*font);

sf::Color			bunny_color_to_sf_color(unsigned int	i)
{
  t_bunny_color			col;

  col.full = i;
  return (sf::Color(col.argb[RED_CMP], col.argb[GREEN_CMP], col.argb[BLUE_CMP], col.argb[ALPHA_CMP]));
}

unsigned int			sf_color_to_bunny_color(const sf::Color	&clr)
{
  t_bunny_color			col;

  col.argb[RED_CMP] = clr.r;
  col.argb[GREEN_CMP] = clr.g;
  col.argb[BLUE_CMP] = clr.b;
  col.argb[ALPHA_CMP] = clr.a;
  return (col.full);
}

#endif	/*			__LAPIN_PRIVATE_GRAPHICS_H__			*/
