// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

typedef struct		s_token
{
  size_t		len;
  const char		*str;
}			t_token;

static bool		precom_tokens(const char			**tokens,
				      t_token				*tok,
				      size_t				max)
{
  size_t		i;

  for (i = 0; tokens[i] && i < max; ++i)
    tok[i].len = strlen(tok[i].str = tokens[i]);
  if (i - 1 >= max)
    return (false);
  tok[i].str = NULL;
  return (true);
}

static size_t		test_token(const char				*str,
				   size_t				pos,
				   t_token				*tok,
				   bool					agreg)
{
  size_t		i, j;

  if (agreg)
    {
      i = pos;
      do
	for (j = 0; tok[j].str && strncmp(&str[i], tok[j].str, tok[j].len); ++j);
      while (tok[j].str && (i += tok[j].len));
      return (i - pos);
    }

  for (j = 0; tok[j].str && strncmp(&str[pos], tok[j].str, tok[j].len); ++j);
  if (tok[j].str)
    return (tok[j].len);
  return (0);
}

const char * const	*bunny_split(const char				*str,
				     const char				**tokens,
				     bool				agreg)
{
  char			*buf[4096];
  t_token		tok[32];
  size_t		i, prev;
  size_t		tmp;
  ssize_t		cur;
  void			*ret;

  if (precom_tokens(tokens, &tok[0], sizeof(tok) / sizeof(tok[0])) == false)
    return (NULL);

  i = 0;
  cur = 0;
  prev = 0;
  while (str[i])
    if ((tmp = test_token(str, i, &tok[0], agreg)))
      {
	if (i != 0 || agreg == false)
	  {
	    if ((buf[cur] = bunny_strndup(&str[prev], i - prev)) == NULL)
	      goto clean;
	    if ((cur += 1) + 1 >= (ssize_t)(sizeof(buf) / sizeof(buf[0])))
	      goto clean;
	  }
	prev = (i += tmp);
      }
    else
      i += 1;
  if (prev != i)
    {
      if ((buf[cur] = bunny_strndup(&str[prev], i - prev)) == NULL)
	goto clean;
      if ((cur += 1) + 1 >= (ssize_t)(sizeof(buf) / sizeof(buf[0])))
	goto clean;
    }
  buf[cur] = NULL;
  if ((ret = bunny_memdup(&buf[0], (cur + 1) * sizeof(buf[0]))) == NULL)
    goto clean;
  return ((char**)ret);

 clean:
  while (--cur >= 0)
    bunny_free(buf[cur]);
  return (NULL);
}

void			bunny_delete_split(const char * const		*tab)
{
  size_t		i;

  for (i = 0; tab[i]; ++i)
    bunny_free((void*)tab[i]);
  bunny_free((void*)tab);
}

