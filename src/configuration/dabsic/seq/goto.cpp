// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_sequence_decision bunny_sequence_goto(t_bunny_configuration	*_seq,
					      t_bunny_configuration	**_params,
					      void			*data)
{
  Sequence		*seq = ((SmallConf*)_seq)->sequence;
  SmallConf		**params = (SmallConf**)_params;

  (void)data;
  if (params[0] == NULL || params[1] != NULL)
    return (BSD_ERROR);

  for (auto& lab : seq->labels)
    {
      const char	*x;

      params[0]->GetString(&x);
      if (lab.second == std::string(x))
	{
	  seq->instruction_pointer.top() = lab.first;
	  return (BSD_PLAY_NEXT);
	}
    }
  // Label not found
  return (BSD_ERROR);
}

