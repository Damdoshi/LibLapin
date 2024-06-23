#include <lapin.h>
#include <assert.h>

int main(void)
{
  // Will contain the root node
  t_bunny_configuration *cnf;
  // Will contain any children
  t_bunny_configuration *adr;
  // Will store retrieved value
  int val;

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

  // Set adr (Team.Player) to 6502
  bunny_configuration_set(adr, 6502);

  // Get the value inside adr
  bunny_configuration_get(adr, &val);
  // Test if the value is 6502, exit brutally if not
  assert(val == 6502);

  // Reset val, to be sure the next operation made something
  val = 0;

  // Change, from root, the value of the node
  bunny_configuration_go_set(cnf, 68000, "Team.Player");

  // Get the value from root
  bunny_configuration_go_get(cnf, &val, "Team.Player");
  // Test everything went well
  assert(val == 68000);

  // Reset again
  val = 0;
  // Get the value from adr, just to be sure
  bunny_configuration_get(adr, &val);
  // Test everything went well
  assert(val == 68000);

  // Delete the whole configuration
  bunny_delete_configuration(cnf);

  return (EXIT_SUCCESS);
}
