// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_get_ciphering
 * @doc-kind function
 * @doc-module security
 * @doc-order 140
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Resolves a ciphering algorithm name.
 * @description The name is compared with gl_bunny_ciphering_table. If no built-in algorithm matches, BS_CUSTOM is returned.
 * @param name The algorithm name to read.
 * @return-success The matching built-in algorithm, or BS_CUSTOM if no built-in algorithm was found.
 * @log This function writes a log entry in the "security" log domain.
 * @see t_bunny_ciphering, gl_bunny_ciphering_table
 *
 * @doc-lang fr
 * @brief Résout un nom d'algorithme de chiffrement.
 * @description Le nom est comparé à gl_bunny_ciphering_table. Si aucun algorithme intégré ne correspond, BS_CUSTOM est renvoyé.
 * @param name Le nom d'algorithme à lire.
 * @return-success L'algorithme intégré correspondant, ou BS_CUSTOM si aucun algorithme intégré n'a été trouvé.
 * @log Cette fonction écrit une entrée de log dans le domaine "security".
 * @see t_bunny_ciphering, gl_bunny_ciphering_table
 */
t_bunny_ciphering	bunny_get_ciphering(const char		*name)
{
  size_t		i;

  for (i = 0; i < BS_CUSTOM; ++i)
    if (strcmp(name, gl_bunny_ciphering_table[i]) == 0)
      {
	scream_log_if("%s -> %zu", "security", name, i);
	return ((t_bunny_ciphering)i);
      }
  scream_log_if("%s -> %d", "security", name, BS_CUSTOM);
  return (BS_CUSTOM);
}

