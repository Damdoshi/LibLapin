// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include			"lapin_private.h"

#define				PATTERN		"%s conf_file, %p sound, %p target_conf, %s is_music -> %s (%s)"

bool				bunny_set_sound_attribute(const char		*conf_file,
							  t_bunny_sound		**sound,
							  t_bunny_configuration **config,
							  bool			is_mus)
{
  t_bunny_sound			*snd;
  const char			*missing_field;
  t_bunny_configuration		*cnf;
  const char			*str;
  int				tmp;

  if (sound == NULL || (cnf = _get_good_conf(conf_file, config)) == NULL)
    scream_error_if(return (false), EINVAL, PATTERN, conf_file, sound, config, is_mus ? "true" : "false", "false", "");

  if (*sound == NULL)
    {
      if (!bunny_configuration_go_get_string(cnf, &str, "RessourceFile[0]"))
	{
	  missing_field = "Missing field RessourceFile";
	  goto InvalidField;
	}
      if (is_mus == false)
	{
	  if ((*sound = (t_bunny_sound*)bunny_load_effect(str)) == NULL)
	    {
	      missing_field = "Cannot load file given by RessourceFile field";
	      goto InvalidField;
	    }
	}
      else
	{
	  if ((*sound = (t_bunny_sound*)bunny_load_music(str)) == NULL)
	    {
	      missing_field = "Cannot load file given by RessourceFile field";
	      goto InvalidField;
	    }
	}
    }
  snd = *sound;

  bunny_configuration_go_get_double(cnf, &snd->volume, "Volume[0]");
  bunny_configuration_go_get_double(cnf, &snd->pitch, "Pitch[0]");
  if (bunny_configuration_go_get_int(cnf, &tmp, "Loop[0]"))
    snd->loop = tmp ? true : false;
  bunny_configuration_go_get_double(cnf, &snd->attenuation, "Attenuation[0]");

  if (bunny_configuration_go_get_double(cnf, &snd->position[0], "Position[0]"))
    if (!bunny_configuration_go_get_double(cnf, &snd->position[1], "Position[1]") ||
	!bunny_configuration_go_get_double(cnf, &snd->position[2], "Position[2]"))
      {
	missing_field = "Missing field Position[1/2]";
	goto InvalidField;
      }

  if (config == NULL)
    bunny_delete_configuration(cnf);
  else
    *config = cnf;
  scream_log_if(PATTERN, conf_file, sound, config, is_mus ? "true" : "false", "true", "");
  return (true);

 InvalidField:
  if (config == NULL || *config == NULL)
    bunny_delete_configuration(cnf);
  scream_error_if(return (false), EINVAL, PATTERN, conf_file, sound, config, is_mus ? "true" : "false", "false", missing_field);
  return (false);
}

