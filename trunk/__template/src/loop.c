/*
** MyName
** MyCompany 1970-2017
**
** BunnyProject
*/

#include		"bunny_project.h"

t_bunny_response	bunny_project_loop(t_bunny_project	*prj)
{
  if (bunny_get_keyboard()[BKS_LEFT])
    {
      if ((prj->bunny_position.x -= bunny_move_speed) < 0)
	prj->bunny_position.x = 0;
      prj->bunny->rotation -= bunny_rot_speed;
    }
  if (bunny_get_keyboard()[BKS_RIGHT])
    {
      if ((prj->bunny_position.x += bunny_move_speed) > prj->window->buffer.width)
	prj->bunny_position.x = prj->window->buffer.width;
      prj->bunny->rotation += bunny_rot_speed;
    }
  if (bunny_get_keyboard()[BKS_UP])
    {
      if ((prj->bunny_position.y -= bunny_move_speed) < 0)
	prj->bunny_position.y = 0;
    }
  if (bunny_get_keyboard()[BKS_DOWN])
    {
      if ((prj->bunny_position.y += bunny_move_speed) > prj->window->buffer.height)
	prj->bunny_position.y = prj->window->buffer.height;
    }
  return (GO_ON);  
}

