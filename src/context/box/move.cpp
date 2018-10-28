// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_box_move(t_bunny_position		rel,
				       void			*data);


static t_bunny_response	search_box(void				*data,
				   t_bunny_gui_box		*box,
				   t_bunny_position		pos)
{
  t_bunny_gui_box	*fnd;

  if (pos.x < box->position.x ||
      pos.y < box->position.y ||
      pos.x > box->position.x + box->size.x ||
      pos.y > box->position.y + box->size.y)
    return (GO_ON);
  pos.x -= box->position.x;
  pos.y -= box->position.y;

  if ((fnd = bunny_fetch_box(box, &pos)) == NULL)
    {
      if (box->mouse_move)
	return (box->mouse_move(pos, (t_bunny_box_system*)data, box));
      return (GO_ON);
    }
  return (search_box(data, fnd, pos));
}

t_bunny_response	bunny_box_move(const t_bunny_position	*rel,
				       void			*data)
{
  const t_bunny_position *mpos = bunny_get_mouse_position();
  t_bunny_box_system	*box = (t_bunny_box_system*)data;
  t_bunny_gui_box	*x = &box->screen;
  t_bunny_response	ret;

  (void)rel;
  if ((ret = search_box(data, x, *mpos)) != GO_ON)
    return (ret);

  if (box->head.subcontext.move)
    if ((ret = box->head.subcontext.move(mpos, data)) != GO_ON)
      return (ret);
  if (box->subhead)
    if ((ret = box->subhead->subcontext.move(mpos, data)) != GO_ON)
      return (ret);
  return (GO_ON);
}

