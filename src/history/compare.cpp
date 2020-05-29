// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

bool			bunny_history_compare(t_bunny_event_history	*a,
					      t_bunny_event_history	*b)
{
  auto			*aa = (struct bunny_event_history*)a;
  auto			*bb = (struct bunny_event_history*)b;
  auto			ait = aa->events.begin();
  auto			bit = bb->events.begin();

  while (ait != aa->events.end() && bit != bb->events.end())
    {
      if (ait->first != bit->first)
	return (false);
      auto		alst = ait->second.begin();
      auto		blst = bit->second.begin();

      while (alst != ait->second.end() && blst != bit->second.end())
	{
	  if ((*alst)->tick != (*blst)->tick)
	    return (false);
	  if ((*alst)->length != (*blst)->length)
	    return (false);
	  for (size_t i = 0; i < (*alst)->length; ++i)
	    if (((char*)((*alst)->data))[i] != ((char*)(*blst)->data)[i])
	      return (false);
	  ++alst;
	  ++blst;
	}
      if (alst != ait->second.end() || blst != bit->second.end())
	return (false);
      ++ait;
      ++bit;
    }
  return (ait == aa->events.end() && bit == bb->events.end());
}
