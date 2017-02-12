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
    SYSTEM_RAM
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
  sf::Sprite			sprite;
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

#endif	/*			__LAPIN_PRIVATE_GRAPHICS_H__	*/
