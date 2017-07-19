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

enum				_music_or_sound
  {
    MUSIC,
    EFFECT
  };

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
  sf::Music			music;
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
  size_t			duration;
  int16_t *			sample;
  size_t			res_id;
  sf::SoundBuffer		*effect;
  sf::Sound			sound;
};


#endif	/*			__LAPIN_PRIVATE_SOUND_H__	*/
