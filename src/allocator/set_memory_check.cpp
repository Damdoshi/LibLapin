// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// LibLapin

#include		"lapin_private.h"

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
# undef			bunny_malloc
# undef			bunny_calloc
# undef			bunny_realloc
# undef			bunny_free
#endif

extern int		memory_check;

/**
 * @doc
 * @doc-symbol bunny_set_memory_check
 * @doc-kind function
 * @doc-module allocator
 * @doc-order 180
 * @doc-since 10
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Enables or disables the final Bunny allocator memory check.
 * @description This function asks the Bunny allocator to perform a memory checkup at the end of the program. The report includes the number of allocation calls, the amount of requested memory, the number of remaining chunks and the number of remaining bytes.
 * @description The check also verifies allocator guard areas. If invalid writes occurred during execution, the program reports altered chunks and deliberately fails.
 * @param check Send true to enable the memory check, false to disable it.
 * @see bunny_malloc, bunny_calloc, bunny_realloc, bunny_free
 *
 * @doc-lang fr
 * @brief Active ou désactive la vérification finale de mémoire de l'allocateur Bunny.
 * @description Cette fonction demande à l'allocateur Bunny d'effectuer un bilan mémoire à la fin du programme. Le rapport inclut le nombre d'appels d'allocation, la quantité de mémoire demandée, le nombre de blocs restants et le nombre d'octets restants.
 * @description La vérification contrôle aussi les zones de garde de l'allocateur. Si des écritures invalides ont eu lieu pendant l'exécution, le programme signale les blocs altérés et échoue volontairement.
 * @param check Envoyez true pour activer la vérification mémoire, false pour la désactiver.
 * @see bunny_malloc, bunny_calloc, bunny_realloc, bunny_free
 */
void			bunny_set_memory_check(bool		chk)
{
  memory_check = chk;
}

