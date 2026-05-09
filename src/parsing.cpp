// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

t_bunny_read_whitespace	gl_bunny_read_whitespace = NULL;


/**
 * @doc
 * @doc-symbol bunny_check_char
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 100
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Counts accepted characters without moving the cursor.
 * @param str The string to inspect.
 * @param index The cursor position used as the starting point.
 * @param token The accepted characters.
 * @return-case success The number of consecutive accepted characters starting at index.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Compte les caractères acceptés sans déplacer le curseur.
 * @param str La chaîne à inspecter.
 * @param index La position du curseur utilisée comme point de départ.
 * @param token Les caractères acceptés.
 * @return-case success Le nombre de caractères acceptés consécutifs à partir de index.
 * @see gl_bunny_read_whitespace
 */

int			bunny_check_char(const char		*str,
					 ssize_t		*index,
					 const char		*token)
{
  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  return (checkchar(str, *index, token));
}


/**
 * @doc
 * @doc-symbol bunny_check_text
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 120
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Checks whether a token appears at the cursor without moving it.
 * @param str The string to inspect.
 * @param index The cursor position used as the starting point.
 * @param token The text to match.
 * @return-case success true if token appears at index.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Vérifie si un jeton apparaît au curseur sans le déplacer.
 * @param str La chaîne à inspecter.
 * @param index La position du curseur utilisée comme point de départ.
 * @param token Le texte à reconnaître.
 * @return-case success true si token apparaît à index.
 * @see gl_bunny_read_whitespace
 */

bool			bunny_check_text(const char		*str,
					 ssize_t		*index,
					 const char		*token)
{
  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  return (strncmp(&str[*index], token, strlen(token)) == 0);
}


/**
 * @doc
 * @doc-symbol bunny_check_text_case
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 140
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Checks whether a token appears at the cursor, ignoring case, without moving it.
 * @param str The string to inspect.
 * @param index The cursor position used as the starting point.
 * @param token The text to match.
 * @return-case success true if token appears at index, ignoring case.
 * @see gl_bunny_read_whitespace, bunny_check_text, bunny_read_text
 *
 * @doc-lang fr
 * @brief Vérifie si un jeton apparaît au curseur, sans tenir compte de la casse et sans le déplacer.
 * @param str La chaîne à inspecter.
 * @param index La position du curseur utilisée comme point de départ.
 * @param token Le texte à reconnaître.
 * @return-case success true si token apparaît à index, sans tenir compte de la casse.
 * @see gl_bunny_read_whitespace, bunny_check_text, bunny_read_text
 */

bool			bunny_check_text_case(const char		*str,
					      ssize_t		*index,
					      const char		*token)
{
  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  return (checktextcase(str, *index, token));
}


/**
 * @doc
 * @doc-symbol bunny_read_char
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 160
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Consumes characters belonging to a whitelist.
 * @param str The string to inspect.
 * @param index The cursor to update.
 * @param token The accepted characters.
 * @return-case success true if at least one character was consumed.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Consomme les caractères appartenant à une liste blanche.
 * @param str La chaîne à inspecter.
 * @param index Le curseur à mettre à jour.
 * @param token Les caractères acceptés.
 * @return-case success true si au moins un caractère a été consommé.
 * @see gl_bunny_read_whitespace
 */

bool			bunny_read_char(const char		*str,
					ssize_t			*index,
					const char		*token)
{
  bool			ret;

  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  ret = readchar(str, *index, token);
  return (ret);
}


/**
 * @doc
 * @doc-symbol bunny_read_text
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 180
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Consumes a fixed text token.
 * @param str The string to inspect.
 * @param index The cursor to update.
 * @param token The text to match.
 * @return-case success true if token was consumed.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Consomme un jeton texte fixe.
 * @param str La chaîne à inspecter.
 * @param index Le curseur à mettre à jour.
 * @param token Le texte à reconnaître.
 * @return-case success true si token a été consommé.
 * @see gl_bunny_read_whitespace
 */

bool			bunny_read_text(const char		*str,
					ssize_t			*index,
					const char		*token)
{
  bool			ret;

  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  ret = readtext(str, *index, token);
  return (ret);
}


/**
 * @doc
 * @doc-symbol bunny_skip_space
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 200
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Skips all whitespace characters.
 * @param str The string to browse.
 * @param index The cursor to update.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Saute tous les caractères blancs.
 * @param str La chaîne à parcourir.
 * @param index Le curseur à mettre à jour.
 * @see gl_bunny_read_whitespace
 */

void			bunny_skip_space(const char		*str,
					 ssize_t		*index)
{
  skipspace(str, *index);
}


