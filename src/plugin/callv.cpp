// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p plugin, %s function name, %p target for return value -> %s"

/**
 * @doc
 * @doc-symbol bunny_plugin_callv
 * @doc-kind function
 * @doc-module plugin
 * @doc-order 240
 * @doc-since 12
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Calls a function exposed by a bunny plugin with variadic parameters.
 * @description bunny_plugin_callv is a convenience wrapper around bunny_plugin_call. It finds funcname in plugin, reads the variadic arguments according to the registered prototype and stores the returned value into return_value.
 * @description Prefer bunny_plugin_call when possible: the variadic interface can hide a parameter count mistake because the count is taken from the registered prototype.
 * @param plugin The dynamic library that is supposed to contain funcname.
 * @param funcname The name of the function to call.
 * @param return_value The address where the returned value must be stored. Its meaningful field depends on the prototype return type.
 * @param ... The parameters to send to funcname. BVT_DOUBLE parameters are read as double; other parameters are read as size_t-sized values and copied into t_bunny_value.
 * @return-case success On $Bsuccess@, returns true after the function was found and called.
 * @return-case failure On $Bfailure@, returns false if funcname cannot be found.
 * @error EINVAL funcname cannot be found inside plugin.
 * @log "ressource,plugin"
 * @see t_bunny_plugin
 * @see t_bunny_value
 * @see bunny_plugin_call
 * @see bunny_plugin_get_function
 *
 * @doc-lang fr
 * @brief Appelle une fonction exposée par un plugin bunny avec des paramètres variadiques.
 * @description bunny_plugin_callv est un assistant autour de bunny_plugin_call. Elle recherche funcname dans plugin, lit les arguments variadiques selon le prototype enregistré et stocke la valeur renvoyée dans return_value.
 * @description Préférez bunny_plugin_call lorsque c'est possible : l'interface variadique peut masquer une erreur de nombre de paramètres, car le nombre est tiré du prototype enregistré.
 * @param plugin La bibliothèque dynamique supposée contenir funcname.
 * @param funcname Le nom de la fonction à appeler.
 * @param return_value L'adresse où stocker la valeur renvoyée. Son champ significatif dépend du type de retour du prototype.
 * @param ... Les paramètres à transmettre à funcname. Les paramètres BVT_DOUBLE sont lus comme double ; les autres paramètres sont lus comme des valeurs de taille size_t puis copiés dans t_bunny_value.
 * @return-case success En cas de $Bsuccès@, renvoie true après que la fonction a été trouvée et appelée.
 * @return-case failure En cas d'$Béchec@, renvoie false si funcname est introuvable.
 * @error EINVAL funcname est introuvable dans plugin.
 * @log "ressource,plugin"
 * @see t_bunny_plugin
 * @see t_bunny_value
 * @see bunny_plugin_call
 * @see bunny_plugin_get_function
 */
bool			bunny_plugin_callv(t_bunny_plugin		*plugin,
					   const char			*func,
					   t_bunny_value		*return_value,
					   ...)
{
  va_list		lst;
  size_t		ptr;
  double		rel;
  t_bunny_value		val
    [sizeof(plugin->prototypes[0].parameters) / sizeof(t_bunny_value_type)];
  size_t		i, j;
  size_t		len;

  va_start(lst, return_value);
  for (i = 0; i < plugin->nbr_functions; ++i)
    if (strcmp(plugin->prototypes[i].name, func) == 0)
      {
	for (j = 0, len = plugin->prototypes[i].nbr_parameters; j < len; ++j)
	  {
	    if (plugin->prototypes[i].parameters[j] == BVT_DOUBLE)
	      {
		rel = va_arg(lst, double);
		val[j].real = rel;
	      }
	    else
	      {
		ptr = va_arg(lst, size_t);
		memcpy(&val[j], &ptr, sizeof(val[j]));
	      }
	  }
	va_end(lst);
	_real_call(&plugin->prototypes[i], return_value, len, &val[0]);
	scream_log_if(PATTERN, "ressource,plugin", plugin, func, return_value, "true");
	return (true);
      }
  va_end(lst);
  scream_error_if(return (false), EINVAL, PATTERN " (Cannot find function name)",
		  "ressource,plugin", plugin, func, return_value, "false");
  return (false);
}

