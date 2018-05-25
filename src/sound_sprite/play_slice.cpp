// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include	"lapin_private.h"

#define		PATTERN		"%p sprite, %d track, %lu id -> %s"

extern bool	gl_bunny_sound_sprite_trap;

static void	bunny_end_sound(t_bunny_sound_sprite			*sprite)
{
  if (sprite->soundset.sound.loop)
    bunny_sound_sprite_play_slice_id
      (sprite, sprite->track, sprite->last_played_slice->id);
  else
    {
      bunny_sound_stop(&sprite->soundset.sound);
      *(t_bunny_sound_slice**)&sprite->last_played_slice = NULL;
      *(t_bunny_music_track*)&sprite->track = BST_LAST_TRACK;
    }
}

static void	bunny_end_sound_async(void				*_sprite,
				      void				*data)
{
  t_bunny_sound_sprite *sprite = (t_bunny_sound_sprite*)_sprite;

  (void)data;
  bunny_usleep
    (sprite->last_played_slice->duration * 1e6
     / sprite->last_played_slice->sound.pitch);
  bunny_end_sound(sprite);
}

static void	bunny_end_sound_trap(double				elapsed,
				     t_bunny_trap			*trap,
				     void				*data)
{
  (void)elapsed;
  bunny_delete_trap(trap);
  bunny_end_sound((t_bunny_sound_sprite*)data);
}

bool		bunny_sound_sprite_play_slice_id(t_bunny_sound_sprite	*sprite,
						 t_bunny_music_track	track,
						 uint64_t		id)
{
  t_bunny_sound_slice *_slice;
  struct bunny_music *slice_sound;
  struct bunny_music *sprite_sound;
  size_t	i;

  _slice = bunny_map_get_data(sprite->sound_areas, id, t_bunny_sound_slice*);
  if (_slice == NULL)
    scream_error_if
      (return (false), BE_CANNOT_FIND_ELEMENT,
       PATTERN ": Slice %lu not found",
       "sound_sprite", sprite, track, (uint64_t)id, "false", id);
  slice_sound = (struct bunny_music*)&_slice->sound;
  sprite_sound = (struct bunny_music*)&sprite->soundset;

  bunny_sound_set_cursor(&sprite->soundset.sound, _slice->index);
  if (sprite_sound->sound_manager)
    {
      bunny_managed_sound_volume
	((t_bunny_sound_manager*)sprite_sound->sound_manager,
	 &sprite->soundset.sound, slice_sound->volume);
      bunny_managed_sound_pitch
	((t_bunny_sound_manager*)sprite_sound->sound_manager,
	 &sprite->soundset.sound, slice_sound->pitch);
      bunny_sound_manager_play_music
	((t_bunny_sound_manager*)sprite_sound->sound_manager,
	 &sprite->soundset, track);
    }
  else
    {
      sprite_sound->volume = slice_sound->volume;
      sprite_sound->pitch = slice_sound->pitch;
      bunny_sound_play(&sprite->soundset.sound);
      track = BST_LAST_TRACK;
    }

   sprite_sound->loop = slice_sound->loop;
  for (i = 0; i < NBRCELL(sprite_sound->position); ++i)
    sprite_sound->position[i] = slice_sound->position[i];
  sprite_sound->attenuation = slice_sound->attenuation;

  *((t_bunny_sound_slice**)&sprite->last_played_slice) = _slice;
  *(t_bunny_music_track*)&sprite->track = track;

  if (gl_bunny_loop_threadpool == NULL || gl_bunny_sound_sprite_trap)
    {
      if (bunny_new_trap
	  (bunny_end_sound_trap, BCO_BEFORE_LOOP_MAIN_FUNCTION,
	   bunny_get_current_time() +
	   _slice->duration / slice_sound->pitch,
	   0, sprite) == NULL)
	scream_error_if
	  (return (false), bunny_errno,
	   PATTERN ": Cannot create trap.",
	   "sound_sprite", sprite, track, (uint64_t)id, "false");
    }
  else
    {
      if (bunny_async_computation_push(bunny_end_sound_async, sprite) == false)
	scream_error_if
	  (return (false), bunny_errno,
	   PATTERN ": Cannot create asynchronous computation.",
	   "sound_sprite", sprite, track, (uint64_t)id, "false");
    }

  scream_log_if(PATTERN, "sound_sprite", sprite, track, (uint64_t)id, "true");
  return (true);
}

#undef		PATTERN
#define		PATTERN		"%p sprite, %d track, %s name -> %s"

bool		bunny_sound_sprite_play_slice_name(t_bunny_sound_sprite	*sprite,
						   t_bunny_music_track	track,
						   const char		*name)
{
  if (bunny_sound_sprite_play_slice_id
      (sprite, track, bunny_sound_sprite_slice_name(name)) == false)
    scream_error_if
      (return (false), BE_CANNOT_FIND_ELEMENT,
       PATTERN ": Slice '%s' cannot be played.",
       "sound_sprite,syntax", sprite, track, name, "false", name);
  scream_log_if(PATTERN, "sound_sprite", sprite, track, name, "true");
  return (true);
}

