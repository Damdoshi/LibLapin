// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		"lapin_private.h"

const char		*fieldname_first_char =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
const char		*fieldname =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890";
const char		*numbers =
  "1234567890";

void			skipspace_inline(const char		*str,
					 ssize_t		&i)
{
  while (str[i] && (str[i] == ' ' || str[i] == '\t'))
    ++i;
}

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

bool			readtext(const char			*str,
				 ssize_t			&index,
				 const std::string		*token,
				 size_t				len)
{
  size_t		i;

  for (i = 0; i < len && token[i] != ""; ++i)
    if (readtext(str, index, token[i].c_str()))
      return (true);
  return (false);
}

int			readlongesttext(const char		*str,
					ssize_t			&index,
					const std::string	*token,
					size_t			toklen)
{
  size_t		len, longest;
  size_t		i;

  len = 0;
  longest = 0;
  for (i = 0; i < toklen && token[i] != ""; ++i)
    if (checktext(str, index, &token[i], 1))
      {
	if (token[i].size() > len)
	  {
	    len = token[i].size();
	    longest = i;
	  }
      }
  if (len == 0)
    return (-1);
  readtext(str, index, token[longest].c_str());
  return (longest);
}

int			checklongesttext(const char		*str,
					 ssize_t		index,
					 const std::string	*token,
					 size_t			toklen)
{
  ssize_t		i = index;

  return (readlongesttext(str, i, token, toklen));
}

bool			checktext(const char			*str,
				  ssize_t			&index,
				  const std::string		*token,
				  size_t			len)
{
  size_t		i;

  for (i = 0; i < len && token[i] != ""; ++i)
    if (strncmp(&str[index], token[i].c_str(), token[i].size()) == 0)
      return (true);
  return (false);
}

bool			readtextcase(const char			*str,
				     ssize_t			&index,
				     const char			*token)
{
  size_t		l;

  if (bunny_strncasecmp(&str[index], token, l = strlen(token)) != 0)
    return (false);
  index += l;
  return (true);
}

bool			readtextcasesep(const char		*str,
					ssize_t			&index,
					const char		*token,
					const char		*forbidden)
{
  ssize_t		i, l;

  i = index;
  if (bunny_strncasecmp(&str[index], token, l = strlen(token)) != 0)
    return (false);
  i += l;
  if (readchar(str, i, forbidden))
    return (false);
  index = i;
  return (true);
}

