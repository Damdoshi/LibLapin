// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// Pentacle Technologie 2008-2024
// EFRIT 2022-2024
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_configuration_is_type(t_bunny_configuration	*cnf,
					    const char			*str)
{
  const char	*natives[] = {
    "int", "integer", "real", "string"
  };
  size_t	i;

  (void)cnf;
  for (i = 0; i < NBRCELL(natives); ++i)
    if (strcmp(str, natives[i]) == 0)
      return (true);
  return (false);
}
