/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
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
# pragma			pack(4)

/*!
** The t_bunny_sound is the header of every other sound structure
** like t_bunny_music or t_bunny_effect. It contains the name of
** the file from which the sound was loaded or NULL if it was generated.
** It also contents private fields.
*/
/**
 * @doc-symbol t_bunny_sound
 * @doc-module sound
 * @doc-kind type
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Base structure for loaded, streamed and generated sounds.
 * @description It is embedded in t_bunny_music, t_bunny_effect and t_bunny_recorder. Any function expecting t_bunny_sound can receive one of these derived sound objects.
 * @param _private Private storage used by LibLapin. Do not edit it.
 * @param file Source file name, or an empty string for generated sounds.
 * @param volume Volume between 0 and 100.
 * @param pitch Playback speed multiplier; 1 is the original speed.
 * @param loop true if the sound loops.
 * @param position Relative 3D position of the sound.
 * @param attenuation Distance attenuation factor.
 * @param playing true while the sound is playing.
 * @param pause true while the sound is paused.
 * @see t_bunny_music, t_bunny_effect, t_bunny_recorder, bunny_delete_sound
 *
 * @doc-lang fr
 * @brief Structure de base des sons chargés, lus en streaming et générés.
 * @description Elle est embarquée dans t_bunny_music, t_bunny_effect et t_bunny_recorder. Toute fonction attendant t_bunny_sound peut recevoir l'un de ces objets sonores dérivés.
 * @param _private Stockage privé utilisé par la LibLapin. Ne le modifiez pas.
 * @param file Nom du fichier source, ou chaîne vide pour les sons générés.
 * @param volume Volume entre 0 et 100.
 * @param pitch Multiplicateur de vitesse de lecture ; 1 correspond à la vitesse originale.
 * @param loop true si le son boucle.
 * @param position Position 3D relative du son.
 * @param attenuation Facteur d'atténuation avec la distance.
 * @param playing true pendant que le son est joué.
 * @param pause true pendant que le son est en pause.
 * @see t_bunny_music, t_bunny_effect, t_bunny_recorder, bunny_delete_sound
 */
typedef struct			s_bunny_sound
{
  const char			_private[sizeof(size_t)];
  const char * const		file;
  double			volume;
  double			pitch;
  bool				loop;
  double			position[3];
  double			attenuation;
  const bool			playing;
  const bool			pause;
}				t_bunny_sound;

