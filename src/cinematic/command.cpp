// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		<limits.h>
#include		"lapin_private.h"

#define			PARAMS				\
  struct bunny_cinematic *cin,				\
    int argc,						\
    t_bunny_configuration **argv,			\
    t_bunny_cinematic_event event __attribute__((unused)), \
    double elapsed __attribute__((unused))
#define			VOID() (void)cin; (void)argc; (void)argv; (void)elapsed

char			*cinematic_refresh(PARAMS)
{
  return (".letgo");
}

char			*cinematic_sleep(PARAMS)
{
  struct		sdt {
    bool		waiting;
    double		end_date;
  }			*sd = (struct sdt*)cin->stack_frame;
  const char		*str;

  if (argc < 1)
    return (NULL);
  if (!sd->waiting)
    {
      if (!bunny_configuration_getf_string(argv[0], &str, "."))
	scream_error_if(return (""), BE_SYNTAX_ERROR,
			"Invalid instruction parameter for %s. "
			"A double was expected. "
			"Line %d in sequence %s",
			"cinematic,syntax",
			__func__,
			cin->current_command,
			bunny_configuration_get_address(cin->program)
			);
      if (*str != '$')
	str = ".";
      if (!bunny_configuration_getf_double(argv[0], &sd->end_date, "%s", str))
	scream_error_if(return (""), BE_SYNTAX_ERROR,
			"Invalid instruction parameter for %s. "
			"A double was expected. "
			"Line %d in sequence %s",
			"cinematic,syntax",
			__func__,
			cin->current_command,
			bunny_configuration_get_address(cin->program)
			);

      sd->end_date += bunny_get_current_time();
      sd->waiting = true;
    }
  if (bunny_time_alive(sd->end_date))
    return (".stay");
  return (NULL);
}

static char		*cinematic_color(PARAMS, bool fore)
{
  t_bunny_color		col;
  double		dtmp;
  int			tmp[4];
  int			i;

  if (argc > 4)
    return (NULL);
  for (i = 0; i < argc; ++i)
    {
      if (!bunny_configuration_getf_int(argv[i], &tmp[i], "."))
	{
	  if (!bunny_configuration_getf_double(argv[i], &dtmp, "."))
	    goto Bad;
	  if (dtmp < 0 || dtmp > 1)
	    goto Bad;
	  tmp[i] = dtmp * 255;
	}
      else if (tmp[i] < 0 || tmp[i] > 255)
	goto Bad;
    }
  if (argc == 0)
    {
      if (fore)
	col.full = TRANSPARENT;
      else
	col.full = BLACK;
    }
  else if (argc == 1)
    {
      col.argb[ALPHA_CMP] = 255;
      col.argb[RED_CMP] = col.argb[GREEN_CMP] = col.argb[BLUE_CMP] = tmp[0] & 0xFF;
    }
  else if (argc == 2)
    {
      col.argb[ALPHA_CMP] = tmp[0] & 0xFF;
      col.argb[RED_CMP] = col.argb[GREEN_CMP] = col.argb[BLUE_CMP] = tmp[1] & 0xFF;
    }
  else if (argc == 3)
    {
      col.argb[ALPHA_CMP] = 255;
      col.argb[RED_CMP] = tmp[0] & 0xFF;
      col.argb[GREEN_CMP] = tmp[1] & 0xFF;
      col.argb[BLUE_CMP] = tmp[2] & 0xFF;
    }
  else if (argc == 4)
    {
      col.argb[ALPHA_CMP] = tmp[0] & 0xFF;
      col.argb[RED_CMP] = tmp[1] & 0xFF;
      col.argb[GREEN_CMP] = tmp[2] & 0xFF;
      col.argb[BLUE_CMP] = tmp[3] & 0xFF;
    }
  if (fore)
    cin->foreground_color.full = col.full;
  else
    cin->background_color.full = col.full;
  return (NULL);

 Bad:
  scream_error_if(return (""), BE_SYNTAX_ERROR,
		  "Invalid instruction parameter for %s. "
		  "An integer in [0;255] or a double in [0;1] was expected. "
		  "Line %d in sequence %s",
		  "cinematic,syntax",
		  __func__,
		  cin->current_command,
		  bunny_configuration_get_address(cin->program)
		  );
}

