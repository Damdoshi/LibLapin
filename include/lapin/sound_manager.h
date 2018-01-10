/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

/*!
** \file sound_manager.h
** The sound manager helps you to manage your general sound configuration.
** You can add and remove sounds from it, set them in three categories.
** You can edit volume and pitch for categories.
** You can set a general volume or pitch.
** You can set a volume or pitch proper to sounds.
*/

#ifndef			__LAPIN_SOUND_MANAGER_H__
# define		__LAPIN_SOUND_MANAGER_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

/*!
** Indicates a music track.
*/
typedef enum		e_bunny_music_track
  {
    BST_ALL		= -1,
    BST_TRACK_01,
    BST_TRACK_02,
    BST_TRACK_03,
    BST_LAST_TRACK
  }			t_bunny_music_track;

/*!
** Indicates a sound type: music, effect or voice.
** Each sound type have a matching volume and pitch.
*/
typedef enum		e_bunny_sound_type
  {
    BST_GENERAL		= -1,
    BST_MUSIC,
    BST_EFFECT,
    BST_VOICE,
    BST_LAST_SOUND_TYPE
  }			t_bunny_sound_type;

/*!
** The sound manager structure is a centralized sound controler
** that allow to restrict the amount of music played
** simultaneously. It allows to control volumes and pitches by category,
** like we often expect in video games.
*/
typedef struct		s_bunny_sound_manager
{
  const t_bunny_sound * const current_music[BST_LAST_TRACK];
  const double		general_volume;
  const double		volumes[BST_LAST_SOUND_TYPE];
  const double		general_pitch;
  const double		pitches[BST_LAST_SOUND_TYPE];
}			t_bunny_sound_manager;

# ifndef		__SRC_SOUND_MANAGER_GLOBAL_CPP__
/*!
** The global sound manager. It is pretty useful to allow
** to generate and store sounds everywhere without having
** to have the sound manager to follow.
*/
extern t_bunny_sound_manager gl_bunny_sound_manager;
# endif

/*!
** Add a sound inside the sound manager associated to a category.
** Its volume and pitch will be modified accordingly to general and category
** volume and pitch, associated to its proper one.
** \param sm The sound manager.
** \param snd The sound to insert
** \param typ The category in which the sound will be added, it cannot be general.
** \return True if the sound was inserted or was already inserted in the
** matching category. False on error.
*/
bool			_bunny_sound_manager_add(t_bunny_sound_manager		*sm,
						 t_bunny_sound			*snd,
						 t_bunny_sound_type		typ);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Add a sound inside the sound manager associated to a category.
** Its volume and pitch will be modified accordingly to general and category
** volume and pitch, associated to its proper one.
** \param sm The sound manager.
** \param snd The sound to insert
** \param typ The category in which the sound will be added, it cannot be general.
** \return True if the sound was inserted or was already inserted in the
** matching category. False on error.
*/
#  define		bunny_sound_manager_add(sm, snd, typ)			\
  _bunny_sound_manager_add							\
  (sm, _Generic((snd),								\
		t_bunny_music*: (t_bunny_sound*)(snd),				\
		t_bunny_effect*: (t_bunny_sound*)(snd),				\
		t_bunny_sound*: (snd)						\
		), typ)
# else
#  define		bunny_sound_manager_add(sm, snd, typ)			\
  _bunny_sound_manager_add(sm, snd, typ)
# endif

/*!
** Remove a sound from the sound manager.
** \param sm The sound manager
** \param snd The sound to remove
*/
void			_bunny_sound_manager_remove(t_bunny_sound_manager	*sm,
						    t_bunny_sound		*snd);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Remove a sound from the sound manager.
** \param sm The sound manager
** \param snd The sound to remove
*/
#  define		bunny_sound_manager_remove(sm, snd)			\
  _bunny_sound_manager_remove							\
  (sm, _Generic((snd),								\
		t_bunny_music*: (t_bunny_sound*)(snd),				\
		t_bunny_effect*: (t_bunny_sound*)(snd),				\
		t_bunny_sound*: (snd)						\
		))
