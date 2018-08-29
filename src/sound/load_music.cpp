// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%s -> %p"

t_bunny_music		*bunny_read_music(t_bunny_configuration	*cnf)
{
  t_bunny_sound		*pc = NULL;

  if (bunny_set_sound_attribute(NULL, &pc, &cnf, true) == false)
    return (NULL);
  return ((t_bunny_music*)pc);
}

t_bunny_music		*bunny_load_music(const char		*file)
{
  struct bunny_music	*mus;

  if (bunny_which_format(file) != BC_CUSTOM)
    {
      t_bunny_configuration *cnf;

      if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
	return (NULL);
      mus = (struct bunny_music*)bunny_read_music(cnf);
      bunny_delete_configuration(cnf);
      return ((t_bunny_music*)mus);
    }

  if ((mus = new (std::nothrow) struct bunny_music) == NULL)
    goto Fail;
  if ((mus->music.openFromFile(file)) == false)
    goto FailStruct;

  mus->file = bunny_strdup(file);
  mus->type = MUSIC;
  mus->duration = mus->music.getDuration().asSeconds();

  mus->volume = 50;
  mus->pitch = 1;
  mus->loop = true;
  mus->position[0] = 0;
  mus->position[1] = 0;
  mus->position[2] = 0;
  mus->attenuation = 5;
  mus->playing = false;
  mus->pause = false;
  mus->sound_manager = NULL;
  mus->sound_areas = NULL;

  scream_log_if(PATTERN, "ressource,sound", file, mus);
  return ((t_bunny_music*)mus);

 FailStruct:
  delete mus;
 Fail:
  scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,sound", file, (void*)NULL);
  return (NULL);
}
