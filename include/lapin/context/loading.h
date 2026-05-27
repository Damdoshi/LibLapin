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
 * @field target Address of the slot that will receive the loaded resource.
 * @field subtarget Optional output receiving resource-specific count information, such as raw file size.
 * @description $Starget@ is a pointer to the caller's storage slot. The slot is cleared before loading and receives the loaded pointer on success.
 * @see bunny_add_to_ressource_list
 * @see gl_bunny_loading_context
 *
 * @doc-lang fr
 * @brief Décrit une ressource prévue pour le contexte de chargement.
 * @field file Chemin de la ressource.
 * @field target Adresse du slot qui recevra la ressource chargée.
 * @field subtarget Sortie optionnelle recevant une information propre au chargement, comme la taille d’un fichier brut.
 * @description $Starget@ est un pointeur vers le slot de stockage de l'appelant. Le slot est vidé avant le chargement et reçoit le pointeur chargé en cas de succès.
 * @see bunny_add_to_ressource_list
 * @see gl_bunny_loading_context
 */
typedef struct			s_bunny_ressource_to_load
{
  const char			*file;
  void				**target;
  size_t			*subtarget;
}				t_bunny_ressource_to_load;

t_bunny_ressource_to_load	*bunny_new_ressource_hook(void);
void				bunny_delete_ressource_hook(t_bunny_ressource_to_load *);
bool				bunny_add_to_ressource_list(t_bunny_list *lst,
							    t_bunny_ressource_to_load *ld,
							    size_t	len);

/**
 * @doc
 * @doc-symbol t_bunny_loading_task_function
 * @doc-kind type
 * @doc-module context
 * @doc-order 605
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type for custom loading tasks.
 * @param data User pointer stored in the loading task.
 * @return-success Returns $Ctrue@ when the task completed successfully.
 * @return-failure Returns $Cfalse@ to make the loading context fail.
 * @see t_bunny_loading_task
 * @see gl_bunny_loading_context
 *
 * @doc-lang fr
 * @brief Type de callback pour les tâches personnalisées de chargement.
 * @param data Pointeur utilisateur stocké dans la tâche de chargement.
 * @return-success Renvoie $Ctrue@ quand la tâche s'est terminée correctement.
 * @return-failure Renvoie $Cfalse@ pour faire échouer le contexte de chargement.
 * @see t_bunny_loading_task
 * @see gl_bunny_loading_context
 */
typedef bool			(*t_bunny_loading_task_function)(void			*data);

/**
 * @doc
 * @doc-symbol t_bunny_loading_task
 * @doc-kind struct
 * @doc-module context
 * @doc-order 606
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Describes one custom task scheduled by the loading context.
 * @field function Function executed by the asynchronous loading worker.
 * @field data User pointer transmitted to $Sfunction@.
 * @description Custom loading tasks are useful for application-specific work that is not a built-in LibLapin resource, such as preparing an Allan level, parsing a large file or building CPU-side data. The callback must not touch thread-unsafe graphics objects unless the application guarantees it is safe.
 * @see bunny_add_to_loading_task_list
 * @see t_bunny_loading_screen
 *
 * @doc-lang fr
 * @brief Décrit une tâche personnalisée planifiée par le contexte de chargement.
 * @field function Fonction exécutée par le worker asynchrone de chargement.
 * @field data Pointeur utilisateur transmis à $Sfunction@.
 * @description Les tâches personnalisées de chargement servent au travail propre à l'application qui n'est pas une ressource LibLapin intégrée, par exemple préparer un niveau Allan, parser un gros fichier ou construire des données côté CPU. La callback ne doit pas toucher d'objets graphiques non thread-safe sauf si l'application garantit que c'est sûr.
 * @see bunny_add_to_loading_task_list
 * @see t_bunny_loading_screen
 */
typedef struct			s_bunny_loading_task
{
  t_bunny_loading_task_function function;
  void				*data;
} 			t_bunny_loading_task;

t_bunny_loading_task		*bunny_new_loading_task(void);
void				bunny_delete_loading_task(t_bunny_loading_task *);
bool				bunny_add_to_loading_task_list(t_bunny_list *lst,
							       t_bunny_loading_task *tasks,
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
 * @brief Runtime structure of the built-in loading context.
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
 * @field tasks Custom application tasks to run during loading.
 * @field percent_completion Smoothed completion ratio in the $C0@-$C1@ range.
 * @field terminated True when loading is complete.
 * @see bunny_init_loading_context
 * @see bunny_clear_all_loaded_ressources
 *
 * @doc-lang fr
 * @brief Structure d’exécution du contexte de chargement intégré.
 * @field head En-tête commun des contextes.
 * @field pictures Images à charger.
 * @field pixelarrays Pixelarrays à charger.
 * @field sprites Sprites à charger.
 * @field musics Musiques à charger.
 * @field effects Effets sonores à charger.
 * @field sound_sprites Sound sprites à charger.
 * @field texts Textes/Fontes à charger.
 * @field files Fichiers bruts à charger.
 * @field configurations Configurations à charger.
 * @field tasks Tâches personnalisées applicatives à exécuter pendant le chargement.
 * @field percent_completion Ratio de progression lissé, dans l’intervalle $C0@-$C1@.
 * @field terminated Vrai quand le chargement est terminé.
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
  t_bunny_list			*tasks;
  double			percent_completion;
  bool				terminated;
  const char			_private[512];
}				t_bunny_loading_screen;

extern const t_bunny_context	gl_bunny_loading_context;

bool				bunny_init_loading_context(t_bunny_loading_screen *);
void				bunny_terminate_loading_context(t_bunny_loading_screen *);

void				bunny_clear_all_loaded_ressources(t_bunny_loading_screen *s);

#endif	/*			__LAPIN_LOADING_SCREEN_H__	*/
