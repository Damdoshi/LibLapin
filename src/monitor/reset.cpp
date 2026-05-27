// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_reset_stored_monitored_value
 * @doc-kind function
 * @doc-module monitor
 * @doc-order 155
 * @doc-since 13
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Clears the stored history of every monitored variable.
 * @description bunny_reset_stored_monitored_value removes the values accumulated by bunny_store_monitored_value while keeping the monitored variables registered.
 * @see bunny_store_monitored_value
 * @see bunny_remove_monitored_value
 *
 * @doc-lang fr
 * @brief Efface l'historique stocké de chaque variable surveillée.
 * @description bunny_reset_stored_monitored_value retire les valeurs accumulées par bunny_store_monitored_value tout en conservant les variables surveillées enregistrées.
 * @see bunny_store_monitored_value
 * @see bunny_remove_monitored_value
 */
void			bunny_reset_stored_monitored_value(void)
{
  std::map<std::string, struct bunny_monitored_value>::iterator it;

  for (it = gl_monitor.begin(); it != gl_monitor.end(); ++it)
    {
      it->second.ihistory.clear();
      it->second.dhistory.clear();
      it->second.shistory.clear();
    }
}

