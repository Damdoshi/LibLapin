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
/**
 * @doc-symbol t_bunny_music_track
 * @doc-module sound_manager
 * @doc-kind type
 * @doc-order 100
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Enumerates independent music tracks handled by a sound manager.
 * @param BST_ALL Special value used to target every track.
 * @param BST_TRACK_01 First music track, often used for main music.
 * @param BST_TRACK_02 Second music track, often used for ambience.
 * @param BST_TRACK_03 Third music track, often used for voices.
 * @param BST_TRACK_04 Fourth music track.
 * @param BST_LAST_TRACK Number of available tracks.
 * @see bunny_sound_manager_play_music, bunny_sound_manager_stop_music
 *
 * @doc-lang fr
 * @brief Énumère les pistes musicales indépendantes gérées par un gestionnaire de sons.
 * @param BST_ALL Valeur spéciale utilisée pour viser toutes les pistes.
 * @param BST_TRACK_01 Première piste musicale, souvent utilisée pour la musique principale.
 * @param BST_TRACK_02 Deuxième piste musicale, souvent utilisée pour l'ambiance.
 * @param BST_TRACK_03 Troisième piste musicale, souvent utilisée pour les voix.
 * @param BST_TRACK_04 Quatrième piste musicale.
 * @param BST_LAST_TRACK Nombre de pistes disponibles.
 * @see bunny_sound_manager_play_music, bunny_sound_manager_stop_music
 */
typedef enum		e_bunny_music_track
  {
    BST_ALL		= -1,
    BST_TRACK_01,	// FOR EXAMPLE: MUSIC
    BST_TRACK_02,	// FOR EXAMPLE: MOOD (Waterfall, wind, etc.)
    BST_TRACK_03,	// FOR EXAMPLE: VOICES
    BST_TRACK_04,
    BST_LAST_TRACK
  }			t_bunny_music_track;

/*!
** Indicates a sound type: music, effect or voice.
** Each sound type have a matching volume and pitch.
*/
/**
 * @doc-symbol t_bunny_sound_type
 * @doc-module sound_manager
 * @doc-kind type
 * @doc-order 120
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Enumerates categories used to apply common volume and pitch settings.
 * @param BST_GENERAL Special category used to edit the global volume or pitch.
 * @param BST_MUSIC Music category.
 * @param BST_EFFECT Sound effect category.
 * @param BST_VOICE Voice category.
 * @param BST_LAST_SOUND_TYPE Number of sound categories.
 * @see bunny_sound_manager_add, bunny_sound_manager_volume, bunny_sound_manager_pitch
 *
 * @doc-lang fr
 * @brief Énumère les catégories utilisées pour appliquer des réglages communs de volume et de hauteur.
 * @param BST_GENERAL Catégorie spéciale utilisée pour modifier le volume ou la hauteur globale.
 * @param BST_MUSIC Catégorie des musiques.
 * @param BST_EFFECT Catégorie des effets sonores.
 * @param BST_VOICE Catégorie des voix.
 * @param BST_LAST_SOUND_TYPE Nombre de catégories sonores.
 * @see bunny_sound_manager_add, bunny_sound_manager_volume, bunny_sound_manager_pitch
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
/**
 * @doc-symbol t_bunny_sound_manager
 * @doc-module sound_manager
 * @doc-kind type
 * @doc-order 140
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Centralized sound controller for volumes, pitches and music tracks.
 * @description It groups sounds into categories so a game can expose global, music, effect and voice controls.
 * @param current_music Music currently playing on each track.
 * @param general_volume Global volume applied to managed sounds.
 * @param volumes Per-category volume multipliers.
 * @param general_pitch Global pitch multiplier applied to managed sounds.
 * @param pitches Per-category pitch multipliers.
 * @see gl_bunny_sound_manager, bunny_sound_manager_add
 *
 * @doc-lang fr
 * @brief Contrôleur sonore centralisé pour les volumes, les hauteurs et les pistes musicales.
 * @description Il regroupe les sons par catégories afin qu'un jeu puisse exposer des contrôles globaux, musique, effets et voix.
 * @param current_music Musique actuellement jouée sur chaque piste.
 * @param general_volume Volume global appliqué aux sons gérés.
 * @param volumes Multiplicateurs de volume par catégorie.
 * @param general_pitch Multiplicateur global de hauteur appliqué aux sons gérés.
 * @param pitches Multiplicateurs de hauteur par catégorie.
 * @see gl_bunny_sound_manager, bunny_sound_manager_add
 */
typedef struct		s_bunny_sound_manager
{
  const t_bunny_sound * const current_music[BST_LAST_TRACK];
  const double		general_volume;
  const double		volumes[BST_LAST_SOUND_TYPE];
  const double		general_pitch;
  const double		pitches[BST_LAST_SOUND_TYPE];
}			t_bunny_sound_manager;

