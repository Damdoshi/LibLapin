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
};

struct				bunny_music
{
  size_t			type;
  char				*file;
  double			duration;
  sf::Music			music;
};

struct				bunny_effect
{
  size_t			type;
  char				*file;
  size_t			sample_per_second;
  size_t			duration;
  int16_t *			sample;
  sf::SoundBuffer		effect;
  sf::Sound			sound;
};


#endif	/*			__LAPIN_PRIVATE_SOUND_H__	*/
