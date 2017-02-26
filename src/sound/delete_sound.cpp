// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_delete_sound(t_bunny_sound		*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  BUNNY_LOG(fprintf(stderr, "%s: Returning %p.\n", __PRETTY_FUNCTION__, sound));
  free((void*)sound->file);
  if (*type == MUSIC)
    delete ((struct bunny_music*)sound);
  else
    {
      bunny_free(((struct bunny_effect*)sound)->sample);
      delete ((struct bunny_effect*)sound);
    }
}
