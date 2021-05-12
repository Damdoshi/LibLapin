// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

t_bunny_read_whitespace	gl_bunny_read_whitespace = NULL;

int			bunny_check_char(const char		*str,
					 ssize_t		*index,
					 const char		*token)
{
  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  return (checkchar(str, *index, token));
}

bool			bunny_check_text(const char		*str,
					 ssize_t		*index,
					 const char		*token)
{
  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  return (strncmp(&str[*index], token, strlen(token)) == 0);
}

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

void			bunny_skip_space(const char		*str,
					 ssize_t		*index)
{
  skipspace(str, *index);
}

void			bunny_inline_skip_space(const char	*str,
						ssize_t		*index)
{
  skipspace_inline(str, *index);
}

bool			bunny_read_field(const char		*str,
					 ssize_t		*index)
{
  bool			ret;

  if (gl_bunny_read_whitespace && gl_bunny_read_whitespace(str, index) == false)
    return (false);
  ret = readfield(str, *index);
  return (ret);
}

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
	  break ;
	}
      case 'x':
      case '0':
	{
	  int	nbr;

	  readinteger(code, j, nbr);
	  *out = nbr & 0xFF;
	  break ;
	}
      default:
	*out = code[j];
      }
  else
    *out = code[j];
  j += 1;
  if (readtext(code, j, "'") == false)
    return (false);
  *index = j;
  return (true);
}

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

int			bunny_which_line(const char		*str,
					 int			index)
{
  return (whichline(str, index));
}

bool			bunny_read_value(const char		*code,
					 ssize_t		*index,
					 t_bunny_configuration	*node,
					 const char		*end_token)
{
  return (readvalue(code, *i, *(SmallConf*)node, end_token))
}

