/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#include			<lapin.h>
#include			<assert.h>
#include			<string.h>
#include			<stdio.h>

struct				bunny_prototype
{
  char *			name;
  void *			function_ptr;
  t_bunny_value_type		return_value;
  size_t			nbrparam;
  t_bunny_value_type		parameters[6];
};

struct				bunny_plugin
{
  char *			name;
  void *			library_handler;
  size_t			nbr_functions;
# ifndef			__ANSI__
  struct bunny_prototype	prototypes[0];
# else
  struct bunny_prototype	prototypes[1];
# endif
};

int				main(void)
{
  char				buffer[1024];
  char				carbon[1024];
  struct bunny_plugin		*plugin
    = bunny_alloca(sizeof(*plugin) + sizeof(plugin->prototypes[0]));
  int64_t			ret;
  int				sav;

  plugin->name = "";
  plugin->library_handler = NULL;
  plugin->nbr_functions = 1;

  plugin->prototypes[0].name = "strlen";
  plugin->prototypes[0].function_ptr = strlen;
  plugin->prototypes[0].return_value = INTEGER;
  plugin->prototypes[0].nbrparam = 1;
  plugin->prototypes[0].parameters[0] = STRING;

  bunny_plugin_callv
    ((t_bunny_plugin*)plugin, "strlen", (t_bunny_value*)&ret, "Coucou!");
  printf("The length of 'Coucou!' is %ld.\n", ret);
  assert(ret == 7);

  plugin->prototypes[0].name = "snprintf";
  plugin->prototypes[0].function_ptr = snprintf;
  plugin->prototypes[0].return_value = INTEGER;
  plugin->prototypes[0].nbrparam = 6;
  plugin->prototypes[0].parameters[0] = STRING;
  plugin->prototypes[0].parameters[1] = INTEGER;
  plugin->prototypes[0].parameters[2] = STRING;
  plugin->prototypes[0].parameters[3] = DOUBLE;
  plugin->prototypes[0].parameters[4] = INTEGER;
  plugin->prototypes[0].parameters[5] = STRING;

  bunny_plugin_callv
    ((t_bunny_plugin*)plugin, "snprintf",
     (t_bunny_value*)&ret,
     &buffer[0],
     sizeof(buffer),
     "1: %lf %ld %s!",
     4.2d,
     42L,
     "Fourtytwo"
     );
  sav = snprintf
    (&carbon[0], sizeof(carbon), "1: %lf %ld %s!", 4.2, 42L, "Fourtytwo");
  printf("'%s'\nmust match\n'%s'\n", &buffer[0], &carbon[0]);
  assert(strcmp(&carbon[0], &buffer[0]) == 0);
  assert(ret == sav);

  bunny_freea(plugin);
  return (EXIT_SUCCESS);
}

