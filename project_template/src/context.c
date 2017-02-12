/*
** MyName
** MyCompany 1970-2017
**
** BunnyProject
*/

#include			"bunny_project.h"

const
t_bunny_anonymous_context	bunny_project_context[CONTEXT_COUNT] =
  {
    {
      .key = bunny_project_key_handler,
      .loop = bunny_project_loop,
      .display = bunny_project_display
    }
  };

