// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include			"lapin_private.h"

#define				PATTERN		"%s conf_file, %p clipable, %p target_conf, %d type -> %s (%s)"

static bool			load_normal_map(t_bunny_clipable	*pic,
						t_bunny_clipable_type	typ,
						const char		*file)
{
  sf::Texture			txt;
  sf::Vector2u			tsiz;
  sf::RenderTexture		**ntexture;
  const sf::Texture		**ntex;

  if (file == NULL)
    return (true);
  if (txt.loadFromFile(file) == false)
    return (false);
  switch (typ)
    {
    case BCT_PIXELARRAY:
      ntexture = &((struct bunny_pixelarray*)pic)->ntexture;
      ntex = &((struct bunny_pixelarray*)pic)->ntex;
      break;
    default:
      ntexture = &((struct bunny_picture*)pic)->ntexture;
      ntex = &((struct bunny_picture*)pic)->ntex;
      break;
    }
  tsiz = txt.getSize();
  if (*ntexture == NULL)
    {
      if (((*ntexture) = new (std::nothrow) sf::RenderTexture(tsiz)) == NULL)
	return (false);
    }
  else if ((*ntexture)->resize(tsiz) == false)
    return (false);
  sf::Sprite spr(txt);
  (*ntexture)->clear(sf::Color(128, 128, 255, 255));
  (*ntexture)->draw(spr);
  (*ntexture)->display();
  *ntex = &(*ntexture)->getTexture();
  return (true);
}

/**
 * @doc-symbol bunny_set_clipable_attribute
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 510
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Loads a clipable configuration file and applies it to a clipable object.
 * @description If *clipable is NULL, the function creates the resource described by the configuration. If *config is NULL, the loaded configuration can be returned to the caller.
 * @param conf_file The configuration file path.
 * @param clipable The clipable to configure, or the storage receiving a newly created one.
 * @param config The optional configuration object to use or receive.
 * @param typ The kind of clipable to configure or create.
 * @return-success true if the configuration was loaded and applied.
 * @return-failure false on invalid parameters, missing fields or loading errors.
 * @error EINVAL Invalid parameter or malformed configuration.
 * @log Logs are written with the "ressource", "graphics" and "syntax" labels.
 * @see t_bunny_clipable_type, t_bunny_clipable
 *
 * @doc-lang fr
 * @brief Charge un fichier de configuration clipable et l’applique à un objet clipable.
 * @description Si *clipable vaut NULL, la fonction crée la ressource décrite par la configuration. Si *config vaut NULL, la configuration chargée peut être renvoyée à l’appelant.
 * @param conf_file Le chemin du fichier de configuration.
 * @param clipable Le clipable à configurer, ou l’emplacement recevant un nouveau clipable.
 * @param config L’objet de configuration optionnel à utiliser ou recevoir.
 * @param typ Le type de clipable à configurer ou créer.
 * @return-success true si la configuration a été chargée et appliquée.
 * @return-failure false en cas de paramètres invalides, de champs manquants ou d’erreur de chargement.
 * @error EINVAL Paramètre invalide ou configuration mal formée.
 * @log Les logs sont écrits avec les labels "ressource", "graphics" et "syntax".
 * @see t_bunny_clipable_type, t_bunny_clipable
 */
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

  if (bunny_configuration_go_get_string(cnf, &str, "RessourceFile[1]"))
    if (load_normal_map(pic, typ, str) == false)
      {
	missing_field = "Cannot load file given by RessourceFile[1] field";
	goto InvalidField;
      }

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

  pic->color_mask.full = WHITE;
  bunny_color_configuration("ColorMask", &pic->color_mask, cnf);

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

  t_bunny_position		split;

  if (bunny_configuration_go_get_int(cnf, &split.x, "Clip.Split[0]") && split.x != 0)
    {
      pic->clip_width = pic->buffer.width / split.x;
      if (bunny_configuration_go_get_int(cnf, &split.y, "Clip.Split[1]") && split.y != 0)
	pic->clip_height = pic->buffer.height / split.y;
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

