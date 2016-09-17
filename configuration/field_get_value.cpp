// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const char		*bunny_ini_field_get_value(const t_bunny_ini_field	*field,
						   unsigned int			index)
{
  bpt::Ini::FieldValue	*fvalue = (bpt::Ini::FieldValue*)field;

  if (fvalue->size() <= index)
    return (NULL);
  return ((*fvalue)[index].c_str());
}

