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

struct				bunny_ttf
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

  size_t			padding[2];

  const char			*string;
  bool				hcrop;
  bool				vcrop;
  bool				justify;
  t_bunny_align			halign;
  t_bunny_align			valign;
  unsigned int			outline;
  sf::Font			font;
  sf::Text			text;
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
  bool				hcrop;
  bool				vcrop;
  bool				justify;
  t_bunny_align			halign;
  t_bunny_align			valign;
  unsigned int			outline;
};

void				__blit_text_gfx(t_bunny_buffer			*buffer,
						const t_bunny_clipable		*font,
						const t_bunny_position		*pos,
						const t_bunny_shader		*shader);

void				__blit_text_ttf(t_bunny_buffer			*buffer,
						const t_bunny_clipable		*font,
						const t_bunny_position		*pos,
						const t_bunny_shader		*shader);

#endif	/*			__LAPIN_PRIVATE_GRAPHICS_H__	*/
