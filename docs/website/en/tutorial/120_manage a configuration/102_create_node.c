  // Will contain the root node
  t_bunny_configuration *cnf;
  // Will contain any children
  t_bunny_configuration *adr;

  // Create the configuration
  cnf = bunny_new_configuration();

  // By default, the create mode is false, so this function will fail
  adr = bunny_configuration_access(cnf, "Team.Player");
  // Test the function failed
  assert(adr == NULL);

  // Switch to create mode so access and set functions create nodes
  bunny_configuration_create_mode(true);

  // Create Team node in root and Player in Team node.
  adr = bunny_configuration_access(cnf, "Team.Player");

  // Test the function is successful
  assert(adr != NULL);