/**
 * @doc
 * @doc-symbol bunny_inline_skip_space
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 220
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Skips spaces and tabulations on the current line.
 * @param str The string to browse.
 * @param index The cursor to update.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Saute les espaces et tabulations sur la ligne courante.
 * @param str La chaîne à parcourir.
 * @param index Le curseur à mettre à jour.
 * @see gl_bunny_read_whitespace
 */

void			bunny_inline_skip_space(const char	*str,
						ssize_t		*index)
{
  skipspace_inline(str, *index);
}


/**
 * @doc
 * @doc-symbol bunny_read_field
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 240
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Consumes a C-like identifier.
 * @param str The string to browse.
 * @param index The cursor to update.
 * @return-case success true if an identifier was consumed.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Consomme un identifiant de style C.
 * @param str La chaîne à parcourir.
 * @param index Le curseur à mettre à jour.
 * @return-case success true si un identifiant a été consommé.
 * @see gl_bunny_read_whitespace
 */

bool			bunny_read_field(const char		*str,
					 ssize_t		*index)
{
  bool			ret;

  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  ret = readfield(str, *index);
  return (ret);
}


/**
 * @doc
 * @doc-symbol bunny_read_double
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 260
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Consumes and returns a double value.
 * @param str The string to parse.
 * @param index The cursor to update.
 * @param val The output value.
 * @return-case success true if a valid double was read.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Consomme et renvoie une valeur double.
 * @param str La chaîne à parser.
 * @param index Le curseur à mettre à jour.
 * @param val La valeur de sortie.
 * @return-case success true si un double valide a été lu.
 * @see gl_bunny_read_whitespace
 */

bool			bunny_read_double(const char		*str,
					  ssize_t		*index,
					  double		*val)
{
  bool			ret;

  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  ret = readdouble(str, *index, *val);
  return (ret);
}


/**
 * @doc
 * @doc-symbol bunny_read_integer
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 280
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Consumes and returns an integer value.
 * @param str The string to parse.
 * @param index The cursor to update.
 * @param val The output value.
 * @return-case success true if a valid integer was read.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Consomme et renvoie une valeur entière.
 * @param str La chaîne à parser.
 * @param index Le curseur à mettre à jour.
 * @param val La valeur de sortie.
 * @return-case success true si un entier valide a été lu.
 * @see gl_bunny_read_whitespace
 */

bool			bunny_read_integer(const char		*str,
					   ssize_t		*index,
					   int			*val)
{
  bool			ret;

  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  ret = readinteger(str, *index, *val);
  return (ret);
}


/**
 * @doc
 * @doc-symbol bunny_read_cchar
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 290
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Consumes and decodes a C-style character literal.
 * @param code The string to parse.
 * @param index The cursor to update.
 * @param out The decoded character.
 * @return-case success true if a valid character literal was read.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Consomme et décode un littéral caractère de style C.
 * @param code La chaîne à parser.
 * @param index Le curseur à mettre à jour.
 * @param out Le caractère décodé.
 * @return-case success true si un littéral caractère valide a été lu.
 * @see gl_bunny_read_whitespace
 */

bool			bunny_read_cchar(const char		*code,
					 ssize_t		*index,
					 char			*out)
{
  ssize_t		j = *index;

  if (readtext(code, j, "'") == false)
    return (false);
  if (readtext(code, j, "\\"))
    switch (code[j])
      {
      case 'a': *out = '\a'; break;
      case 'b': *out = '\b'; break;
      case 'v': *out = '\v'; break;
      case 'f': *out = '\f'; break;
      case 'n': *out = '\n'; break;
      case 't': *out = '\t'; break;
      case '\\': *out = '\\'; break;
      case 'r': *out = '\r'; break;
      case '"': *out = '"'; break;
      case '\'': *out = '\''; break;
      case 'u':
	{
	  int	nbr;

	  readinteger(code, j, nbr);
	  *out = nbr & 0xFF;
	  goto End;
	}
      case 'x':
      case '0':
	{
	  int	nbr;

	  readinteger(code, j, nbr);
	  *out = nbr & 0xFF;
	  goto End;
	}
      default:
	*out = code[j];
      }
  else
    *out = code[j];
  j += 1;
 End:
  if (readtext(code, j, "'") == false)
    return (false);
  *index = j;
  return (true);
}


