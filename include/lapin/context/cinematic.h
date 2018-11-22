/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file splash.h
**
*/

#ifndef				__LAPIN_CINEMATIC_H__
# define			__LAPIN_CINEMATIC_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** ******************************************************************
** ***************** HANGED BUNNY STUDIO CINEMATIC ******************
** ******************************************************************
**
** A cinematic context that allow to animate stuff on screen throught
** a sequence language.
**
** [CinematicNode
**   BackgroundColor=X
**   [Pictures [* NodeName = "FilePath" / [NodeName Content] *] ]
**   [Voices [* NodeName = "FilePath" / [NodeName Content] *] ]
**   [TextBoxes [* NodeName = "FilePath" / [NodeName Content] *] ]
**   [Effects [* NodeName = "FilePath" / [NodeName Content] *] ]
**   [Musics [* NodeName = "FilePath" / [NodeName Content] *] ]
**   Cinematic = [Sequence
**     'standard sequence commands
**     if expression
**     else
**     endif
**     goto label
**     exec expression
**     wait second
**
**     'cinematic commands
**     play music_name/effect_name/voice_name
**     text box display_fashion string_node [voice] [facepicture]
**   ]
** ]
**
*/
typedef struct			s_bunny_cinematic_screen
{
  t_bunny_context_runtime_info	head;

  // Data that are never cleared
  t_bunny_context_runtime_info	*subhead;
  t_bunny_sound_manager		*sound_manager;
  t_bunny_sequence_fallback_command custom_command;
  const char			*language; // If null, text/talk with fetch [].Language

  // Data that can be cleared but not emptied
  t_bunny_configuration		*cinematic;
  t_bunny_map			*standard_command; /* [string] -> t_bunny_cinematic_command */

  // Data that can be cleared and emptied
  t_bunny_map			*pictures;	/* [string] -> t_bunny_sprite* */
  t_bunny_map			*text_boxes;	/* [string] -> t_bunny_font* */
  t_bunny_map			*voices;	/* [string] -> t_bunny_sound_sprite* */
  t_bunny_map			*effects;	/* [string] -> t_bunny_effect* */
  t_bunny_map			*musics;	/* [string] -> t_bunny_music* */

  t_bunny_color			background_color;
  t_bunny_color			foreground_color;
}				t_bunny_cinematic_screen;

extern const t_bunny_context	gl_bunny_cinematic_context;

bool				bunny_init_cinematic(t_bunny_cinematic_screen	*scr);
void				bunny_clear_cinematic(t_bunny_cinematic_screen	*scr);

bool				bunny_load_cinematic(t_bunny_cinematic_screen	*scr,
						     const char			*file);
void				bunny_empty_cinematic(t_bunny_cinematic_screen	*scr);

t_bunny_response		bunny_cinematic_play(t_bunny_configuration	*seq,
						     const char			*cmd,
						     const char			*params,
						     t_bunny_cinematic_screen	*scr);
t_bunny_response		bunny_cinematic_text(t_bunny_configuration	*seq,
						     const char			*cmd,
						     const char			*params,
						     t_bunny_cinematic_screen	*scr);

#endif	/*			__LAPIN_CINEMATIC_H__			*/

