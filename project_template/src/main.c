/*
** MyName
** MyCompany 1970-2017
**
** BunnyProject
*/

#include			<string.h>
#include			<stdio.h>
#include			"bunny_project.h"

static void			binary_directory(char	*relative_path)
{
  size_t			i;

  for (i = strlen(relative_path); i && relative_path[i] != '/'; --i);
  relative_path[i] = '\0';
  if (chdir(relative_path) == -1)
    {
      perror(&relative_path[i + 1]);
      exit(EXIT_FAILURE);
    }
}

int				main(int		argc,
				     char		**argv)
{
  /* Static in order to put the structure on the heap, in case it is big */
  static t_bunny_project	project;
  const t_bunny_position	*screen;
  t_bunny_response		response;

  (void)argc;
  binary_directory(argv[0]);
  screen = bunny_get_screen_resolution();
  if ((project.window = bunny_start(screen->x, screen->y, true, BUNNY_TITLE)) == NULL)
    {
      bunny_printlerr("Failed to open the window.");
      return (EXIT_FAILURE);
    }
  if ((project.bunny = bunny_load_picture("lapin_noir.png")) == NULL)
    {
      bunny_printlerr("Failed to load bunny.png");
      bunny_stop(project.window);
      return (EXIT_FAILURE);
    }

  project.bunny->scale.x = project.bunny->scale.y = 16.0;
  project.bunny->origin.x = project.bunny->buffer.width / 2;
  project.bunny->origin.y = project.bunny->buffer.height / 2;
  project.bunny_position.x = project.window->buffer.width / 2;
  project.bunny_position.y = project.window->buffer.height / 2;

  do
    {
      bunny_set_context((t_bunny_context*)&bunny_project_context[project.context]);
      response = bunny_loop(project.window, BUNNY_FREQUENCY, &project);
    }
  while (response == SWITCH_CONTEXT);
  bunny_stop(project.window);
  return (EXIT_SUCCESS);
}

