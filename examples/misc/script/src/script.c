
#include		<stdio.h>
#include		<lapin.h>
#include		<unistd.h>

static size_t		dstrlen(const char	*str)
{
  const char		*s = str;

  while (*str++);
  return (str - s);
}

int			main(int	argc,
			     char	**argv)
{
  const char		*str;
  t_bunny_ini		*ini;
  t_bunny_ini_scope	*scope;
  t_bunny_ini_field	*field;
  int			i;

  if (argc != 1)
    {
      for (i = 1; i < argc; ++i)
	{
	  ini = bunny_load_ini(argv[i]);
	  for (scope = bunny_ini_first(ini); scope != LAST_SCOPE; scope = bunny_ini_next(ini, scope))
	    printf("%s\n", bunny_ini_scope_name(ini, scope));
	  bunny_delete_ini(ini);
	}
      return (EXIT_SUCCESS);
    }
  i = 0;
  for (i = 0; i < 20; ++i)
    bunny_load_ini("lechec.ini");
  if ((ini = bunny_load_ini("blob.ini")) == NULL)
    return (EXIT_FAILURE);
  while ((str = bunny_ini_get_field(ini, "section", "field", i++)) != NULL)
    {
      write(1, str, dstrlen(str));
      write(1, "\n", 1);
    }
  write(1, "\n", 1);
  for (scope = bunny_ini_first(ini); scope != LAST_SCOPE; scope = bunny_ini_next(ini, scope))
    {
      write(1, bunny_ini_scope_name(ini, scope), dstrlen(bunny_ini_scope_name(ini, scope)));
      write(1, "\n", 1);
      for (field = bunny_ini_first_field(scope); field != LAST_FIELD; field = bunny_ini_next_field(scope, field))
	{
	  write(1, bunny_ini_field_name(scope, field), dstrlen(bunny_ini_field_name(scope, field)));
	  write(1, "\n", 1);
	}
    }

  write(1, "Dumping : \n", 11);
  bunny_save_ini(ini, "/dev/stdout");

  bunny_delete_ini(ini);
  return (EXIT_SUCCESS);
}
