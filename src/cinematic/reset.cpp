// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include	"lapin_private.h"

void		bunny_reset_cinematic(t_bunny_cinematic		*cin)
{
  struct bunny_cinematic *cn = (struct bunny_cinematic*)cin;

  bunny_cinematic_stop(cin);
  cn->current_command = 0;
  cn->stack_top = 0;
}