/*!
** The t_bunny_music structure is useful to play, load and
** manage music. It contains an attribute named "duration"
** which is, in seconds, the duration of the music.
*/
/**
 * @doc-symbol t_bunny_music
 * @doc-module sound
 * @doc-kind type
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents streamed music.
 * @description A music embeds t_bunny_sound and is streamed from disk instead of being fully loaded as editable samples.
 * @param sound Common sound header.
 * @param duration Duration of the music in seconds.
 * @see t_bunny_sound, bunny_load_music, bunny_read_music, bunny_delete_sound
 *
 * @doc-lang fr
 * @brief Représente une musique lue en streaming.
 * @description Une musique embarque t_bunny_sound et est lue depuis le disque au lieu d'être entièrement chargée sous forme d'échantillons modifiables.
 * @param sound En-tête sonore commun.
 * @param duration Durée de la musique en secondes.
 * @see t_bunny_sound, bunny_load_music, bunny_read_music, bunny_delete_sound
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
/**
 * @doc-symbol t_bunny_effect
 * @doc-module sound
 * @doc-kind type
 * @doc-order 140
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a sound effect loaded in memory.
 * @description Its sample buffer can be edited manually, then submitted with bunny_compute_effect before playback.
 * @param sound Common sound header.
 * @param sample_per_second Number of samples stored for one second.
 * @param duration Duration of the effect in seconds.
 * @param sample Writable signed 16-bit sample buffer.
 * @see t_bunny_sound, bunny_new_effect, bunny_load_effect, bunny_compute_effect, bunny_delete_sound
 *
 * @doc-lang fr
 * @brief Représente un effet sonore chargé en mémoire.
 * @description Son tampon d'échantillons peut être modifié manuellement, puis soumis avec bunny_compute_effect avant la lecture.
 * @param sound En-tête sonore commun.
 * @param sample_per_second Nombre d'échantillons stockés pour une seconde.
 * @param duration Durée de l'effet en secondes.
 * @param sample Tampon modifiable d'échantillons signés sur 16 bits.
 * @see t_bunny_sound, bunny_new_effect, bunny_load_effect, bunny_compute_effect, bunny_delete_sound
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
t_bunny_music			*bunny_read_music(t_bunny_configuration		*cnf);

/*!
** The bunny_load_effect function create in the bunny_malloc memory space a sample
** of duration seconds. bunny_new_effect create SAMPLE_PER_SECONDS int16_t inside
** the t_bunny_effect structure per second.
** \param duration The duration of the sound effect in seconds
** \return A valid t_bunny_effect or NULL on error.
*/
/**
 * @doc-symbol bunny_new_effect
 * @doc-module sound
 * @doc-kind macro
 * @doc-order 180
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates an empty mono sound effect with the default sample rate.
 * @description The sample buffer contains duration multiplied by SAMPLE_PER_SECONDS samples. Fill sample, call bunny_compute_effect, then play the sound.
 * @param d Duration in seconds.
 * @return-success A newly allocated t_bunny_effect.
 * @return-failure NULL if the effect cannot be allocated.
 * @error ENOMEM Out of memory.
 * @log Calls _bunny_new_effect, which may log in the "ressource" and "sound" domains.
 * @see SAMPLE_PER_SECONDS, bunny_create_effect, bunny_new_sound, bunny_compute_effect
 *
 * @doc-lang fr
 * @brief Crée un effet sonore mono vide avec la fréquence d'échantillonnage par défaut.
 * @description Le tampon sample contient duration multiplié par SAMPLE_PER_SECONDS échantillons. Remplissez sample, appelez bunny_compute_effect, puis jouez le son.
 * @param d Durée en secondes.
 * @return-success Un t_bunny_effect nouvellement alloué.
 * @return-failure NULL si l'effet ne peut pas être alloué.
 * @error ENOMEM Mémoire insuffisante.
 * @log Appelle _bunny_new_effect, qui peut écrire dans les domaines "ressource" et "sound".
 * @see SAMPLE_PER_SECONDS, bunny_create_effect, bunny_new_sound, bunny_compute_effect
 */
# define			bunny_new_effect(d)				_bunny_new_effect(d, SAMPLE_PER_SECONDS, 1)
/**
 * @doc-symbol bunny_create_effect
 * @doc-module sound
 * @doc-kind macro
 * @doc-order 182
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates an empty mono sound effect with a custom sample rate.
 * @param d Duration in seconds.
 * @param s Samples per second.
 * @return-success A newly allocated t_bunny_effect.
 * @return-failure NULL if the effect cannot be allocated.
 * @error ENOMEM Out of memory.
 * @log Calls _bunny_new_effect, which may log in the "ressource" and "sound" domains.
 * @see bunny_new_effect, bunny_new_sound, bunny_compute_effect
 *
 * @doc-lang fr
 * @brief Crée un effet sonore mono vide avec une fréquence d'échantillonnage personnalisée.
 * @param d Durée en secondes.
 * @param s Échantillons par seconde.
 * @return-success Un t_bunny_effect nouvellement alloué.
 * @return-failure NULL si l'effet ne peut pas être alloué.
 * @error ENOMEM Mémoire insuffisante.
 * @log Appelle _bunny_new_effect, qui peut écrire dans les domaines "ressource" et "sound".
 * @see bunny_new_effect, bunny_new_sound, bunny_compute_effect
 */
