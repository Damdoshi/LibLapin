// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		"lapin_private.h"

#define			tcc t_bunny_cinematic_command

// La valeur de retour, c'est ou il faut aller.
// NULL pour l'instruction suivante
// "stay" pour rester ici
// "back" pour revenir a l'instruction d'avant
// "skip" pour sauter la prochaine instruction
typedef char		*t_cinematic_command(struct bunny_cinematic	*cin,
					     int			argc,
					     t_bunny_configuration	**argv,
					     t_bunny_cinematic_event	event,
					     double			elapsed);

/*
    {"sleep", &hbs::Cinematic::SleepCommand, true},
    {"text", &hbs::Cinematic::TextCommand, true},
    {"fadeout", &hbs::Cinematic::FadeCommand, true},
    {"fadein", &hbs::Cinematic::FadeCommand, true},
    {"show", &hbs::Cinematic::FadeCommand, true},
    {"move", &hbs::Cinematic::MoveCommand, true},
    {"place", &hbs::Cinematic::PlaceCommand, true},
    {"hide", &hbs::Cinematic::HideCommand, false},
    {"show", &hbs::Cinematic::HideCommand, false},
    {"go", &hbs::Cinematic::GoToCommand, false},
    {"skipif", &hbs::Cinematic::IfCommand, false},
    {"tweak", &hbs::Cinematic::TweakCommand, false},

    {"trace", &hbs::Cinematic::DebugCommand, false},
    {"display", &hbs::Cinematic::DisplayCommand, false},

    {"animate", &hbs::Cinematic::AnimateCommand, false}, // Anime de frame 0 a n
    {"displayx", &hbs::Cinematic::DisplayXCommand, false},
    {"hidex", &hbs::Cinematic::HideXCommand, false},
    {"color", &hbs::Cinematic::ColorCommand, false},
    {"label", &hbs::Cinematic::LabelCommand, false},
    {"notskipif", &hbs::Cinematic::IfCommand, false},

    {"else", &hbs::Cinematic::ElseCommand, false},
    {"endif", &hbs::Cinematic::EndIfCommand, false},
    {"playmusic", &hbs::Cinematic::PlayMusicCommand, false},
    {"stopmusic", &hbs::Cinematic::StopMusicCommand, false},
    {"playeffect", &hbs::Cinematic::PlayEffectCommand, false},
    {"playvoice", &hbs::Cinematic::PlayVoiceCommand, false}
*/

t_cinematic_command
  cinematic_refresh,
  cinematic_sleep,
  cinematic_backcolor,
  cinematic_forecolor,
  cinematic_text,
  cinematic_tweak,
  cinematic_move,
  cinematic_display,
  cinematic_hide,
  cinematic_fadeout,
  cinematic_fadein,
  cinematic_playmusic,
  cinematic_stopmusic,
  cinematic_test,
  cinematic_math,
  cinematic_go,
  cinematic_trace,
  cinematic_playeffect,
  cinematic_skipif,
  cinematic_noskipif
  ;