/**
 * @doc
 * @doc-symbol bunny_read_cstring
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 300
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Consumes and decodes a C-style string literal.
 * @param str The string to parse.
 * @param index The cursor to update.
 * @param out The output buffer.
 * @param out_len The output buffer size.
 * @return-case success true if a valid string literal was read.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Consomme et décode un littéral chaîne de style C.
 * @param str La chaîne à parser.
 * @param index Le curseur à mettre à jour.
 * @param out Le buffer de sortie.
 * @param out_len La taille du buffer de sortie.
 * @return-case success true si un littéral chaîne valide a été lu.
 * @see gl_bunny_read_whitespace
 */

bool			bunny_read_cstring(const char		*str,
					   ssize_t		*index,
					   char			*out,
					   size_t		out_len)
{
  bool			ret;

  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  ret = readstring(str, *index, out, out_len);
  return (ret);
}


/**
 * @doc
 * @doc-symbol bunny_write_cstring
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 340
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Encodes a string as a C-style string body.
 * @param str The input string.
 * @param out The output string pointer or existing buffer.
 * @param siz The size of the existing output buffer when *out is not NULL.
 * @return-case success true if the string was encoded.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Encode une chaîne sous forme de corps de chaîne C.
 * @param str La chaîne d'entrée.
 * @param out Le pointeur de chaîne de sortie ou le buffer existant.
 * @param siz La taille du buffer de sortie existant quand *out ne vaut pas NULL.
 * @return-case success true si la chaîne a été encodée.
 * @see gl_bunny_read_whitespace
 */

bool			bunny_write_cstring(const char		*cstr,
					    char		**out,
					    size_t		siz)
{
  std::string		str(cstr);
  std::stringstream	ss;
  char			*x;

  writestring(ss, str);
  str = ss.str();
  if (*out == NULL)
    {
      if ((x = (char*)bunny_malloc(str.size() + 1)) == NULL)
	return (false);
      strcpy(x, str.c_str());
      *out = x;
    }
  else
    strncpy(*out, str.c_str(), siz);
  return (true);
}


/**
 * @doc
 * @doc-symbol bunny_read_rawstring
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 320
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Consumes raw text until one of the ending tokens is encountered.
 * @param str The string to parse.
 * @param index The cursor to update.
 * @param out The output buffer.
 * @param out_len The output buffer size.
 * @param end_token Characters that stop the raw string.
 * @return-case success true if a raw string was read.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Consomme du texte brut jusqu'à rencontrer un des jetons de fin.
 * @param str La chaîne à parser.
 * @param index Le curseur à mettre à jour.
 * @param out Le buffer de sortie.
 * @param out_len La taille du buffer de sortie.
 * @param end_token Les caractères qui arrêtent la chaîne brute.
 * @return-case success true si une chaîne brute a été lue.
 * @see gl_bunny_read_whitespace
 */

bool			bunny_read_rawstring(const char		*code,
					     ssize_t		*index,
					     char		*out,
					     size_t		out_len,
					     char		*end_tok)
{
  bool			ret;

  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(code, index) == false)
    return (false);
  ret = readrawchar(code, *index, out, out_len, end_tok);
  return (ret);
}


/**
 * @doc
 * @doc-symbol bunny_which_line
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 380
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Computes the line number containing a character index.
 * @param str The string to inspect.
 * @param index The character index.
 * @return-case success The one-based line number.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Calcule le numéro de ligne contenant un index de caractère.
 * @param str La chaîne à inspecter.
 * @param index L'index du caractère.
 * @return-case success Le numéro de ligne, en commençant à 1.
 * @see gl_bunny_read_whitespace
 */

int			bunny_which_line(const char		*str,
					 int			index)
{
  return (whichline(str, index));
}


/**
 * @doc
 * @doc-symbol bunny_read_value
 * @doc-kind function
 * @doc-module parsing
 * @doc-order 400
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Reads a configuration value from text.
 * @param code The string to parse.
 * @param index The cursor to update.
 * @param node The configuration node that receives the value.
 * @param end_token Characters that stop the value.
 * @return-case success true if a value was read.
 * @see gl_bunny_read_whitespace
 *
 * @doc-lang fr
 * @brief Lit une valeur de configuration depuis du texte.
 * @param code La chaîne à parser.
 * @param index Le curseur à mettre à jour.
 * @param node Le noeud de configuration qui reçoit la valeur.
 * @param end_token Les caractères qui arrêtent la valeur.
 * @return-case success true si une valeur a été lue.
 * @see gl_bunny_read_whitespace
 */

bool			bunny_read_value(const char		*code,
					 ssize_t		*index,
					 t_bunny_configuration	*node,
					 const char		*end_token)
{
  return (readvalue(code, *index, *(SmallConf*)node, end_token));
}

