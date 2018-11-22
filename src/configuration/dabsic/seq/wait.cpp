// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_sequence_decision bunny_sequence_wait_loop(t_bunny_configuration	*_seq,
						   t_bunny_configuration	**_params,
						   void				*data)
{
  SmallConf		**params = (SmallConf**)_params;
  t_bunny_time		now = bunny_get_time();
  Sequence		*seq = ((SmallConf*)_seq)->sequence;
  double		param;

  (void)data;
  if (params[0] == NULL || params[1] != NULL)
    return (BSD_ERROR);

  params[0]->GetDouble(&param);
  if (now - seq->previous >= param * 1e9)
    {
      seq->previous = 0;
      return (BSD_PLAY_NEXT);
    }
  return (BSD_STAY);
}


t_bunny_sequence_decision bunny_sequence_wait(t_bunny_configuration		*_seq,
					      t_bunny_configuration		**_params,
					      void				*data)
{
  Sequence		*seq = ((SmallConf*)_seq)->sequence;

  (void)data;
  (void)_params;
  seq->previous = bunny_get_time();
  return (BSD_STAY);
}