# define			bunny_create_effect(d, s)			_bunny_new_effect(d, s, 1)
/**
 * @doc-symbol bunny_new_sound
 * @doc-module sound
 * @doc-kind macro
 * @doc-order 184
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates an empty sound effect with custom sample rate and channel count.
 * @param d Duration in seconds.
 * @param s Samples per second.
 * @param c Number of channels.
 * @return-success A newly allocated t_bunny_effect.
 * @return-failure NULL if the effect cannot be allocated.
 * @error ENOMEM Out of memory.
 * @log Calls _bunny_new_effect, which may log in the "ressource" and "sound" domains.
 * @see bunny_new_effect, bunny_create_effect, bunny_compute_effect
 *
 * @doc-lang fr
 * @brief Crée un effet sonore vide avec une fréquence d'échantillonnage et un nombre de canaux personnalisés.
 * @param d Durée en secondes.
 * @param s Échantillons par seconde.
 * @param c Nombre de canaux.
 * @return-success Un t_bunny_effect nouvellement alloué.
 * @return-failure NULL si l'effet ne peut pas être alloué.
 * @error ENOMEM Mémoire insuffisante.
 * @log Appelle _bunny_new_effect, qui peut écrire dans les domaines "ressource" et "sound".
 * @see bunny_new_effect, bunny_create_effect, bunny_compute_effect
 */
# define			bunny_new_sound(d, s, c)			_bunny_new_effect(d, s, c)
t_bunny_effect			*_bunny_new_effect(double			duration,
						   int				sample_per_second,
						   int				channel);

/*!
** The bunny_load_effect function load a sound file and return a matching t_bunny_effect.
** The reserved memory to handle it is inside the bunny_malloc space.
** Supported formats are .wav and .ogg.
** \param file The sound file.
** \return A t_bunny_effect pointer or NULL on error.
*/
t_bunny_effect			*bunny_load_effect(const char			*file);

/*!
** This function is not implemented.
** The bunny_read_effect_id function read in memory a sound file and return
** a matching t_bunny_effect.
** The reserved memory to handle it is inside the bunny_malloc space.
** Supported formats are .wav and .ogg.
** \param data The chunk of memory to read
** \param len The size of the memory chunk
** \param file The original sound file name, or any unique label.
** \return A t_bunny_effect pointer or NULL on error.
*/
t_bunny_effect			*bunny_read_effect_id(const void		*data,
						      size_t			len,
						      const char		*file);

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
** Play the sound. Applies all attributes to the sound, so even if the sound was
** being played, you can edit its attributes and call bunny_sound_play to edit all of
** them simultaneously.
** If the sound is a t_bunny_effect and that it was manually edited,
** do to forget to call bunny_compute_effect before calling this function.
** \param sound The sound to play.
*/
void				bunny_sound_play(t_bunny_sound			*sound);

/*!
** Pause the sound.
** \param sound The sound to play.
*/
void				bunny_sound_pause(t_bunny_sound			*sound);

/*!
** Stop the sound. Unpause it if it was paused.
** \param sound The sound to stop.
*/
void				bunny_sound_stop(t_bunny_sound			*sound);

/*!
** Set the position in seconds of the cursor for the sent sound.
** \param snd The sound to move the cursor in
** \param secds The position of the cursor to set
*/
void				bunny_sound_set_cursor(t_bunny_sound		*snd,
						       double			secs);

/*!
** Get the position in seconds of the sent sound.
** \param snd The sound to know where the cursor is
** \return The position in seconds between the beginning and the current cursor.
*/
double				bunny_sound_get_cursor(const t_bunny_sound	*snd);

/*!
**
**
*/
double				bunny_sound_get_duration(const t_bunny_sound	*snd);

/*!
**
**
*/
bool				bunny_sound_is_playing(const t_bunny_sound	*snd);

