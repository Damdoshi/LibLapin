/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_SOUND_H__
# define			__LAPIN_PRIVATE_SOUND_H__
# include			<SFML/Audio.hpp>
# include			<map>
# include			<array>

enum				_music_or_sound
  {
    MUSIC,
    EFFECT
  };

# ifdef				__MINGW32__
#  pragma			pack(1)
# endif
struct				bunny_sound
{
  size_t			type;
  char				*file;
  double			volume;
  double			pitch;
  bool				loop;
  double			position[3];
  double			attenuation;
  bool				playing;
  bool				pause;
};

struct				bunny_music
{
  size_t			type;
  char				*file;
  double			volume;
  double			pitch;
  bool				loop;
  double			position[3];
  double			attenuation;
  bool				playing;
  bool				pause;

  double			duration;
  t_bunny_map			*sound_areas; // only in t_bunny_sound_sprite
  void				*last_played_slice; // only in t_bunny_sound_sprite
  t_bunny_music_track		track; // only in t_bunny_sound_sprite

  //
  sf::Music			music;
  void				*sound_manager;
};

struct				bunny_effect
{
  size_t			type;
  char				*file;
  double			volume;
  double			pitch;
  bool				loop;
  double			position[3];
  double			attenuation;
  bool				playing;
  bool				pause;

  size_t			sample_per_second;
  double			duration;
  int16_t *			sample;
  size_t			res_id;
  sf::SoundBuffer		*effect;
  sf::Sound			sound;
  void				*sound_manager;
};
# pragma			pack()

typedef struct			s_bunny_managed_sound
{
  double			proper_volume;
  double			proper_pitch;
}				t_bunny_managed_sound;

struct				bunny_sound_manager
{
  t_bunny_sound			*current_music[BST_LAST_TRACK];
  double			general_volume;
  double			volumes[BST_LAST_SOUND_TYPE];
  double			general_pitch;
  double			pitches[BST_LAST_SOUND_TYPE];
  std::map<
    t_bunny_sound*,
    t_bunny_sound_type
    >				sound_to_type;
  std::array<
    std::map<t_bunny_sound*, t_bunny_managed_sound>,
    BST_LAST_SOUND_TYPE
    >				sounds;
};

#endif	/*			__LAPIN_PRIVATE_SOUND_H__	*/
