/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<lapin.h>

int			main(void)
{
  t_bunny_configuration	*cnf;
  t_bunny_configuration *a;
  double		dec;
  const char		*str;
  int			i;

  assert(cnf = bunny_load_configuration(BC_INI, "./simple.ini", NULL));
  assert(cnf = bunny_read_configuration(BC_INI, "OnTheFly=true\n", cnf));
  assert(cnf = bunny_load_configuration(BC_INI, "./additionnal.ini", cnf));

  a = cnf;
  assert(a = bunny_configuration_access(a, "NewScope"));
  assert(a = bunny_configuration_access(a, "Field"));
  assert(a = bunny_configuration_access(a, 0));
  assert(bunny_configuration_get_int(a, &i));
  assert(i == 42);

  assert(bunny_configuration_go_get(cnf, &str, "GlobalScopeFieldString[0]"));
  assert(strcmp(str, "A\r") == 0);
  assert(bunny_configuration_go_get(cnf, &str, "GlobalScopeFieldString[1]"));
  assert(strcmp(str, "B\n") == 0);
  assert(bunny_configuration_go_get(cnf, &str, "GlobalScopeFieldString[2]"));
  assert(strcmp(str, "C\t") == 0);
  assert(!bunny_configuration_go_get(cnf, &str, "GlobalScopeFieldString[3]"));

  assert(bunny_configuration_go_get(cnf, &i, "GlobalScopeFieldInt[0]"));
  assert(i == 0);
  assert(bunny_configuration_go_get(cnf, &i, "GlobalScopeFieldInt[1]"));
  assert(i == 1);
  assert(bunny_configuration_go_get(cnf, &i, "GlobalScopeFieldInt[2]"));
  assert(i == 2);

  assert(bunny_configuration_go_get(cnf, &dec, "Scope.FieldDouble[0]"));
  assert(dec - 0.1 < 0.01);
  assert(bunny_configuration_go_get(cnf, &dec, "Scope.FieldDouble[1]"));
  assert(dec - 0.2 < 0.01);
  assert(bunny_configuration_go_get(cnf, &dec, "Scope.FieldDouble[2]"));
  assert(dec - 0.3 < 0.01);

  assert(bunny_configuration_go_get(cnf, &dec, "Scope.FieldPercent[0]"));
  assert(dec - 0.2 < 0.01);
  assert(bunny_configuration_go_get(cnf, &dec, "Scope.FieldPercent[1]"));
  assert(dec - 0.4 < 0.01);
  assert(bunny_configuration_go_get(cnf, &dec, "Scope.FieldPercent[2]"));
  assert(dec - 0.6 < 0.01);

  assert(bunny_configuration_go_get(cnf, &i, "Scope.FieldPercent[0]"));
  assert(i == 0);
  assert(bunny_configuration_go_get(cnf, &i, "Scope.FieldPercent[1]"));
  assert(i == 0);
  assert(bunny_configuration_go_get(cnf, &i, "Scope.FieldPercent[2]"));
  assert(i == 0);
  assert(bunny_configuration_go_get(cnf, &i, "Scope.FieldPercent[3]"));
  assert(i == 1);

  assert(bunny_configuration_go_get(cnf, &str, "Scope.FieldRawString[0]"));
  assert(strcmp(str, "X") == 0);
  assert(bunny_configuration_go_get(cnf, &str, "Scope.FieldRawString[1]"));
  assert(strcmp(str, "Y") == 0);
  assert(bunny_configuration_go_get(cnf, &str, "Scope.FieldRawString[2]"));
  assert(strcmp(str, "Z") == 0);

  // Use field name directly, without [0]
  assert(bunny_configuration_go_get(cnf, &i, "NewField"));
  assert(i == 42);

  // Use field name directly, without [0]
  assert(bunny_configuration_go_get(cnf, &i, "OnTheFly"));
  assert(i != 0);

  // Use field name directly, without [0]
  // Use another field as index or key
  assert(bunny_configuration_go_get(cnf, &str, "LanguageLib[Language]"));
  assert(strcmp(str, "RU") == 0);

  // Use field name directly, without [0]
  // Use another field as index or key
  assert(bunny_configuration_go_get(cnf, &i, "NewScope[FieldName]"));
  assert(i == 42);

  assert(a = bunny_configuration_go_get_node(cnf, "NewField[0]"));
  i = 50;
  bunny_configuration_set(a, i);
  assert(bunny_configuration_go_get(cnf, &i, "NewField[0]"));
  assert(i == 50);

  static const char	*addr[] =
    {
      "Scope.FieldRawString[0]",
      "Scope.FieldRawString[2]",
      "Scope",
      "",
      "NewField[0]",
      "OnTheFly[0]",
      "OnTheFly"
    };
  size_t		j;

  for (j = 0; j < sizeof(addr) / sizeof(addr[0]); ++j)
    {
      assert(a = bunny_configuration_go_get_node(cnf, addr[j]));
      assert(strcmp(bunny_configuration_get_address(a), addr[j]) == 0);
    }

  bunny_delete_configuration(cnf);

  /////////////////////////////////////////////////////////////////
  // Now, [0] is never precised

  assert(cnf = bunny_load_configuration(BC_INI, "./base.ini", NULL));

  assert(bunny_configuration_go_get(cnf, &i, "BaseField"));
  assert(i == 42);

  assert(bunny_configuration_go_get(cnf, &i, "Included0Scope.Field"));
  assert(i == 69);

  assert(bunny_configuration_go_get(cnf, &i, "Included1Scope.Field"));
  assert(i == 81);

  assert(bunny_configuration_go_get(cnf, &i, "Scope.OtherField"));
  assert(i == 22);

  assert(bunny_configuration_go_get(cnf, &i, "Scope.Field[0]"));
  assert(i == 77);

  assert(bunny_configuration_go_get(cnf, &i, "Scope.Field[2]"));
  assert(i == 420);

  assert(bunny_configuration_go_get(cnf, &i, "InsertedField"));
  assert(i == 50);

  assert(bunny_configuration_go_get(cnf, &i, "InsertedScope.VeryDeep"));
  assert(i == 1337);

  assert(bunny_configuration_go_get(cnf, &i, "Scope.InsertedField"));
  assert(i == 50);

  assert(bunny_configuration_go_get(cnf, &i, "Scope.InsertedScope.VeryDeep"));
  assert(i == 1337);

  assert(bunny_configuration_go_get(cnf, &i, "Scope.Field[1].InsertedField"));
  assert(i == 50);

  assert(bunny_configuration_go_get(cnf, &i, "Scope.Field[1].InsertedScope.VeryDeep"));
  assert(i == 1337);

  bunny_set_error_descriptor(2);
  assert(bunny_save_configuration(BC_INI, "tmp.ini", cnf));
  assert(a = bunny_load_configuration(BC_INI, "tmp.ini", NULL));
  assert(bunny_save_configuration(BC_INI, "tmp2.ini", a));
  assert(system("diff tmp.ini tmp2.ini") == 0);
  system("rm tmp*.ini");

  assert(bunny_configuration_go_get(a, &i, "BaseField"));
  assert(i == 42);

  assert(bunny_configuration_go_get(a, &i, "Included0Scope.Field"));
  assert(i == 69);

  assert(bunny_configuration_go_get(a, &i, "Included1Scope.Field"));
  assert(i == 81);

  assert(bunny_configuration_go_get(a, &i, "Scope.OtherField"));
  assert(i == 22);

  assert(bunny_configuration_go_get(a, &i, "Scope.Field[0]"));
  assert(i == 77);

  assert(bunny_configuration_go_get(a, &i, "Scope.Field[2]"));
  assert(i == 420);

  assert(bunny_configuration_go_get(a, &i, "InsertedField"));
  assert(i == 50);

  assert(bunny_configuration_go_get(a, &i, "InsertedScope.VeryDeep"));
  assert(i == 1337);

  assert(bunny_configuration_go_get(a, &i, "Scope.InsertedField"));
  assert(i == 50);

  assert(bunny_configuration_go_get(a, &i, "Scope.InsertedScope.VeryDeep"));
  assert(i == 1337);

  assert(bunny_configuration_go_get(a, &i, "Scope.Field[1].InsertedField"));
  assert(i == 50);

  assert(bunny_configuration_go_get(a, &i, "Scope.Field[1].InsertedScope.VeryDeep"));
  assert(i == 1337);

  bunny_delete_configuration(a);
  bunny_set_error_descriptor(-1);

  bunny_delete_configuration(cnf);

  printf("Fully done!\n");
  return (EXIT_SUCCESS);
}

