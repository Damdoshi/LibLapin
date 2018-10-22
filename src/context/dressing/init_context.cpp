// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"
#define			PATTERN	"%p dressing character, %p configuration, %d nbr -> %s. %s"

bool			bunny_init_dressing_context_conf(t_bunny_configuration *cnf,
							 t_bunny_dressing_screen *c)
{
  (void)cnf;
  (void)c;
  /*
  const char		*missing_field;
  t_bunny_dressing_character *dchar;
  t_bunny_configuration	*chars;
  int			i;

  if ((c->nbr_characters = i = bunny_configuration_casesf(cnf, "Characters")) == 0)
    {
      missing_field = "Field 'Characters' is missing.";
      goto InvalidField;
    }
  if ((c->characters = (t_bunny_dressing_character*)
       bunny_calloc(i, sizeof(*c->characters))) == NULL)
    return (false);
  for (i = 0; bunny_configuration_getf_node(cnf, &chars, "Characters[%d]", i); ++i)
    {
      dchar = &c->characters[i];
      if (dressing_load_character(dchar, chars, i) == false)
	{
	  bunny_clear_dressing_context(c);
	  return (false);
	}
    }
  return (true);

 InvalidField:
  scream_error_if
    (return (false), EINVAL, PATTERN, "ressource,dressing",
     cnf, c, "false", missing_field);
  return (false);
  */
  return (false);
}

#undef PATTERN
#define PATTERN "%p conf, %p dressing screen -> %s. %s"

bool			bunny_init_dressing_context_file(const char	*file,
							 t_bunny_dressing_screen *c)
{
  (void)file;
  (void)c;
  /*
  t_bunny_configuration	*cnf;
  bool			ret;

  if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
    return (false);
  ret = bunny_init_dressing_context_conf(cnf, c);
  bunny_delete_configuration(cnf);
  return (ret);
  */
  return (false);
}

