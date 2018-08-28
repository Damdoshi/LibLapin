// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	"lapin_private.h"

static void	apply_transformations(t_bunny_3d_coordinate	*crd,
				      t_bunny_obj_file		*obj)
{
  double	x, y, z;

  // Apply origin
  crd->mx = crd->x - obj->origin.x;
  crd->my = crd->y - obj->origin.y;
  crd->mz = crd->z - obj->origin.z;

  // Apply scale
  crd->mx *= obj->scale.x;
  crd->my *= obj->scale.y;
  crd->mz *= obj->scale.z;

  // Apply rotation
  // X axis
  x = crd->mx;
  y = cos(obj->rotation.x) * crd->my - sin(obj->rotation.x) * crd->mz;
  z = sin(obj->rotation.x) * crd->my + cos(obj->rotation.x) * crd->mz;
  crd->mx = x;
  crd->my = y;
  crd->mz = z;

  // Y axis
  x = cos(obj->rotation.y) * crd->mx + sin(obj->rotation.y) * crd->mz;
  y = crd->my;
  z = -sin(obj->rotation.y) * crd->mx + cos(obj->rotation.y) * crd->mz;
  crd->mx = x;
  crd->my = y;
  crd->mz = z;

  // Z axis
  x = cos(obj->rotation.z) * crd->mx - sin(obj->rotation.z) * crd->my;
  y = sin(obj->rotation.z) * crd->mx + cos(obj->rotation.z) * crd->my;
  z = crd->mz;
  crd->mx = x;
  crd->my = y;
  crd->mz = z;

  // Apply position
  crd->mx += obj->position.x;
  crd->my += obj->position.y;
  crd->mz += obj->position.z;
}

void		bunny_compute_obj(t_bunny_obj_file		*obj)
{
  size_t	j;
  size_t	i;

  for (i = 0; i < obj->nbr_object; ++i)
    {
      for (j = 0; j < obj->object[i].nbr_vertex; ++j)
	apply_transformations(&obj->object[i].vertex[j], obj);
      for (j = 0; j < obj->object[i].nbr_texcoord; ++j)
	apply_transformations(&obj->object[i].texcoord[j], obj);
      for (j = 0; j < obj->object[i].nbr_normal; ++j)
	apply_transformations(&obj->object[i].normal[j], obj);
    }
}

