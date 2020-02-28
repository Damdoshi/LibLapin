// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_text(const char		*code,
					 ssize_t		&i,
					 SmallConf		&conf,
					 SmallConf		&root)
{
  char			buf[9];
  ssize_t		j, k, l;

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
  while (code[i] && i - j < 8 && !readtext(code, i, ")"))
    i += 1;
  if (i - j >= 8)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token ')' was expected to close the text terminator specification at maximum 8 chars from start on line %s:%d",
       "ressource,configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, j)
       );
  strncpy(&buf[0], &code[j], i - j - 1);
  buf[i - j - 1] = '\0';
  k = i;

  // On avance au premier caractère
  dabsic_read_separator(code, i);
  l = i;
  while (code[i] && strncmp(&code[i], &buf[0], k - j - 1) != 0)
    i = i + 1;
  if (!code[i])
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token '%s' was expected to close the text start on line %s:%d",
       "ressource,configuration,syntax", &buf[0],
       SmallConf::file_read.top().c_str(), whichline(code, j)
       );
  conf.SetString(std::string(&code[l], i - l - 1));

  i += k - j - 1;
  dabsic_read_separator(code, i);
  if (readtext(code, i, "]") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token ']' was expected to close the Text scope on line %s:%d",
       "ressource,configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  dabsic_read_separator(code, i);
  return (BD_OK);
}

