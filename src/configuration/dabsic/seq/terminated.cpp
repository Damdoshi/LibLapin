// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			bunny_sequence_terminated(t_bunny_configuration	*cnf)
{
  Sequence		*seq = ((SmallConf*)cnf)->sequence;

  return (seq->instruction_pointer.size() == 0 ||
	  (seq->instruction_pointer.size() == 1 &&
	   seq->instruction_pointer.top() == (int)seq->nbr_lines)
	  );
}

