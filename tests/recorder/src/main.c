// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include		<lapin.h>

int			main(int		argc,
			     char		**argv)
{
  t_bunny_recorder	*recorder;
  int			ret;
  int			i;

  if (bunny_record_available() == false)
    {
      fprintf(stderr, "%s: Record devices not available.\n", argv[0]);
      return (EXIT_FAILURE);
    }
  if (argc != 2)
    {
      const char	**x = bunny_record_devices();

      fprintf(stdout, "%s: Usage is:\n\t%s device\n", argv[0], argv[0]);
      fprintf(stdout, "Liste of devices:\n");
      for (i = 0; x[i] != NULL; ++i)
	{
	  fprintf(stdout, " - %s", x[i]);
	  if (strcmp(x[i], bunny_default_record_device()) == 0)
	    fprintf(stdout, " (Default device)");
	  fprintf(stdout, "\n");
	}
      return (EXIT_SUCCESS);
    }
  ret = EXIT_FAILURE;
  if ((recorder = bunny_new_recorder(argv[1], 44100)) == NULL)
    {
      fprintf(stderr, "%s: Cannot create a new recorder.\n", argv[0]);
      return (EXIT_FAILURE);
    }

  if (bunny_start_record(recorder) == false)
    {
      fprintf(stderr, "%s: Cannot start recorder.\n", argv[0]);
      goto End;
    }
  fprintf(stdout, "%s: Recorder started. Press enter to stop.\n", argv[0]);
  read(0, &i, 1);
  bunny_stop_record(recorder);
  fprintf(stdout, "%s: Recording stopped.\n", argv[0]);
  bunny_save_effect(&recorder->effect, "out.ogg");

  ret = EXIT_SUCCESS;
 End:
  bunny_delete_sound(&recorder->effect.sound);
  return (ret);
}

