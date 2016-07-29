// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include			<new>
#include			<string.h>
#include			"PVM110N.hpp"
#include			"lapin.h"

struct				bunny_hardware
{
  hbs::PVM110N			*board;
  int				id;
  bool				digital_inputs[5];
  double			analog_inputs[2];
  bool				digital_outputs[8];
  double			analog_outputs[2];
};

t_bunny_hardware		*bunny_new_hardware(size_t		id)
{
  struct bunny_hardware		*ptr;

  if (id > 3)
    return (NULL);
  if ((ptr = (struct bunny_hardware*)bunny_malloc(sizeof(*ptr))) == NULL)
    return (NULL);
  memset(ptr, 0, sizeof(*ptr));
  if ((ptr->board = new (std::nothrow) hbs::PVM110N) == NULL)
    {
      bunny_free(ptr);
      return (NULL);
    }
  if ((ptr->board->Open((hbs::PVM110N::CardId)id)) == false)
    {
      delete ptr->board;
      bunny_free(ptr);
      return (NULL);
    }
  ptr->id = id;
  return ((t_bunny_hardware*)ptr);
}

