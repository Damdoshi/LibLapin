// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include			<new>
#include			<string.h>
#include			"PVM110N.hpp"
#include			"lapin_private.h"

struct				bunny_vm110n
{
  hbs::PVM110N			*board;
  int				id;
  bool				digital_inputs[5];
  double			analog_inputs[2];
  bool				digital_outputs[8];
  double			analog_outputs[2];
};

#define				PATTERN		"%zu id -> %p"


/**
 * @doc
 * @doc-symbol bunny_new_vm110n
 * @doc-kind function
 * @doc-module hardware
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Creates a handler for a Velleman VM110N board.
 * @param id Board identifier configured by jumper.
 * @return-success Returns a newly allocated VM110N handler.
 * @return-failure Returns NULL on invalid id, allocation failure or hardware access failure.
 * @log "vm110n"
 * @see t_bunny_vm110n, bunny_delete_vm110n
 *
 * @doc-lang fr
 * @brief Crée un gestionnaire pour une carte Velleman VM110N.
 * @param id Identifiant de carte configuré par cavalier.
 * @return-success Renvoie un gestionnaire VM110N nouvellement alloué.
 * @return-failure Renvoie NULL en cas d’id invalide, d’échec d’allocation ou d’accès matériel.
 * @log "vm110n"
 * @see t_bunny_vm110n, bunny_delete_vm110n
 */
t_bunny_vm110n		*bunny_new_vm110n(size_t		id)
{
  struct bunny_vm110n		*ptr;

  if (id > 3)
    scream_error_if(return (NULL), EINVAL, PATTERN, "vm110n", id, (void*)NULL);
  if ((ptr = (struct bunny_vm110n*)bunny_calloc(1, sizeof(*ptr))) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "vm110n", id, (void*)NULL);
  memset(ptr, 0, sizeof(*ptr));
  if ((ptr->board = new (std::nothrow) hbs::PVM110N) == NULL)
    {
      bunny_free(ptr);
      scream_error_if(return (NULL), ENOMEM, PATTERN, "vm110n", id, (void*)NULL);
    }
  if ((ptr->board->Open((hbs::PVM110N::CardId)id)) == false)
    {
      delete ptr->board;
      bunny_free(ptr);
      scream_error_if(return (NULL), BE_CANT_GENERATE_RESSOURCE, PATTERN, "vm110n", id, (void*)NULL);
    }
  ptr->id = id;
  scream_log_if(PATTERN, "vm110n", id, ptr);
  return ((t_bunny_vm110n*)ptr);
}