char			*cinematic_backcolor(PARAMS)
{
  return (cinematic_color(cin, argc, argv, event, elapsed, false));
}

char			*cinematic_forecolor(PARAMS)
{
  return (cinematic_color(cin, argc, argv, event, elapsed, true));
}

char			*cinematic_text(PARAMS)
{
  struct cinematic_text	*cte = (struct cinematic_text*)cin->stack_frame;
  const char		*str;

  // font_id display_speed text_id voice_id mouth(picture)_id

  if (cte->init)
    {
      size_t	tlen = strlen(cte->tex);

      if (cte->cursor == 0 && cte->voi)
	{
	  if (cte->voice_label[0])
	    bunny_sound_sprite_play_slice_name(cte->voi, BST_TRACK_03, cte->voice_label);
	  // else bunny_sound_manager_play_sound(&gl_bunny_sound_manager, (t_bunny_effect*)cte->voi);
	}

      // Rien ne se passe, ou on demande simplement à aller plus vite
      if (event == BCE_NO_EVENT || event == BCE_FASTER_EVENT)
	{
	  double	coef = event == BCE_NO_EVENT ? 1 : 2;

	  if ((cte->cursor += elapsed * fabs(cte->speed) * coef) >= tlen)
	    {
	      cte->cursor = tlen;
	      cte->fnt->string_len = cte->cursor;
	      if (cte->speed < 0)
		{
		  event = BCE_TERMINATE_EVENT;
		  goto Leave;
		}
	    }
	  while (cte->fnt->string[(int)cte->cursor] == ' ')
	    cte->cursor = (int)cte->cursor + 1;
	  cte->fnt->string_len = cte->cursor;
	  return (".stay");
	}
    Leave:
      // On demande à arriver a l'état de fin de l'évenement
      // Si on y est pas, on y va, sinon on passe au suivant
      if (event == BCE_TERMINATE_EVENT)
	{
	  if (tlen - cte->cursor > 1)
	    {
	      cte->cursor = tlen;
	      cte->fnt->string_len = cte->cursor;
	      return (".stay");
	    }
	  event = BCE_NEXT_EVENT;
	}
      // On demande a passer a l'evenement suivant
      if (event == BCE_NEXT_EVENT)
	{
	  if (cte->voi)
	    {
	      if (cte->voice_label[0])
		bunny_sound_sprite_stop_slice(cte->voi);
	      // else bunny_sound_manager_stop_sound(&gl_bunny_sound_manager, (t_bunny_effect*)cte->voi);
	    }
	  cte->init = false;
	  cte->cursor = 0;
	  cte->fnt->string_len = 0;
	}
      return (".letgo");
    }

  if (argc < 3 || !bunny_configuration_getf_string(argv[0], &str, "."))
    goto BadCommand;
  cte->init = true;
  cte->speed = INT_MAX;

  if ((cte->fnt = bunny_map_get_data(cin->fonts, str, t_bunny_font*)) == NULL)
    scream_error_if(return (""), BE_SYNTAX_ERROR,
		    "Invalid %s instruction parameter. "
		    "Unknown font named %s."
		    "Line %d in sequence %s",
		    "cinematic,syntax",
		    __func__, str,
		    cin->current_command,
		    bunny_configuration_get_address(cin->program)
		    );
  if (!bunny_configuration_getf_double(argv[1], &cte->speed, "."))
    goto BadCommand;
  if (!bunny_configuration_getf_string(argv[2], &str, "."))
    goto BadCommand;
  if ((cte->tex = bunny_map_get_data(cin->texts, str, const char*)) == NULL)
    scream_error_if(return (""), BE_SYNTAX_ERROR,
		    "Invalid %s instruction parameter. "
		    "Unknown text named %s."
		    "Line %d in sequence %s",
		    "cinematic,syntax",
		    __func__, str,
		    cin->current_command,
		    bunny_configuration_get_address(cin->program)
		    );
  cte->fnt->string = cte->tex;
  cte->fnt->string_len = 0;

  ////////////////////////////////////////////////////////////////////
  // Pour la voix ===================================================
  if (argc <= 3)
    return (".stay");

  if (!bunny_configuration_getf_string(argv[3], &str, "."))
    goto BadCommand;
  char buffer[4096];
  char *lab;
  snprintf(buffer, sizeof(buffer), "%s", str);
  if ((lab = strchr(buffer, ':')) != NULL)
    {
      *lab = '\0';
      snprintf(cte->voice_label, sizeof(cte->voice_label), "%s", lab + 1);
    }
  else
    cte->voice_label[0] = 0;
  if ((cte->voi = bunny_map_get_data(cin->voices, buffer, t_bunny_sound_sprite*)) == NULL)
    scream_error_if(return (""), BE_SYNTAX_ERROR,
		    "Invalid %s instruction parameter. "
		    "Unknown voice named %s."
		    "Line %d in sequence %s",
		    "cinematic,syntax",
		    __func__, str,
		    cin->current_command,
		    bunny_configuration_get_address(cin->program)
		    );

  ////////////////////////////////////////////////////////////////////
  // Pour la bouche =================================================

  if (argc <= 4)
    return (".stay");

  if (!bunny_configuration_getf_string(argv[4], &str, "."))
    goto BadCommand;
  if ((cte->fac = bunny_map_get_data(cin->fonts, str, t_bunny_sprite*)) == NULL)
    scream_error_if(return (""), BE_SYNTAX_ERROR,
		    "Invalid %s instruction parameter. "
		    "Unknown sprite named %s."
		    "Line %d in sequence %s",
		    "cinematic,syntax",
		    __func__, str,
		    cin->current_command,
		    bunny_configuration_get_address(cin->program)
		    );

  return (".stay");

 BadCommand:
  scream_error_if(return (""), BE_SYNTAX_ERROR,
		  "Invalid %s instruction. "
		  "Syntax is: text FontName letter_per_second TextName [VoiceName:PartName [FaceSpriteName]]"
		  "Line %d in sequence %s",
		  "cinematic,syntax",
		  __func__,
		  cin->current_command,
		  bunny_configuration_get_address(cin->program)
		  );
}

