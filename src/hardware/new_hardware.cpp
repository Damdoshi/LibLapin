// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include			<new>
#include			<string.h>
#include			"PVM110N.hpp"
#include			"lapin_private.h"

struct				bunny_hardware
{
  hbs::PVM110N			*board;
  int				id;
  bool				digital_inputs[5];
  double			analog_inputs[2];
  bool				digital_outputs[8];
  double			analog_outputs[2];
};

#define				PATTERN		"%zu id -> %p"

t_bunny_hardware		*bunny_new_hardware(size_t		id)
{
  struct bunny_hardware		*ptr;

  if (id > 3)
    scream_error_if(return (NULL), EINVAL, PATTERN, "hardware", id, (void*)NULL);
  if ((ptr = (struct bunny_hardware*)bunny_malloc(sizeof(*ptr))) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "hardware", id, (void*)NULL);
  memset(ptr, 0, sizeof(*ptr));
  if ((ptr->board = new (std::nothrow) hbs::PVM110N) == NULL)
    {
      bunny_free(ptr);
      scream_error_if(return (NULL), ENOMEM, PATTERN, "hardware", id, (void*)NULL);
    }
  if ((ptr->board->Open((hbs::PVM110N::CardId)id)) == false)
    {
      delete ptr->board;
      bunny_free(ptr);
      scream_error_if(return (NULL), BE_CANT_GENERATE_RESSOURCE, PATTERN, "hardware", id, (void*)NULL);
    }
  ptr->id = id;
  scream_log_if(PATTERN, "hardware", id, ptr);
  return ((t_bunny_hardware*)ptr);
}

