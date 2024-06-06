// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		"lapin_private.h"

t_bunny_cinematic	*bunny_load_cinematic_wh(const char	*file,
						 unsigned int	w,
						 unsigned int	h,
						 const char	*language)
{
  t_bunny_configuration	*cnf = NULL;
  struct bunny_cinematic *cin;
  
  if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  bunny_configuration_resolve(cnf);
  if (!(cin = (struct bunny_cinematic*)bunny_read_cinematic_wh(cnf, w, h, language)))
    bunny_delete_configuration(cin->configuration);
  // Pas de suppression de la configuration, celle-ci
  // reste stockée dans cinematic si succès
  return ((t_bunny_cinematic*)cin);
}


t_bunny_cinematic	*bunny_load_cinematic(const char	*file,
					      const char	*language)
{
  t_bunny_configuration	*cnf = NULL;
  struct bunny_cinematic *cin;
  
  if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  bunny_configuration_resolve(cnf);
  if (!(cin = (struct bunny_cinematic*)bunny_read_cinematic(cnf, language)))
    bunny_delete_configuration(cnf);
  // Pas de suppression de la configuration, celle-ci
  // reste stockée dans cinematic si succès
  return ((t_bunny_cinematic*)cin);
}