char			*cinematic_tweak(PARAMS)
{
  const char		*tmp;

  if (argc < 4)
    return ("");
  if (!bunny_configuration_getf_string(argv[0], &tmp, "."))
    return ("");
  if (strcasecmp(tmp, "picture") == 0)
    {
      if (!bunny_configuration_getf_string(argv[1], &tmp, "."))
	return ("");
      t_bunny_picture	*pic = bunny_map_get_data(cin->pictures, tmp, t_bunny_picture*);

      if (pic == NULL)
	return ("");
      if (!bunny_configuration_getf_string(argv[2], &tmp, "."))
	return ("");
      if (strcasecmp(tmp, "position") == 0)
	{
	  if (argc < 5)
	    return ("");
	  if (bunny_configuration_getf_double(argv[3], &pic->position.x, ".") == false ||
	      bunny_configuration_getf_double(argv[4], &pic->position.y, ".") == false)
	    return ("");
	  return (NULL);
	}
      else
	return (NULL);
    }
  return (NULL);
}

char			*cinematic_move(PARAMS)
{
  struct cinematic_move	cte;
  const char		*tmp;

  if (argc < 4)
    return ("");
  if (!bunny_configuration_getf_string(argv[0], &tmp, "."))
    return ("");
  if ((cte.pic = bunny_map_get_data(cin->pictures, tmp, t_bunny_picture*)) == NULL)
    return ("");
  if (bunny_configuration_getf_double(argv[1], &cte.target.x, ".") == false ||
      bunny_configuration_getf_double(argv[2], &cte.target.y, ".") == false ||
      bunny_configuration_getf_double(argv[3], &cte.speed, ".") == false)
    return ("");
  double		xdiff = cte.target.x - cte.pic->position.x;
  double		ydiff = cte.target.y - cte.pic->position.y;
  double		angle = atan2(ydiff, xdiff);
  double		dist = xdiff * xdiff + ydiff * ydiff;
  double		coef = 1;

  if (event == BCE_TERMINATE_EVENT || event == BCE_NEXT_EVENT)
    {
      cte.pic->position.x = cte.target.x;
      cte.pic->position.y = cte.target.y;
      return (NULL);
    }
  if (event == BCE_FASTER_EVENT)
    coef = 2;

  cte.pic->position.x += cos(angle) * cte.speed * coef * elapsed;
  cte.pic->position.y += sin(angle) * cte.speed * coef * elapsed;

  xdiff = cte.target.x - cte.pic->position.x;
  ydiff = cte.target.y - cte.pic->position.y;
  double		ndist = xdiff * xdiff + ydiff * ydiff;
  
  if (dist < ndist)
    {
      cte.pic->position = cte.target;
      return (NULL);
    }

  if (argc == 5 && bunny_configuration_getf_string(argv[4], &tmp, ".") && strcasecmp(tmp, "async") == 0)
    return (NULL);
  return (".stay");
}

