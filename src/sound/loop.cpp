// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_loop
 * @doc-module sound
 * @doc-kind function
 * @doc-order 300
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Enables or disables looping.
 * @param sound Sound to modify.
 * @param loop true to loop, false to play once.
 * @log May log in the "ressource" and "sound" domains.
 * @see bunny_sound_play, bunny_sound_stop
 *
 * @doc-lang fr
 * @brief Active ou désactive la boucle.
 * @param sound Son à modifier.
 * @param loop true pour boucler, false pour jouer une seule fois.
 * @log Peut écrire dans les domaines "ressource" et "sound".
 * @see bunny_sound_play, bunny_sound_stop
 */
void			bunny_sound_loop(t_bunny_sound		*sound,
					 bool			lop)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  sound->loop = lop;
  scream_log_if("%p sound, %s loop", "ressource,sound", sound, lop ? "true" : "false");
  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.setLooping(lop);
  else
    ((struct bunny_effect*)sound)->sound->setLooping(lop);
}
