/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_LOADING_SCREEN_H__
# define			__LAPIN_LOADING_SCREEN_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*
** ******************************************************************
** ************************ LOADING SCREEN **************************
** ******************************************************************
**
** This context is a customizable loading screen.
*/

/**
 * @doc
 * @doc-symbol t_bunny_ressource_to_load
 * @doc-kind struct
 * @doc-module context
 * @doc-order 600
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Describes one resource scheduled for the loading context.
 * @field file Resource file path.
 * @field target Pointer to the slot that will receive the loaded resource.
 * @field subtarget Optional output receiving resource-specific count information.
 * @see bunny_add_to_ressource_list
 * @see gl_bunny_loading_context
 *
 * @doc-lang fr
 * @brief Décrit une ressource prévue pour le contexte de chargement.
 * @field file Resource file path.
 * @field target Pointer to the slot that will receive the loaded resource.
 * @field subtarget Optional output receiving resource-specific count information.
 * @see bunny_add_to_ressource_list
 * @see gl_bunny_loading_context
 */
typedef struct			s_bunny_ressource_to_load
{
  const char			*file;
  void				*target;
  size_t			*subtarget;
}				t_bunny_ressource_to_load;

t_bunny_ressource_to_load	*bunny_new_ressource_hook(void);
void				bunny_delete_ressource_hook(t_bunny_ressource_to_load *);
bool				bunny_add_to_ressource_list(t_bunny_list *lst,
							    t_bunny_ressource_to_load *ld,
							    size_t	len);

/**
 * @doc
 * @doc-symbol t_bunny_loading_screen
 * @doc-kind struct
 * @doc-module context
 * @doc-order 610
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Runtime structure of the built-in asynchronous loading context.
 * @field head Common context runtime header.
 * @field pictures Pictures to load.
 * @field pixelarrays Pixelarrays to load.
 * @field sprites Sprites to load.
 * @field musics Musics to load.
 * @field effects Sound effects to load.
 * @field sound_sprites Sound sprites to load.
 * @field texts Text resources to load.
 * @field files Raw files to load.
 * @field configurations Configurations to load.
 * @field percent_completion Current completion ratio.
 * @field terminated True when loading is complete.
 * @see bunny_init_loading_context
 * @see bunny_clear_all_loaded_ressources
 *
 * @doc-lang fr
 * @brief Structure d’exécution du contexte de chargement asynchrone intégré.
 * @field head Common context runtime header.
 * @field pictures Pictures to load.
 * @field pixelarrays Pixelarrays to load.
 * @field sprites Sprites to load.
 * @field musics Musics to load.
 * @field effects Sound effects to load.
 * @field sound_sprites Sound sprites to load.
 * @field texts Text resources to load.
 * @field files Raw files to load.
 * @field configurations Configurations to load.
 * @field percent_completion Current completion ratio.
 * @field terminated True when loading is complete.
 * @see bunny_init_loading_context
 * @see bunny_clear_all_loaded_ressources
 */
typedef struct			s_bunny_loading_screen
{
  t_bunny_context_runtime_info	head;
  t_bunny_list			*pictures;
  t_bunny_list			*pixelarrays;
  t_bunny_list			*sprites;
  t_bunny_list			*musics;
  t_bunny_list			*effects;
  t_bunny_list			*sound_sprites;
  t_bunny_list			*texts;
  t_bunny_list			*files;
  t_bunny_list			*configurations;
  double			percent_completion;
  bool				terminated;
  const char			_private[512];
}				t_bunny_loading_screen;

extern const t_bunny_context	gl_bunny_loading_context;

bool				bunny_init_loading_context(t_bunny_loading_screen *);
void				bunny_terminate_loading_context(t_bunny_loading_screen *);

void				bunny_clear_all_loaded_ressources(t_bunny_loading_screen *s);

#endif	/*			__LAPIN_LOADING_SCREEN_H__	*/
