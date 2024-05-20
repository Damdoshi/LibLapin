// Jason Brillante "Damdoshi"
// EFRITS SAS 2022-2022
// Pentacle Technologie 2008-2022
// Hanged Bunny Studio 2014-2021
//
// Lapin library

#include		"lapin_private.h"

static std::string	tab_to_space(const std::string		&code)
{
  std::stringstream	ss;

  for (size_t i = 0; i < code.length(); ++i)
    if (code[i] == '\t')
      ss << "        ";
    else
      ss << code[i];
  return (ss.str());
}

static std::string	remove_space_offset(const std::string	&code)
{
  int			smallest_space = -1;
  bool			startline = true;
  int			spaces = 0;
  std::stringstream	ss;
  size_t		i;

  // On trouve l'espace le plus petit
  for (i = 0; i < code.length(); ++i)
    {
      if (startline)
	{
	  if (code[i] == ' ')
	    spaces += 1;
	  else
	    {
	      spaces = 0;
	      startline = false;
	      if (smallest_space == -1 || smallest_space > spaces)
		smallest_space = spaces;
	    }
	}
      else if (code[i] == '\n' || code[i] == '\v')
	startline = true;
    }

  spaces = 0;
  startline = true;
  for (i = 0; i < code.length(); ++i)
    {
      if (startline)
	{
	  if (code[i] == ' ')
	    {
	      if (spaces >= smallest_space)
		ss << code[i];
	      else
		spaces += 1;
	    }
	  else
	    {
	      ss << code[i];
	      spaces = 0;
	      startline = false;
	    }
	}
      else
	{
	  ss << code[i];
	  if (code[i] == '\n' || code[i] == '\n')
	    startline = true;
	}
    }
  return (ss.str());
}

bool			_bunny_resolve_text_block(SmallConf	&variable,
						  SmallConf	*root,
						  SmallConf	*local,
						  SmallConf	*artif,
						  SmallConf	*params)
{
  std::vector<SmallConf*>::iterator itv;
  std::stringstream ss;
  const char *out;

  if (!variable.was_text_block)
    return (true);
  for (itv = variable.array.begin(); itv != variable.array.end(); ++itv)
    if ((*itv)->GetString(&out, root, local, artif, params) == false)
      return (false);
    else
      ss << out;
  variable.SetString(remove_space_offset(tab_to_space(ss.str())));
  variable.array.clear();
  variable.construct = SmallConf::PLAIN;
  variable.was_text_block = false;
  return (true);
}
