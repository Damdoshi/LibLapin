// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		"lapin_private.h"

t_bunny_response	bunny_cinematic(t_bunny_cinematic		*_cin,
					t_bunny_cinematic_event		event,
					double				elapsed)
{
  struct bunny_cinematic *cin = (struct bunny_cinematic*)_cin;
  SmallConf		&scnf = *(SmallConf*)cin->program;
  Sequence		&seq = *scnf.sequence;
  t_bunny_configuration	*argv[128];
  size_t		argc;

  if (seq.lines.size() <= cin->current_command)
    return (EXIT_ON_SUCCESS);

  for (argc = 0;
       argc < seq.lines[cin->current_command].nbr_parameters
	 && argc < NBRCELL(argv) - 1
	 ;
       ++argc)
    argv[argc] = seq.lines[cin->current_command].parameters[argc];
  argv[argc] = 0;

  t_bunny_cinematic_command cmd;
  std::string		cmdmne = seq.lines[cin->current_command].command;
  char			*res;
  char			*res2;

  for (size_t i = 0; i < cmdmne.size(); ++i)
    cmdmne[i] = tolower(cmdmne[i]);
  if (!(cmd = bunny_map_get_data(cin->commands, cmdmne.c_str(), t_bunny_cinematic_command)))
    scream_error_if(return (EXIT_ON_ERROR), BE_SYNTAX_ERROR,
		    "Invalid instruction %s on "
		    "line %d in sequence %s",
		    "cinematic,syntax",
		    seq.lines[cin->current_command].command.c_str(),
		    cin->current_command,
		    bunny_configuration_get_address(cin->program)
		    );

  // Animate pictures based on cinematic animaton
  t_bunny_map		**node;
  t_bunny_sprite	*pic;

  for (bunny_map_all(cin->pictures, node))
    {
      pic = bunny_map_data(*node, t_bunny_sprite*);
      if (!pic->clipable.color_mask.argb[ALPHA_CMP])
	continue ;
      bunny_sprite_animate_elapsed(pic, elapsed);
    }

  res = cmd(_cin, argc, argv, event, elapsed);

  // Erreur. Le détail est dans la commande.
  if (res != NULL && *res == '\0')
    scream_error_if(return (EXIT_ON_ERROR), BE_SYNTAX_ERROR,
		    "Stopped at instruction %s on "
		    "line %d in sequence %s",
		    "cinematic,syntax",
		    seq.lines[cin->current_command].command.c_str(),
		    cin->current_command,
		    bunny_configuration_get_address(cin->program)
		    );

  // On nettoie toujours les commandes d'instructions, sauf
  // si l'on reste sur la même instruction
  if (res == NULL || strcmp(res, ".stay") != 0)
    memset(cin->command_data[cin->stack_top], 0, sizeof(cin->command_data[0]));
  else
    return (GO_ON);

  if (res == NULL)
    {
      if ((cin->current_command += 1) >= seq.nbr_lines)
	{
	  if (!cin->repeat)
	    {
	      bunny_cinematic_stop((t_bunny_cinematic*)cin);
	      return (EXIT_ON_SUCCESS);
	    }
	  cin->current_command = 0;
	  cin->stack_top = 0;
	  memset(cin->command_data, 0, sizeof(cin->command_data));
	  memset(cin->return_position, 0, sizeof(cin->return_position));
	}
      return (GO_ON);
    }
  else if (strcmp(res, ".skip") == 0)
    cin->current_command += 2;
  else if (strcmp(res, ".back") == 0)
    cin->current_command -= 1;
  else if (strcmp(res, ".reset") == 0)
    cin->current_command = 0;
  else if (strcmp(res, ".return") == 0)
    {
      if (cin->stack_top == 0)
	return (EXIT_ON_ERROR);
      cin->stack_top -= 1;
      cin->current_command = cin->return_position[cin->stack_top];
    }
  else
    {
      char		buf[1024];
      auto		it = seq.labels.begin();

      if ((res2 = strchr(res, '!')) != NULL)
	{
	  if (cin->stack_top + 1 >= NBRCELL(cin->command_data))
	    return (EXIT_ON_ERROR);
	  memcpy(buf, res, res2 - res);
	  buf[res2 - res] = 0;
	  cin->return_position[cin->stack_top] = cin->current_command + 1;
	  cin->stack_top += 1;
	  res = &buf[0];
	}
      for (; it != seq.labels.end(); ++it)
	if (it->second == std::string(res))
	  break ;
      if (it == seq.labels.end())
	return (EXIT_ON_ERROR);
      cin->current_command = it->first;
    }

  return (GO_ON);
}
