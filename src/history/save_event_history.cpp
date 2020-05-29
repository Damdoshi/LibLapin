// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

bool			bunny_save_event_history(t_bunny_event_history	*his,
						 t_bunny_configuration	*cnf)
{
  struct bunny_event_history *h = (struct bunny_event_history*)his;
  bool			cmode = bunny_configuration_get_create_mode();
  int			i = 0;

  bunny_configuration_create_mode(true);
  bunny_clear_configuration(cnf);
  for (auto it = h->events.begin(); it != h->events.end(); ++it)
    {
      t_bunny_configuration *nod;
      int		j = 0;

      if (bunny_configuration_getf_node(cnf, &nod, "[%d]", i) == false)
	goto Clear;
      if (bunny_configuration_setf_int(nod, (int)it->first, "Tick") == false)
	goto Clear;
      for (auto itx = it->second.begin(); itx != it->second.end(); ++itx)
	{
	  char		*out = NULL;
	  size_t	outlen = 0;

	  if (bunny_base64_encode((*itx)->data, (*itx)->length, &out, &outlen) == false)
	    goto Clear;
	  if (bunny_configuration_setf_string(nod, out, "Events[%d]", j) == false)
	    goto Clear;
	  bunny_free(out);
	  j += 1;
	}
      i += 1;
    }
  bunny_configuration_create_mode(cmode);
  return (true);
 Clear:
  bunny_configuration_create_mode(cmode);
  bunny_clear_configuration(cnf);
  return (false);
}
