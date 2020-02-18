/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** FetchConf
**
** [#]?Field [-f files]+
** stdout
*/

#include		<stdio.h>
#include		<lapin.h>
#include		<string.h>

int			main(int		argc,
			     char		**argv)
{
  const char		*files[1024];
  const char		*fields[1024];
  int			nfiles = 0;
  int			nfields = 0;

  if (argc == 1)
    {
      fprintf(stderr, "%s: Usage is:\n\t%s [[#]?field_address]+ [-f files]+.\n\t'#' stand for \"print array\".\n",
	      *argv, *argv);
      return (EXIT_FAILURE);
    }

  for (int i = 1; i < argc; ++i)
    if (strcmp(argv[i], "-f") == 0)
      {
	files[nfiles++] = argv[i + 1];
	i += 1;
      }
    else
      fields[nfields++] = argv[i];
  t_bunny_configuration	*cnf;
  int			ret;

  ret = EXIT_SUCCESS;
  for (int i = 0; i < nfiles; ++i)
    if ((cnf = bunny_open_configuration(files[i], NULL)) == NULL)
      {
	fprintf(stderr, "%s: Cannot open file configuration %s.\n", *argv, files[i]);
	ret = EXIT_FAILURE;
      }
    else
      {
	const char	*str;

	for (int j = 0; j < nfields; ++j)
	  if (fields[j][0] == '#')
	    for (int k = 0; bunny_configuration_getf(cnf, &str, "%s[%d]", &fields[j][1], k); ++k)
	      puts(str);
	  else if (bunny_configuration_getf(cnf, &str, "%s", fields[j]))
	    puts(str);
      }
  return (ret);
}

