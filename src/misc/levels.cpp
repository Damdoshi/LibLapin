// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

int			bunny_next_level_experience(int		lvl)
{
  lvl += 1;
  return (lvl * (lvl - 1) / 2);
}

