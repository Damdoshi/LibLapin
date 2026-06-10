// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

#define				PATTERN		"%s file, %d ciphering algorithm, %p key -> %s"

/**
 * @doc
 * @doc-symbol bunny_uncipher_file
 * @doc-kind function
 * @doc-module security
 * @doc-order 320
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Unciphers a file in place.
 * @description The function loads the whole file, applies bunny_uncipher_data to its content, saves it back and releases the temporary buffer.
 * @param file The path of the file to uncipher.
 * @param ciphering The ciphering algorithm to use.
 * @param key The key used by the algorithm. Some algorithms ignore it.
 * @return-success true if the file was loaded, unciphered and saved.
 * @return-failure false if the file cannot be loaded or saved.
 * @error errno An error reported by file loading or saving was propagated.
 * @log This function writes log entries in the "security" log domain.
 * @see bunny_cipher_file, bunny_cipher_data, bunny_uncipher_data
 *
 * @doc-lang fr
 * @brief Déchiffre un fichier sur place.
 * @description La fonction charge tout le fichier, applique bunny_uncipher_data à son contenu, le sauvegarde à nouveau et libère le tampon temporaire.
 * @param file Le chemin du fichier à déchiffrer.
 * @param ciphering L'algorithme de chiffrement à utiliser.
 * @param key La clé utilisée par l'algorithme. Certains algorithmes l'ignorent.
 * @return-success true si le fichier a été chargé, déchiffré et sauvegardé.
 * @return-failure false si le fichier ne peut pas être chargé ou sauvegardé.
 * @error errno Une erreur signalée par le chargement ou la sauvegarde du fichier a été propagée.
 * @log Cette fonction écrit des entrées de log dans le domaine "security".
 * @see bunny_cipher_file, bunny_cipher_data, bunny_uncipher_data
 */
bool				bunny_uncipher_file(const char			*file,
						    t_bunny_ciphering		cip,
						    const t_bunny_cipher_key	*key)
{
  char				*cnt;
  size_t			len;
  bool				ret;

  if (bunny_load_file(file, (void**)&cnt, &len) == -1)
    scream_error_if(return (false), bunny_errno, PATTERN, "security", file, cip, key, "false");
  bunny_uncipher_data(cnt, len, cip, key);
  ret = bunny_save_file(file, cnt, len);
  len = bunny_errno;
  bunny_delete_file(cnt, file);
  if (ret == false)
    scream_error_if(return (false), len, PATTERN, "security", file, cip, key, "false");
  scream_log_if(PATTERN, "security", file, cip, key, "true");
  return (ret);
}

