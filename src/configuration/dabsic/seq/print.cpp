// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdio.h>
#include		"lapin_private.h"

static t_bunny_sequence_decision bunny_sequence_printx(t_bunny_configuration	*_seq,
						       t_bunny_configuration	**_params,
						       void			*data,
						       FILE			*stream)
{
  SmallConf		**params = (SmallConf**)_params;
  const char		*x;
  int			i;

  (void)data;
  (void)_seq;
  for (i = 0; params[i] != NULL; ++i)
    {
      params[i]->GetString(&x);
      fprintf(stream, "%s", x);
    }
  return (BSD_STEP);
}

t_bunny_sequence_decision bunny_sequence_print(t_bunny_configuration	*_seq,
					       t_bunny_configuration	**_params,
					       void			*data)
{
  return (bunny_sequence_printx(_seq, _params, data, stdout));
}

t_bunny_sequence_decision bunny_sequence_printerr(t_bunny_configuration	*_seq,
						  t_bunny_configuration	**_params,
						  void			*data)
{
  return (bunny_sequence_printx(_seq, _params, data, stderr));
}