bool			checktextcase(const char		*str,
				      ssize_t			&index,
				      const char		*token)
{
  size_t		l;

  return (bunny_strncasecmp(&str[index], token, l = strlen(token)) == 0);
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
				     bool			overwrite,
				     bool			manda)
{
  ssize_t		readlen, j;

  j = i;
  if (readfield(code, j) == false)
    {
      if (manda)
	fprintf(stderr, "A name was expected. (Line %d)\n",
		whichline(code, i));
      return (false);
    }

  if ((readlen = j - i) > buflen / 2)
    {
      if (manda)
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

  readchar(code, j, "+-");
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
  int			moved;

  moved = 0;
  if (strncmp(&code[i], "0b", 2) == 0)
    {
      d = 0;
      j += 2;
      while (code[j] == '1' || code[j] == '0')
	{
	  d <<= 1;
	  d |= (code[j] == '1') ? 1 : 0;
	  j += 1;
	}
      if (j == i + 2)
	return (false);
      i = j;
      return (true);
    }
  if (strncmp(&code[i], "0c", 2) == 0)
    {
      i += (moved = 2);
      d = strtol(&code[i], &end, 3);
    }
  else if (code[i] == 'u' || code[i] == 'x')
    {
      i += (moved = 1);
      d = strtol(&code[i], &end, 16);
    }
  else
    d = strtol(&code[i], &end, 0);
  if (end == &code[i])
    {
      i -= moved;
      return (false);
    }
  i += end - &code[i];
  return (true);
}

bool			is_in(char				c,
			      const char			*tok)
{
  size_t		i;

  for (i = 0; tok[i]; ++i)
    if (tok[i] == c)
      return (true);
  return (false);
}

bool			readrawchar(const char			*code,
				    ssize_t			&i,
				    char			*d,
				    ssize_t			len,
				    const char			*endtok)
{
  ssize_t		j;

  for (j = i; code[j] &&
	 code[j] != '\n' && code[j] != '\r'
	 && !is_in(code[j], endtok); ++j);
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
	    strncpy(&d[p++], &code[j++], 1);
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
	    case 'u':
	      {
		int	nbr;

		readinteger(code, j, nbr);
		d[p++] = nbr & 0xFF;
		j -= 1;
		break ;
	      }
	    case 'x':
	    case '0':
	      {
		int	nbr;

		readinteger(code, j, nbr);
		d[p++] = nbr & 0xFF;
		j -= 1;
		break ;
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

bool			readpath(const char			*code,
				 ssize_t			&i,
				 char				*d,
				 ssize_t			len)
{
  ssize_t		j = i;

  if (readtext(code, j, "@") == false)
    return (false);
  if (readstring(code, j, d, len) == false)
    return (false);
  i = j;
  return (true);
}

void			writestring(std::ostream		&ss,
				    const std::string		&str,
				    bool			json)
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
	else if (json)
	  {
	    char buffer[5];
	    int len = 1;

	    /* CETTE NOTATION C'EST DE LA MERDE. COMMENT ON FAIT SI ON A QU'UN CARACTERE PUTAIN?!
	      buffer[0] = 0;
	      snprintf(&buffer[0], sizeof(buffer), "%04X", (int)(str[i] & 0xFF));
	      ss << "\\u" << &buffer[0];
	    */
	    buffer[0] = str[i];
	    buffer[1] = '\0';
	    len = 1;
	    if (str[i] & 0x80)
	      {
		if ((str[i] & 0xE0) == 0xC0)
		  {
		    buffer[1] = str[i + 1];
		    buffer[2] = '\0';
		    len = 2;
		  }
		else if ((str[i] & 0xE0) == 0xC0)
		  {
		    buffer[1] = str[i + 1];
		    buffer[2] = str[i + 2];
		    buffer[3] = '\0';
		    len = 3;
		  }
		else if ((str[i] & 0xF8) == 0xF0)
		  {
		    buffer[1] = str[i + 1];
		    buffer[2] = str[i + 2];
		    buffer[3] = str[i + 3];
		    buffer[4] = '\0';
		    len = 4;
		  }
	      }
	    ss << &buffer[0];
	    i += len - 1;
	  }
	else if (str[i] == '\0')
	  ss << "\\0";
	else
	  ss << "\\0" << std::oct << ((int)str[i] & 0xFF) << std::dec;
      }
  ss << "\"";
}

bool			readaddress(const char			*addr,
				    ssize_t			&i,
				    SmallConf			&out)
{
  const char		*str;
  ssize_t		start;
  ssize_t		j;

  start = j = i;
  while (addr[i] && addr[i] != ']')
    {
      if (addr[i] == '[')
	j = i;
      else if (readchar(addr, j, fieldname) == false)
	return (false);

      while (readtext(addr, j, "["))
	{
	  i = j;
	  j = strtol(&addr[i], (char**)&str, 0);
	  if (str == &addr[i])
	    {
	      if (readaddress(addr, i, out) == false)
		return (false);
	    }
	  else
	    i += str - &addr[i];

	  if (readtext(addr, i, "]") == false)
	    return (false);
	  j = i;
	}

      if (readtext(addr, j, "->") == false
	  && readtext(addr, j, ".") == false)
	{
	  i = j;
	  break ;
	}
      i = j;
    }
  out.SetString(std::string(&addr[start], i - start), true);
  return (true);
}

bool			readvalue(const char			*code,
				  ssize_t			&i,
				  SmallConf			&nod,
				  const char			*endtok)
{
  char			buffer[512 * 1024];
  int			ival;
  double		val;
  int			bef;

  bef = i;
  if (readtext(code, i, "b64\""))
    {
      void		*out;
      size_t		outlen;

      if (bunny_read_base64(code, &i, &out, &outlen) == false)
	return (false);
      nod.construct = SmallConf::ARRAY;
      nod.was_b64 = true;
      for (size_t i = 0; i < outlen / sizeof(int); ++i)
	{
	  int		j = *(int*)out;

	  nod[i].SetInt(j);
	}
      bunny_free(out);
    }
  else if (readdouble(code, i, val))
    {
      nod.SetDouble(val);
      nod.original_value = std::string(&code[bef], i - bef);
    }
  else if (readinteger(code, i, ival))
    {
      nod.SetInt(ival);
      nod.original_value = std::string(&code[bef], i - bef);
    }
  else if (readpath(code, i, &buffer[0], sizeof(buffer)))
    {
      const char	*tmp = bunny_configuration_resolve_path(&buffer[0]);

      if (tmp == NULL)
	nod.SetString(std::string(&buffer[0]));
      else
	nod.SetString(std::string(tmp));
    }
  else if (readstring(code, i, &buffer[0], sizeof(buffer)))
    nod.SetString(std::string(&buffer[0]));
  else if (endtok != NULL)
    {
      readrawchar(code, i, &buffer[0], sizeof(buffer), endtok);
      if (strcmp(&buffer[0], "true") == 0)
	{
	  nod.SetInt(1);
	  nod.original_value = "1";
	}
      else if (strcmp(&buffer[0], "false") == 0)
	{
	  nod.SetInt(0);
	  nod.original_value = "0";
	}
      else
	nod.SetString(std::string(&buffer[0]), true);
    }
  else
    {
      if (readtext(code, i, "true"))
	{
	  nod.SetInt(1);
	  nod.original_value = "1";
	}
      else if (readtext(code, i, "false"))
	{
	  nod.SetInt(0);
	  nod.original_value = "0";
	}
      else
	return (false);
    }
  return (true);
}

void			writevalue(std::ostream			&ss,
				   const SmallConf		&cnf,
				   bool				jsonehx)
{
  if (cnf.last_type == SmallConf::DOUBLE)
    ss << cnf.converted;
  else if (cnf.last_type == SmallConf::INTEGER)
    ss << cnf.converted_2;
  else if (cnf.last_type == SmallConf::STRING)
    writestring(ss, cnf.original_value, jsonehx);
  else
    ss << cnf.original_value;
}
