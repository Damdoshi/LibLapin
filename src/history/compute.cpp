// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

int			bunny_historic_element_compute(t_bunny_historic_element	*elem,
						       int64_t			tick,
						       t_bunny_event_history	*events,
						       void			*data)
{
  size_t		stlen = sizeof(*elem->status) + elem->status_length + elem->status_length % 8;
  char			*tab = (char*)&elem->status[0];
  int64_t		ctick = elem->last_tick;

  // If there is not computed status yet or no key frame, we cant compute
  if (elem->last_tick == -1)
    return (-1);
  // On va du dernier tick calculé jusqu'au tick demandé
  while (ctick < tick)
    {
      size_t		ctickplusmod = ((ctick + 1) % elem->status_array_length);
      size_t		ctickmod = ((ctick + 0) % elem->status_array_length);
      int		len = bunny_history_count_events_of(events, ctick);

      if (len > 0)
	{
	  t_bunny_historic_state *current = (t_bunny_historic_state*)&tab[ctickmod * stlen];
	  t_bunny_historic_state *next = (t_bunny_historic_state*)&tab[ctickplusmod * stlen];
	  t_bunny_historical_event evt[len];

	  // On récupère tous les evenements associés au tick actuel
	  bunny_history_get_events_of(events, ctick, &evt[0]);
	  // On etabli les valeurs de l'état historique
	  next->key_frame = false;
	  next->tick = ctick + 1;
	  // On ecrase les données associées au prochain état
	  memset(&next->data[0], 0, elem->status_length);
	  // On appelle la fonction qui va ecrire l'état suivant
	  if (elem->apply_history_march
	      (&next->data[0], &current->data[0], current->tick,
	       &evt[0], len, data) == false)
	    // Si elle envoi faux, on arrete et on renvoi le tick d'arret
	    // Le sens de cet arret depend entièrement de l'element.
	    // La plupart du temps, cela sera certainement pour signifier la mort de l'objet
	    break ;
	}
      ctick += 1;
    }
  elem->last_tick = ctick;
  // On renvoi le dernier tick calculé (a priori, c'est tick si tout s'est bien passé)
  return (ctick);
}


