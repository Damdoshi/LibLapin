// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include			"lapin_private.h"

/**
 * @doc-symbol bunny_compute_effect
 * @doc-module sound
 * @doc-kind function
 * @doc-order 240
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Generates the backend sound buffer from the current sample array.
 * @param effect Effect whose samples must be submitted.
 * @return-success true if the sound buffer was generated.
 * @return-failure false if generation failed.
 * @error ENOMEM Out of memory.
 * @log May log in the "sound" domain.
 * @see t_bunny_effect, bunny_new_effect, bunny_sound_play
 *
 * @doc-lang fr
 * @brief Génère le tampon sonore backend depuis le tableau sample courant.
 * @param effect Effet dont les échantillons doivent être soumis.
 * @return-success true si le tampon sonore a été généré.
 * @return-failure false si la génération a échoué.
 * @error ENOMEM Mémoire insuffisante.
 * @log Peut écrire dans le domaine "sound".
 * @see t_bunny_effect, bunny_new_effect, bunny_sound_play
 */
bool				bunny_compute_effect(t_bunny_effect		*effect)
{
  struct bunny_effect		*eff = (struct bunny_effect*)effect;
  bool				ret;

  ret = (eff->effect->loadFromSamples
	 (eff->sample,
	  eff->duration * eff->sample_per_second,
	  1,
	  eff->sample_per_second,
	  gl_channels[1]));
  if (ret == false)
    scream_error_if(return (false), bunny_errno, "%p -> %s", "sound", effect, "false");
  scream_log_if("%p -> %s", "sound", effect, "true");
  return (true);
}

