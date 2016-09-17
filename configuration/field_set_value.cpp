// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include			"lapin_private.h"

void				bunny_ini_field_set_value(t_bunny_ini_field	*field,
							  unsigned int		index,
							  const char		*value)
{
  std::vector<std::string>	*vec = (std::vector<std::string>*)field;

  if (vec->size() < index)
    return ;
  (*vec)[index] = std::string(value);
}

