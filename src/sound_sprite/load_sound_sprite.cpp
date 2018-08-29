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
       "ressource,sound_sprite,syntax", cnf, (void*)NULL);
  arr = &cnf["Slices"];
  for (it = arr->Begin(); it != arr->End(); ++it)
    {
      t_bunny_sound_slice *s;

      slice = it->second;
      if (slice->Access("Index") == false
	  || slice->Access("Duration") == false)
	scream_error_if
	  (goto DeleteAll, BE_SYNTAX_ERROR,
	   PATTERN ": Inside 'Slices', field must be 2 length long for index and duration",
	   "ressource,sound_sprite,syntax", _cnf, (void*)NULL);

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

      if ((*slice)["Index"].GetDouble(&s->index) == false)
	{
	  bunny_free(s);
	  scream_error_if
	    (goto DeleteAll, BE_SYNTAX_ERROR,
	     PATTERN ": A double was expected inside 'Index'",
	     "ressource,sound_sprite,syntax", _cnf, (void*)NULL);
	}
      if ((*slice)["Duration"].GetDouble(&s->duration) == false)
	{
	  bunny_free(s);
	  scream_error_if
	    (goto DeleteAll, BE_SYNTAX_ERROR,
	     PATTERN ": A double was expected inside 'Duration'",
	     "ressource,sound_sprite,syntax", _cnf, (void*)NULL);
	}
      s->active_duration = s->duration;
      if (slice->Access("ActiveDuration"))
	{
	  if ((*slice)["ActiveDuration"].GetDouble(&s->active_duration) == false)
	    {
	      bunny_free(s);
	      scream_error_if
		(goto DeleteAll, BE_SYNTAX_ERROR,
		 PATTERN ": A double was expected inside 'ActiveDuration'",
		 "ressource,sound_sprite,syntax", _cnf, (void*)NULL);
	    }
	}
      s->active_start = 0;
      if (slice->Access("ActiveStart"))
	{
	  if ((*slice)["ActiveStart"].GetDouble(&s->active_duration) == false)
	    {
	      bunny_free(s);
	      scream_error_if
		(goto DeleteAll, BE_SYNTAX_ERROR,
		 PATTERN ": A double was expected inside 'ActiveStart'",
		 "ressource,sound_sprite,syntax", _cnf, (void*)NULL);
	    }
	}
      t_bunny_sound	*snd = &s->sound;

      if (bunny_set_sound_attribute
	  (NULL, &snd, (t_bunny_configuration**)&slice, true) == false)
	{
	  bunny_free(s);
	  scream_error_if
	    (goto DeleteAll, bunny_errno,
	     PATTERN ": An error happen when retrieving sound attributes.",
	     "ressource,sound_sprite,syntax", _cnf, (void*)NULL);
	}
      s->sound.loop = false;
      if (bunny_map_set_data
	  (ss->sound_areas,
	   bunny_sound_sprite_slice_name(it->first.c_str()),
	   s,
	   t_bunny_sound_slice*) == NULL)
	{
	  bunny_free(s);
	  scream_error_if
	    (goto DeleteAll, bunny_errno,
	     PATTERN ": Cannot add the sound slice into the sound sprite",
	     "ressource,sound_sprite", _cnf, (void*)NULL);
	}
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
