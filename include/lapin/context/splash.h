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


/**
 * @doc
 * @doc-symbol splash
 * @doc-kind module
 * @doc-module splash
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Provides the built-in Hanged Bunny Studio splash screen context.
 * @header lapin/context/splash.h
 *
 * @doc-lang fr
 * @brief Fournit le contexte intégré d'écran de démarrage Hanged Bunny Studio.
 * @header lapin/context/splash.h
 */

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


/**
 * @doc
 * @doc-symbol t_bunny_splash_screen
 * @doc-kind struct
 * @doc-module splash
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Runtime data required by the built-in splash screen context.
 * @description Fill the public fields, then run gl_bunny_splash_context with bunny_loop. The file fields are paths to resources loaded by the splash context.
 * @field head Context runtime information and optional subcontext.
 * @field bunny_picture_file Path to the bunny picture configuration or resource.
 * @field rope_picture_file Path to the rope picture configuration or resource.
 * @field title_picture_file Path to the title picture configuration or resource.
 * @field jingle_sound_file Path to the jingle sound.
 * @field boom_sound_file Path to the boom sound.
 * @field outch_sound_file Path to the outch sound.
 * @field falling_sound_file Path to the falling sound.
 * @field _private Private splash context storage. Initialize it to zero and do not modify it.
 * @see gl_bunny_splash_context, bunny_set_context, bunny_loop
 *
 * @doc-lang fr
 * @brief Données d'exécution requises par le contexte intégré d'écran de démarrage.
 * @description Remplissez les champs publics, puis lancez gl_bunny_splash_context avec bunny_loop. Les champs de fichiers sont des chemins vers les ressources chargées par le contexte splash.
 * @field head Informations d'exécution du contexte et sous-contexte optionnel.
 * @field bunny_picture_file Chemin vers la configuration ou ressource de l'image du lapin.
 * @field rope_picture_file Chemin vers la configuration ou ressource de la corde.
 * @field title_picture_file Chemin vers la configuration ou ressource du titre.
 * @field jingle_sound_file Chemin vers le son de jingle.
 * @field boom_sound_file Chemin vers le son boom.
 * @field outch_sound_file Chemin vers le son outch.
 * @field falling_sound_file Chemin vers le son de chute.
 * @field _private Stockage privé du contexte splash. Initialisez-le à zéro et ne le modifiez pas.
 * @see gl_bunny_splash_context, bunny_set_context, bunny_loop
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
  char				_private[512];
}				t_bunny_splash_screen;



/**
 * @doc
 * @doc-symbol gl_bunny_splash_context
 * @doc-kind variable
 * @doc-module splash
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Built-in context descriptor implementing the HBS splash screen.
 * @description Pass this context to bunny_set_context, then call bunny_loop with a configured t_bunny_splash_screen as the user data.
 * @see t_bunny_splash_screen
 *
 * @doc-lang fr
 * @brief Descripteur de contexte intégré implémentant l'écran de démarrage HBS.
 * @description Transmettez ce contexte à bunny_set_context, puis appelez bunny_loop avec un t_bunny_splash_screen configuré comme donnée utilisateur.
 * @see t_bunny_splash_screen
 */
extern const t_bunny_context	gl_bunny_splash_context;


#endif	/*			__LAPIN_SPLASH_H__		*/
