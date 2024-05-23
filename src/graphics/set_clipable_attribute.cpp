// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include			"lapin_private.h"

#define				PATTERN		"%s conf_file, %p clipable, %p target_conf, %d type -> %s (%s)"

bool				bunny_set_clipable_attribute(const char		*conf_file,
							     t_bunny_clipable	**clipable,
							     t_bunny_configuration **config,
							     t_bunny_clipable_type	typ)
{
  t_bunny_clipable		*pic;
  const char			*missing_field;
  t_bunny_configuration		*cnf;
  const char			*str;
  int				tmp[4];

  if (clipable == NULL || (cnf = _get_good_conf(conf_file, config)) == NULL)
    scream_error_if
      (return (false), EINVAL, PATTERN, "ressource,graphics",
       conf_file, clipable, config, typ, "false", "");

  bunny_configuration_resolve(cnf);
  if (*clipable == NULL)
    {
      if (!bunny_configuration_go_get_string(cnf, &str, "RessourceFile[0]"))
	{
	  missing_field = "Missing field RessourceFile";
	  goto InvalidField;
	}
      if (typ == BCT_PICTURE)
	{
	  if ((*clipable = bunny_load_picture(str)) == NULL)
	    {
	      missing_field = "Cannot load file given by RessourceFile field";
	      goto InvalidField;
	    }
	}
      else if (typ == BCT_PIXELARRAY)
	{
	  if ((*clipable = (t_bunny_picture*)bunny_load_pixelarray(str)) == NULL)
	    {
	      missing_field = "Cannot load file given by RessourceFile field";
	      goto InvalidField;
	    }
	}
    }
  pic = *clipable;

  if (bunny_configuration_go_get_double(cnf, &pic->position.x, "Position[0]"))
    if (bunny_configuration_go_get_double(cnf, &pic->position.y, "Position[1]") == false)
      {
	missing_field = "Missing field Position[1]";
	goto InvalidField;
      }

  if (bunny_configuration_go_get_double(cnf, &pic->origin.x, "Origin[0]"))
    {
      if (bunny_configuration_go_get_double(cnf, &pic->origin.y, "Origin[1]") == false)
	{
	  missing_field = "Missing field Origin[1]";
	  goto InvalidField;
	}
      if (pic->origin.x > 0 && pic->origin.x < 1)
	pic->origin.x *= pic->buffer.width;
      if (pic->origin.y > 0 && pic->origin.y < 1)
	pic->origin.y *= pic->buffer.height;
    }

  if (bunny_configuration_go_get_double(cnf, &pic->scale.x, "Scale[0]"))
    if (bunny_configuration_go_get_double(cnf, &pic->scale.y, "Scale[1]") == false)
      pic->scale.y = pic->scale.x;

  bunny_configuration_go_get_double(cnf, &pic->rotation, "Rotation[0]");

  if (bunny_color_configuration("ColorMask", &pic->color_mask, cnf) == BD_ERROR)
    {
      missing_field = "Invalid ColorMask field";
      goto InvalidField;
    }

  if (bunny_configuration_go_get_int(cnf, &tmp[0], "Transparency[0]"))
    pic->color_mask.argb[ALPHA_CMP] = tmp[0];

  if (bunny_configuration_go_get_int(cnf, &pic->clip_x_position, "Clip.Position[0]"))
    if (bunny_configuration_go_get_int(cnf, &pic->clip_y_position, "Clip.Position[1]") == false)
      {
	missing_field = "Missing field Clip.Position[1]";
	goto InvalidField;
      }

  if (bunny_configuration_go_get_int(cnf, &pic->clip_width, "Clip.Size[0]"))
    if (bunny_configuration_go_get_int(cnf, &pic->clip_height, "Clip.Size[1]") == false)
      {
	missing_field = "Missing field Clip.Size[1]";
	goto InvalidField;
      }

  if (bunny_configuration_go_get_int(cnf, &tmp[0], "Clip.Selected[0]"))
    {
      tmp[1] = pic->buffer.width / pic->clip_width;
      tmp[2] = tmp[0] % tmp[1];
      tmp[3] = tmp[0] / tmp[1];
      pic->clip_x_position = tmp[2] * pic->clip_width;
      pic->clip_y_position = tmp[3] * pic->clip_height;
    }

  pic->smooth = false;
  pic->mosaic = false;
  bunny_configuration_getf_bool(cnf, &pic->smooth, "Smooth");
  bunny_configuration_getf_bool(cnf, &pic->mosaic, "Mosaic");

  if (config == NULL)
    bunny_delete_configuration(cnf);
  else
    *config = cnf;
  scream_log_if(PATTERN, "graphics", conf_file, clipable, config, typ, "true", "");
  return (true);

 InvalidField:
  if (config == NULL || *config == NULL)
    bunny_delete_configuration(cnf);
  scream_error_if(return (false), EINVAL, PATTERN, "ressource,graphics,syntax", conf_file, clipable, config, typ, "false", missing_field);
  return (false);
}

