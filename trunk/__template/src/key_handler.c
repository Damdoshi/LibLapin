/*
** MyName
** MyCompany 1970-2017
**
** BunnyProject
*/

#include		"bunny_project.h"

t_bunny_response	bunny_project_key_handler(t_bunny_event_state	state,
						  t_bunny_keysym	sym,
						  t_bunny_project	*prj)
{
  (void)prj;
  if (state == GO_DOWN && sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

