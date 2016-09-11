// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

double			bunny_music_get_cursor(t_bunny_music		*music)
{
  struct bunny_music	*mus = (struct bunny_music*)music;

  return (mus->music.getPlayingOffset().asSeconds());
}
