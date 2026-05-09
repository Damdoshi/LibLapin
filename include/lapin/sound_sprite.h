/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_SOUND_SPRITE_H__
# define		__LAPIN_SOUND_SPRITE_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif


/**
 * @doc
 * @doc-symbol sound_sprite
 * @doc-kind module
 * @doc-module sound_sprite
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Loads and plays named or hashed slices from a single sound resource.
 * @header lapin/sound_sprite.h
 *
 * @doc-lang fr
 * @brief Charge et joue des tranches nommées ou hashées depuis une ressource sonore unique.
 * @header lapin/sound_sprite.h
 */



/**
 * @doc
 * @doc-symbol t_bunny_sound_slice
 * @doc-kind struct
 * @doc-module sound_sprite
 * @doc-order 110
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Describes one playable slice inside a sound sprite.
 * @field sound Playback settings applied to the slice.
 * @field id Numeric identifier, usually generated from the slice name.
 * @field index Start time of the slice in the source sound.
 * @field duration Duration of the slice.
 * @field active_start Start of the active/talking part inside the slice.
 * @field active_duration Duration of the active/talking part.
 * @see t_bunny_sound_sprite, bunny_sound_sprite_play_slice_id
 *
 * @doc-lang fr
 * @brief Décrit une tranche jouable dans un sound sprite.
 * @field sound Réglages de lecture appliqués à la tranche.
 * @field id Identifiant numérique, généralement généré depuis le nom de la tranche.
 * @field index Temps de départ de la tranche dans le son source.
 * @field duration Durée de la tranche.
 * @field active_start Début de la partie active/parlée dans la tranche.
 * @field active_duration Durée de la partie active/parlée.
 * @see t_bunny_sound_sprite, bunny_sound_sprite_play_slice_id
 */
typedef struct		s_bunny_sound_slice
{
  t_bunny_sound		sound;
  uint64_t		id;
  double		index;
  double		duration;
  double		active_start; // The "talk time", start point
  double		active_duration; // The "talk time", duration
}			t_bunny_sound_slice;

# ifdef			__MINGW32__
#  pragma		pack(4)
# endif


/**
 * @doc
 * @doc-symbol t_bunny_sound_sprite
 * @doc-kind struct
 * @doc-module sound_sprite
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Combines a sound resource with a map of playable slices.
 * @description t_bunny_sound_sprite starts with a t_bunny_music so it can be destroyed with bunny_delete_sound.
 * @field soundset Underlying music resource.
 * @field sound_areas Map from slice id to t_bunny_sound_slice.
 * @field last_played_slice Last slice started by the sprite API.
 * @field track Last track used by the sprite API.
 * @see bunny_load_sound_sprite, bunny_sound_sprite_play_slice
 *
 * @doc-lang fr
 * @brief Associe une ressource sonore à une map de tranches jouables.
 * @description t_bunny_sound_sprite commence par un t_bunny_music, ce qui permet de le détruire avec bunny_delete_sound.
 * @field soundset Ressource musicale sous-jacente.
 * @field sound_areas Map associant un id de tranche à t_bunny_sound_slice.
 * @field last_played_slice Dernière tranche lancée par l'API sprite.
 * @field track Dernière piste utilisée par l'API sprite.
 * @see bunny_load_sound_sprite, bunny_sound_sprite_play_slice
 */
typedef struct		s_bunny_sound_sprite
{
  t_bunny_music		soundset;
  t_bunny_map		*sound_areas;	// hash[size_t] -> t_bunny_sound_slice
  const t_bunny_sound_slice * const last_played_slice;
  const t_bunny_music_track track;
}			t_bunny_sound_sprite;
# pragma		pack()

t_bunny_sound_sprite	*bunny_load_sound_sprite(const char		*file);
t_bunny_sound_sprite	*bunny_read_sound_sprite(t_bunny_configuration	*cnf);
t_bunny_configuration	*bunny_write_sound_sprite(t_bunny_sound_sprite	*sprite);
t_bunny_configuration	*bunny_save_sound_sprite(t_bunny_configuration	*sprite,
						 const char		*file);

bool			bunny_sound_sprite_play_slice_name(t_bunny_sound_sprite *sprite,
							   t_bunny_music_track track,
							   const char	*name);
bool			bunny_sound_sprite_play_slice_id(t_bunny_sound_sprite *sprite,
							 t_bunny_music_track track,
							 uint64_t	name);


/**
 * @doc
 * @doc-symbol bunny_sound_sprite_play_slice
 * @doc-kind macro
 * @doc-module sound_sprite
 * @doc-order 130
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Plays a slice selected either by name or by numeric id.
 * @description This C11 generic macro dispatches to bunny_sound_sprite_play_slice_name for strings and to bunny_sound_sprite_play_slice_id for integer identifiers.
 * @param spr Sound sprite.
 * @param track Music track to use.
 * @param anim Slice name or slice id.
 * @return-success Returns true if the slice is found and playback starts.
 * @return-failure Returns false on error.
 * @see bunny_sound_sprite_play_slice_name, bunny_sound_sprite_play_slice_id
 *
 * @doc-lang fr
 * @brief Joue une tranche sélectionnée par nom ou par id numérique.
 * @description Cette macro générique C11 redirige vers bunny_sound_sprite_play_slice_name pour les chaînes et vers bunny_sound_sprite_play_slice_id pour les identifiants entiers.
 * @param spr Sound sprite.
 * @param track Piste musicale à utiliser.
 * @param anim Nom ou id de tranche.
 * @return-success Renvoie true si la tranche est trouvée et que la lecture démarre.
 * @return-failure Renvoie false en cas d'erreur.
 * @see bunny_sound_sprite_play_slice_name, bunny_sound_sprite_play_slice_id
 */
#  define		bunny_sound_sprite_play_slice(spr, track, anim)	\
  _Generic((anim),							\
	   const char*: bunny_sound_sprite_play_slice_name,		\
	   char*: bunny_sound_sprite_play_slice_name,			\
	   uint64_t: bunny_sound_sprite_play_slice_id,			\
	   int: bunny_sound_sprite_play_slice_id			\
	   )(spr, track, anim)

void			bunny_sound_sprite_trap_or_sync(bool		trap);
bool			bunny_sound_sprite_is_talking(t_bunny_sound_sprite *sprite);

bool			bunny_sound_sprite_stop_slice(t_bunny_sound_sprite *sprite);



/**
 * @doc
 * @doc-symbol bunny_sound_sprite_slice_name
 * @doc-kind macro
 * @doc-module sound_sprite
 * @doc-order 190
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Converts a slice name to the numeric id used by sound sprites.
 * @param name Slice name.
 * @return-success Returns the DJB2 hash used as slice id.
 * @see bunny_sound_sprite_play_slice_id
 *
 * @doc-lang fr
 * @brief Convertit un nom de tranche vers l'id numérique utilisé par les sound sprites.
 * @param name Nom de tranche.
 * @return-success Renvoie le hash DJB2 utilisé comme id de tranche.
 * @see bunny_sound_sprite_play_slice_id
 */
# define		bunny_sound_sprite_slice_name(name)		\
  bunny_hash(BH_DJB2, name, strlen(name))

// No delete. Use bunny_delete_sound

#endif	/*		__LAPIN_SOUND_SPRITE_H__			*/
