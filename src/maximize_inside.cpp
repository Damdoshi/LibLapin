// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_maximize_inside
 * @doc-kind function
 * @doc-module placement
 * @doc-order 500
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Scales and centers a clipable so it fits inside another clipable.
 * @param to_resize The clipable to resize.
 * @param container The clipable that defines the available area.
 * @return-case success The resized clipable is modified in place.
 * @see t_bunny_position, t_bunny_area
 *
 * @doc-lang fr
 * @brief Agrandit et centre un clipable pour qu'il tienne dans un autre clipable.
 * @param to_resize Le clipable à redimensionner.
 * @param container Le clipable qui définit la zone disponible.
 * @return-case success Le clipable redimensionné est modifié en place.
 * @see t_bunny_position, t_bunny_area
 */

void			bunny_maximize_inside(t_bunny_clipable		*tr,
					      const t_bunny_clipable	*cn)
{
  tr->scale.x = (double)cn->buffer.width / tr->buffer.width;
  tr->scale.y = (double)cn->buffer.height / tr->buffer.height;

  tr->scale.x = (int)tr->scale.x;
  tr->scale.y = (int)tr->scale.y;

  if (tr->scale.x < tr->scale.y)
    tr->scale.y = tr->scale.x;
  else
    tr->scale.x = tr->scale.y;

  tr->position.x = cn->buffer.width / 2.0;
  tr->position.y = cn->buffer.height / 2.0;
  tr->origin.x = tr->buffer.width / 2.0;
  tr->origin.y = tr->buffer.height / 2.0;
}

