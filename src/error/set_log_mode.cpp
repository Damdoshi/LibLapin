// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			gl_complete_log = false;


/**
 * @doc
 * @doc-symbol bunny_set_log_mode
 * @doc-kind function
 * @doc-module error
 * @doc-order 280
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Selects compact or complete log formatting.
 * @param complete true for complete logs, false for compact logs.
 * @see bunny_set_log_filter
 *
 * @doc-lang fr
 * @brief Sélectionne le formatage compact ou complet des logs.
 * @param complete true pour les logs complets, false pour les logs compacts.
 * @see bunny_set_log_filter
 */
void			bunny_set_log_mode(bool		c)
{
  gl_complete_log = c;
}

