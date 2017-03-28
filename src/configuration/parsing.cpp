// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin Library

#include		"lapin_private.h"

const char		*fieldname_first_char =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
const char		*fieldname =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890";
const char		*numbers =
  "1234567890";

void			skipspace(const char			*str,
				  ssize_t			&i)
{
  while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'))
    ++i;
}

int			checkchar(const char			*str,
				  ssize_t			&index,
				  const char			*tokens)
{
  ssize_t		t;
  ssize_t		i;

  for (i = index; str[i]; ++i)
    {
      for (t = 0; tokens[t] && str[i] != tokens[t]; ++t);
      if (tokens[t] == '\0')
	return (i - index);
    }
  return (i - index);
}

bool			readtext(const char			*str,
				 ssize_t			&index,
				 const char			*token)
{
  size_t		l;

  if (strncmp(&str[index], token, l = strlen(token)) != 0)
    return (false);
  index += l;
  return (true);
}

bool			readchar(const char			*str,
				 ssize_t			&index,
				 const char			*token)
{
  ssize_t		i;

  if ((i = checkchar(str, index, token)))
    {
      index += i;
      return (true);
    }
  return (false);
}

int			whichline(const char			*code,
				  int				i)
{
  int			line = 1;

  while (i > 0)
    {
      if (code[i] == '\n' || (code[i] == '\r' && code[i + 1] != '\n'))
	line += 1;
      i -= 1;
    }
  return (line);
}

bool			readfield(const char			*str,
				  ssize_t			&index)
{
  if (readchar(str, index, fieldname_first_char) == false)
    return (false);
  readchar(str, index, fieldname);
  return (true);
}

bool			getfieldname(const char			*code,
				     ssize_t			&i,
				     char			*out,
				     ssize_t			buflen,
				     SmallConf			&scope,
				     bool			overwrite)
{
  ssize_t		readlen, j;

  j = i;
  if (readfield(code, j) == false)
    {
      fprintf(stderr, "A name was expected. (Line %d)\n",
	      whichline(code, i));
      return (false);
    }

  if ((readlen = j - i) > buflen / 2)
    {
      fprintf(stderr, "The name is too long. Max is %zu. (Line %d)\n",
	      buflen / 2, whichline(code, i));
      return (false);
    }
  strncpy(&out[0], &code[i], readlen);
  out[readlen] = '\0';
  i = j;

  if (overwrite)
    return (true);

  j = -2;
  do
    if (++j < 0)
      out[readlen] = '\0';
    else
      snprintf(&out[readlen], buflen - readlen, "%zu", j);
  while (scope.Access(std::string(&out[0])));
  return (true);
}

bool			readdouble(const char			*code,
				   ssize_t			&i,
				   double			&d)
{
  ssize_t		j = i;

  if (readchar(code, j, numbers) == false)
    return (false);
  if (readtext(code, j, ".") == false)
    {
      if (readtext(code, j, "%") == false)
	return (false);
      d = strtod(&code[i], NULL) / 100.0;
      i = j;
      return (true);
    }
  readchar(code, j, numbers);
  d = strtod(&code[i], NULL);
  i = j;
  return (true);
}

bool			readinteger(const char			*code,
				    ssize_t			&i,
				    int				&d)
{
  char			*end;

  if (strncmp(&code[i], "0b", 2) == 0)
    {
      d = 0;
      i += 2;
      while (code[i] == '1' || code[i] == '0')
	{
	  d <<= 1;
	  d |= (code[i] == '1') ? 1 : 0;
	  i += 1;
	}
      return (true);
    }
  d = strtol(&code[i], &end, 0);
  if (end == &code[i])
    return (false);
  i += end - &code[i];
  return (true);
}

bool			readrawchar(const char			*code,
				    ssize_t			&i,
				    char			*d,
				    ssize_t			len,
				    char			endtok)
{
  ssize_t		j;

  for (j = i; code[j] && code[j] != '\n' && code[j] != '\r' && code[j] != endtok; ++j);
  if (j - i >= len - 1)
    {
      fprintf(stderr, "The raw string is too long. (Line %d)\n",
	      whichline(code, i));
      return (false);
    }
  strncpy(d, &code[i], j - i);
  d[j - i] = '\0';
  i = j;
  return (true);
}

