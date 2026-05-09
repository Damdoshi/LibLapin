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


/**
 * @doc
 * @doc-symbol bunny_vsnprintf
 * @doc-kind function
 * @doc-module misc
 * @doc-order 60
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Builds a string from several printf-style fragments stored in a va_list.
 * @param buffer Destination buffer.
 * @param buflen Destination buffer size.
 * @param lst Argument list. It must contain repeated const char * format strings and their arguments, and end with NULL.
 * @return-success Returns the number of characters that would have been written.
 * @see bunny_snprintf
 *
 * @doc-lang fr
 * @brief Construit une chaîne depuis plusieurs fragments de style printf stockés dans une va_list.
 * @param buffer Tampon de destination.
 * @param buflen Taille du tampon de destination.
 * @param lst Liste d'arguments. Elle doit contenir des chaînes de format const char * et leurs arguments, puis se terminer par NULL.
 * @return-success Renvoie le nombre de caractères qui auraient été écrits.
 * @see bunny_snprintf
 */
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


/**
 * @doc
 * @doc-symbol bunny_snprintf
 * @doc-kind function
 * @doc-module misc
 * @doc-order 70
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Builds a string from several printf-style fragments.
 * @param buffer Destination buffer.
 * @param buflen Destination buffer size.
 * @param ... Repeated const char * format strings and their arguments. The sequence must end with NULL.
 * @return-success Returns the number of characters that would have been written.
 * @see bunny_vsnprintf
 *
 * @doc-lang fr
 * @brief Construit une chaîne depuis plusieurs fragments de style printf.
 * @param buffer Tampon de destination.
 * @param buflen Taille du tampon de destination.
 * @param ... Chaînes de format const char * et leurs arguments. La séquence doit se terminer par NULL.
 * @return-success Renvoie le nombre de caractères qui auraient été écrits.
 * @see bunny_vsnprintf
 */
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
