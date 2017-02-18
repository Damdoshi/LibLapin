// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			read_sequence(const char		*code,
				      ssize_t			&i,
				      SmallConf			&config)
{
  (void)config;
  if (!readtext(code, i, "]"))
    {
      fprintf(stderr, "A ']' closing the sequence section was expected. (Line %d)\n", whichline(code, i));
      return (false);
    }
  return (true);
}

