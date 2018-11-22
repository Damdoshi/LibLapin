// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_sequence_decision bunny_sequence_return(t_bunny_configuration	*_seq,
						t_bunny_configuration	**_params,
						void			*data)
{
  Sequence		*seq = ((SmallConf*)_seq)->sequence;
  SmallConf		**params = (SmallConf**)_params;

  (void)data;
  if (params[0] != NULL)
    return (BSD_ERROR);
  seq->instruction_pointer.top() = seq->nbr_lines;
  return (BSD_STAY);
}

