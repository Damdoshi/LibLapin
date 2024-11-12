// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bunny Library

#include		"lapin_private.h"

void			 _wbset(t_bunny_waterbox			*wb,
				t_bunny_bitfield			*bf,
				int					x,
				int					y,
				int					z,
				t_bunny_waterbox_point			wp);

t_bunny_waterbox	*bunny_read_waterbox(t_bunny_configuration	*cnf)
{
  t_bunny_configuration	*nod;
  t_bunny_waterbox	*wb;
  const char		*str;
  int			w;
  int			h;
  int			d = 1;

  if (!bunny_configuration_getf_int(cnf, &w, "Width"))
    if (!bunny_configuration_getf_int(cnf, &w, "Size[0]"))
      return (NULL);
  if (!bunny_configuration_getf_int(cnf, &h, "Height"))
    if (!bunny_configuration_getf_int(cnf, &h, "Size[1]"))
      return (NULL);
  if (!bunny_configuration_getf_int(cnf, &d, "Depth"))
    bunny_configuration_getf_int(cnf, &d, "Size[2]");
  if ((wb = bunny_new_waterbox(w, h, d)) == NULL)
    return (NULL);
  if (bunny_color_configuration("Color", &wb->color, cnf) == BD_ERROR)
    goto Error;
  if (!bunny_configuration_getf_string(cnf, &str, "Points"))
    for (size_t i = 0; bunny_configuration_getf_node(cnf, &nod, "Points[%zu]", i); ++i)
      {
	int		type;
	int		x = 0;
	int		y = 0;
	int		z = 0;

	if (!bunny_configuration_getf_string(nod, &str, "Type"))
	  goto Error;
	if (!bunny_strcasecmp(str, "Wall"))
	  type = BWP_WALL;
	else if (!bunny_strcasecmp(str, "Drain"))
	  type = BWP_DRAIN;
	else if (!bunny_strcasecmp(str, "Water"))
	  type = BWP_WATER;
	else if (!bunny_strcasecmp(str, "Source"))
	  {
	    type = BWP_SOURCE;
	    if (bunny_configuration_getf_int(nod, &x, "Strength"))
	      {
		if (x < 0 || x > 3)
		  goto Error;
		type = type + x;
		x = 0;
	      }
	  }
	
	if (!bunny_configuration_getf_int(nod, &x, "Position[0]") &&
	    !bunny_configuration_getf_int(nod, &x, "X"))
	  goto Error;
	bunny_configuration_getf_int(nod, &y, "Position[1]");
	bunny_configuration_getf_int(nod, &y, "Y");
	bunny_configuration_getf_int(nod, &z, "Position[2]");
	bunny_configuration_getf_int(nod, &z, "Z");
	
	_wbset(wb, wb->boxes[wb->current_box], x, y, z, (t_bunny_waterbox_point)type);
      }
  else
    {
      // Chargement de l'image contenant la carte
    }
  return (wb);
 Error:
  bunny_delete_waterbox(wb);
  return (NULL);
}