char			*cinematic_display(PARAMS)
{
  t_bunny_clipable	*pic;
  const char		*str;
  int			i;

  for (i = 0; i < argc; ++i)
    {
      if (!bunny_configuration_getf_string(argv[i], &str, "."))
	goto Bad;
      if (*str == '$') // Variables
	if (!bunny_configuration_getf_string(cin->configuration, &str, "%s", &str[1]))
	  goto Bad;
      if ((pic = bunny_map_get_data(cin->pictures, str, t_bunny_clipable*)) == NULL)
	goto Bad;
      pic->color_mask.argb[ALPHA_CMP] = 255;
    }
  return (NULL);

 Bad:
  scream_error_if(return (""), BE_SYNTAX_ERROR,
		  "Invalid instruction parameter for %s. "
		  "Only valid picture names were expected. "
		  "Line %d in sequence %s",
		  "cinematic,syntax",
		  __func__,
		  cin->current_command,
		  bunny_configuration_get_address(cin->program)
		  );
}

char			*cinematic_hide(PARAMS)
{
  t_bunny_clipable	*pic;
  const char		*str;
  int			i;

  for (i = 0; i < argc; ++i)
    {
      if (!bunny_configuration_getf_string(argv[i], &str, "."))
	goto Bad;
      if (*str == '$') // Variables
	if (!bunny_configuration_getf_string(cin->configuration, &str, "%s", &str[1]))
	  goto Bad;
      if ((pic = bunny_map_get_data(cin->pictures, str, t_bunny_clipable*)) == NULL)
	goto Bad;
      pic->color_mask.argb[ALPHA_CMP] = 0;
    }
  return (NULL);

 Bad:
  scream_error_if(return (""), BE_SYNTAX_ERROR,
		  "Invalid instruction parameter for %s. "
		  "Only valid picture names were expected. "
		  "Line %d in sequence %s",
		  __func__,
		  cin->current_command,
		  bunny_configuration_get_address(cin->program),
		  "cinematic,syntax");
}

