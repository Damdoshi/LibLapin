// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

t_bunny_event_history	*bunny_read_event_history(t_bunny_configuration	*cnf)
{
  struct bunny_event_history *his = (struct bunny_event_history*)bunny_new_event_history();
  t_bunny_configuration	*nod;

  for (int i = 0; bunny_configuration_getf_node(cnf, &nod, "[%d]", i); ++i)
    {
      const char	*str;
      int		tick;

      if (bunny_configuration_getf_int(nod, &tick, "Tick") == false)
	goto Clear;
      for (int j = 0; bunny_configuration_getf_string(nod, &str, "Events[%d]", j); ++j)
	{
	  void		*out = NULL;
	  size_t	outlen = 0;

	  if (bunny_base64_decode(str, strlen(str), &out, &outlen) == false)
	    goto Clear;
	  if (bunny_history_add_event((t_bunny_event_history*)his, tick, outlen, out) == false)
	    goto Clear;
	  bunny_free(out);
	}
    }
  return (his);
 Clear:
  bunny_delete_event_history(his);
  return (NULL);
}

