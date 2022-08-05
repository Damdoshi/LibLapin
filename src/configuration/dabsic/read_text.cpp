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
** = [Text($,EOF,COM)   texte COM c'est du commentaire\n $(expression) texte EOF] <=== A FAIRE
**
** Cette fonction est à refaire: l'adjonction des paramètres entre parenthèses
** sont une bonne idée, mais c'est fait à l'arrache et du coup difficile à modifier
*/

Decision		dabsic_read_text(const char		*code,
					 ssize_t		&i,
					 SmallConf		&conf,
					 SmallConf		&root)
{
  char			buf[9];
  char			tok[9];
  // Ca serait bien de pouvoir etablir un token pour des commentaires inlines
  ssize_t		j, k, l;

  tok[0] = '\0';
  dabsic_read_separator(code, i);
  if (readtext(code, i, "[Text") == false)
    return (BD_NOT_FOUND);
  dabsic_read_separator(code, i);
  if (readtext(code, i, "(") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token '(' was expected to specify the terminator of the Textscope on line %s:%d",
       "ressource,configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  j = i;
  while (code[i] && i - j < (int)sizeof(buf) - 1 && !checktext(code, i, ")") && !checktext(code, i, ","))
    i += 1;
  if (i - j >= (int)sizeof(buf) - 1)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token ')' was expected to close the text terminator specification at maximum %d chars from start on line %s:%d",
       "ressource,configuration,syntax",
       sizeof(buf) - 1,
       SmallConf::file_read.top().c_str(), whichline(code, j)
       );
  if (checktext(code, i, ","))
    {
      strncpy(&tok[0], &code[j], i - j);
      tok[i - j] = '\0';
      readtext(code, i, ",");
      dabsic_read_separator(code, i);
      j = i;
      while (code[i] && i - j < (int)sizeof(buf) - 1 && !checktext(code, i, ")"))
	i += 1;
      if (i - j >= (int)sizeof(buf) - 1)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "The token ')' was expected to close the text terminator specification at maximum %d chars from start on line %s:%d",
	   "ressource,configuration,syntax",
	   sizeof(buf) - 1,
	   SmallConf::file_read.top().c_str(), whichline(code, j)
	   );
    }
  strncpy(&buf[0], &code[j], i - j);
  buf[i - j] = '\0';
  if (readtext(code, i, ")") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token ')' was expected to close the text terminator specification at maximum %d chars from start on line %s:%d",
       "ressource,configuration,syntax",
       sizeof(buf) - 1,
       SmallConf::file_read.top().c_str(), whichline(code, j)
       );
  k = i;

  // On avance au premier caractère
  int			index;

  index = 0;
  // On arrive au début de la première ligne non vide du bloc
  readchar(code, i, "\n\v");
  l = i;
  while (code[i] && readtext(code, i, &buf[0]) == false)
    {
      if (tok[0] && readtext(code, i, &tok[0]))
	{
	  if (readtext(code, i, "(") == false)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "The token '(' was expected after the variable insertion token on line %s:%d",
	       "ressource,configuration,syntax", SmallConf::file_read.top().c_str(), whichline(code, j)
	       );
	  // On enregistre ce qu'on a deja parcouru
	  conf[index++].SetString(std::string(&code[l], i - l - 1 - strlen(tok)));
	  if (dabsic_read_litterals(code, i, conf[index++], root, true) == BD_ERROR) // true: shrink
	    return (BD_ERROR);
	  if (readtext(code, i, ")") == false)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "The token ')' was expected after the variable insertion token and its expression on line %s:%d",
	       "ressource,configuration,syntax", SmallConf::file_read.top().c_str(), whichline(code, j)
	       );
	  l = i;
	}
      else
	i = i + 1;
    }
  if (!code[i])
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token '%s' was expected to close the text start on line %s:%d",
       "ressource,configuration,syntax", &buf[0],
       SmallConf::file_read.top().c_str(), whichline(code, j)
       );
  if (l != i)
    conf[index].SetString(std::string(&code[l], i - l - strlen(buf)));

  dabsic_read_separator(code, i);
  if (readtext(code, i, "]") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token ']' was expected to close the Text scope on line %s:%d",
       "ressource,configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  conf.was_text_block = true;
  dabsic_read_separator(code, i);
  return (BD_OK);
}