char			*cinematic_fadeout(PARAMS)
{
  struct cinematic_fade	*cte = (struct cinematic_fade*)cin->stack_frame;
  double		coef = 1;

  VOID();
  if (argc < 2)
    return ("");
  if (event == BCE_FASTER_EVENT)
    coef = 2;
  if (!cte->init)
    {
      cte->init = true;
      cte->acc = 0;
      if (!bunny_configuration_getf_double(argv[0], &cte->delay, "."))
	return ("");
    }
  else if ((cte->acc += elapsed * coef) >= cte->delay)
    cte->acc = cte->delay;

  if (event == BCE_TERMINATE_EVENT || event == BCE_NEXT_EVENT)
    cte->acc = cte->delay;

  for (int i = 1; i + 1 < argc; i += 2)
    {
      const char	*tmp;

      if (!bunny_configuration_getf_string(argv[i], &tmp, "."))
	return ("");
      if (strcasecmp(tmp, "picture") == 0)
	{
	  t_bunny_picture *pic;

	  if (!bunny_configuration_getf_string(argv[i + 1], &tmp, "."))
	    return ("");
	  if (!(pic = bunny_map_get_data(cin->pictures, tmp, t_bunny_picture*)))
	    return ("");
	  if ((pic->color_mask.argb[ALPHA_CMP] = (1.0 - cte->acc / cte->delay) * 255) < 16)
	    pic->color_mask.argb[ALPHA_CMP] = 0;
	}
      else if (strcasecmp(tmp, "music") == 0)
	{
	}
      else if (strcasecmp(tmp, "effect") == 0)
	{
	}
      else if (strcasecmp(tmp, "voice") == 0)
	{
	}
    }
  if (cte->acc >= cte->delay)
    return (NULL);
  return (".stay");
}

char			*cinematic_fadein(PARAMS)
{
  struct cinematic_fade	*cte = (struct cinematic_fade*)cin->stack_frame;
  double		coef = 1;

  VOID();
  if (argc < 2)
    return ("");
  if (event == BCE_FASTER_EVENT)
    coef = 2;
  if (!cte->init)
    {
      cte->init = true;
      cte->acc = 0;
      if (!bunny_configuration_getf_double(argv[0], &cte->delay, "."))
	return ("");
    }
  else if ((cte->acc += elapsed * coef) >= cte->delay)
    cte->acc = cte->delay;

  if (event == BCE_TERMINATE_EVENT || event == BCE_NEXT_EVENT)
    cte->acc = cte->delay;

  for (int i = 1; i + 1 < argc; i += 2)
    {
      const char	*tmp;

      if (!bunny_configuration_getf_string(argv[i], &tmp, "."))
	return ("");
      if (strcasecmp(tmp, "picture") == 0)
	{
	  t_bunny_picture *pic;

	  if (!bunny_configuration_getf_string(argv[i + 1], &tmp, "."))
	    return ("");
	  if (!(pic = bunny_map_get_data(cin->pictures, tmp, t_bunny_picture*)))
	    return ("");
	  if ((pic->color_mask.argb[ALPHA_CMP] = (cte->acc / cte->delay) * 255) < 16)
	    pic->color_mask.argb[ALPHA_CMP] = 0;
	}
      else if (strcasecmp(tmp, "music") == 0)
	{
	}
      else if (strcasecmp(tmp, "effect") == 0)
	{
	}
      else if (strcasecmp(tmp, "voice") == 0)
	{
	}
    }
  if (cte->acc >= cte->delay)
    return (NULL);
  return (".stay");
}

char			*cinematic_playmusic(PARAMS)
{
  VOID();
  for (int i = 0; i < argc; ++i)
    {
      const char *tmp;
      t_bunny_sound *snd;

      if (!bunny_configuration_getf_string(argv[i], &tmp, "."))
	return ("");
      if ((snd = bunny_map_get_data(cin->musics, tmp, t_bunny_sound*)) == NULL)
	return ("");
      bunny_sound_loop(snd, true);
      bunny_sound_play(snd);
    }
  return (NULL);
}

