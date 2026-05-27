// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p plugin, %s function name, %p target for return value, %zu parameter array length, %p parameters -> %s"

/**
 * @doc
 * @doc-symbol bunny_plugin_call
 * @doc-kind function
 * @doc-module plugin
 * @doc-order 220
 * @doc-since 12
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Calls a function exposed by a bunny plugin.
 * @description bunny_plugin_call searches funcname in plugin, checks that arrlen matches the function prototype, calls the function with the values stored in val and writes the returned value into return_value.
 * @param plugin The dynamic library that is supposed to contain funcname.
 * @param funcname The name of the function to call.
 * @param return_value The address where the returned value must be stored. Its meaningful field depends on the prototype return type.
 * @param arrlen The number of elements in val.
 * @param val The array of parameters to pass to funcname.
 * @return-case success On $Bsuccess@, returns true after the function was found and called.
 * @return-case failure On $Bfailure@, returns false if funcname cannot be found or if arrlen does not match the registered prototype.
 * @error EINVAL funcname cannot be found inside plugin, or arrlen does not match the registered prototype.
 * @log "plugin"
 * @see t_bunny_plugin
 * @see t_bunny_value
 * @see bunny_plugin_callv
 * @see bunny_plugin_get_function
 *
 * @doc-lang fr
 * @brief Appelle une fonction exposée par un plugin bunny.
 * @description bunny_plugin_call recherche funcname dans plugin, vérifie que arrlen correspond au prototype de la fonction, appelle la fonction avec les valeurs stockées dans val et écrit la valeur renvoyée dans return_value.
 * @param plugin La bibliothèque dynamique supposée contenir funcname.
 * @param funcname Le nom de la fonction à appeler.
 * @param return_value L'adresse où stocker la valeur renvoyée. Son champ significatif dépend du type de retour du prototype.
 * @param arrlen Le nombre d'éléments dans val.
 * @param val Le tableau de paramètres à transmettre à funcname.
 * @return-case success En cas de $Bsuccès@, renvoie true après que la fonction a été trouvée et appelée.
 * @return-case failure En cas d'$Béchec@, renvoie false si funcname est introuvable ou si arrlen ne correspond pas au prototype enregistré.
 * @error EINVAL funcname est introuvable dans plugin, ou arrlen ne correspond pas au prototype enregistré.
 * @log "plugin"
 * @see t_bunny_plugin
 * @see t_bunny_value
 * @see bunny_plugin_callv
 * @see bunny_plugin_get_function
 */
bool			bunny_plugin_call(t_bunny_plugin		*plugin,
					  const char			*func,
					  t_bunny_value			*return_value,
					  size_t			arrlen,
					  t_bunny_value			*params)
{
  size_t		i;

  for (i = 0; i < plugin->nbr_functions; ++i)
    if (strcmp(plugin->prototypes[i].name, func) == 0)
      {
	if (plugin->prototypes[i].nbr_parameters != arrlen)
	  scream_error_if(return (false), EINVAL, PATTERN " (Invalid array length)",
			  "plugin",
			  plugin, func, return_value, arrlen, params, "false");
	_real_call(&plugin->prototypes[i], return_value, arrlen, params);
	scream_log_if
	  (PATTERN, "plugin", plugin, func, return_value, arrlen, params, "true");
	return (true);
      }
  scream_error_if(return (false), EINVAL, PATTERN " (Cannot find function name)",
		  "plugin", plugin, func, return_value, arrlen, params, "false");
  return (false);
}
