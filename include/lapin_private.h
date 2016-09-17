/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_PRIVATE_H__
# define		__LAPIN_PRIVATE_H__
# include		<SFML/Graphics.hpp>
# include		<SFML/Audio.hpp>
# ifdef			__WIN32
#  pragma		packed
# endif
# include		"Ini.hpp"
# include		"lapin.h"

# define		MEMORY_CHUNK_SIZE			64

struct			memtree;
struct			memchunk
{
  size_t		border0;
  struct memtree	*tree;
  struct memchunk	*prev;
  struct memchunk	*next;
  char			*data;
  size_t		real_size;
  size_t		border1;
};

struct			memtree
{
  size_t		chunk_size;
  struct memchunk	*allocated;
  struct memchunk	*freed;
  struct memtree	*greater;
  struct memtree	*lesser;
};

struct			memhead
{
  size_t		alloc_count;
  size_t		total_count;
  size_t		alloc;
  size_t		total;
  struct memtree	*first;
  void			*limit;
  char			*last_position;
};

struct memchunk		*get_node(struct memhead		*head,
				       size_t			data);

enum			_buffer_type
  {
    WINDOW,
    GRAPHIC_RAM,
    SYSTEM_RAM
  };

struct			bunny_window
{
  size_t		type;
  sf::RenderWindow	*window;
  unsigned int		width;
  unsigned int		height;
  const char		*window_name;
};

struct			bunny_picture
{
  size_t		type;
  sf::RenderTexture	*texture;
  unsigned int		width;
  unsigned int		height;
  sf::IntRect		rect;
  double		x_origin;
  double		y_origin;
  double		x_scale;
  double		y_scale;
  double		rotation;
  t_bunny_color		color_mask;
  const sf::Texture	*tex;
  sf::Sprite		sprite;
};

struct			bunny_pixelarray
{
  size_t		type;
  size_t		unused;
  unsigned int		width;
  unsigned int		height;
  sf::IntRect		rect;
  double		x_origin;
  double		y_origin;
  double		x_scale;
  double		y_scale;
  double		rotation;
  t_bunny_color		color_mask;
  unsigned int		*rawpixels;
  sf::Image		image;
  sf::Texture		tex;
  sf::Sprite		sprite;
};

enum			_music_or_sound
  {
    MUSIC,
    EFFECT
  };

struct			bunny_sound
{
  enum _music_or_sound	type;
  char			*file;
};

struct			bunny_music
{
  enum _music_or_sound	type;
  char			*file;
  double		duration;
  sf::Music		music;
};

struct			bunny_effect
{
  enum _music_or_sound	type;
  char			*file;
  size_t		sample_per_second;
  size_t		duration;
  int16_t *		sample;
  sf::SoundBuffer	effect;
  sf::Sound		sound;
};

extern t_bunny_context	gl_callback;
extern bool		gl_keyboard[BKS_LAST_KEY];
extern t_bunny_position	gl_mouse;
extern bool		gl_button[LAST_BUNNY_MOUSEBUTTON];
extern bool		gl_joy_button[LAST_BUNNY_JOYSTICK][LAST_BUNNY_BUTTON];
extern float		gl_joy_axis[LAST_BUNNY_JOYSTICK][LAST_BUNNY_AXIS];
extern t_bunny_joystick	gl_joystick[LAST_BUNNY_JOYSTICK];
extern t_bunny_window	*gl_window;
extern bool		gl_full_blit;

#endif	/*		__LAPIN_PRIVATE_H__	*/
