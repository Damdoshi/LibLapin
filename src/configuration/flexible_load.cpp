// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// Lapin library

#include		"lapin_private.h"

static bool		load_node_or_file(t_bunny_configuration				*c,
					  bool						keep,
					  t_flexible_load				load,
					  void						**tar)
{
  const char		*str;

  if (bunny_configuration_getf_string(c, &str, "."))
    {
      if (bunny_which_format(str) != BC_CUSTOM)
	{
	  // Le noeud contenait un fichier de configuration
	  if (keep) // Et on a demandé a garder la configuration chargée
	    {
	      if (bunny_open_configuration(str, c) == NULL)
		return (false);
	    }
	  else // On ne veut pas garder la configuration.
	    {
	      if ((c = bunny_open_configuration(str, NULL)) == NULL)
		return (false);
	      *tar = load(c);
	      bunny_delete_configuration(c);
	      return (!!*tar);
	    }
	}
      // Le noeud contenait une valeur...
    }
  // else {} Le noeud était un noeud pur jus.

  // On charge le contenu du noeud: soit la valeur seule, soit le noeud, soit le fichier chargé
  return (!!(*tar = load(c)));
}

int			bunny_configuration_flexible_load(t_bunny_configuration		*cnf,
							  t_flexible_load_mode		mode,
							  t_flexible_load		load,
							  void				***ptr,
							  const char			*pattern,
							  ...)
{
  char			buffer[4096];
  va_list		lst;
  int			cnt;

  va_start(lst, pattern);
  vsnprintf(&buffer[0], sizeof(buffer), pattern, lst);
  if ((cnf = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    return (0);
  cnt = 0;
  if (mode == 0 || mode & FLM_LOAD_FIELD)
    cnt += 1;
  if (mode & FLM_LOAD_ARRAY)
    cnt += bunny_configuration_casesf(cnf, ".");;
  if (mode & FLM_LOAD_HASHMAP)
    cnt += bunny_configuration_childrenf(cnf, ".");;
  if ((*ptr = (void**)bunny_calloc(cnt, sizeof(*ptr))) == NULL)
    return (0);

  cnt = 0;
  if (mode == 0 || mode & FLM_LOAD_FIELD)
    {
      if (load_node_or_file(cnf, mode & FLM_KEEP_CONFIGURATION, load, &(*ptr)[cnt++]) == false)
	return (-cnt);
    }
  if (mode & FLM_LOAD_ARRAY)
    {
      t_bunny_configuration	*c;
      ssize_t			i;

      for (bunny_configuration_all_cases(cnf, i))
	{
	  bunny_configuration_getf_node(cnf, &c, "[%zd]", i);
	  if (load_node_or_file(c, mode & FLM_KEEP_CONFIGURATION, load, &(*ptr)[cnt]) == false)
	    return (-cnt);
	  cnt += 1;
	}
    }
  if (mode & FLM_LOAD_HASHMAP)
    {
      t_bunny_configuration	*c;

      for (bunny_configuration_all_children(cnf, c))
	{
	  if (load_node_or_file(c, mode & FLM_KEEP_CONFIGURATION, load, &(*ptr)[cnt]) == false)
	    return (-cnt);
	  cnt += 1;
	}
    }
  return (cnt);
}

