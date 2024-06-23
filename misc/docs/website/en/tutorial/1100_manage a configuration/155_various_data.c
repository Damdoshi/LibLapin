
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
