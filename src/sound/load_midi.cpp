// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"fluidsynth.h"
#include		"lapin_private.h"

#define			PATTERN		"%s midi file, %s sound font file -> %p"

fluid_settings_t	*gl_fluid_settings = NULL;
fluid_synth_t		*gl_fluid_synth = NULL;
fluid_audio_driver_t	*gl_fluid_driver = NULL;
fluid_midi_router_t	*gl_fluid_router = NULL;

void			clear_fluid(void)
{
  if (gl_fluid_router)
    {
      delete_fluid_midi_router(gl_fluid_router);
      gl_fluid_router = NULL;
    }
  if (gl_fluid_driver)
    {
      delete_fluid_audio_driver(gl_fluid_driver);
      gl_fluid_driver = NULL;
    }
  if (gl_fluid_synth)
    {
      delete_fluid_synth(gl_fluid_synth);
      gl_fluid_synth = NULL;
    }
  if (gl_fluid_settings)
    {
      delete_fluid_settings(gl_fluid_settings);
      gl_fluid_settings = NULL;
    }
}

t_bunny_music		*bunny_load_midi(const char		*midfile,
					 const char		*sffile)
{
  struct bunny_midi	*mid;
  char			buf[512];
  uint64_t		hash;

  if (midfile == NULL && sffile == NULL)
    {
      clear_fluid();
      return (NULL);
    }

  if (gl_fluid_driver == NULL)
    {
      if ((gl_fluid_settings = new_fluid_settings()) == NULL)
	return (NULL);
      if ((gl_fluid_synth = new_fluid_synth(gl_fluid_settings)) == NULL)
	{
	  clear_fluid();
	  return (NULL);
	}
      if ((gl_fluid_driver = new_fluid_audio_driver(gl_fluid_settings, gl_fluid_synth)) == NULL)
	{
	  clear_fluid();
	  return (NULL);
	}
      if ((gl_fluid_router = new_fluid_midi_router(gl_fluid_settings, fluid_synth_handle_midi_event, (void *)gl_fluid_synth)) == NULL)
	{
	  clear_fluid();
	  return (NULL);
	}
      atexit(clear_fluid);
    }

  if ((mid = new (std::nothrow) struct bunny_midi) == NULL)
    return (NULL);
  memset(mid, 0, sizeof(*mid));

  hash = bunny_hash(BH_FNV, sffile, strlen(sffile));
  if (RessourceManager.disable_manager)
    {
      if ((mid->font_id = (int)(size_t)RessourceManager.TryGet
	   (ResManager::FLUID_FONT, hash)) == 0)
	{
	  if ((mid->font_id = fluid_synth_sfload(gl_fluid_synth, sffile, 1)) == 0)
	    goto Fail;
	  if ((mid->font = fluid_synth_get_sfont_by_id
	       (gl_fluid_synth, mid->font_id)) == NULL)
	    goto Fail;
	}
      mid->font = fluid_synth_get_sfont_by_id(gl_fluid_synth, mid->font_id);
    }

  hash = bunny_hash(BH_FNV, midfile, strlen(midfile));
  if (RessourceManager.disable_manager ||
      (mid->player = (fluid_player_t*)RessourceManager.TryGet
       (ResManager::FLUID_PLAYER, hash)) == NULL)
    {
      if ((mid->player = new_fluid_player(gl_fluid_synth)) == NULL)
	goto Fail;
      if (fluid_player_add(mid->player, midfile) == FLUID_FAILED)
	goto Fail;
    }

  if (RessourceManager.disable_manager == false)
    {
      RessourceManager.AddToPool
	(ResManager::FLUID_FONT, sffile, hash, mid, (void*)(size_t)mid->font_id);
      RessourceManager.AddToPool
	(ResManager::FLUID_PLAYER, midfile, hash, mid, mid->player);
    }

  fluid_player_set_loop(mid->player, true);

  snprintf(&buf[0], sizeof(buf), "%s%s", midfile, sffile);
  mid->file = bunny_strdup(&buf[0]);
  mid->type = MIDI;
  mid->duration = 0;
  mid->volume = 50;
  mid->pitch = 1;
  mid->loop = true;
  mid->position[0] = 0;
  mid->position[1] = 0;
  mid->position[2] = 0;
  mid->attenuation = 5;
  mid->playing = false;
  mid->pause = false;
  mid->sound_manager = NULL;

  scream_log_if(PATTERN, "ressource,sound", midfile, sffile, mid);
  return ((t_bunny_music*)mid);

 Fail:
#warning potential bugs
  // And what if player failed and mid font is from the ressource manager?
  // you did not thought about that, uh? stupid
  if (mid->font)
    fluid_synth_sfunload(gl_fluid_synth, mid->font_id, 0);
  if (mid->player)
    delete_fluid_player(mid->player);
  delete mid;
  scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,sound", midfile, sffile, (void*)NULL);
  return (NULL);
}
