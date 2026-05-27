// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		<unistd.h>
#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_display_monitored_value
 * @doc-kind function
 * @doc-module monitor
 * @doc-order 160
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Writes monitored values into a font object and draws it.
 * @description bunny_display_monitored_value prepares a textual representation of one or several monitored values, temporarily assigns it to textarea, draws the font object, then clears the string field.
 * @param textarea The font object used as the drawing area.
 * @param n The name of the monitored value to display. NULL or * displays all values. A name ending with * displays every value whose name starts with the preceding prefix.
 * @see bunny_add_monitored_value
 * @see bunny_remove_monitored_value
 * @see bunny_print_monitored_value
 *
 * @doc-lang fr
 * @brief Écrit des valeurs surveillées dans un objet font et le dessine.
 * @description bunny_display_monitored_value prépare une représentation textuelle d'une ou plusieurs valeurs surveillées, l'assigne temporairement à textarea, dessine l'objet font, puis efface le champ string.
 * @param textarea L'objet font utilisé comme zone de dessin.
 * @param n Le nom de la valeur surveillée à afficher. NULL ou * affiche toutes les valeurs. Un nom terminé par * affiche chaque valeur dont le nom commence par le préfixe précédent.
 * @see bunny_add_monitored_value
 * @see bunny_remove_monitored_value
 * @see bunny_print_monitored_value
 */
void			bunny_display_monitored_value(t_bunny_font		*f,
						      const char		*n)
{
  _bunny_monitor_prepare_buffer(&bunny_big_buffer[0], sizeof(bunny_big_buffer), n);
  f->string = &bunny_big_buffer[0];
  bunny_draw(&f->clipable);
  f->string = NULL;
}

