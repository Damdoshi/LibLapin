/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_THIRD_DIMENSION_H__
# define			__LAPIN_THIRD_DIMENSION_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

typedef struct			s_bunny_3d_coordinate
{
  double			ox;
  double			oy;
  double			oz;

  double			mx;
  double			my;
  double			mz;
}				t_bunny_3d_coordinate;

typedef struct			s_bunny_3d_triangle
{
  t_bunny_3d_coordinate		*vertex[3];
  t_bunny_3d_coordinate		*texture[3];
  t_bunny_3d_coordinate		*normal[3];
}				t_bunny_3d_triangle;

typedef struct			s_bunny_3d_object
{
  const char			*name;
  t_bunny_picture		*texture;
  t_bunny_3d_coordinate		*vertex;
  size_t			nbr_vertex;
  t_bunny_3d_coordinate		*texcoord;
  size_t			nbr_texcoord;
  t_bunny_3d_coordinate		*normal;
  size_t			nbr_normal;
  t_bunny_3d_triangle		*triangle;
  size_t			nbr_triangle;
}				t_bunny_3d_object;

typedef struct			s_bunny_obj_file
{
  const char			*file;
  t_bunny_3d_object		*object;
  size_t			nbr_object;

  t_bunny_3d_coordinate		position;
  t_bunny_3d_coordinate		rotation;
  t_bunny_3d_coordinate		scale;
  t_bunny_3d_coordinate		origin;
}				t_bunny_obj_file;

t_bunny_obj_file		*bunny_load_obj_file(const char		*file);
void				bunny_delete_obj_file(t_bunny_obj_file	*obj);
void				bunny_compute_obj(t_bunny_obj_file	*obj);

#endif	/*			__LAPIN_THIRD_DIMENSION_H__		*/
