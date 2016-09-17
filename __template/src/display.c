/*
** MyName
** MyCompany 1970-2017
**
** BunnyProject
*/

#include		"bunny_project.h"

t_bunny_response	bunny_project_display(const t_bunny_project	*prj)
{
  t_bunny_position	pos = {prj->bunny_position.x, prj->bunny_position.y};

  bunny_fill(&prj->window->buffer, ALPHA(64, rand()));
  bunny_blit(&prj->window->buffer, prj->bunny, &pos);
  bunny_display(prj->window);
  return (GO_ON);
}

