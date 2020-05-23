/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_HISTORY_H__
# define			__LAPIN_PRIVATE_HISTORY_H__
# include			<list>

struct				bunny_event_history
{
  std::map<uint64_t, std::list<t_bunny_historical_event*>> events;
};

# define			bunny_new_historic_state(type)			\
  bunny_calloc(1, sizeof(t_bunny_historic_state) + sizeof(type))
# define			bunny_delete_historic_state(x)			\
  bunny_free(x)

#endif	/*			__LAPIN_PRIVATE_HISTORY_H__	*/
