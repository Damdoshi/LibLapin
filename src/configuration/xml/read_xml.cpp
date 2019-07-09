// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static t_bunny_decision	xml_read_doctype(const char			*code,
					 ssize_t			&i)
{
  xml_read_separator(code, i);
  if (readtext(code, i, "<?xml") == false)
    return (BD_OK);
  while (code[i] && !readtext(code, i, "?>"))
    i += 1;
  if (!code[i])
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "Opening XML markup is not closed on line %s:%d",
       "configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  xml_read_separator(code, i);
  return (BD_OK);
}

t_bunny_configuration	*_bunny_read_xml(const char			*code,
					 t_bunny_configuration		*config)
{
  SmallConf		*conf = (SmallConf*)config;
  ssize_t		i;
  bool			cmode = SmallConf::create_mode;

  i = 0;
  SmallConf::create_mode = true;
  conf->construct = SmallConf::MAP;
  if (xml_read_doctype(code, i) != BD_OK)
    {
      SmallConf::create_mode = cmode;
      return (NULL);
    }
  if (xml_read_between_markup(code, i, *conf, *conf) != BD_OK)
    {
      SmallConf::create_mode = cmode;
      return (NULL);
    }
  SmallConf::create_mode = cmode;
  scream_log_if("%s code, %p config -> %p", "configuration", code, config, config);
  return (config);
}

