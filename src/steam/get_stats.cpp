// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	<steam_api.h>
#undef		BUNNY_CAMERA
#include	"lapin_private.h"

bool		bunny_steam_get_int_stats(t_bunny_steam	*steam,
					  const char	*name,
					  int		*out)
{
  struct bunny_steam *st = (struct bunny_steam*)steam;
  int32_t	x;

  if (st->stats->GetStat(name, &x) == false)
    return (false);
  *out = x;
  return (true);
}


bool		bunny_steam_get_float_stats(t_bunny_steam *steam,
					    const char	*name,
					    float	*out)
{
  struct bunny_steam *st = (struct bunny_steam*)steam;

  return (st->stats->GetStat(name, out));
}
