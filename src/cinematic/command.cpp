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
    t_bunny_event *event __attribute__((unused)),	\
    double elapsed __attribute__((unused))
#define			VOID() (void)cin; (void)argc; (void)argv; (void)elapsed

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

  if (cte->init)
    {
      if (!event)
	{
	  size_t	tlen = strlen(cte->tex);

	  if ((cte->fnt->string_len += elapsed * fabs(cte->speed)) >= tlen)
	    {
	      cte->fnt->string_len = tlen;
	      if (cte->speed < 0)
		return (NULL);
	    }
	  return (".stay");
	}
      if (event->type == BET_KEY_RELEASED)
	{
	  /////////////////
	}

      /// Gestion des events
      return (NULL);
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
  if (!bunny_configuration_getf_int(argv[1], &cte->speed, "."))
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

  // Pour la voix
  if (argc <= 3)
    return (".stay");

  if (!bunny_configuration_getf_string(argv[3], &str, "."))
    goto BadCommand;
  if ((cte->voi = bunny_map_get_data(cin->voices, str, t_bunny_sound_sprite*)) == NULL)
    scream_error_if(return (""), BE_SYNTAX_ERROR,
		    "Invalid %s instruction parameter. "
		    "Unknown voice named %s."
		    "Line %d in sequence %s",
		    "cinematic,syntax",
		    __func__, str,
		    cin->current_command,
		    bunny_configuration_get_address(cin->program)
		    );

  cte->fnt->string_len = 0;
  cte->fnt->string = cte->tex;

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
  VOID();
  return (NULL);
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

char			*cinematic_fade(PARAMS)
{
  VOID();
  return (NULL);
}

char			*cinematic_start_music(PARAMS)
{
  VOID();
  return (NULL);
}

char			*cinematic_stop_music(PARAMS)
{
  VOID();
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
  return (NULL);
}
