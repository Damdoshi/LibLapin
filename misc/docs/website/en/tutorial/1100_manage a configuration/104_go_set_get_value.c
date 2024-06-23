  // Will store retrieved value
  int val;

  // Change, from root, the value of the node
  bunny_configuration_go_set(cnf, 68000, "Team.Player");

  // Get the value from root
  bunny_configuration_go_get(cnf, &val, "Team.Player");
  // Test everything went well
  assert(val == 68000);

  // Reset
  val = 0;
  // Get the value from adr, just to be sure
  bunny_configuration_get(adr, &val);
  // Test everything went well
  assert(val == 68000);