# else
#  define		bunny_sound_manager_remove(sm, snd)			\
  _bunny_sound_manager_remove(sm, snd)
# endif

/*!
** Play a music on the sent track. Stop the previous music if any on the track.
** If the music that was playing is the same as the sent one, does nothing.
** If ALL is sent as track, all tracks are stopped and the music is played on
** track 1.
** \param sm The sound manager
** \param snd The music to play
** \param n The track on which to play the music
** \return True if the music is played or was already playing, else false.
*/
bool			bunny_sound_manager_play_music(t_bunny_sound_manager	*sm,
						       t_bunny_music		*snd,
						       t_bunny_music_track	n);

/*!
** Stop the music that was playing on the sent track.
** If ALL is sent as track, stop all tracks.
** \param sm The sound manager
** \param n The track to stop.
*/
void			bunny_sound_manager_stop_music(t_bunny_sound_manager	*sm,
						       t_bunny_music_track	n);

/*!
** Play the sent sound.
** \param sm The sound manager
** \param The sound to play
** \return True if the sound was played, else false.
*/
bool			bunny_sound_manager_play_sound(t_bunny_sound_manager	*sm,
						       t_bunny_effect		*snd);

/*!
** Stop the send sound.
** \param The sound manager
** \param snd The sound to stop
*/
void			bunny_sound_manager_stop_sound(t_bunny_sound_manager	*sm,
						       t_bunny_effect		*snd);

/*!
** Set the general volume or a category volume.
** \param sm The sound manager
** \param typ The category.
** \param vol The volume to set to the category.
*/
void			bunny_sound_manager_volume(t_bunny_sound_manager	*sm,
						   t_bunny_sound_type		typ,
						   double			vol);

/*!
** Set the general pitch or a category pitch.
** \param sm The sound manager
** \param typ The category.
** \param pit The pitch to set to the category.
*/
void			bunny_sound_manager_pitch(t_bunny_sound_manager		*sm,
						  t_bunny_sound_type		typ,
						  double			pit);

/*!
** Set the proper volume of the sent sound.
** \param sm The sound manager
** \param snd The sound
** \param vol The proper volume of the sent sound
** \return True if the sound was found and set, else false.
*/
bool			_bunny_managed_sound_volume(t_bunny_sound_manager	*sm,
						    t_bunny_sound		*snd,
						    double			vol);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Set the proper volume of the sent sound.
** \param sm The sound manager
** \param snd The sound
** \param vol The proper volume of the sent sound
** \return True if the sound was found and set, else false.
*/
#  define		bunny_managed_sound_volume(sm, snd, vol)		\
  _bunny_managed_sound_volume							\
  (sm, _Generic((snd),								\
		t_bunny_music*: (t_bunny_sound*)(snd),				\
		t_bunny_effect*: (t_bunny_sound*)(snd),				\
		t_bunny_sound*: (snd)						\
		), vol)
# else
#  define		bunny_managed_sound_volume(sm, snd, vol)		\
  _bunny_managed_sound_volume(sm, snd, vol)
# endif

/*!
** Set the proper pitch of the sent sound.
** \param sm The sound manager
** \param snd The sound
** \param pit The proper pitch of the sent sound
** \return True if the sound was found and set, else false.
*/
bool			_bunny_managed_sound_pitch(t_bunny_sound_manager	*sm,
						   t_bunny_sound		*snd,
						   double			pit);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Set the proper pitch of the sent sound.
** \param sm The sound manager
** \param snd The sound
** \param pit The proper pitch of the sent sound
** \return True if the sound was found and set, else false.
*/
#  define		bunny_managed_sound_pitch(sm, snd, pit)			\
  _bunny_managed_sound_pitch							\
  (sm, _Generic((snd),								\
		t_bunny_music*: (t_bunny_sound*)(snd),				\
		t_bunny_effect*: (t_bunny_sound*)(snd),				\
		t_bunny_sound*: (snd)						\
		), pit)
# else
#  define		bunny_managed_sound_pitch(sm, snd, pit)			\
  _bunny_managed_sound_pitch(sm, snd, pit)
# endif

#endif	/*		__LAPIN_SOUND_MANAGER_H__				*/
