// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		"lapin_private.h"

/*
** Config parameters when config is full:
** first element is local variable
** second element is parameter
** before last element is node address "artif"
** last element is root
**
** when there is  asingle conf, it is often artif
*/

t_bunny_configuration	*bunny_configuration_resolve_address(t_bunny_configuration		**config,
							     size_t				nbrconfig,
							     const char				*addr,
							     ssize_t				&i)
{
  t_bunny_configuration	*cnf;
  const char		*str;
  char			buffer[4096];
  ssize_t		j;
  int			tmp;

  j = i;
  if (addr == NULL || *addr == 0 || strcmp(addr, ".") == 0)
    return ((t_bunny_configuration*)config[0]);
  
  if (strncmp(&addr[i], "@", 1) == 0 && _bunny_handle_directive(addr, i, NULL, NULL, NULL, Expression::LAST_OPERATOR_FAMILY, true) == BD_NOT_FOUND)
    {
      SmallConf		*sc;
      ssize_t		k = 0;

      if ((sc = (SmallConf*)bunny_configuration_resolve_address(config, nbrconfig, addr, ++i)) == NULL)
	return (NULL);
      bunny_configuration_execute(sc, true, NULL);
      if (sc->last_type != SmallConf::RAWSTRING)
	return (NULL);
      return (bunny_configuration_resolve_address(config, nbrconfig, sc->original_value.c_str(), k));
    }
  
  if (strncmp(&addr[i], "[]", 2) == 0)
    {
      cnf = bunny_configuration_get_root(config[nbrconfig - 1]);
      j = i += 2;
      readtext(addr, i, ".");
      j = i;
    }
  else if (strncmp(&addr[i], "[.]", 3) == 0)
    {
      for (size_t k = 0; k < nbrconfig; ++k)
	{
	  cnf = config[k];
	  while (cnf && ((SmallConf*)cnf)->local_root == false)
	    cnf = bunny_configuration_get_parent(cnf);
	  if (cnf != NULL)
	    break ;
	}
      if (cnf == NULL)
	cnf = bunny_configuration_get_root((t_bunny_configuration*)config[nbrconfig - 1]);
      j = i += 3;
      readtext(addr, i, ".");
      j = i;
    }
  else if (strncmp(&addr[i], "[#", 2) == 0)
    {
      j = i += 2;
      // Remonter jusqu'a trouver un noeud du nom donné - ou la racine
      readchar(addr, j, fieldname);
      strncpy(&buffer[0], &addr[i], j - i);
      buffer[j - i] = '\0';
      for (size_t k = 0; k < nbrconfig; ++k)
	{
	  cnf = config[k];
	  while (cnf != bunny_configuration_get_root(cnf) &&
		 strcmp(bunny_configuration_get_name(cnf), buffer))
	    cnf = bunny_configuration_get_parent(cnf);
	  if (cnf != NULL)
	    break ;
	}
      if (readtext(addr, j, "]") == false)
	return (NULL);
      readtext(addr, j, ".");
      i = j;
    }
  else
    cnf = NULL;

  while (addr[i] && addr[i] != ']')
    {
      if (addr[i] != '[')
	{
	  if (readchar(addr, j, fieldname) == false)
	    return (NULL);
	  if (j - i >= (ssize_t)sizeof(buffer) - 1)
	    return (NULL);
	  strncpy(&buffer[0], &addr[i], j - i);
	  buffer[j - i] = '\0';
	  if (strcmp(&buffer[0], "_") == 0)
	    {
	      // First element in address
	      if (cnf == NULL)
		{
		  // Get artif in ANY case
		  if (nbrconfig == 1)
		    cnf = config[0];
		  else
		    cnf = config[nbrconfig - 2];
		}
	      cnf = bunny_configuration_get_parent(cnf);
	    }
	  else
	    {
	      if (cnf == NULL)
		for (size_t k = 0; k < nbrconfig && cnf == NULL; ++k)
		  cnf = bunny_configuration_get_child(config[k], &buffer[0]);
	      else
		cnf = bunny_configuration_get_child(cnf, &buffer[0]);
	    }
	  if (cnf == NULL)
	    return (NULL);
	}
      else
	j = i;
      while (readtext(addr, j, "["))
	{
	  // Ici, ca devrait etre une lecture d'expression recursive plutot qu'un simple check de type de caractère
	  // Mais... bon. Ca va pas se changer en deux temps trois mouvements ca.
	  /// CE MANQUE EMPECHE DE FAIRE v[i + 1] PAR EXEMPLE
	  i = j;
	  j = strtol(&addr[i], (char**)&str, 0);
	  if (str == &addr[i])
	    {
	      t_bunny_configuration *sub;

	      if ((sub = bunny_configuration_resolve_address(config, nbrconfig, addr, i)) == NULL)
		return (NULL);
	      else if (bunny_configuration_get_int(sub, &tmp))
		{
		  if ((cnf = bunny_configuration_get_case(cnf, tmp)) == NULL)
		    return (NULL);
		}
	      else if (bunny_configuration_get_string(sub, &str))
		{
		  if ((cnf = bunny_configuration_get_child(cnf, str)) == NULL)
		    return (NULL);
		}
	      else
		return (NULL);
	      /*
	      for (j = i, tmp = 1; addr[j] && (i == j || tmp != 0); ++j)
		if (addr[j] == '[')
		  tmp += 1;
		else if (addr[j] == ']')
		  tmp -= 1;
	      if (tmp == 0)
		i = j - 1;
	      else
		i = j;
	      */
	    }
	  else
	    {
	      if (cnf == NULL)
		{
		  // Get artif in ANY case
		  if (nbrconfig == 1)
		    cnf = config[0];
		  else
		    cnf = config[nbrconfig - 2];
		}
	      if ((cnf = bunny_configuration_get_case(cnf, j)) == NULL)
		return (NULL);
	      i += str - &addr[i];
	    }
	  if (readtext(addr, i, "]") == false)
	    return (NULL);
	  j = i;
	}
      if (readtext(addr, j, "->"))
	{
	  if (bunny_configuration_get_string(cnf, &str) == false)
	    return (NULL);
	  cnf = bunny_configuration_get_root(config[nbrconfig - 1]);
	  ssize_t k = 0;
	  if ((cnf = bunny_configuration_resolve_address(&cnf, 1, str, k)) == NULL)
	    return (NULL);
	}
      else if (readtext(addr, j, ".") == false)
	{
	  i = j;
	  return (cnf);
	}
      i = j;
    }
  return (cnf);
}
