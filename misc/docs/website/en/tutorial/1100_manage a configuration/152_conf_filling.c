  t_bunny_configuration *cnf;

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