static bool		cinematic_load_assets(struct bunny_cinematic	*cin,
					      t_bunny_configuration	*cnf,
					      const char		*language)
{
  t_bunny_configuration	*section;
  t_bunny_configuration	*node;
  char			*str;

  bunny_configuration_getf_double(cnf, &cin->volumes.music, "Volumes.Music");
  bunny_configuration_getf_double(cnf, &cin->volumes.voice, "Volumes.Voice");
  bunny_configuration_getf_double(cnf, &cin->volumes.effect, "Volumes.Effect");

  if (bunny_configuration_getf_node(cnf, &section, "Pictures"))
    for (bunny_configuration_all_children(section, node))
      {
	t_bunny_sprite	*spr;

	if (bunny_configuration_getf_string(node, (const char**)&str, "."))
	  spr = bunny_load_sprite(str);
	else
	  spr = bunny_read_sprite(node);
	if (!spr)
	  return (false);
	spr->clipable.color_mask.argb[ALPHA_CMP] = 0;
	str = (char*)bunny_configuration_get_name(node);
	if (_bunny_map_set_data(cin->pictures, str, spr) == NULL)
	  {
	    bunny_delete_clipable(&spr->clipable);
	    return (false);
	  }
      }

  if (bunny_configuration_getf_node(cnf, &section, "Musics"))
    for (bunny_configuration_all_children(section, node))
      {
	t_bunny_music	*mus;

	if (bunny_configuration_getf_string(node, (const char **)&str, "."))
	  mus = bunny_load_music(str);
	else
	  mus = bunny_read_music(node);
	if (!mus)
	  return (false);
	bunny_sound_volume(&mus->sound, cin->volumes.music * 100);
	str = (char*)bunny_configuration_get_name(node);
	if (_bunny_map_set_data(cin->musics, str, mus) == NULL)
	  {
	    bunny_delete_sound(&mus->sound);
	    return (false);
	  }
      }

  if (bunny_configuration_getf_node(cnf, &section, "Effects"))
    for (bunny_configuration_all_children(section, node))
      {
	t_bunny_effect	*eff;

	if (bunny_configuration_getf_string(node, (const char **)&str, "."))
	  eff = bunny_load_effect(str);
	else
	  return ("");
	if (!eff)
	  return (false);
	bunny_sound_volume(&eff->sound, cin->volumes.effect * 100);
	str = (char*)bunny_configuration_get_name(node);
	if (_bunny_map_set_data(cin->effects, str, eff) == NULL)
	  {
	    bunny_delete_sound(&eff->sound);
	    return (false);
	  }
      }

  if (bunny_configuration_getf_node(cnf, &section, "Voices"))
    for (bunny_configuration_all_children(section, node))
      {
	t_bunny_sound_sprite *voi;

	if (bunny_configuration_getf_string(node, (const char **)&str, "."))
	  voi = bunny_load_sound_sprite(str);
	else
	  voi = bunny_read_sound_sprite(node);
	if (!voi)
	  return (false);
	bunny_sound_volume(&voi->soundset.sound, cin->volumes.voice * 100);
	str = (char*)bunny_configuration_get_name(node);
	if (_bunny_map_set_data(cin->voices, str, voi) == NULL)
	  {
	    bunny_delete_sound(&voi->soundset.sound);
	    return (false);
	  }
      }

  if (bunny_configuration_getf_node(cnf, &section, "Fonts"))
    for (bunny_configuration_all_children(section, node))
      {
	t_bunny_font	*fnt;

	if (bunny_configuration_getf_string(node, (const char **)&str, "."))
	  fnt = bunny_load_text(str);
	else
	  fnt = bunny_read_textbox(node);
	if (!fnt)
	  return (false);
	str = (char*)bunny_configuration_get_name(node);
	if (_bunny_map_set_data(cin->fonts, str, fnt) == NULL)
	  {
	    bunny_delete_clipable(&fnt->clipable);
	    return (false);
	  }
      }

  if (bunny_configuration_getf_node(cnf, &section, "Texts.%s", language))
    for (bunny_configuration_all_children(section, node))
      {
	char		*txt;

	if (!bunny_configuration_getf_string(node, (const char **)&txt, "."))
	  return (false);
	str = (char*)bunny_configuration_get_name(node);
	if (_bunny_map_set_data(cin->texts, str, txt) == NULL)
	  return (false);
      }

  bunny_map_set_data(cin->commands, "sleep", cinematic_sleep, tcc);
  bunny_map_set_data(cin->commands, "backcolor", cinematic_backcolor, tcc);
  bunny_map_set_data(cin->commands, "forecolor", cinematic_forecolor, tcc);
  bunny_map_set_data(cin->commands, "text", cinematic_text, tcc);
  bunny_map_set_data(cin->commands, "tweak", cinematic_tweak, tcc);
  bunny_map_set_data(cin->commands, "move", cinematic_move, tcc);
  bunny_map_set_data(cin->commands, "display", cinematic_display, tcc);
  bunny_map_set_data(cin->commands, "show", cinematic_display, tcc);
  bunny_map_set_data(cin->commands, "hide", cinematic_hide, tcc);
  bunny_map_set_data(cin->commands, "fadeout", cinematic_fadeout, tcc);
  bunny_map_set_data(cin->commands, "fadein", cinematic_fadein, tcc);
  bunny_map_set_data(cin->commands, "playmusic", cinematic_playmusic, tcc);
  bunny_map_set_data(cin->commands, "stopmusic", cinematic_stopmusic, tcc);
  bunny_map_set_data(cin->commands, "play_music", cinematic_playmusic, tcc);
  bunny_map_set_data(cin->commands, "stop_music", cinematic_stopmusic, tcc);

  bunny_map_set_data(cin->commands, "skipif", cinematic_skipif, tcc);
  bunny_map_set_data(cin->commands, "go", cinematic_go, tcc);
  bunny_map_set_data(cin->commands, "playeffect", cinematic_playeffect, tcc);
  bunny_map_set_data(cin->commands, "play_effect", cinematic_playeffect, tcc);
  bunny_map_set_data(cin->commands, "trace", cinematic_trace, tcc);
  bunny_map_set_data(cin->commands, "refresh", cinematic_refresh, tcc);

  cin->current_command = 0;
  memset(cin->command_data, 0, sizeof(cin->command_data));
  cin->stack_top = 0;
  cin->stack_frame = cin->command_data[cin->stack_top];
  memset(cin->stack_frame, 0, sizeof(cin->command_data[0]));

  cin->background_color.full = PINK2;
  cin->foreground_color.full = TRANSPARENT;

  return (true);
}

