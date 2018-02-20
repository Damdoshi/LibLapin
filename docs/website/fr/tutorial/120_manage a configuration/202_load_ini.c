#include <stdio.h>
#include <lapin.h>
#include <stdlib.h>

int main(void)
{
  t_bunny_configuration *cnf;
  char *str;

  // Open a configuration file and parse it
  cnf = bunny_open_configuration("./201_ini_file.ini", NULL);

  // Switch to create mode
  bunny_configuration_create_mode(true);

  // Modify a field
  bunny_configuration_go_set(cnf, "Modified", "NewField[0]");

  // Generate a string with the modified configuration
  str = bunny_write_configuration(BC_INI, cnf);

  // Print it
  puts(str);

  // Free the generated string
  bunny_free(str);

  // Free the configuration
  bunny_delete_configuration(cnf);

  return (EXIT_SUCCESS);
}
