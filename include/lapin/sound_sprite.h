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

typedef struct		s_bunny_sound_slice
{
  t_bunny_sound		sound;
  uint64_t		id;
  double		index;
  double		duration;
  double		active_duration; // The "talk time"
}			t_bunny_sound_slice;

typedef struct		s_bunny_sound_sprite
{
  t_bunny_music		soundset;
  t_bunny_map		*sound_areas;	// hash[size_t] -> t_bunny_sound_slice
  const t_bunny_sound_slice * const last_played_slice;
  const t_bunny_music_track track;
}			t_bunny_sound_sprite;

t_bunny_sound_sprite	*bunny_load_sound_sprite(const char		*file);

bool			bunny_sound_sprite_play_slice_name(t_bunny_sound_sprite *sprite,
							   t_bunny_music_track track,
							   const char	*name);
bool			bunny_sound_sprite_play_slice_id(t_bunny_sound_sprite *sprite,
							 t_bunny_music_track track,
							 uint64_t	name);
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

# define		bunny_sound_sprite_slice_name(name)		\
  bunny_hash(BH_DJB2, name, strlen(name))

#endif	/*		__LAPIN_SOUND_SPRITE_H__			*/
