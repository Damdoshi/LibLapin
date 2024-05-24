// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

/*
** = [Text    texte    ]
** = [Text($)    texte   $(expression)  texte       ]
** = [Text($,EOF)    texte   $(expression)  texte       EOF]
** = [Text($,EOF,COM)   texte COM c'est du commentaire\n $(expression) texte EOF]
**
** Cette fonction est à refaire: l'adjonction des paramètres entre parenthèses
** sont une bonne idée, mais c'est fait à l'arrache et du coup difficile à modifier
*/

Decision		dabsic_read_text_cont(const char	*code,
					      ssize_t		&i,
					      SmallConf		&conf,
					      SmallConf		&root,
					      std::string	vartok,
					      std::string	eoftok,
					      std::string	comtok)
{
  vartok += "(";
  int			index = 0;
  int			l;

  readchar(code, i, "\n\v");
  l = i;
  while (code[i] && (eoftok == "" || !readtext(code, i, eoftok.c_str())))
    {
      // On a trouvé une variable
      if (vartok != "" && readtext(code, i, vartok.c_str()))
	{
	  conf[index++].SetString(std::string(&code[l], i - l - vartok.size()));
	  if (dabsic_read_litterals(code, i, conf[index++], root, true) == BD_ERROR)
	    return (BD_ERROR);
	  if (readtext(code, i, ")") == false)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "The token ')' was expected after the variable insertion token and its expression on line %s:%d",
	       "ressource,configuration,syntax", SmallConf::file_read.top().c_str(), whichline(code, i)
	       );
	  l = i;
	}
      // On a trouvé un commentaire inline
      else if (comtok != "" && readtext(code, i, comtok.c_str()))
	{
	  // On enregistre ce qu'on a deja parcou
	  conf[index++].SetString(std::string(&code[l], i - l - 1 - comtok.size()));
	  while (code[i] && code[i] != '\n')
	    i += 1;
	  while (code[i] == '\n')
	    i += 1;
	  l = i;
	}
      else
	i = i + 1;
    }

  if (!code[i] && eoftok != "")
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token '%s' was expected to close the text start on line %s:%d",
       "ressource,configuration,syntax", eoftok.c_str(),
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  if (l != i)
    conf[index].SetString(std::string(&code[l], i - l - eoftok.size()));
  return (BD_OK);
}


Decision		dabsic_read_text_conf(const char	*code,
					      ssize_t		&i,
					      std::string	&vartok,
					      std::string	&eoftok,
					      std::string	&comtok)
{
  std::string		*toks[3] = {&vartok, &eoftok, &comtok};
  char			buffer[128];
  int			j, k;
  int			tok;

  for (tok = 0; tok < NBRCELL(toks); ++tok)
    {
      for (k = i; code[k] && code[k] != ')' && code[k] != ','; ++k);
      if (!code[k])
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "The token ')' was expected to close the text terminator specification "
	   "chars on line %s:%d",
	   "ressource,configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, k)
	   );
      if (k - i > NBRCELL(buffer))
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "The configurable token for Text is too long."
	   "Maximum is %d on line %s:%d",
	   "ressource,configuration,syntax",
	   NBRCELL(buffer),
	   SmallConf::file_read.top().c_str(), whichline(code, k)
	   );
      strncpy(buffer, &code[i], k - i);
      buffer[k - i] = '\0';
      i = k;
      for (j = 0; buffer[j] && isspace(buffer[j]); ++j);
      if (!buffer[j])
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "Configurable token for Text scope is empty "
	   "on line %s:%d",
	   "ressource,configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, k)
	   );
      for (k = j; buffer[k] && !isspace(buffer[k]); ++k);
      toks[tok]->assign(&buffer[j], k - j);
      if (code[i] == ')')
	return (BD_OK);
      i += 1;
      dabsic_read_separator(code, i);
    }
  return (BD_OK);
}



Decision		dabsic_read_text(const char		*code,
					 ssize_t		&i,
					 SmallConf		&conf,
					 SmallConf		&root)
{
  std::string		vartok;
  std::string		eoftok;
  std::string		comtok;
  // Ca serait bien de pouvoir etablir un token pour des commentaires inlines

  dabsic_read_separator(code, i);
  if (readtext(code, i, "[Text") == false)
    return (BD_NOT_FOUND);
  dabsic_read_separator(code, i);

  if (readtext(code, i, "("))
    {
      if (dabsic_read_text_conf(code, i, vartok, eoftok, comtok) == BD_ERROR)
	return (BD_ERROR);
      if (!readtext(code, i, ")"))
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "The token ')' was expected to close the text terminator specification "
	   "on line %s:%d",
	   "ressource,configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
    }

  eoftok = eoftok + "]";
  if ((vartok != "" && (vartok == eoftok || vartok == comtok)) ||
      (eoftok != "" && (vartok == eoftok || eoftok == comtok)) ||
      (comtok != "" && (vartok == comtok || eoftok == comtok)))
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "Configurable token in Text block specification cannot be identical "
       "on line %s:%d",
       "ressource,configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );  
  if (dabsic_read_text_cont(code, i, conf, root, vartok, eoftok, comtok) == BD_ERROR)
    return (BD_ERROR);
  dabsic_read_separator(code, i);
  conf.was_text_block = true;
  return (BD_OK);
}

