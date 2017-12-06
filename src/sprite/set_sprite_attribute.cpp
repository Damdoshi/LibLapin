// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	<string.h>
#include	"lapin_private.h"

#define		PATTERN		"%p sprite, %p conf -> %s"

bool		_bunny_set_sprite_attribute(struct bunny_sprite	&sprite,
					    SmallConf		&config)
{
  std::map<std::string, SmallConf*>::iterator it;
  SmallConf	*repet, *aconf, *animnode;
  double	default_delay;
  t_bunny_animation *anim;
  const char	*str;
  unsigned int	i, j;
  int		tmp;

  sprite.current_frame = 0;
  sprite.current_time = 0;
  sprite.current_repeat = 0;
  sprite.current_frame_repeat = 0;

  // MANDATORY FIELDS //

  // ANIMATIONS MAP
  if (config.Access("Animations") == false)
    scream_error_if
      (return (false), BE_SYNTAX_ERROR,
       PATTERN ": An 'Animations' scope was expected",
       "sprite,syntax", &sprite, &config, "false");

  // INITIAL ANIMATION
  if (config.Access("InitialAnimation") == false)
    scream_error_if
      (return (false), BE_SYNTAX_ERROR,
       PATTERN ": An 'InitialAnimation' field was expected",
       "sprite,syntax", &sprite, &config, "false");
  if (config["InitialAnimation"].GetString(&str) == false)
    scream_error_if
      (return (false), BE_SYNTAX_ERROR,
       PATTERN ": Invalid value for 'InitialAnimation' field",
       "sprite,syntax", &sprite, &config, "false");
  if (config["Animations"].Access(str) == false)
    scream_error_if
      (return (false), BE_SYNTAX_ERROR,
       PATTERN ": Unknown animation %s",
       "sprite,syntax", &sprite, &config, "false", str);
  sprite.current_animation = bunny_hash(BH_DJB2, str, strlen(str));

  // ALLOC
  if ((sprite.animation = bunny_new_vector
       (config["Animations"].NbrChild(), t_bunny_animation)) == NULL)
    goto ExitDirectly;
  if ((sprite.hashname_id = bunny_new_map(NULL, NULL, NULL, NULL)) == NULL)
    goto DeleteVector;

  // OPTIONAL FIELDS
  default_delay = -1;
  if (config.Access("Frequency"))
    {
      if (config["Frequency"].GetDouble(&default_delay) == false ||
	  default_delay <= 0)
	scream_error_if
	  (goto DeleteMap, BE_SYNTAX_ERROR,
	   PATTERN ": Invalid 'Frequency' value",
	   "sprite,syntax", &sprite, &config, "false");
      default_delay = 1 / default_delay;
    }

  // ANIMATION FIELDS
  animnode = &config["Animations"];
  for (it = animnode->Begin(), i = 0; it != animnode->End(); ++it, ++i)
    {
      aconf = it->second;
      anim = &bunny_vector_data(sprite.animation, i, t_bunny_animation);
      anim->hash = bunny_hash(BH_DJB2, it->first.c_str(), it->first.size());
      bunny_map_set_data(sprite.hashname_id, anim->hash, i, int);

      // FREQUENCY
      if ((*aconf).Access("Frequency") == false)
	{
	  if (default_delay == -1)
	    scream_error_if
	      (goto DeleteMap, BE_SYNTAX_ERROR,
	       PATTERN ": No 'Frequency' value available for animation '%s'",
	       "sprite,syntax", &sprite, &config, "false", it->first.c_str());
	  anim->delay = default_delay;
	}
      else if ((*aconf)["Frequency"].GetDouble(&anim->delay) == false)
	scream_error_if
	  (goto DeleteMap, BE_SYNTAX_ERROR,
	   PATTERN ": Invalid 'Frequency' value for animation '%s'",
	   "sprite,syntax", &sprite, &config, "false", it->first.c_str());
      else
	anim->delay = 1 / anim->delay;

      // FRAME
      if ((*aconf).Access("Frame") == false
	  || (*aconf)["Frame"].GetInt(&tmp) == false
	  || (anim->nbr_frame = tmp) < 1)
	scream_error_if
	  (goto DeleteMap, BE_SYNTAX_ERROR,
	   PATTERN ": Invalid or absent 'Frame' value for animation '%s'",
	   "sprite,syntax", &sprite, &config, "false", it->first.c_str());

      if ((*aconf).Access("Position") == false
	  || (*aconf)["Position"].Access(0) == false
	  || (*aconf)["Position"].Access(1) == false
	  || (*aconf)["Position"][0].GetInt(&tmp) == false
	  || (anim->position.x = tmp) < 0
	  || (*aconf)["Position"][1].GetInt(&tmp) == false
	  || (anim->position.y = tmp) < 0)
       	scream_error_if
	  (goto DeleteMap, BE_SYNTAX_ERROR,
	   PATTERN ": Invalid or absent 'Position' field for animation '%s'",
	   "sprite,syntax", &sprite, &config, "false", it->first.c_str());

      // REPETITION
      if ((*aconf).Access("FramePlay"))
	{
	  repet = &(*aconf)["FramePlay"];
	  if (repet->Size() != anim->nbr_frame)
	    scream_error_if
	      (goto DeleteMap, BE_SYNTAX_ERROR,
	       PATTERN ": The 'FramePlay' array size must match the amount of "
	       "frame for animation '%s'",
	       "sprite,syntax", &sprite, &config, "false", it->first.c_str());
	  if ((anim->frame_repetition = bunny_new_vector(tmp, int)) == NULL)
	    scream_error_if
	      (goto DeleteMap, ENOMEM,
	       PATTERN ": Not enough memory to store the 'Repetition' array "
	       "for animation '%s'",
	       "sprite,syntax", &sprite, &config, "false", it->first.c_str());
	  for (j = 0; j < anim->nbr_frame; ++j)
	    {
	      if ((*repet)[j].GetInt(&tmp) == false || tmp < 0)
		scream_error_if
		  (goto DeleteMap, BE_SYNTAX_ERROR,
		   PATTERN ": Invalid value 'Repetition[%u]' field for animation '%s'",
		   "sprite,syntax", &sprite, &config, "false", j, it->first.c_str());
	      bunny_vector_data(anim->frame_repetition, j, int) = tmp;
	    }
	}
      else
	anim->frame_repetition = NULL;

      // ANIMATION BROWSING
      if ((*aconf).Access("Browsing"))
	{
	  if ((*aconf)["Browsing"].GetString(&str) == false
	      || (strcmp(str, "LeftToRight")
		  && strcmp(str, "RightToLeft")
		  && strcmp(str, "BackAndForth")))
	    scream_error_if
	      (goto DeleteMap, BE_SYNTAX_ERROR,
	       PATTERN ": Invalid value for 'Browsing' for animation '%s'",
	       "sprite,syntax", &sprite, &config, "false", it->first.c_str());
	  if (strcmp(str, "LeftToRight") == 0)
	    anim->browsing = BFB_LEFT_TO_RIGHT;
	  else if (strcmp(str, "RightToLeft") == 0)
	    anim->browsing = BFB_RIGHT_TO_LEFT;
	  else if (strcmp(str, "BackAndForth") == 0)
	    anim->browsing = BFB_BACK_AND_FORTH;
	}
      else
	anim->browsing = BFB_LEFT_TO_RIGHT;

      // ANIMATION REPEAT
      if ((*aconf).Access("AnimationPlay"))
	{
	  if ((*aconf)["AnimationPlay"].GetInt(&tmp) == false || tmp < -1)
	    scream_error_if
	      (goto DeleteMap, BE_SYNTAX_ERROR,
	       PATTERN ": Invalid value for 'AnimationPlay' for animation '%s'",
	       "sprite,syntax", &sprite, &config, "false", it->first.c_str());
	  anim->animation_repeat = tmp;
	}
      else
	anim->animation_repeat = -1;

      // NEXT ANIMATION
      if ((*aconf).Access("RepeatAnimation"))
	{
	  if ((*aconf)["RepeatAnimation"].GetInt(&tmp) == false || tmp < -1)
	    scream_error_if
	      (goto DeleteMap, BE_SYNTAX_ERROR,
	       PATTERN ": Invalid value for 'RepeatAnimation' for animation '%s'",
	       "sprite,syntax", &sprite, &config, "false", it->first.c_str());
	  anim->animation_repeat = tmp;
	}
      else
	anim->animation_repeat = -1;

      // NEXT ANIMATION
      if ((*aconf).Access("NextAnimation"))
	{
	  if ((*aconf)["NextAnimation"].GetString(&str) == false)
	    scream_error_if
	      (goto DeleteMap, BE_SYNTAX_ERROR,
	       PATTERN ": Invalid value for 'NextAnimation' for animation '%s'",
	       "sprite,syntax", &sprite, &config, "false", it->first.c_str());
	  if (config["Animations"].Access(str) == false)
	    scream_error_if
	      (goto DeleteMap, BE_SYNTAX_ERROR,
	       PATTERN ": Unknown animation %s",
	       "sprite,syntax", &sprite, &config, "false", str);
	  anim->next_animation = bunny_hash(BH_DJB2, str, strlen(str));
	}
      else
	anim->next_animation = -1;
    }
  for (i = 0; i < bunny_vector_size(sprite.animation); ++i)
    {
      anim = &bunny_vector_data(sprite.animation, i, t_bunny_animation);
      if (anim->next_animation != -1)
	anim->next_animation = bunny_map_get_data
	  (sprite.hashname_id, anim->next_animation, int);
    }

  return (true);

 DeleteMap:
  bunny_delete_map(sprite.hashname_id);
 DeleteVector:
  bunny_delete_vector(sprite.animation);
 ExitDirectly:
  return (false);
}

