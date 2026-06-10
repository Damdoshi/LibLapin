// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%s -> %p"

/**
 * @doc-symbol bunny_save_effect
 * @doc-module sound
 * @doc-kind function
 * @doc-order 220
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Saves a sound effect into a file.
 * @description The effect is computed before saving so manual changes in sample are taken into account.
 * @param effect Effect to save.
 * @param str Destination file path.
 * @return-success true if the effect was computed and saved.
 * @return-failure false if computing or saving fails.
 * @log May log in the "sound" domain through bunny_compute_effect.
 * @see bunny_compute_effect, bunny_load_effect
 *
 * @doc-lang fr
 * @brief Sauvegarde un effet sonore dans un fichier.
 * @description L'effet est calculé avant la sauvegarde afin que les modifications manuelles de sample soient prises en compte.
 * @param effect Effet à sauvegarder.
 * @param str Chemin du fichier de destination.
 * @return-success true si l'effet a été calculé puis sauvegardé.
 * @return-failure false si le calcul ou la sauvegarde échoue.
 * @log Peut écrire dans le domaine "sound" via bunny_compute_effect.
 * @see bunny_compute_effect, bunny_load_effect
 */
bool			bunny_save_effect(const t_bunny_effect		*_eff,
					  const char			*file)
{
  struct bunny_effect	*eff = (struct bunny_effect*)_eff;

  if (bunny_compute_effect((t_bunny_effect*)_eff) == false)
    return (false);
  return (eff->effect->saveToFile(file));
}

