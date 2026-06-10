// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%s -> %p"

/**
 * @doc-symbol bunny_read_effect_id
 * @doc-module sound
 * @doc-kind function
 * @doc-order 210
 * @doc-since 13
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Reads a sound effect from memory and assigns it an identifier.
 * @description This public entry point is currently not implemented and returns NULL.
 * @param data Memory buffer containing the encoded sound.
 * @param len Size of the memory buffer in bytes.
 * @param file Original file name or unique label.
 * @return-failure NULL because the function is not implemented yet.
 * @see bunny_load_effect
 *
 * @doc-lang fr
 * @brief Lit un effet sonore depuis la mémoire et lui associe un identifiant.
 * @description Ce point d'entrée public n'est actuellement pas implémenté et renvoie NULL.
 * @param data Tampon mémoire contenant le son encodé.
 * @param len Taille du tampon mémoire en octets.
 * @param file Nom du fichier d'origine ou libellé unique.
 * @return-failure NULL car la fonction n'est pas encore implémentée.
 * @see bunny_load_effect
 */
t_bunny_effect		*bunny_read_effect_id(const char	*data,
					      size_t		len,
					      const char	*file)
{
#warning A faire
  (void)data;
  (void)len;
  (void)file;
  return (NULL);
}
