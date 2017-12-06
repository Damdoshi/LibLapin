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

#ifndef				__LAPIN_SPLASH_H__
# define			__LAPIN_SPLASH_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

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
  const char			_private[512];
}				t_bunny_splash_screen;

extern const t_bunny_context	gl_bunny_splash_context;


#endif	/*			__LAPIN_SPLASH_H__		*/