char			*cinematic_stopmusic(PARAMS)
{
  VOID();
  for (int i = 0; i < argc; ++i)
    {
      const char *tmp;
      t_bunny_sound *snd;

      if (!bunny_configuration_getf_string(argv[i], &tmp, "."))
	return ("");
      if ((snd = bunny_map_get_data(cin->musics, tmp, t_bunny_sound*)) == NULL)
	return ("");
      bunny_sound_stop(snd);
    }
  return (NULL);
}

char			*cinematic_test(PARAMS)
{
  VOID();
  return (NULL);
}

char			*cinematic_go(PARAMS)
{
  VOID();
  const char		*tmp;

  if (argc != 1)
    return ("");
  if (!bunny_configuration_getf_string(argv[0], &tmp, "."))
    return ("");
  return ((char*)tmp);
}

char			*cinematic_trace(PARAMS)
{
  VOID();
  for (int i = 0; i < argc; ++i)
    {
      const char *tmp;

      if (bunny_configuration_getf_string(argv[i], &tmp, "."))
	puts(tmp);
    }
  return (NULL);
}

char			*cinematic_playeffect(PARAMS)
{
  VOID();
  for (int i = 0; i < argc; ++i)
    {
      const char *tmp;
      t_bunny_sound *snd;

      if (!bunny_configuration_getf_string(argv[i], &tmp, "."))
	return ("");
      if ((snd = bunny_map_get_data(cin->effects, tmp, t_bunny_sound*)) == NULL)
	return ("");
      bunny_sound_play(snd);
    }
  return (NULL);
}

char			*cinematic_skipif(PARAMS)
{
  const char		*tmp;
  int			tmpi;

  // skipif picture X position N
  if (argc < 3)
    return ("");
  if (!bunny_configuration_getf_string(argv[0], &tmp, "."))
    return ("");
  if (strcasecmp(tmp, "picture") == 0)
    {
      t_bunny_sprite	*spr;
      int		i;
      bool		ret = true;

      for (i = 1; i < argc;)
	{
	  if (!bunny_configuration_getf_string(argv[i], &tmp, "."))
	    return ("");
	  if (!(spr = bunny_map_get_data(cin->pictures, tmp, t_bunny_sprite*)))
	    return ("");
	  i += 1;
	  if (!bunny_configuration_getf_string(argv[i], &tmp, "."))
	    return ("");
	  i += 1;
	  if (!bunny_configuration_getf_int(argv[i], &tmpi, "."))
	    return ("");
	  i += 1;
	  if (strcasecmp(tmp, "x") == 0 && (int)spr->clipable.position.x != tmpi)
	    ret = false;
	  if (strcasecmp(tmp, "y") == 0 && (int)spr->clipable.position.y != tmpi)
	    ret = false;
	}
      if (ret)
	return (".skip");
    }
  return (NULL);
}

char			*cinematic_noskipif(PARAMS)
{
  const char		*tmp;
  int			tmpi;

  // skipif picture X position N
  if (argc < 3)
    return ("");
  if (!bunny_configuration_getf_string(argv[0], &tmp, "."))
    return ("");
  if (strcasecmp(tmp, "picture") == 0)
    {
      t_bunny_sprite	*spr;
      int		i;

      if (!bunny_configuration_getf_string(argv[1], &tmp, "."))
	return ("");
      if (!(spr = bunny_map_get_data(cin->pictures, tmp, t_bunny_sprite*)))
	return ("");
      for (i = 2; i + 1 < argc; i += 2)
	{
	  if (!bunny_configuration_getf_string(argv[i], &tmp, "."))
	    return ("");
	  if (!bunny_configuration_getf_int(argv[i + 1], &tmpi, "."))
	    return ("");
	  if (strcasecmp(tmp, "x") == 0 && (int)spr->clipable.position.x == tmpi)
	    return (NULL);
	  if (strcasecmp(tmp, "y") == 0 && (int)spr->clipable.position.y == tmpi)
	    return (NULL);
	}
    }
  return (".skip");
}

