/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_STEAM_H__
# define			__LAPIN_STEAM_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

typedef struct			s_bunny_achievement
{
  int				id;
  const char			*id_string;
  char				name[128];
  char				description[256];
  bool				achieved;
  int				icon;
}				t_bunny_achievement;

typedef t_bunny_response	(*t_bunny_steam_overlay)(t_bunny_event_state	state,
							 void			*data);

typedef t_bunny_response	(*t_bunny_steam_achievement)(t_bunny_event_state state,
							     void		*data);

typedef t_bunny_response	(*t_bunny_steam_stats)(t_bunny_event_state	state,
						       void			*data);

typedef struct			s_bunny_steam_context
{
  t_bunny_steam_overlay		overlay;
  t_bunny_steam_achievement	achievement;
  t_bunny_steam_stats		stats;
}				t_bunny_steam_context;

# ifdef				__MINGW32__
#  pragma			pack(1);
# endif
typedef struct			s_bunny_steam
{
  const uint64_t		game_id;
  const char * const		username;
  const char * const		language;
  const char * const		last_error;
}				t_bunny_steam;
# pragma			pack()

t_bunny_steam			*bunny_connect_to_steam(uint64_t		game_id);
void				bunny_close_steam(t_bunny_steam			*steam);

/// Called by bunny_loop and bunny_loop_mw
t_bunny_response		bunny_handle_events(t_bunny_steam		*steam,
						    void			*data);

void				bunny_set_achievement(t_bunny_steam		*steam,
						      const char		*name);
bool				bunny_get_achievement(t_bunny_steam		*steam,
						      const char		*name);
const char * const		*bunny_get_achievement_list(t_bunny_steam	*steam);

void				bunny_set_statistic(t_bunny_steam		*steam,
						    const char			*name,
						    int				value);
int				bunny_get_statistic(t_bunny_steam		*steam,
						    const char			*name);
const char * const		*bunny_get_statistic_list(t_bunny_steam		*steam);

const char                      *bunny_get_username(const t_bunny_steam         *steam);
const char                      *bunny_get_language(const t_bunny_steam         *steam);
uint64_t                        bunny_get_user_id(const t_bunny_steam           *steam);

#endif	/*			__LAPIN_STEAM_H__			*/
