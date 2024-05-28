// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

char			*bunny_stick(const char * const		*tab,
				     const char			*glue,
				     bool			no_last)
{
  char			*data;
  size_t		len;
  size_t		wt;
  size_t		i;

  for (i = 0, len = 0; tab[i]; ++i)
    len += strlen(tab[i]);
  len += strlen(glue) * (i - no_last ? 1 : 0) + 1;
  if ((data = (char*)bunny_malloc(sizeof(*data) * len)) == NULL)
    return (NULL);
  for (i = 0, wt = 0; tab[i]; ++i)
    {
      wt += snprintf(&data[wt], len, "%s", tab[i]);
      if (tab[i + 1] != NULL || no_last == false)
	wt += snprintf(&data[wt], len, "%s", glue);
    }
  return (data);
}

