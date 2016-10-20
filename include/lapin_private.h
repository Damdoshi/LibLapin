/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_H__
# define			__LAPIN_PRIVATE_H__
# include			<SFML/Graphics.hpp>
# include			<SFML/Audio.hpp>
# ifdef				__WIN32
#  pragma			packed
# endif
# include			"lapin.h"
//# include			"Configuration.hpp"

# define			MEMORY_CHUNK_SIZE			64

struct				memtree;
struct				memchunk
{
  size_t			border0;
  struct memtree		*tree;
  struct memchunk		*prev;
  struct memchunk		*next;
  char				*data;
  size_t			real_size;
  size_t			border1;
};

struct				memtree
{
  size_t			chunk_size;
  struct memchunk		*allocated;
  struct memchunk		*freed;
  struct memtree		*greater;
  struct memtree		*lesser;
};

struct				memhead
{
  size_t			alloc_count;
  size_t			total_count;
  size_t			alloc;
  size_t			total;
  struct memtree		*first;
  void				*limit;
  char				*last_position;
};

struct memchunk			*get_node(struct memhead		*head,
					  size_t			data);

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
  unsigned int			width;
  unsigned int			height;
  const char			*window_name;
};

struct				bunny_picture
{
  size_t			type;
  sf::RenderTexture		*texture;
  unsigned int			width;
  unsigned int			height;
  sf::IntRect			rect;
  double			x_origin;
  double			y_origin;
  double			x_scale;
  double			y_scale;
  double			rotation;
  t_bunny_color			color_mask;
  const sf::Texture		*tex;
  sf::Sprite			sprite;
};

struct				bunny_pixelarray
{
  size_t			type;
  size_t			unused;
  unsigned int			width;
  unsigned int			height;
  sf::IntRect			rect;
  double			x_origin;
  double			y_origin;
  double			x_scale;
  double			y_scale;
  double			rotation;
  t_bunny_color			color_mask;
  unsigned int			*rawpixels;
  sf::Image			image;
  sf::Texture			tex;
  sf::Sprite			sprite;
};

enum				_music_or_sound
  {
    MUSIC,
    EFFECT
  };

struct				bunny_sound
{
  enum _music_or_sound		type;
  char				*file;
};

struct				bunny_music
{
  enum _music_or_sound		type;
  char				*file;
  double			duration;
  sf::Music			music;
};

struct				bunny_effect
{
  enum _music_or_sound		type;
  char				*file;
  size_t			sample_per_second;
  size_t			duration;
  int16_t *			sample;
  sf::SoundBuffer		effect;
  sf::Sound			sound;
};

extern t_bunny_context		gl_callback;
extern bool			gl_keyboard[BKS_LAST_KEY];
extern t_bunny_position		gl_mouse;
extern bool			gl_button[LAST_BUNNY_MOUSEBUTTON];
extern bool			gl_joy_button[LAST_BUNNY_JOYSTICK][LAST_BUNNY_BUTTON];
extern float			gl_joy_axis[LAST_BUNNY_JOYSTICK][LAST_BUNNY_AXIS];
extern t_bunny_joystick		gl_joystick[LAST_BUNNY_JOYSTICK];
extern t_bunny_window		*gl_window;
extern bool			gl_full_blit;

struct				bunny_database
{
  
};

struct				bunny_database_iterator
{
  int				index;
  int				nbr_rows;
  // hbs::Dictionnary<size_t>	*dic;
};

struct				bunny_configuration
{
  // hbs::Configuration		*config;
  char				*data[4];
  size_t			type;
  const char			*name;
  const char			*value;
};

void				__bunny_xor(char			*cnt,
					    size_t			len,
					    const t_bunny_cipher_key	*key);
void				__bunny_caesar(char			*cnt,
					       size_t			len,
					       const t_bunny_cipher_key	*key,
					       bool			cipher);
void				__bunny_shaker(char			*cnt,
					       size_t			len,
					       const t_bunny_cipher_key	*key,
					       bool			cipher);

struct				bunny_trap
{
  struct bunny_trap		*next;
  struct bunny_trap		*prev;
  char				remove_it;
  char				__unused1;
  char				__unused2;
  char				__unused3;
  double			start_time;
  double			duration;
  t_bunny_trap_function		func;
  void				*param;
};

extern sf::Clock		gl_bunny_current_time;
struct bunny_trap		*gl_bunny_trap_head[4];

void				__bunny_delete_trap(t_bunny_trap	*_trap);

#endif	/*			__LAPIN_PRIVATE_H__	*/
