/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** FetchConf
**
** stdin / [-f files]+
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
	  if (bunny_configuration_getf(cnf, &str, "%s", fields[j]))
	    puts(str);
      }
  return (ret);
}

