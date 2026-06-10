// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin Library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_store_monitored_value
 * @doc-kind function
 * @doc-module monitor
 * @doc-order 150
 * @doc-since 13
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Stores the current value of every monitored variable in its history.
 * @description bunny_store_monitored_value snapshots all registered monitored values. Later calls to bunny_display_monitored_value or bunny_print_monitored_value display the stored history before the current value.
 * @see bunny_reset_stored_monitored_value
 * @see bunny_display_monitored_value
 * @see bunny_print_monitored_value
 *
 * @doc-lang fr
 * @brief Stocke la valeur courante de chaque variable surveillée dans son historique.
 * @description bunny_store_monitored_value capture toutes les valeurs surveillées enregistrées. Les appels ultérieurs à bunny_display_monitored_value ou bunny_print_monitored_value affichent l'historique stocké avant la valeur courante.
 * @see bunny_reset_stored_monitored_value
 * @see bunny_display_monitored_value
 * @see bunny_print_monitored_value
 */
void			bunny_store_monitored_value(void)
{
  std::map<std::string, struct bunny_monitored_value>::iterator it;

  for (it = gl_monitor.begin(); it != gl_monitor.end(); ++it)
    switch (it->second.type)
      {
      case BMT_INTEGER:
	it->second.ihistory.push_back(*(int*)it->second.data);
	break ;
      case BMT_DOUBLE:
	it->second.dhistory.push_back(*(double*)it->second.data);
	break ;
      case BMT_STRING:
	it->second.shistory.push_back((const char*)it->second.data);
	break ;
      }
}

