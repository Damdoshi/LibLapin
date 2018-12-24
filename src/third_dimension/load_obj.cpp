// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<stdio.h>
#include		"lapin_private.h"

static const char *obj_comment = "#";
static const std::string obj_texture[1] = {"vt"};
static const std::string obj_normal[1] = {"vn"};
static const std::string obj_vertex[1] = {"v"};
static const std::string obj_triangle[1] = {"f"};
static const std::string obj_group[1] = {"g"};
static const std::string obj_object[1] = {"o"};

static size_t		how_many_objects(const char		*code)
{
  size_t		cnt;
  ssize_t		i;

  for (i = 0, cnt = 0; code[i]; ++cnt)
    {
      skipspace(code, i);
      if (readchar(code, i, obj_comment)
	  || readtext(code, i, obj_texture, 1)
	  || readtext(code, i, obj_normal, 1)
	  || readtext(code, i, obj_vertex, 1)
	  || readtext(code, i, obj_triangle, 1)
	  || readtext(code, i, obj_group, 1)
	  )
	for (; code[i] && (code[i] != '\r' && code[i] != '\n'); ++i);
      else if (readtext(code, i, obj_object, 1) == false)
	return (0);
    }
  return (cnt);
}

static bool		how_many_elements(const char		*code,
					  t_bunny_3d_object	*obj)
{
  ssize_t		i;

  for (i = 0; code[i];)
    {
      skipspace(code, i);
      if (readchar(code, i, obj_comment))
	{}
      else if (readtext(code, i, obj_texture, 1))
	obj->nbr_texcoord += 1;
      else if (readtext(code, i, obj_normal, 1))
	obj->nbr_normal += 1;
      else if (readtext(code, i, obj_vertex, 1))
	obj->nbr_vertex += 1;
      else if (readtext(code, i, obj_triangle, 1))
	obj->nbr_triangle += 1;
      else if (readtext(code, i, obj_group, 1))
	fprintf(stderr, ".obj file loading function: group are not supported\n");
      else if (readtext(code, i, obj_object, 1))
	return (false);
      for (; code[i] && (code[i] != '\r' && code[i] != '\n'); ++i);
    }
  if ((obj->vertex = (t_bunny_3d_coordinate*)bunny_calloc(obj->nbr_vertex, sizeof(*obj->vertex))) == NULL)
    return (false);
  if ((obj->texcoord = (t_bunny_3d_coordinate*)bunny_calloc(obj->nbr_texcoord, sizeof(*obj->texcoord))) == NULL)
    goto DeleteVertex;
  if ((obj->normal = (t_bunny_3d_coordinate*)bunny_calloc(obj->nbr_normal, sizeof(*obj->normal))) == NULL)
    goto DeleteTexture;
  if ((obj->triangle = (t_bunny_3d_triangle*)bunny_calloc(obj->nbr_triangle, sizeof(*obj->triangle))) == NULL)
    goto DeleteNormal;
  return (true);
 DeleteNormal:
  bunny_free(obj->normal);
 DeleteTexture:
  bunny_free(obj->texcoord);
 DeleteVertex:
  bunny_free(obj->vertex);
  return (false);
}

static bool		read_values(const char			*code,
				    ssize_t			&i,
				    t_bunny_3d_coordinate	&coord,
				    int				min)
{
  char			*x;

  skipspace_inline(code, i);
  coord.mx = coord.x = strtod(&code[i], &x);
  if (x == &code[i])
    return (min < 1);
  if (isnan(coord.x))
    return (false);

  i += x - code;
  skipspace_inline(code, i);
  coord.my = coord.y = strtod(&code[i], &x);
  if (x == &code[i])
    return (min < 2);
  if (isnan(coord.y))
    return (false);

  i += x - code;
  skipspace_inline(code, i);
  coord.mz = coord.z = strtod(&code[i], &x);
  if (x == &code[i])
    return (min < 3);
  if (isnan(coord.z))
    return (false);

  return (true);
}

