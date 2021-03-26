// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_sound_play(t_bunny_sound		*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  bunny_sound_volume(sound, sound->volume);
  bunny_sound_pitch(sound, sound->pitch);
  bunny_sound_loop(sound, sound->loop);
  bunny_sound_position
    (sound, sound->position[0], sound->position[1], sound->position[2]);
  bunny_sound_attenuation(sound, sound->attenuation);

  if (sound->pause)
    *((bool*)&sound->pause) = false;
  else
    *((bool*)&sound->playing) = true;

  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.play();
  else
    ((struct bunny_effect*)sound)->sound->play();
  scream_log_if("%p", "ressource,sound", sound);
}

