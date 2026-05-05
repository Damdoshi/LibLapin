// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_loop
 * @doc-module events
 * @doc-kind function
 * @doc-order 380
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Runs the event loop for one window.
 * @description The loop dispatches registered event callbacks, calls the main loop callback at the requested frequency and calls the display callback when a refresh is needed.
 * @description If the loop callback falls behind, the scheduler may call it several times before one display callback to catch up.
 * @param win The window that produces events.
 * @param freq The requested number of main-loop callback calls per second.
 * @param dat The data pointer sent to every registered callback.
 * @return-success The t_bunny_response value that stopped the loop.
 * @log This function writes log entries in the "event" log domain through bunny_loop_mw.
 * @see bunny_loop_mw, bunny_set_loop_main_function, bunny_set_display_function
 *
 * @doc-lang fr
 * @brief Lance la boucle d'événements pour une fenêtre.
 * @description La boucle distribue les callbacks d'événements enregistrés, appelle le callback de boucle principale à la fréquence demandée et appelle le callback d'affichage lorsqu'un rafraîchissement est nécessaire.
 * @description Si le callback de boucle prend du retard, le planificateur peut l'appeler plusieurs fois avant un seul callback d'affichage afin de rattraper ce retard.
 * @param win La fenêtre qui produit les événements.
 * @param freq Le nombre d'appels au callback de boucle principale demandé par seconde.
 * @param dat Le pointeur de données transmis à tous les callbacks enregistrés.
 * @return-success La valeur t_bunny_response qui a arrêté la boucle.
 * @log Cette fonction écrit des entrées de log dans le domaine "event" via bunny_loop_mw.
 * @see bunny_loop_mw, bunny_set_loop_main_function, bunny_set_display_function
 */
t_bunny_response	bunny_loop(t_bunny_window	*window,
				   unsigned int		freq,
				   void			*data)
{
  return (bunny_loop_mw(&window, 1, freq, data));
}

