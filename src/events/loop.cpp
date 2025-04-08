// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_loop(t_bunny_window	*window,
				   unsigned int		freq,
				   void			*data)
{
  return (bunny_loop_mw(&window, 1, freq, data));
}

