// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

int			bunny_check_char(const char		*str,
					 ssize_t		*index,
					 const char		*token)
{
  return (checkchar(str, *index, token));
}

bool			bunny_check_text(const char		*str,
					 ssize_t		*index,
					 const char		*token)
{
  return (strncmp(&str[*index], token, strlen(token)) == 0);
}

bool			bunny_read_char(const char		*str,
					ssize_t			*index,
					const char		*token)
{
  return (readchar(str, *index, token));
}

bool			bunny_read_text(const char		*str,
					ssize_t			*index,
					const char		*token)
{
  return (readtext(str, *index, token));
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
  return (readfield(str, *index));
}

bool			bunny_read_double(const char		*str,
					  ssize_t		*index,
					  double		*val)
{
  return (readdouble(str, *index, *val));
}

bool			bunny_read_integer(const char		*str,
					   ssize_t		*index,
					   int			*val)
{
  return (readinteger(str, *index, *val));
}

bool			bunny_read_cstring(const char		*str,
					   ssize_t		*index,
					   char			*out,
					   size_t		out_len)
{
  return (readstring(str, *index, out, out_len));
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
  return (readrawchar(code, *index, out, out_len, end_tok));
}

int			bunny_which_line(const char		*str,
					 int			index)
{
  return (whichline(str, index));
}

