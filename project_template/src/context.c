/*
** MyName
** MyCompany 1970-2017
**
** BunnyProject
*/

#include			"bunny_project.h"

bunny_declare_context(main_screen);

const
t_bunny_anonymous_context	bunny_project_context[CONTEXT_COUNT] =
  {
    {
      .key = main_screen_key,
      .loop = main_screen_loop,
      .display = main_screen_display
    }
  };