/*
** This define here is only present for inside needs.
** The symbol inside will always be available.
*/
# ifndef		__SRC_SOUND_MANAGER_GLOBAL_CPP__
/*!
** The global sound manager. It is pretty useful to allow
** to generate and store sounds everywhere without having
** to have the sound manager to follow.
*/
/**
 * @doc-symbol gl_bunny_sound_manager
 * @doc-module sound_manager
 * @doc-kind variable
 * @doc-order 160
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Global sound manager provided by LibLapin.
 * @description It avoids carrying a manager pointer everywhere. You can still create your own manager if needed.
 * @see t_bunny_sound_manager, bunny_sound_manager_add
 *
 * @doc-lang fr
 * @brief Gestionnaire de sons global fourni par la LibLapin.
 * @description Il évite de transporter un pointeur de gestionnaire partout. Vous pouvez tout de même créer votre propre gestionnaire si nécessaire.
 * @see t_bunny_sound_manager, bunny_sound_manager_add
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

/**
 * @doc-symbol bunny_sound_manager_add
 * @doc-module sound_manager
 * @doc-kind macro
 * @doc-order 180
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Adds a sound to a manager and associates it with a category.
 * @description Managed sounds should use bunny_managed_sound_volume and bunny_managed_sound_pitch instead of direct sound setters.
 * @param sm Sound manager that will contain the association.
 * @param snd Sound, music, sound sprite or effect to add.
 * @param typ Category in which the sound is inserted; it cannot be BST_GENERAL.
 * @return-success true if the sound was inserted or was already in the same category.
 * @return-failure false if the category is invalid or the sound is already in another category.
 * @see bunny_sound_manager_remove, bunny_managed_sound_volume, bunny_managed_sound_pitch
 *
 * @doc-lang fr
 * @brief Ajoute un son à un gestionnaire et l'associe à une catégorie.
 * @description Les sons gérés devraient utiliser bunny_managed_sound_volume et bunny_managed_sound_pitch au lieu des modificateurs directs.
 * @param sm Gestionnaire de sons qui contiendra l'association.
 * @param snd Son, musique, sound sprite ou effet à ajouter.
 * @param typ Catégorie dans laquelle le son est inséré ; elle ne peut pas être BST_GENERAL.
 * @return-success true si le son a été inséré ou était déjà dans la même catégorie.
 * @return-failure false si la catégorie est invalide ou si le son est déjà dans une autre catégorie.
 * @see bunny_sound_manager_remove, bunny_managed_sound_volume, bunny_managed_sound_pitch
 */
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
		t_bunny_sound_sprite*: (t_bunny_sound*)(snd),			\
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

/**
 * @doc-symbol bunny_sound_manager_remove
 * @doc-module sound_manager
 * @doc-kind macro
 * @doc-order 200
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Removes a sound from a sound manager.
 * @param sm Sound manager from which the sound is removed.
 * @param snd Sound, music, sound sprite or effect to remove.
 * @see bunny_sound_manager_add, bunny_delete_sound
 *
 * @doc-lang fr
 * @brief Retire un son d'un gestionnaire de sons.
 * @param sm Gestionnaire de sons duquel le son est retiré.
 * @param snd Son, musique, sound sprite ou effet à retirer.
 * @see bunny_sound_manager_add, bunny_delete_sound
 */
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
		t_bunny_sound_sprite*: (t_bunny_sound*)(snd),			\
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

/**
 * @doc-symbol bunny_managed_sound_volume
 * @doc-module sound_manager
 * @doc-kind macro
 * @doc-order 340
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Sets the proper volume of a managed sound.
 * @description The effective volume combines this value, the global manager volume and the category volume.
 * @param sm Sound manager containing the sound.
 * @param snd Managed sound to update.
 * @param vol Proper volume to set before manager multipliers are applied.
 * @return-success true if the sound was found and updated.
 * @return-failure false if the sound is not managed by sm.
 * @see bunny_managed_sound_pitch, bunny_sound_manager_volume
 *
 * @doc-lang fr
 * @brief Définit le volume propre d'un son géré.
 * @description Le volume effectif combine cette valeur, le volume global du gestionnaire et le volume de la catégorie.
 * @param sm Gestionnaire de sons contenant le son.
 * @param snd Son géré à modifier.
 * @param vol Volume propre à fixer avant l'application des multiplicateurs du gestionnaire.
 * @return-success true si le son a été trouvé et modifié.
 * @return-failure false si le son n'est pas géré par sm.
 * @see bunny_managed_sound_pitch, bunny_sound_manager_volume
 */
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
		t_bunny_sound_sprite*: (t_bunny_sound*)(snd),			\
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

/**
 * @doc-symbol bunny_managed_sound_pitch
 * @doc-module sound_manager
 * @doc-kind macro
 * @doc-order 360
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Sets the proper pitch of a managed sound.
 * @description The effective pitch combines this value, the global manager pitch and the category pitch.
 * @param sm Sound manager containing the sound.
 * @param snd Managed sound to update.
 * @param pit Proper pitch to set before manager multipliers are applied.
 * @return-success true if the sound was found and updated.
 * @return-failure false if the sound is not managed by sm.
 * @see bunny_managed_sound_volume, bunny_sound_manager_pitch
 *
 * @doc-lang fr
 * @brief Définit la hauteur propre d'un son géré.
 * @description La hauteur effective combine cette valeur, la hauteur globale du gestionnaire et la hauteur de la catégorie.
 * @param sm Gestionnaire de sons contenant le son.
 * @param snd Son géré à modifier.
 * @param pit Hauteur propre à fixer avant l'application des multiplicateurs du gestionnaire.
 * @return-success true si le son a été trouvé et modifié.
 * @return-failure false si le son n'est pas géré par sm.
 * @see bunny_managed_sound_volume, bunny_sound_manager_pitch
 */
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
