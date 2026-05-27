// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"PVM110N.hpp"
#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_delete_vm110n
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 140
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Destroys a VM110N handler.
 * @param hdr Handler to destroy.
 * @log "vm110n"
 * @see bunny_new_vm110n
 *
 * @doc-lang fr
 * @brief Détruit un gestionnaire VM110N.
 * @param hdr Gestionnaire à détruire.
 * @log "vm110n"
 * @see bunny_new_vm110n
 */
void			bunny_delete_vm110n(t_bunny_vm110n		*hdr)
{
  delete (hbs::PVM110N*)hdr->_private;
  bunny_free(hdr);
  scream_log_if("%p", "vm110n", hdr);
}

