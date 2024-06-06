// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"
#define			fallback t_bunny_sequence_fallback_command

bool			sequence_compute(SmallConf			&func,
					 SmallConf			*proto,
					 SmallConf			*root,
					 SmallConf			*local,
					 SmallConf			*params,
					 const fallback			*fb,
					 void				*dat)
{
  (void)func;
  (void)proto;
  (void)root;
  (void)local;
  (void)params;
  (void)fb;
  (void)dat;
  return (false);
}

t_bunny_response	bunny_sequence_execute(t_bunny_configuration	*cnf,
					       t_bunny_configuration	*_params,
					       t_bunny_sequence_fallback_function ucmd,
					       t_bunny_sequence_fallback_function urpt,
					       t_bunny_sequence_fallback_event uevt,
					       void			*dat)
{
  fallback		fb = {ucmd, urpt, uevt};
  SmallConf		*root = (SmallConf*)bunny_configuration_get_root(cnf);
  SmallConf		*artif = (SmallConf*)cnf;
  SmallConf		*params = (SmallConf*)_params;
  SmallConf		*proto;

  if (artif->Access(".prototype") == false)
    proto = NULL;
  else
    proto = &(*artif)[".prototype"];
  if (sequence_compute(*artif, proto, root, artif, params, &fb, dat) == false)
    return (EXIT_ON_ERROR);
  return (GO_ON);
}

