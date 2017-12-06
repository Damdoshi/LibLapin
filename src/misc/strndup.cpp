// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin Library

#include		<string.h>
#include		"lapin_private.h"

char			*bunny_strndup(const char	*str,
				       size_t		max)
{
  char			*s;
  size_t		i;

  if ((s = (char*)bunny_malloc(sizeof(*s) + (max + 1))) == NULL)
    scream_error_if
      (return (s), bunny_errno, "%s string, %zu max_size -> %p", "misc",
       str, max, (void*)NULL);
  for (i = 0; str[i] && i < max; ++i)
    s[i] = str[i];
  s[i] = '\0';
  scream_log_if("%s string, %zu max_size -> %p", "misc", str, max, s);
  return (s);
}

char			*bunny_strdup(const char	*str)
{
  return (bunny_strndup(str, strlen(str)));
}

