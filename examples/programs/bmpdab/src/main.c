/*
** *****************************************************************************
** damdoshi <damdoshi@blacklatex>
** Ecole 89 - 27/11/2020 11:10:33
**
** - BMP TO DABSIC -
**
** *****************************************************************************
*/

#include		<lapin.h>
#include		"bmpdab.h"

int			main(int		argc,
			     char		**argv)
{
  t_bunny_configuration	*cnf;
  t_bunny_pixelarray	*px;
  char			buffer[512];
  int			i;

  if (argc == 1)
    {
      bunny_printlerr("Usage is:\n\t./bmpdab [picture]+");
      return (EXIT_FAILURE);
    }
  i = 1;
  while (i < argc)
    {
      if (strlen(argv[i]) >= sizeof(buffer) - 4)
	fprintf(stderr, "File name %s is too long. Skipping\n", argv[i]);
      else if ((px = bunny_load_pixelarray(argv[i])) == NULL)
	fprintf(stderr, "Cannot load picture file %s. Skipping.\n", argv[i]);
      else if ((cnf = convert_bmp_to_dabsic(px)) == NULL)
	fprintf(stderr, "Failed to convert pciture file %s to dabsic. Skipping.\n", argv[i]);
      else
	{
	  char		*str;

	  bunny_delete_clipable(&px->clipable);
	  str = strrchr(argv[i], '.');
	  strncpy(&buffer[0], argv[i], str - argv[i]);
	  buffer[str - argv[i]] = '\0';
	  strncat(&buffer[0], ".dab", sizeof(buffer) - 5);
	  if (bunny_save_configuration(BC_DABSIC, &buffer[0], cnf) == false)
	    fprintf(stderr, "Failed to save configuration to %s, generated for file %s. Skipping\n",
		    &buffer[0], argv[i]);
	  bunny_delete_configuration(cnf);
	}
      i = i + 1;
    }
}

