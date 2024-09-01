// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		\
  "%s conf_file, %p clipable, %p target_conf -> %s (%s)"

bool			bunny_set_font_attribute(const char		*conf_file,
						 t_bunny_font		**font,
						 t_bunny_configuration	**config)
{
  const char		*missing_field;
  const char		*resfile;
  t_bunny_font		*ofnt;
  struct bunny_ttf_font	*fnt;
  t_bunny_configuration	*cnf;
  t_bunny_position	siz;
  t_bunny_position	gly;
  int			tmp;
  t_bunny_color		clr;
  int			err = EINVAL;
  int			i;

  ofnt = NULL;
  if (font == NULL || (cnf = _get_good_conf(conf_file, config)) == NULL)
    scream_error_if
      (return (false), EINVAL, PATTERN, "ressource,graphics",
       conf_file, font, config, "false", "");

  bunny_configuration_resolve(cnf);
  if (bunny_configuration_go_get_string(cnf, &resfile, "RessourceFile") == false)
    {
      missing_field = "Missing field RessourceFile";
      goto InvalidField;
    }
  if (bunny_configuration_go_get_int(cnf, &siz.x, "BoxSize[0]") == false &&
      bunny_configuration_go_get_int(cnf, &siz.x, "Size[0]") == false)
    {
      missing_field = "Missing field BoxSize[0] or Size[0]";
      goto InvalidField;
    }
  if (bunny_configuration_go_get_int(cnf, &siz.y, "BoxSize[1]") == false &&
      bunny_configuration_go_get_int(cnf, &siz.y, "Size[1]") == false)
    {
      missing_field = "Missing field BoxSize[1] or Size[1]";
      goto InvalidField;
    }
  if (bunny_configuration_go_get_int(cnf, &gly.x, "GlyphSize[0]") == false)
    {
      missing_field = "Missing field GlyphSize[0]";
      goto InvalidField;
    }
  if (bunny_configuration_go_get_int(cnf, &gly.y, "GlyphSize[1]") == false)
    gly.y = gly.x;
  if ((ofnt = bunny_load_font(siz.x, siz.y, resfile, &gly)) == NULL)
    {
      missing_field = "Cannot load font";
      goto InvalidField;
    }
  if (bunny_set_clipable_attribute(conf_file, (t_bunny_clipable**)&ofnt, &cnf, BCT_FONT) == false)
    {
      bunny_delete_configuration(cnf);
      return (false);
    }

  fnt = (struct bunny_ttf_font*)ofnt;
  if (bunny_configuration_go_get_string(cnf, &resfile, "String[0]") ||
      bunny_configuration_go_get_string(cnf, &resfile, "Text[0]"))
    {
      char cat[1024 * 16];
      int end;

      i = 0;
      end = 0;
      cat[0] = '\0';
      do
	{
	  if (!bunny_configuration_getf_string(cnf, &resfile, "String[%d]", i)
	      && !bunny_configuration_getf_string(cnf, &resfile, "Text[%d]", i))
	    break ;
	  end += snprintf(&cat[end], sizeof(cat) - end, "%s", resfile);
	  i += 1;
	}
      while (1);

      if ((fnt->string = fnt->conf_string = bunny_strdup(&cat[0])) == NULL)
	{
	  err = ENOMEM;
	  missing_field = "Cannot duplicate string.";
	  goto InvalidField;
	}
    }

  if (bunny_configuration_go_get_int(cnf, &tmp, "StringOffset[0]") ||
      bunny_configuration_go_get_int(cnf, &tmp, "TextOffset[0]"))
    fnt->string_offset = tmp;

  if (bunny_configuration_go_get_int(cnf, &tmp, "StringLength[0]") ||
      bunny_configuration_go_get_int(cnf, &tmp, "TextLength[0]"))
    fnt->string_len = tmp;
  else if (fnt->string)
    fnt->string_len = strlen(fnt->string);

  if (bunny_configuration_go_get_string(cnf, &resfile, "HorizontalAlign"))
    {
      if (strcmp(resfile, "Left") == 0)
	fnt->halign = BAL_LEFT;
      else if (strcmp(resfile, "Right") == 0)
	fnt->halign = BAL_RIGHT;
      else if (strcmp(resfile, "Middle") == 0 || strcmp(resfile, "Center") == 0)
	fnt->halign = BAL_MIDDLE;
      else if (strcmp(resfile, "Justify") == 0)
	fnt->halign = BAL_JUSTIFY;
      else
	{
	  missing_field = "Invalid field HorizontalAlign";
	  goto InvalidField;
	}
    }

  if (bunny_configuration_go_get_string(cnf, &resfile, "VerticalAlign"))
    {
      if (strcmp(resfile, "Top") == 0)
	fnt->valign = BAL_TOP;
      else if (strcmp(resfile, "Bottom") == 0)
	fnt->valign = BAL_BOTTOM;
      else if (strcmp(resfile, "Middle") == 0 || strcmp(resfile, "Center") == 0)
	fnt->valign = BAL_MIDDLE;
      else if (strcmp(resfile, "Justify") == 0)
	fnt->valign = BAL_JUSTIFY;
      else
	{
	  missing_field = "Invalid field VerticalAlign";
	  goto InvalidField;
	}
    }

  missing_field = "Invalid color format";
  if (bunny_color_configuration("Color", &clr, cnf) == BD_ERROR)
    goto InvalidField;
  else
    fnt->color = clr.full;

  if (bunny_color_configuration("OutlineColor", &clr, cnf) == BD_ERROR)
    goto InvalidField;
  else
    fnt->outline_color = clr.full;

  if (bunny_configuration_go_get_int(cnf, &tmp, "OutlineSize[0]"))
    fnt->outline_size = tmp;

  if (bunny_configuration_go_get_int(cnf, &tmp, "Interglyph[0]"))
    {
      fnt->interglyph_space.x = tmp;
      if (bunny_configuration_go_get_int(cnf, &tmp, "Interglyph[1]"))
	fnt->interglyph_space.y = tmp;
    }

  if (bunny_configuration_go_get_int(cnf, &tmp, "Scrolling[0]"))
    {
      fnt->offset.x = tmp;
      if (bunny_configuration_go_get_int(cnf, &tmp, "Scrolling[1]"))
	fnt->offset.y = tmp;
    }

  fnt->glactive = false;

  if (config == NULL)
    bunny_delete_configuration(cnf);
  else
    *config = cnf;
  *font = ofnt;
  scream_log_if(PATTERN, "graphics", conf_file, font, config, "true", "");
  return (true);

 InvalidField:
  if (ofnt)
    bunny_delete_clipable(&ofnt->clipable);
  if (config == NULL || *config == NULL)
    bunny_delete_configuration(cnf);
  scream_error_if(return (false), err, PATTERN, "ressource,graphics,syntax", conf_file, font, config, "false", missing_field);
  return (false);
}

