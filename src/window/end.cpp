// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Lapin library

#include	"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_end
 * @doc-kind function
 * @doc-module window
 * @doc-order 430
 * @doc-since 13
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Stops every window in a NULL-terminated window array.
 * @description This helper stops every window stored in the array, then releases the array itself. It is designed to release arrays returned by bunny_begin, bunny_beginc, bunny_begin_configuration and bunny_all_fullscreen.
 * @param windows The NULL-terminated array of windows to stop and release.
 * @see bunny_begin, bunny_beginc, bunny_begin_configuration, bunny_all_fullscreen, bunny_stop
 *
 * @doc-lang fr
 * @brief Ferme toutes les fenêtres d'un tableau terminé par NULL.
 * @description Cet utilitaire ferme chaque fenêtre stockée dans le tableau, puis libère le tableau lui-même. Il est prévu pour libérer les tableaux renvoyés par bunny_begin, bunny_beginc, bunny_begin_configuration et bunny_all_fullscreen.
 * @param windows Le tableau de fenêtres terminé par NULL à fermer et libérer.
 * @see bunny_begin, bunny_beginc, bunny_begin_configuration, bunny_all_fullscreen, bunny_stop
 */
void		bunny_end(t_bunny_window		**w)
{
  for (size_t i = 0; w[i]; ++i)
    bunny_stop(w[i]);
  bunny_free(w);
}

