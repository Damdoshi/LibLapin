/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file sound.h
** The sound module contains facilities to load, generate and play sounds.
** Recording is currently not supported.
*/

#ifndef				__LAPIN_SOUND_H__
# define			__LAPIN_SOUND_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The t_bunny_sound is the header of every other sound structure
** like t_bunny_music or t_bunny_effect. It contains the name of
** the file from which the sound was loaded or NULL if it was generated.
** It also contents private fields.
*/
typedef struct			s_bunny_sound
{
  const char			_private[sizeof(int32_t)];
  const char * const		file;
}				t_bunny_sound;

/*!
** The t_bunny_music structure is useful to play, load and
** manage music. It contains an attribute named "duration"
** which is, in seconds, the duration of the music.
*/
typedef struct			s_bunny_music
{
  t_bunny_sound			sound;
  const double			duration;
}				t_bunny_music;

/*!
** The t_bunny_effect structure is useful to play, load and
** manage sound effects. It contains attributes like
** sample_per_second which contains how many int16_t is
** neccessary to a one second sound. duration is the
** sound duration in seconds.
** and finaly sample which is the sound wave itself.
** sample is the sound equivalent of the t_bunny_pixelarray
** 's pixel field: it is an array of duration * sample_per_second
** int16_t.
*/
typedef struct			s_bunny_effect
{
  t_bunny_sound			sound;
  const size_t			sample_per_second;
  const double			duration;
  int16_t * const		sample;
}				t_bunny_effect;

/*!
** The bunny_load_music function load a sound file and return a matching t_bunny_music.
** The reserved memory to handle it is outside the bunny_malloc space.
** Supported formats are .wav and .ogg.
** \param file The music file
** \return A t_bunny_music pointer or NULL on error.
*/
t_bunny_music			*bunny_load_music(const char			*file);

/*!
** The bunny_load_effect function create in the bunny_malloc memory space a sample
** of duration seconds. bunny_new_effect create SAMPLE_PER_SECONDS int16_t inside
** the t_bunny_effect structure per second.
** \param duration The duration of the sound effect in seconds
** \return A valid t_bunny_effect or NULL on error.
*/
# define			SAMPLE_PER_SECONDS				44100
t_bunny_effect			*bunny_new_effect(double			duration);

/*!
** The bunny_load_effect function load a sound file and return a matching t_bunny_effect.
** The reserved memory to handle it is inside the bunny_malloc space.
** Supported formats are .wav and .ogg.
** \param file The sound file.
** \return A t_bunny_effect pointer or NULL on error.
*/
t_bunny_effect			*bunny_load_effect(const char			*file);

/*!
** The bunny_save_effect function save into a sound file the given sound.
** Supported formats are .wav and .ogg
** \param effect The sound to save
** \param str The file where to save
** \return True if everything went well else false.
*/
bool				bunny_save_effect(const t_bunny_effect		*effect,
						  const char			*str);

/*!
** In case you have created a sound effect and then filled its content manually thanks
** to the sample attribute, before playing the sound effect, you must call this function.
** \param effect The sound effect to generate
*/
bool				bunny_compute_effect(t_bunny_effect		*effect);

/*!
** The bunny_sound_volume change the volume of the given sound.
** \param sound The sound to modify
** \param volume A value between 0 and 100
*/
void				bunny_sound_volume(t_bunny_sound		*sound,
						   double			volume);

/*!
** The bunny_sound_pitch function accellerate or make slower the playing speed of
** the given sound, making it more acute or lower.
** \param sound The sound to modify
** \param pitch A value that will be multiplied with the playing speed. If set to 1,
** the sound is played with the original speed.
*/
void				bunny_sound_pitch(t_bunny_sound			*sound,
						  double			pitch);

/*!
** Set if the sound will be played again if it reaches its end.
** \param sound The sound to calibrate
** \param True to activate the loop, false to deactivate the loop.
*/
void				bunny_sound_loop(t_bunny_sound			*sound,
						 bool				loop);

/*!
** Set the position of the sound in space. You should use headphones to feel it better.
** \param sound The sound to modify
** \param x The horizontal position of the sound
** \param y The vertical position of the sound
** \param z The in-front-of-you/behind-you axis of the sound
*/
void				bunny_sound_position(t_bunny_sound		*sound,
						     double			x,
						     double			y,
						     double			z);

/*!
** Calibrate the way the sound is getting lower when getting far from the position (0, 0, 0)
** when bunny_sound_position is set.
** \param sound The sound to modify
** \param attenuation A value between 0 and 10.
*/
void				bunny_sound_attenuation(t_bunny_sound		*sound,
							double			attenuation);

/*!
** Play the sound. If the sound is a t_bunny_effect and that it was manually edited,
** do to forget to call bunny_compute_effect before.
** \param sound The sound to play.
*/
void				bunny_sound_play(t_bunny_sound			*sound);

/*!
** Stop the sound.
** \param sound The sound to stop.
*/
void				bunny_sound_stop(t_bunny_sound			*sound);

/*!
** Get the position in seconds of the sent music.
** \param music The music to know where the cursor is
** \return The position in seconds between the beginning and the current cursor.
*/
double				bunny_music_get_cursor(t_bunny_music		*music);

/*!
** Delete the sent sound.
** \param The sound to destroy
*/
void				bunny_delete_sound(t_bunny_sound		*sound);

#endif	/*			__LAPIN_SOUND_H__	*/

