/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2021
** Pentacle Technologie 2008-2022
** EFRITS SAS 2022
**
** LibLapin
*/

#include	<stdarg.h>
#include	"lapin_private.h"

int				bunny_vsnprintf(char			*buffer,
						size_t			buflen,
						va_list			lst)
{
  const char			*str;
  int				total = 0;
  int				remaining;

  while ((str = va_arg(lst, const char*)) != NULL)
    {
      if ((remaining = buflen - total) <= 0)
	remaining = 0;
      total += vsnprintf(&buffer[total], remaining, str, lst);
    }
  return (total);
}

int				bunny_snprintf(char			*buffer,
					       size_t			buflen,
					       ...)
{
  va_list			lst;
  int				ret;

  va_start(lst, buflen);
  ret = bunny_vsnprintf(buffer, buflen, lst);
  va_end(lst);
  return (ret);
}
