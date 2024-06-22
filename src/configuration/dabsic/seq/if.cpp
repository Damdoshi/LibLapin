// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_sequence_decision bunny_sequence_if(t_bunny_configuration	*_seq,
					    t_bunny_configuration	**_params,
					    void			*data)
{
  Sequence		*seq = ((SmallConf*)_seq)->sequence;
  SmallConf		**params = (SmallConf**)_params;
  const char		*str;
  int			res;

  if (params[0] == NULL || params[1] == NULL)
    return (BSD_ERROR);
  if (params[1]->GetString(&str) == false)
    return (BSD_ERROR);

  if (bunny_configuration_execute(params[0], NULL, NULL) == false)
    return (BSD_ERROR);
  if (bunny_configuration_getf_int(_seq, &res, ".") == false)
    return (BSD_ERROR);

  if (bunny_strcasecmp(str, "then") != 0)
    {
      if (bunny_strcasecmp(str, "goto") != 0)
	return (BSD_ERROR);
      if (params[2] == NULL || params[3] != NULL)
	return (BSD_ERROR);
      return (bunny_sequence_goto(_seq, &_params[2], data));
    }
  if (params[2] != NULL)
    return (BSD_ERROR);

  if (res)
    return (BSD_PLAY_NEXT);
  for (res = seq->instruction_pointer.top() + 1; res < (int)seq->nbr_lines; ++res)
    if (seq->lines[res].command == "elseif")
      {
	seq->instruction_pointer.top() = res;
	return (bunny_sequence_if(_seq, _params, data));
      }
    else if (seq->lines[res].command == "else" || seq->lines[res].command == "endif")
      {
	seq->instruction_pointer.top() = res + 1;
	return (BSD_PLAY_NEXT);
      }
  seq->instruction_pointer.top() = res;
  return (BSD_STAY);
}

