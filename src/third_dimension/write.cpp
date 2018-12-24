// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

size_t			bunny_write_obj_file(const t_bunny_obj_file	*file,
					     char			*buffer,
					     size_t			buflen)
{
  size_t		len = 0;
  size_t		i;

  for (i = 0; i < file->nbr_object; ++i)
    {
      t_bunny_3d_object	&obj = *file->object[i];

      len += snprintf(buffer, buflen - len, "o %s\n", file.name);
      for (j = 0; j < obj.nbr_vertex; ++j)
	len += snprintf(buffer, buflen - len, "v %f %f %f\n",
			obj.vertex[j].x, obj.vertex[j].y, obj.vertex[j].z);
      for (j = 0; j < obj.nbr_texcoord; ++j)
	len += snprintf(buffer, buflen - len, "v %f %f %f\n",
			obj.vertex[j].x, obj.vertex[j].y, obj.texcoord[j].z);
      for (j = 0; j < obj.nbr_normal; ++j)
	len += snprintf(buffer, buflen - len, "v %f %f %f\n",
			obj.vertex[j].x, obj.vertex[j].y, obj.texcoord[j].z);
    }
}

size_t			bunny_write_obj_file(const t_bunny_obj_file	*file,
					     t_bunny_configuration_type	type,
					     char			*buffer,
					     size_t			buflen)
{
  if (type == BC_CUSTOM)
    return (bunny_write_real_obj_file(file, buffer, buflen));
  t_bunny_configuration	*cnf;
  char			*out;

  cnf = NULL; // Must be replaced by the configuration build
  if ((out = bunny_write_configuration(type, cnf)) == NULL)
    return (0);
  bunny_delete_configuration(cnf);
  strncpy(&buffer[0], out, buflen - 2);
  buffer[buflen - 1] = '\0';
  bunny_free(out);
  return (strlen(&buffer[0]));
}

