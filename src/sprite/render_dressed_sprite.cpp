// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#warning MEILLEUR DESIGN DE RENDER DRESSED SPRITE
/*
** Afin d'éviter d'avoir a respecter le formalisme (et pour économiser de l'espace)
** il faudrait pouvoir coller vetement par vetement correctement sur la sprite de base
** chaque vetement.
** Eventuellement, cela pourrait etre configuré et le comportement actuel (blit complet)
** pourrait etre un comportement en cas de defaut de champ de configuration requis
*/

void			merge_clothe(t_bunny_map		*nod,
				     void			*pnw)
{
  struct bunny_sprite	_clipable;
  t_bunny_clipable	*clipable = (t_bunny_clipable*)&_clipable;
  t_bunny_clothe	*clothe = bunny_map_data(nod, t_bunny_clothe*);
  t_bunny_sprite	*nw = (t_bunny_sprite*)pnw;
  t_bunny_position	pos = {0, 0};

  if (!clothe || !nw)
    return ;

  // Test if the clothe follow the organization of the base sprite
  if (1)
    {
      bunny_clipable_copy(clipable, &clothe->sprite->clipable);

      clothe->sprite->clipable.clip_x_position = 0;
      clothe->sprite->clipable.clip_y_position = 0;
      clothe->sprite->clipable.clip_width = clothe->sprite->clipable.buffer.width;
      clothe->sprite->clipable.clip_height = clothe->sprite->clipable.buffer.height;
      bunny_blit(&nw->clipable.buffer, &clothe->sprite->clipable, &pos);
      bunny_draw(&nw->clipable);

      bunny_clipable_copy(&clothe->sprite->clipable, clipable);
    }
  // The clothe does not follow the organization: it must be blitted part by part
  else
    {
      //
    }
}

t_bunny_sprite		*bunny_render_dressed_sprite(t_bunny_dressed_sprite	*sprite)
{
  t_bunny_sprite	*nw;

  bunny_draw(&sprite->sprite.clipable);
  if ((nw = bunny_duplicate_sprite(&sprite->sprite)) == NULL)
    return (NULL);
  bunny_map_foreach(sprite->clothes, merge_clothe, nw);
  return (nw);
}

