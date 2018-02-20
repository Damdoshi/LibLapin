#include <lapin.h>
#include <assert.h>

int main(void)
{
  t_bunny_configuration *cnf;
  t_bunny_configuration *adr;
  t_bunny_configuration *it;
  const char            *str;
  int                   i;

  // We create a configuration node
  cnf = bunny_new_configuration();
  bunny_configuration_create_mode(true);

  // We fill the configuration.
  bunny_configuration_go_set(cnf, "France", "Country.Name");
  bunny_configuration_go_set(cnf, (int)60e6, "Country.Population");
  bunny_configuration_go_set(cnf, "Communist", "Country.Regime");
  bunny_configuration_go_set(cnf, "Administrative fraction", "Country.Region");
  bunny_configuration_go_set(cnf, "Ile-de-France", "Country.Region[0]");
  bunny_configuration_go_set(cnf, "Seine-et-Marne", "Country.Region[0].Department[0]");
  bunny_configuration_go_set(cnf, "Val-de-Marne", "Country.Region[0].Department[1]");
  bunny_configuration_go_set(cnf, "Paris", "Country.Region[0].Department[2]");

  bunny_configuration_go_set(cnf, "Bretagne", "Country.Region[1]");
  bunny_configuration_go_set(cnf, "Morbihan", "Country.Region[1].Department[0]");
  bunny_configuration_go_set(cnf, "Finistere", "Country.Region[1].Department[1]");

  // We disable the create mode so accessing to field arbitrary
  // or throught index browsing does not create nodes
  bunny_configuration_create_mode(false);

  // We get the node at some address, which contains Name, Population and Regime
  adr = bunny_configuration_access(cnf, "Country");
  for (it = bunny_configuration_first(adr);
       it != bunny_configuration_end(adr);
       it = bunny_configuration_next(it))
    {
      // We stop if the string fetching failed
      assert(bunny_configuration_get(it, &str));
      // We print the name of the field followed by the value of the field
      printf("%s: %s\n", bunny_configuration_get_name(it), str);
    }

  // We get the node at some address, which contains three element in an array
  adr = bunny_configuration_access(cnf, "Country.Region[0].Department");
  for (i = 0; (it = bunny_configuration_access(adr, i)) != NULL; ++i)
    {
      // We stop if the string fetching failed
      assert(bunny_configuration_get(it, &str));
      // We print the name of the field followed by the value of the field
      printf("%s: %s\n", bunny_configuration_get_name(it), str);
    }

  // We fetch a node which is supposed to have three array children and check
  adr = bunny_configuration_access(cnf, "Country.Region[0].Department");
  assert(bunny_configuration_get_nbr_case(adr) == 3);

  // We fetch the country node which is supposed to have four name children and check
  adr = bunny_configuration_access(cnf, "Country");
  // Children are Name, Population, Regime and Region
  assert(bunny_configuration_get_nbr_child(adr) == 4);
  // We check the parent of Country is the root node
  assert(bunny_configuration_get_parent(adr) == cnf);

  // Address fetching and checking
  adr = bunny_configuration_access(cnf, "Country.Region");
  assert(strcmp("Country.Region", bunny_configuration_get_address(adr)) == 0);
  adr = bunny_configuration_access(cnf, "Country.Region[1].Department");
  assert(strcmp("Country.Region[1].Department", bunny_configuration_get_address(adr)) == 0);

  bunny_delete_configuration(cnf);

  return (EXIT_SUCCESS);
}
