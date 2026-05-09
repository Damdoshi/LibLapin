// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

bool		gl_bunny_sound_sprite_trap = true;


/**
 * @doc
 * @doc-symbol bunny_sound_sprite_trap_or_sync
 * @doc-kind function
 * @doc-module sound_sprite
 * @doc-order 170
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Selects whether slice playback traps the current track or synchronizes with it.
 * @param trap true to trap, false to synchronize.
 * @see bunny_sound_sprite_play_slice
 *
 * @doc-lang fr
 * @brief Sélectionne si la lecture d’une tranche piège la piste courante ou se synchronise avec elle.
 * @param trap true pour piéger, false pour synchroniser.
 * @see bunny_sound_sprite_play_slice
 */
void		bunny_sound_sprite_trap_or_sync(bool		trap)
{
  gl_bunny_sound_sprite_trap = trap;
}