t_bunny_cinematic	*bunny_read_cinematic_wh(t_bunny_configuration	*cnf,
						 unsigned int		w,
						 unsigned int		h,
						 const char		*language)
{
  struct bunny_cinematic *cin;
  size_t		i;

  if ((cin = new (std::nothrow) struct bunny_cinematic) == NULL)
    return (NULL);
  cin->configuration = cnf;
  if (!bunny_configuration_getf_node(cnf, &cin->program, "Animation"))
    return (NULL);
  if ((cin->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteCin;
  if ((cin->texture = new (std::nothrow) sf::RenderTexture) == NULL)
    goto DeleteSprite;
  if (cin->texture->create(w, h) == false)
    goto DeleteTexture;

  cin->res_id = 0;
  cin->tex = &cin->texture->getTexture();
  cin->type = CINEMATIC;
  cin->width = cin->rect.w = w;
  cin->height = cin->rect.h = h;
  cin->rect.x = cin->rect.y = 0;
  cin->position.x = cin->position.y = 0;
  cin->origin.x = cin->origin.y = 0;
  cin->scale.x = cin->scale.y = 1.0;
  cin->rotation = 0;
  cin->color_mask.full = WHITE;
  cin->smooth = cin->mosaic = false;

  if (bunny_set_clipable_attribute(NULL, (t_bunny_clipable**)&cin, &cnf, BCT_CINEMATIC) == false)
    goto DeleteTexture;
  for (i = 0; i < NBRCELL(cin->maps); ++i)
    cin->maps[i] = NULL;
  for (i = 0; i < NBRCELL(cin->maps); ++i)
    if ((cin->maps[i] = bunny_new_map(string_map)) == NULL)
      goto DeleteMaps;

  cin->volumes.music = 0.6;
  cin->volumes.effect = 0.8;
  cin->volumes.voice = 1.0;

  if (!cinematic_load_assets(cin, cnf, language))
    {
      bunny_delete_cinematic((t_bunny_cinematic*)cin);
      return (NULL);
    }

  return ((t_bunny_cinematic*)cin);

 DeleteMaps:
  for (i = 0; i < NBRCELL(cin->maps); ++i)
    if (cin->maps[i])
      bunny_delete_map(cin->maps[i]);
 DeleteTexture:
  delete cin->texture;
 DeleteSprite:
  delete cin->sprite;
 DeleteCin:
  delete cin;
  return (NULL);
}

t_bunny_cinematic	*bunny_read_cinematic(t_bunny_configuration	*cnf,
					      const char		*language)
{
  int			w;
  int			h;

  if (!bunny_configuration_getf_int(cnf, &w, "Size[0]"))
    return (NULL);
  if (!bunny_configuration_getf_int(cnf, &h, "Size[1]"))
    return (NULL);
  return (bunny_read_cinematic_wh(cnf, w, h, language));
}
