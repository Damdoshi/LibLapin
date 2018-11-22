// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_sequence_decision bunny_sequence_else_if(t_bunny_configuration	*_seq,
						 t_bunny_configuration	**_params,
						 void			*data)
{
  (void)_seq;
  (void)_params;
  (void)data;
  if (_params[0] == NULL || _params[1] != NULL)
    return (BSD_ERROR);
  return (BSD_PLAY_NEXT);
}

t_bunny_sequence_decision bunny_sequence_else(t_bunny_configuration	*_seq,
					      t_bunny_configuration	**_params,
					      void			*data)
{
  (void)_seq;
  (void)data;
  if (_params[0] != NULL)
    return (BSD_ERROR);
  return (BSD_PLAY_NEXT);
}

t_bunny_sequence_decision bunny_sequence_endif(t_bunny_configuration	*_seq,
					       t_bunny_configuration	**_params,
					       void			*data)
{
  (void)_seq;
  (void)data;
  if (_params[0] != NULL)
    return (BSD_ERROR);
  return (BSD_PLAY_NEXT);
}