static bool		read_triangles(const char		*code,
				       ssize_t			&i,
				       t_bunny_3d_object	*obj,
				       t_bunny_3d_triangle	&coord)
{
  size_t		target;
  char			*x;
  int			r;

  for (target = 0; target < 3; ++target)
    {
      skipspace_inline(code, i);
      readtext(code, i, obj_vertex);
      r = strtol(&code[i], &x, 0);
      if (r < 0 || r >= (int)obj->nbr_vertex)
	return (false);
      coord.vertex[target] = &obj->vertex[r];
      if (x == &code[i])
	return (false);
      if (readchar(code, i, "/") == false)
	continue ;

      readtext(code, i, obj_texture);
      r = strtol(&code[i], &x, 0);
      if (r < 0 || r >= (int)obj->nbr_texcoord)
	return (false);
      coord.texture[target] = &obj->texcoord[r];
      if (x == &code[i])
	return (false);
      if (readchar(code, i, "/") == false)
	continue ;

      readtext(code, i, obj_normal);
      r = strtol(&code[i], &x, 0);
      if (r < 0 || r >= (int)obj->nbr_normal)
	return (false);
      coord.normal[target] = &obj->normal[r];
      if (x == &code[i])
	return (false);
    }
  skipspace_inline(code, i);
  if (!readchar(code, i, "\r\n"))
    {
      fprintf(stderr, "'f' field in obj file loading: "
	      "does not support more than three parameters. skipping\n");
      for (; code[i] && (code[i] != '\r' && code[i] != '\n'); ++i);

    }
  return (true);
}

static t_bunny_obj_file	*bunny_load_real_obj_file(const char		*file)
{
  t_bunny_obj_file	*obj;
  char			*code;
  ssize_t		vertex, texture, normal, triangle;
  ssize_t		obj_i;
  ssize_t		i;

  if (bunny_load_file(file, (void**)&code, NULL) == -1)
    return (NULL);
  if ((obj = (t_bunny_obj_file*)bunny_calloc(1, sizeof(*obj))) == NULL)
    goto DeleteFile;
  if ((obj->file = bunny_strdup(file)) == NULL)
    goto DeleteAll;
  if ((obj->nbr_object = how_many_objects(code)) == 0)
    goto DeleteAll;
  if ((obj->object = (t_bunny_3d_object*)bunny_calloc
       (obj->nbr_object, sizeof(*obj->object))) == NULL)
    goto DeleteAll;

  obj_i = -1;
  vertex = texture = normal = triangle = 0;
  for (i = 0; code[i];)
    {
      bool ok = true;

      skipspace(code, i);
      if (readchar(code, i, obj_comment))
	{}
      else if (readtext(code, i, obj_texture, 1))
	ok = read_values(code, i, obj->object[obj_i].texcoord[texture++], 3);
      else if (readtext(code, i, obj_normal, 1))
	ok = read_values(code, i, obj->object[obj_i].normal[normal++], 2);
      else if (readtext(code, i, obj_vertex, 1))
	ok = read_values(code, i, obj->object[obj_i].vertex[vertex++], 3);
      else if (readtext(code, i, obj_triangle, 1))
	ok = read_triangles(code, i, &obj->object[obj_i], obj->object[obj_i].triangle[triangle++]);
      else if (readtext(code, i, obj_object, 1))
	{
	  ssize_t j;

	  obj_i += 1;
	  skipspace_inline(code, i);
	  j = i;
	  if (readchar(code, j, fieldname) == false)
	    goto DeleteAll;
	  if ((obj->object[obj_i].name = bunny_strndup(&code[i], j - i)) == NULL)
	    goto DeleteAll;
	  i = j;
	  if (how_many_elements(&code[i],  &obj->object[obj_i]) == false)
	    goto DeleteAll;
	}
      else
	goto DeleteAll;
      if (ok == false)
	goto DeleteAll;
      for (; code[i] && (code[i] != '\r' && code[i] != '\n'); ++i);
    }
  bunny_delete_file(code, file);
  return (obj);
 DeleteAll:
  bunny_delete_obj_file(obj);
 DeleteFile:
  bunny_delete_file(code, file);
  return (NULL);
}

t_bunny_obj_file	*bunny_load_obj_file(const char		*file)
{
  t_bunny_configuration_type typ;
  t_bunny_configuration	*cnf;
  t_bunny_obj_file	*obj;

  if ((typ = bunny_which_format(file)) == BC_CUSTOM)
    return (bunny_load_real_obj_file(file));
  if ((cnf = bunny_load_configuration(typ, file, NULL)) == NULL)
    return (NULL);
  if ((obj = (t_bunny_obj_file*)bunny_calloc(1, sizeof(*obj))) == NULL)
    goto DeleteConfiguration;
  if ((obj->file = bunny_strdup(file)) == NULL)
    goto DeleteObjFile;

  //
  fprintf(stderr, "3D object file loading is not implemented in any not custom language\n");

  bunny_delete_configuration(cnf);
  return (obj);

 DeleteObjFile:
  bunny_delete_obj_file(obj);
 DeleteConfiguration:
  bunny_delete_configuration(cnf);
  return (NULL);
}
