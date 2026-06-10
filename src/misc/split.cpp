// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
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

#define			PATTERN		"%s string, %p tokens, %s agreg -> %p"


/**
 * @doc
 * @doc-symbol bunny_split
 * @doc-kind function
 * @doc-module misc
 * @doc-order 220
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Splits a string with an ordered list of separators.
 * @param str String to split.
 * @param tokens NULL-terminated array of separator strings. Earlier tokens have priority.
 * @param agreg If true, consecutive separators are aggregated.
 * @return-success Returns a NULL-terminated array of newly allocated strings.
 * @return-failure Returns NULL on error.
 * @description The current implementation is limited to fewer than 4096 resulting parts and fewer than 32 separator tokens.
 * @see bunny_delete_split, bunny_split_len, bunny_stick, t_bunny_split
 *
 * @doc-lang fr
 * @brief Découpe une chaîne avec une liste ordonnée de séparateurs.
 * @param str Chaîne à découper.
 * @param tokens Tableau terminé par NULL de chaînes séparatrices. Les premiers séparateurs sont prioritaires.
 * @param agreg Si true, les séparateurs consécutifs sont agrégés.
 * @return-success Renvoie un tableau terminé par NULL de chaînes nouvellement allouées.
 * @return-failure Renvoie NULL en cas d'erreur.
 * @description L'implémentation actuelle est limitée à moins de 4096 morceaux résultants et moins de 32 séparateurs.
 * @see bunny_delete_split, bunny_split_len, bunny_stick, t_bunny_split
 */
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
    scream_error_if(return (NULL), ENOMEM, PATTERN " (Too many parts)", "misc", str, tokens, agreg ? "true" : "false", (void*)NULL);

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

  scream_log_if(PATTERN, "misc", str, tokens, agreg ? "true" : "false", ret);
  return ((char**)ret);

 clean:
  tmp = bunny_errno;
  while (--cur >= 0)
    bunny_free(buf[cur]);
  bunny_errno = tmp;
  scream_error_if(return (NULL), bunny_errno, PATTERN, "misc",
		  str, tokens, agreg ? "true" : "false", (void*)NULL);
  return (NULL);
}


/**
 * @doc
 * @doc-symbol bunny_delete_split
 * @doc-kind function
 * @doc-module misc
 * @doc-order 230
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes an array returned by bunny_split.
 * @param tab Split array to delete. NULL is accepted.
 * @see bunny_split, bunny_split_len
 *
 * @doc-lang fr
 * @brief Supprime un tableau renvoyé par bunny_split.
 * @param tab Tableau découpé à supprimer. NULL est accepté.
 * @see bunny_split, bunny_split_len
 */
void			bunny_delete_split(const char * const		*tab)
{
  size_t		i;

  for (i = 0; tab[i]; ++i)
    bunny_free((void*)tab[i]);
  bunny_free((void*)tab);
  scream_log_if("%p", "misc", tab);
}


/**
 * @doc
 * @doc-symbol bunny_split_len
 * @doc-kind function
 * @doc-module misc
 * @doc-order 235
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Counts the entries in a NULL-terminated split array.
 * @param tab Array to inspect.
 * @return-success Returns the number of strings before the NULL terminator.
 * @see bunny_split, bunny_delete_split
 *
 * @doc-lang fr
 * @brief Compte les entrées d'un tableau découpé terminé par NULL.
 * @param tab Tableau à inspecter.
 * @return-success Renvoie le nombre de chaînes avant le terminateur NULL.
 * @see bunny_split, bunny_delete_split
 */
size_t			bunny_split_len(const char * const		*tab)
{
  size_t		i;

  for (i = 0; tab[i]; ++i);
  return (i);
}

