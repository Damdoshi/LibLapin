// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bunny_declare_context(dressing);

const t_bunny_context	gl_bunny_dressing_context =
  {
    (t_bunny_key)dressing_key,
    bunny_context_type,
    (t_bunny_click)dressing_click,
    (t_bunny_move)dressing_move,
    (t_bunny_wheel)dressing_wheel,
    bunny_context_joy_connect, // Faire les joysticks plus tard
    bunny_context_joy_button,
    bunny_context_joy_axis,
    bunny_context_get_focus,
    bunny_context_lost_focus,
    bunny_context_resize,
    (t_bunny_loop)dressing_loop,
    (t_bunny_display)dressing_display,
    bunny_context_close,
    NULL,
    bunny_context_message,
    bunny_context_connect,
    (t_bunny_loop)dressing_entering,
    (t_bunny_leaving_context)dressing_leaving,
    bunny_context_async_computation,
    bunny_context_event_response
  };

#define			PATTERN	"%p dressing character, %p configuration, %d nbr -> %s. %s"

static bool		dressing_load_character(t_bunny_dressing_character	*d,
						t_bunny_configuration		*c,
						int				nbr)
{
  char			missing_field[512];
  t_bunny_configuration	*tmp;
  t_bunny_configuration	*dc;
  const char		*stmp;
  int			i;
  int			j;

  if ((i = bunny_configuration_casesf(c, "Dressings")) == 0)
    {
      snprintf(&missing_field[0], sizeof(missing_field),
	       "Field 'Characters[%d].Dressings' is missing.", nbr);
      goto InvalidField;
    }
  d->nbr_dressing = i;

  if (bunny_configuration_getf_string(c, &stmp, "Name") == false)
    {
      if (bunny_configuration_getf_node(c, &tmp, "Name") == false)
	{
	  snprintf(&missing_field[0], sizeof(missing_field),
		   "Field 'Characters[%d].Name' is missing.", nbr);
	  goto InvalidField;
	}
      if (bunny_set_font_attribute(NULL, &d->character_name, &tmp) == false)
	return (false);
    }
  else if ((d->character_name = bunny_load_text(stmp)) == NULL)
    return (false);

  if (bunny_configuration_getf_string(c, &stmp, "Background") == false)
    {
      if (bunny_configuration_getf_node(c, &tmp, "Background") == false)
	{
	  snprintf(&missing_field[0], sizeof(missing_field),
		   "Field 'Characters[%d].Background' is missing.", nbr);
	  goto InvalidField;
	}
      if (bunny_set_clipable_attribute
	  (NULL, &d->background, &tmp, BCT_PICTURE) == false)
	return (false);
    }
  else if ((d->background = bunny_load_picture(stmp)) == NULL)
    return (false);

  if (bunny_configuration_getf_string(c, &stmp, "Character") == false)
    {
      if (bunny_configuration_getf_node(c, &tmp, "Character") == false)
	{
	  snprintf(&missing_field[0], sizeof(missing_field),
		   "Field 'Characters[%d].Character' is missing.", nbr);
	  goto InvalidField;
	}
      if ((d->character = bunny_read_sprite(tmp)) == NULL)
	return (false);
    }
  else if ((d->character = bunny_load_sprite(stmp)) == NULL)
    return (false);

  if ((d->dressing = (t_bunny_dressing*)bunny_calloc
       (d->nbr_dressing, sizeof(*d->dressing))) == NULL)
    return (false);
  if ((d->displayed_clothes = (t_bunny_sprite**)bunny_calloc
       (d->nbr_dressing, sizeof(*d->displayed_clothes))) == NULL)
    return (false);

  for (i = 0; i < (int)d->nbr_dressing; ++i)
    {
      t_bunny_dressing *dress = &d->dressing[i];

      bunny_configuration_getf_node(c, &dc, "Dressings[%d]", i);
      if (bunny_configuration_getf_string(dc, &stmp, "Name") == false)
	{
	  if (bunny_configuration_getf_node(c, &tmp, "Name") == false)
	    {
	      snprintf(&missing_field[0], sizeof(missing_field),
		       "Field 'Characters[%d].Dressings[%d].Name' is missing.", nbr, i);
	      goto InvalidField;
	    }

	  if (bunny_set_font_attribute(NULL, &dress->dressing_name, &tmp) == false)
	    return (false);
	}
      else if ((dress->dressing_name = bunny_load_text(stmp)) == NULL)
	return (false);

      if (!bunny_configuration_getf_int
	  (dc, &dress->clothe_position.x, "ClothePosition[0]"))
	{
	  snprintf(&missing_field[0], sizeof(missing_field),
		   "Field 'Characters[%d].Dressings[%d].ClothePosition[0]' is missing.", nbr, i);
	  goto InvalidField;
	}
      if (!bunny_configuration_getf_int
	  (dc, &dress->clothe_position.y, "ClothePosition[1]"))
	{
	  snprintf(&missing_field[0], sizeof(missing_field),
		   "Field 'Characters[%d].Dressings[%d].ClothePosition[1]' is missing.", nbr, i);
	  goto InvalidField;
	}
      if (!bunny_configuration_getf_int
	  (dc, &dress->depth, "ClothePosition[2]"))
	dress->depth = 0;

      if ((dress->nbr_clothes = bunny_configuration_casesf(dc, "Clothes")) == 0)
	{
	  snprintf(&missing_field[0], sizeof(missing_field),
		   "Field 'Characters[%d].Dressings[%d].Clothes' is missing.", nbr, i);
	  goto InvalidField;
	}
      if ((dress->clothes = (t_bunny_sprite**)bunny_calloc(dress->nbr_clothes, sizeof(*dress->clothes)))
	  == NULL)
	return (false);
      if ((dress->on_character_clothes = (t_bunny_sprite**)bunny_calloc(dress->nbr_clothes, sizeof(*dress->clothes)))
	  == NULL)
	return (false);

      for (j = 0; j < (int)dress->nbr_clothes; ++j)
	{
	  if (bunny_configuration_getf_string
	      (dc, &stmp, "Clothes[%d].Icon", j) == false)
	    {
	      if (bunny_configuration_getf_node
		  (dc, &tmp, "Clothes[%d].Icon", j) == false)
		{
		  snprintf(&missing_field[0], sizeof(missing_field),
			   "Field 'Characters[%d].Dressings[%d].Clothes[%d].Icon' is missing.", nbr, i, j);
		  goto InvalidField;
		}
	      if ((dress->clothes[j] = bunny_read_sprite(tmp)) == NULL)
		return (false);
	    }
	  else if ((dress->clothes[j] = bunny_load_sprite(stmp)) == NULL)
	    return (false);

	  if (bunny_configuration_getf_string
	      (dc, &stmp, "Clothe[%d].OnCharacter", j) == false)
	    {
	      if (bunny_configuration_getf_node
		  (dc, &tmp, "Clothes[%d].OnCharacter", j) == false)
		{
		  snprintf(&missing_field[0], sizeof(missing_field),
			   "Field 'Characters[%d].Dressings[%d].Clothes[%d].OnCharacter' is missing.", nbr, i, j);
		  goto InvalidField;
		}
	      if ((dress->clothes[j] = bunny_read_sprite(tmp)) == NULL)
		return (false);
	    }
	  else if ((dress->clothes[j] = bunny_load_sprite(stmp)) == NULL)
	    return (false);

	  dress->clothes[j]->clipable.buffer.data[0].int_data = dress->depth;
	}
    }
  return (true);

 InvalidField:
  scream_error_if
    (return (false), EINVAL, PATTERN, "ressource,dressing",
     d, c, nbr, "false", &missing_field[0]);
  return (false);
}

