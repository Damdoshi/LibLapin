  // Will store retrieved value
  int val;

  // Set adr (Team.Player) to 6502
  bunny_configuration_set(adr, 6502);

  // Get the value inside adr
  bunny_configuration_get(adr, &val);
  // Test if the value is 6502, exit brutally if not
  assert(val == 6502);