/*
** Load the sent configuration file (must be accepted by the bunny_configuration module)
** and set all values accordingly to what is inside the file.
**
** If conf_file or sound is NULL, an error occurs.
** If *sound is NULL, then a picture will be created et set thanks to the associated field
** in configuration file. The picture will be returned throught *clipable.
** If *sound is not NULL, every of its attribute will be set depending on the config file.
**
** If config is NULL, then a configuration file will be loaded, used and destroyed.
** If *config is NULL, then a configuration file will be loaded, used and set to *config
** to be returned.
** If *config is not NULL, then it will be used as target to load the new configuration
** file.
**
** See formats/sound to see how to format you files accordinly to their syntax.
**
** \param conf_file The configuration file that contains attributes.
** \param sound The sound to configure, or where to store the new one
** \param config The configuration file to use, or where to store the new loaded one.
** \param is_music Is the sound a music or a sound effect.
** \return True if the loading, reading and setting were done properly.
*/
bool				bunny_set_sound_attribute(const char		*conf_file,
							  t_bunny_sound		**sound,
							  t_bunny_configuration **config,
							  bool			is_music);

/*!
** Delete the sent sound.
** \param The sound to destroy
*/
void				_bunny_delete_sound(t_bunny_sound		*sound);

# if				defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
/*!
** Delete the sent sound.
** \param The sound to destroy
*/
#  define			bunny_delete_sound(snd)				\
  _bunny_delete_sound								\
  (_Generic((snd),								\
	    t_bunny_music*: (t_bunny_sound*)(snd),				\
	    t_bunny_sound_sprite*: (t_bunny_sound*)(snd),			\
	    t_bunny_effect*: (t_bunny_sound*)(snd),				\
	    t_bunny_sound*: (snd)						\
	    ))
# else
#  define			bunny_delete_sound(snd)				\
  _bunny_delete_sound(snd)
# endif

/*!
** The effect loading function use a ressource manager to avoid loading several
** times the same file. This means behind every t_bunny_effect you will create
** throught bunny_load_effect, there is only one single true load.
** This mean that modifying a single effect would modify every effects that was
** loaded throught the same file.
**
** To avoid this behaviour if that what you want, you can use this function that
** will turn unique the sent effect and contains modification to itself.
** Calling this function on an already unique effect does not make anything.
**
** This function is the effect equivalent of bunny_make_clipable_unique in graphics.
**
** \param eff The effect that will be turned unique
** \return True if everything went well. If the effect was already unique,
** everything went well.
*/
bool				bunny_make_effect_unique(t_bunny_effect		*eff);


/**
 * @doc-symbol t_bunny_recorder
 * @doc-module sound
 * @doc-kind type
 * @doc-order 600
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Represents an audio recorder and the effect produced by its recording.
 * @param effect Embedded effect containing recorded samples after bunny_stop_record.
 * @param _private Private storage used by LibLapin. Do not edit it.
 * @param device Name of the selected recording device.
 * @param recording true while capture is running.
 * @see bunny_new_recorder, bunny_start_record, bunny_stop_record, bunny_record_devices
 *
 * @doc-lang fr
 * @brief Représente un enregistreur audio et l'effet produit par son enregistrement.
 * @param effect Effet embarqué contenant les échantillons enregistrés après bunny_stop_record.
 * @param _private Stockage privé utilisé par la LibLapin. Ne le modifiez pas.
 * @param device Nom du périphérique d'enregistrement sélectionné.
 * @param recording true pendant que la capture est en cours.
 * @see bunny_new_recorder, bunny_start_record, bunny_stop_record, bunny_record_devices
 */
typedef struct			s_bunny_recorder
{
  t_bunny_effect		effect;
  size_t			_private[4];
  const char * const		device;
  const bool			recording;
}				t_bunny_recorder;

t_bunny_recorder		*bunny_new_recorder(const char			*device,
						    unsigned int		sample_rate);

bool				bunny_start_record(t_bunny_recorder		*recorder);
void				bunny_stop_record(t_bunny_recorder		*recorder);
const char			**bunny_record_devices(void);
const char			*bunny_default_record_device(void);
bool				bunny_record_available(void);

# pragma			pack()
#endif	/*			__LAPIN_SOUND_H__	*/

