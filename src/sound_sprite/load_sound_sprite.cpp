// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%p -> %p"

t_bunny_sound_sprite	*bunny_read_sound_sprite(t_bunny_configuration	*_cnf)
{
  t_bunny_sound_sprite	*ss;
  t_bunny_sound		*snd;
  int			tmp;

  if ((ss = (t_bunny_sound_sprite*)bunny_read_music(_cnf)) == NULL)
    return (NULL);
  if (bunny_configuration_go_get_int(_cnf, &tmp, "Loop[0]"))
    ss->soundset.sound.loop = tmp ? true : false;
  else
    ss->soundset.sound.loop = false;

  if ((ss->sound_areas = bunny_new_map(NULL, NULL, NULL, NULL)) == NULL)
    {
      bunny_delete_sound(&ss->soundset.sound);
      return (NULL);
    }
  std::map<std::string, SmallConf*>::iterator it;
  SmallConf		&cnf = *(SmallConf*)_cnf;
  SmallConf		*arr, *slice;

  if (cnf.Access("Slices") == false)
    scream_error_if
      (goto DeleteAll, BE_SYNTAX_ERROR,
       PATTERN ": A 'Slices' scope was expected",
       "ressource,sound_sprite,syntax", _cnf, (void*)NULL);

  arr = &cnf["Slices"];
  for (it = arr->Begin(); it != arr->End(); ++it)
    {
      t_bunny_sound_slice *s;

      slice = it->second;
      if ((s = (t_bunny_sound_slice*)bunny_malloc(sizeof(*s))) == NULL)
	goto DeleteAll;

      s->id = bunny_sound_sprite_slice_name(it->first.c_str());
      s->sound.volume = ss->soundset.sound.volume;
      s->sound.loop = ss->soundset.sound.loop;
      s->sound.pitch = ss->soundset.sound.pitch;
      s->sound.attenuation = ss->soundset.sound.attenuation;
      s->sound.position[0] = ss->soundset.sound.position[0];
      s->sound.position[1] = ss->soundset.sound.position[1];
      s->sound.position[2] = ss->soundset.sound.position[2];

      ////////////////////////////////////////

      if (bunny_configuration_read_time(slice, "Index", &s->index) == false)
	goto DeleteAllLoop;
      s->active_start = s->index;

      ////////////////////////////////////////

      if (slice->Access("EndIndex"))
	{
	  if (bunny_configuration_read_time(slice, "EndIndex", &s->duration) == false)
	    goto DeleteAllLoop;
	  if (s->duration < s->index)
	    scream_error_if
	      (goto DeleteAllLoop, BE_SYNTAX_ERROR,
	       PATTERN ": EndIndex cannot be lesser than Index",
	       "ressource,sound_sprite,syntax", _cnf, (void*)NULL);
	  s->duration = s->duration - s->index;
	}
      else if (bunny_configuration_read_time(slice, "Duration", &s->duration) == false)
	goto DeleteAllLoop;
      s->active_duration = s->duration;

      ////////////////////////////////////////
      // OPTIONAL
      if (slice->Access("ActiveEnd"))
	{
	  if (bunny_configuration_read_time(slice, "ActiveEnd", &s->active_duration) == false)
	    goto DeleteAllLoop;
	  if (s->active_duration < s->index)
	    scream_error_if
	      (goto DeleteAllLoop, BE_SYNTAX_ERROR,
	       PATTERN ": ActiveEnd cannot be lesser than Index",
	       "ressource,sound_sprite,syntax", _cnf, (void*)NULL);
	  s->active_duration = s->active_duration - s->index;
	}
      else if (slice->Access("ActiveDuration"))
	if (bunny_configuration_read_time
	    (slice, "ActiveDuration", &s->active_duration) == false)
	  goto DeleteAllLoop;

      ////////////////////////////////////////
      // OPTIONAL
      if (slice->Access("ActiveIndex"))
	{
	  if (bunny_configuration_read_time(slice, "ActiveIndex", &s->active_start) == false)
	    goto DeleteAllLoop;
	}
      else if (slice->Access("ActiveStart"))
	{
	  if (bunny_configuration_read_time(slice, "ActiveStart", &s->active_start) == false)
	    goto DeleteAllLoop;
	  s->active_start = s->active_start + s->index;
	}

      ////////////////////////////////////////
      // SET SOUND

      snd = &s->sound;
      if (bunny_set_sound_attribute
	  (NULL, &snd, (t_bunny_configuration**)&slice, true) == false)
	scream_error_if
	  (goto DeleteAllLoop, bunny_errno,
	   PATTERN ": An error happen when retrieving sound attributes.",
	   "ressource,sound_sprite,syntax", _cnf, (void*)NULL);

      s->sound.loop = false;
      if (bunny_map_set_data
	  (ss->sound_areas,
	   bunny_sound_sprite_slice_name(it->first.c_str()),
	   s,
	   t_bunny_sound_slice*) == NULL)
	scream_error_if
	  (goto DeleteAllLoop, bunny_errno,
	   PATTERN ": Cannot add the sound slice into the sound sprite",
	   "ressource,sound_sprite", _cnf, (void*)NULL);

      continue;
    DeleteAllLoop:
      bunny_free(s);
      goto DeleteAll;
    }

  *(t_bunny_sound_slice**)&ss->last_played_slice = NULL;
  *(t_bunny_music_track*)&ss->track = BST_LAST_TRACK;
  scream_log_if(PATTERN, "ressource,sound_sprite", _cnf, ss);
  return (ss);

 DeleteAll:
  bunny_map_foreach(ss->sound_areas, bunny_foreach_map_bunny_free, NULL);
  bunny_delete_map(ss->sound_areas);
  bunny_delete_sound(&ss->soundset.sound);
  return (NULL);
}

t_bunny_sound_sprite	*bunny_load_sound_sprite(const char	*file)
{
  t_bunny_sound_sprite	*spr;
  t_bunny_configuration	*cnf;

  if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  spr = bunny_read_sound_sprite(cnf);
  bunny_delete_configuration(cnf);
  return (spr);
}
