// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

static bool		read_inside_scope(const char			*code,
					  ssize_t			&i,
					  SmallConf			&config);

static void		read_separator(const char			*code,
				       ssize_t				&i)
{
  bool			once;

  once = true;
  skipspace(code, i);
  while (once == true)
    {
      once = false;
      while (code[i] == '\'')
	{
	  once = true;
	  while (code[i] != '\0' && code[i] != '\n' && code[i] != '\r')
	    ++i;
	  skipspace(code, i);
	}
      while (strncmp(&code[i], "[*", 2) == 0)
	{
	  once = true;
	  while (code[i] != '\0' && strncmp(&code[i], "*]", 2) != 0)
	    ++i;
	  if (code[i])
	    i += 2;
	  skipspace(code, i);
	}
    }
}

static bool		read_field_value(const char			*code,
					 ssize_t			&i,
					 SmallConf			&config)
{
  read_separator(code, i);
  if (readtext(code, i, "=") == false)
    return (true);
  read_separator(code, i);
  if (readtext(code, i, "[Scope"))
    return (read_inside_scope(code, i, config));
  if (readtext(code, i, "[Data"))
    return (read_data(code, i, config));
  if (readtext(code, i, "[Sequence"))
    return (read_sequence(code, i, config));
  if (readtext(code, i, "[Function"))
    return (read_function(code, i, config));
  if (readvalue(code, i, config, '\0') == false)
    {
      fprintf(stderr, "A data, sequence or function "
	      "scope or a value was expected after '='."
	      " (Line %d)\n", whichline(code, i));
      return (false);
    }
  read_separator(code, i);
  return (true);
}

static bool		read_inside_scope(const char			*code,
					  ssize_t			&i,
					  SmallConf			&config)
{
  char			buffer[128];
  SmallConf		*newnode;

  read_separator(code, i);
  if (read_field_value(code, i, config) == false)
    return (false);
  read_separator(code, i);
  while (code[i] != '\0' && code[i] != ']')
    {
      read_separator(code, i);
      if (readtext(code, i, "["))
	{
	  int		start;

	  read_separator(code, i);
	  if (getfieldname(code, i, &buffer[0], sizeof(buffer), config, true) == false)
	    return (false);
	  if ((newnode = &config[&buffer[0]]) == NULL)
	    return (false);
	  start = i;
	  if (read_inside_scope(code, i, *newnode) == false)
	    return (false);
	  read_separator(code, i);
	  if (readtext(code, i, "]") == false)
	    {
	      fprintf(stderr, "The ']' token was expected to close the scope. (Scope opened line %d)\n",
		      whichline(code, start));
	      return (false);
	    }
	}
      else if (readtext(code, i, "{"))
	{
	  int		start;

	  read_separator(code, i);
	  if (getfieldname(code, i, &buffer[0], sizeof(buffer), config, true) == false)
	    return (false);
	  if ((newnode = &config[&buffer[0]]) == NULL)
	    return (false);
	  start = i;
	  if (read_data(code, i, *newnode) == false)
	    return (false);
	  read_separator(code, i);
	  if (readtext(code, i, "}") == false)
	    {
	      fprintf(stderr, "The '}' token was expected to close the array. (Array opened line %d)\n",
		      whichline(code, start));
	      return (false);
	    }
	}
      else if (getfieldname(code, i, &buffer[0], sizeof(buffer), config, true))
	{
	  if ((newnode = &config[&buffer[0]]) == NULL)
	    return (false);
	  if (read_field_value(code, i, *newnode) == false)
	    return (false);
	}
      else
	{
	  fprintf(stderr, "A new scope or a field was expected. (Line %d)\n", whichline(code, i));
	  return (false);
	}
      read_separator(code, i);
    }
  return (true);
}

t_bunny_configuration	*_bunny_read_dabsic(const char			*code,
					    t_bunny_configuration	*config)
{
  ssize_t		i;
  bool			cmode = SmallConf::create_mode;

  i = 0;
  SmallConf::create_mode = true;
  do
    if (read_inside_scope(code, i, *(SmallConf*)config) == false)
      {
	SmallConf::create_mode = cmode;
	return (NULL);
      }
  while (code[i] != '\0');
  SmallConf::create_mode = cmode;
  return (config);
}