#undef PATTERN
#define PATTERN "%p conf, %p dressing screen -> %s. %s"

bool			bunny_init_dressing_context_conf(t_bunny_configuration *cnf,
							 t_bunny_dressing_screen *c)
{
  const char		*missing_field;
  t_bunny_dressing_character *dchar;
  t_bunny_configuration	*chars;
  int			i;

  if ((c->nbr_characters = i = bunny_configuration_casesf(cnf, "Characters")) == 0)
    {
      missing_field = "Field 'Characters' is missing.";
      goto InvalidField;
    }
  if ((c->characters = (t_bunny_dressing_character*)
       bunny_calloc(i, sizeof(*c->characters))) == NULL)
    return (false);
  for (i = 0; bunny_configuration_getf_node(cnf, &chars, "Characters[%d]", i); ++i)
    {
      dchar = &c->characters[i];
      if (dressing_load_character(dchar, chars, i) == false)
	{
	  bunny_clear_dressing_context(c);
	  return (false);
	}
    }
  return (true);

 InvalidField:
  scream_error_if
    (return (false), EINVAL, PATTERN, "ressource,dressing",
     cnf, c, "false", missing_field);
  return (false);
}

bool			bunny_init_dressing_context_file(const char	*file,
							 t_bunny_dressing_screen *c)
{
  t_bunny_configuration	*cnf;
  bool			ret;

  if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
    return (false);
  ret = bunny_init_dressing_context_conf(cnf, c);
  bunny_delete_configuration(cnf);
  return (ret);
}

void			bunny_clear_dressing_context(t_bunny_dressing_screen *cnt)
{
  t_bunny_dressing_character *dchar;
  int			i, j, k;

  if (cnt->characters == NULL)
    return ;
  for (i = 0; i < (int)cnt->nbr_characters; ++i)
    {
      dchar = &cnt->characters[i];

      if (dchar->character_name)
	bunny_delete_clipable(&dchar->character_name->clipable);

      if (dchar->background)
	bunny_delete_clipable(dchar->background);

      if (dchar->character)
	bunny_delete_clipable(&dchar->character->clipable);

      if (dchar->dressing)
	{
	  for (j = 0; j < (int)dchar->nbr_dressing; ++j)
	    {
	      bunny_delete_clipable(&dchar->dressing[j].dressing_name->clipable);
	      if (dchar->dressing[j].clothes)
		{
		  for (k = 0; k < (int)dchar->dressing[j].nbr_clothes; ++k)
		    bunny_delete_clipable(&dchar->dressing[j].clothes[k]->clipable);
		  bunny_free(dchar->dressing[j].clothes);
		}
	      if (dchar->dressing[j].on_character_clothes)
		{
		  for (k = 0; k < (int)dchar->dressing[j].nbr_clothes; ++k)
		    bunny_delete_clipable
		      (&dchar->dressing[j].on_character_clothes[k]->clipable);
		  bunny_free(dchar->dressing[j].on_character_clothes);
		}
	    }
	  bunny_free(dchar->dressing);
	}

      if (dchar->displayed_clothes)
	bunny_free(dchar->displayed_clothes);
    }
  bunny_free(cnt->characters);
  cnt->characters = NULL;
}