bool			readstring(const char			*code,
				   ssize_t			&i,
				   char				*d,
				   ssize_t			len)
{
  ssize_t		j = i;
  ssize_t		p;

  if (readtext(code, j, "\"") == false)
    return (false);
  p = 0;
  while (code[j] && !checkchar(code, j, "\""))
    {
      if (code[j] & 0x80) // Unicode character
	{
	  if ((code[j] & 0xE0) == 0xC0) // 110x xxxx
	    {
	      strncpy(&d[p], &code[j], 2);
	      j += 2;
	      p += 2;
	    }
	  else if ((code[j] & 0xF0) == 0xE0) // 1110 xxxx
	    {
	      strncpy(&d[p], &code[j], 3);
	      j += 3;
	      p += 3;
	    }
	  else if ((code[j] & 0xF8) == 0xF0) // 1111 0xxx
	    {
	      strncpy(&d[p], &code[j], 4);
	      j += 4;
	      p += 4;
	    }
	  else
	    {
	      fprintf(stderr, "Unknown character. (Line %d)\n", whichline(code, j));
	      return (false);
	    }
	}
      else if (code[j] != '\\')
	strncpy(&d[p++], &code[j++], 1);
      else
	{
	  switch (code[++j])
	    {
	    case 'a': d[p++] = '\a'; break;
	    case 'b': d[p++] = '\b'; break;
	    case 'v': d[p++] = '\v'; break;
	    case 'f': d[p++] = '\f'; break;
	    case 'n': d[p++] = '\n'; break;
	    case 't': d[p++] = '\t'; break;
	    case '\\': d[p++] = '\\'; break;
	    case 'r': d[p++] = '\r'; break;
	    case '"': d[p++] = '"'; break;
	    case '\'': d[p++] = '\''; break;
	    case '0':
	      {
		int	nbr;
		
		readinteger(code, j, nbr);
		d[p++] = nbr & 0xFF;
	      }
	    default:
	      fprintf(stderr, "Unknown escaped character. (Line %d)\n", whichline(code, j));
	      return (false);
	    }
	  j += 1;
	}
      if (p >= len - 5)
	{
	  fprintf(stderr, "The litteral string is too long. Max is %zu. (Line %d)\n",
		  len - 5, whichline(code, j));
	  return (false);
	}
    }
  if (readtext(code, j, "\"") == false)
    return (false);
  d[p] = '\0';
  i = j;
  return (true);
}

void			writestring(std::stringstream		&ss,
				    std::string			&str)
{
  size_t		i;

  ss << "\"";
  for (i = 0; i < str.size(); ++i)
    switch (str[i])
      {
      case '\a': ss << "\\a"; break;
      case '\b': ss << "\\b"; break;
      case '\v': ss << "\\v"; break;
      case '\f': ss << "\\f"; break;
      case '\n': ss << "\\n"; break;
      case '\t': ss << "\\t"; break;
      case '\\': ss << "\\\\"; break;
      case '\r': ss << "\\r"; break;
      case '"':  ss << "\""; break;
      case '\'': ss << "'"; break;
      default:
	if (str[i] >= ' ' && str[i] <= '~')
	  ss << str[i];
	else if (str[i] == '\0')
	  ss << "\\0";
	else
	  ss << "\\0" << std::oct << ((int)str[i] & 0xFF) << std::dec;
      }
  ss << "\"";
}

bool			readvalue(const char			*code,
				  ssize_t			&i,
				  SmallConf			&nod,
				  char				endtok)
{
  char			buffer[512 * 1024];
  int			ival;
  double		val;
  int			bef;

  bef = i;
  if (readdouble(code, i, val))
    {
      nod.SetDouble(val);
      nod.original_value = std::string(&code[bef], i - bef);
    }
  else if (readinteger(code, i, ival))
    {
      nod.SetInt(ival);
      nod.original_value = std::string(&code[bef], i - bef);
    }
  else if (readstring(code, i, &buffer[0], sizeof(buffer)))
    nod.SetString(std::string(&buffer[0]));
  else if (endtok != '\0')
    {
      readrawchar(code, i, &buffer[0], sizeof(buffer), endtok);
      nod.SetString(std::string(&buffer[0]), true);
    }
  else
    return (false);
  return (true);
}

void			writevalue(std::stringstream		&ss,
				   const SmallConf		&cnf)
{
  if (cnf.last_type == SmallConf::DOUBLE)
    ss << cnf.converted;
  else if (cnf.last_type == SmallConf::INTEGER)
    ss << cnf.converted_2;
  else if (cnf.last_type == SmallConf::STRING)
    writestring(ss, cnf.original_value);
  else
    ss << cnf.original_value;
}

