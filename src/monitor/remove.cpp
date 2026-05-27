// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_remove_monitored_value
 * @doc-kind function
 * @doc-module monitor
 * @doc-order 140
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Removes a value from the debug monitor.
 * @description bunny_remove_monitored_value removes a value previously registered with bunny_add_monitored_value or _bunny_add_monitored_value.
 * @param name The name of the monitored value to remove. NULL removes all monitored values.
 * @return-case success On $Bsuccess@, returns true.
 * @return-case failure On $Bfailure@, returns false when name is not NULL and no matching value exists.
 * @error BE_CANNOT_FIND_ELEMENT The monitored value cannot be found.
 * @see bunny_add_monitored_value
 * @see _bunny_add_monitored_value
 * @see bunny_display_monitored_value
 * @see bunny_print_monitored_value
 *
 * @doc-lang fr
 * @brief Retire une valeur du moniteur de débogage.
 * @description bunny_remove_monitored_value retire une valeur précédemment enregistrée avec bunny_add_monitored_value ou _bunny_add_monitored_value.
 * @param name Le nom de la valeur surveillée à retirer. NULL retire toutes les valeurs surveillées.
 * @return-case success En cas de $Bsuccès@, renvoie true.
 * @return-case failure En cas d'$Béchec@, renvoie false lorsque name n'est pas NULL et qu'aucune valeur correspondante n'existe.
 * @error BE_CANNOT_FIND_ELEMENT La valeur surveillée est introuvable.
 * @see bunny_add_monitored_value
 * @see _bunny_add_monitored_value
 * @see bunny_display_monitored_value
 * @see bunny_print_monitored_value
 */
bool			bunny_remove_monitored_value(const char		*name)
{
  std::map<std::string, struct bunny_monitored_value>::iterator		it;

  if (name == NULL)
    {
      gl_monitor.clear();
      return (true);
    }
  if ((it = gl_monitor.find(std::string(name))) == gl_monitor.end())
    {
      bunny_errno = BE_CANNOT_FIND_ELEMENT;
      return (false);
    }
  gl_monitor.erase(it);
  return (true);
}

