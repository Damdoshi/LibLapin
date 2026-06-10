// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_sound_position
 * @doc-module sound
 * @doc-kind function
 * @doc-order 320
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Sets the relative 3D position of a sound.
 * @param sound Sound to modify.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param z Front/back position.
 * @log May log in the "sound" domain.
 * @see bunny_sound_attenuation
 *
 * @doc-lang fr
 * @brief Définit la position 3D relative d'un son.
 * @param sound Son à modifier.
 * @param x Position horizontale.
 * @param y Position verticale.
 * @param z Position avant/arrière.
 * @log Peut écrire dans le domaine "sound".
 * @see bunny_sound_attenuation
 */
void			bunny_sound_position(t_bunny_sound		*sound,
					     double			x,
					     double			y,
					     double			z)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  sound->position[0] = x;
  sound->position[1] = y;
  sound->position[2] = z;

  if (*type == MUSIC)
    ((struct bunny_music*)sound)->music.setPosition({x, y, z});
  else
    ((struct bunny_effect*)sound)->sound->setPosition({x, y, z});
  scream_log_if("%p sound, %f x, %f y, %f z", "sound", sound, x, y, z);
}

