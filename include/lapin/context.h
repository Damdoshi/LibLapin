/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file context.h
** Library of already programmed context that fulfill different purpose.
** Consider this part as modules to insert or tweak to insert in your program
** directly and not like a toolbox like other part of the bunny library.
*/

#ifndef				__LAPIN_CONTEXT_H__
# define			__LAPIN_CONTEXT_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** This structure is the corner stone of every context.
** All context defined in the bunny library will lay on it
** to work. They need you to set those fields before using
** them.
**
** The main_structure pointer is present to be set to your
** data address. It is mainly present to be passed to
** callbacks that may be additionnally provided by the context.
** It is also present in case you wish to create your own
** context with this "standard".
**
** The subcontext will allow you to do set callbacks that will
** be called by the foreground context. Note that those calls
** entirely depends of the context. About the return value,
** the behaviour should always to return the first not GO_ON
** value to bunny_loop.
**
** The screen pointer is the area where the pixel will be
** drawn. It may be the window, it may be something else.
**
** The next_context field is the id of the context that
** should be used after leaving the current one.
**
**
**
** A quite interesting exemple mixing the usage of a t_bunny_picture
** for screen and an additionnal display function in subcontext would
** be to resize the graphic output.
*/
typedef struct			s_bunny_context_runtime_info
{
  void				*main_structure;
  t_bunny_context		subcontext;
  t_bunny_buffer		*screen;
  size_t			next_context;
}				t_bunny_context_runtime_info;

/*!
** ******************************************************************
** ************** HANGED BUNNY STUDIO SPLASH SCREEN *****************
** ******************************************************************
**
** This context is the HBS splash screen.
** To use it, you need to provide a full runtime info,
** the path for the bunny, rope and title picture file.
** Once set, simply call bunny_set_context with
** the gl_bunny_splash_context and call bunny_loop
** with your window, any amount of frame per seconds
** and your t_bunny_splash_screen instance as third parameter.
**
** All *_file can be found in the ressources/ folder at the root
** of the repository. Use INI files, not directly ressource:
** they will be used throught bunny_load_* and bunny_set_*_attribute.
** See example/misc/splash for a complexe example.
**
** Note that the subcontext display function is called at the end
** of the splash context display function, so you may set a t_bunny_picture
** as screen instead of a t_bunny_window and blit it on window after
** resizing.
** If not set, the context will consider the screen to be a window
** and display it.
*/
typedef struct			s_bunny_splash_screen
{
  // Public fields - set them
  t_bunny_context_runtime_info	head;
  char				*bunny_picture_file;
  char				*rope_picture_file;
  char				*title_picture_file;
  char				*jingle_sound_file;
  char				*boom_sound_file;
  char				*outch_sound_file;
  char				*falling_sound_file;

  // Private fields - do not set them
  size_t			animation_step;
  double			time_counter;
  double			middle_of_screen;
  double			bunny_fall_speed;
  double			rope_wave_length;
  double			rope_amplitude;
  double			shake_amplitude;
  double			up_speed;
  bool				jingle_played;

  t_bunny_picture		*bunny;
  t_bunny_picture		*rope;
  t_bunny_picture		*title;
  t_bunny_effect		*jingle;
  t_bunny_effect		*boom;
  t_bunny_effect		*outch;
  t_bunny_effect		*falling;
}				t_bunny_splash_screen;

extern const t_bunny_context	gl_bunny_splash_context;

/*!
** ******************************************************************
** ************** HANGED BUNNY STUDIO DEPTH ENGINE ******************
** ******************************************************************
**
** This context is the HBS Depth graphic engine.
**
**
*/

typedef struct			s_bunny_depth_engine
{
  t_bunny_context_runtime_info	head;

  t_bunny_position		map_size;
}				t_bunny_depth_engine;

#endif	/*			__LAPIN_CONTEXT_H__			*/
