/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_STEAM_H__
# define		__LAPIN_STEAM_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

typedef struct		s_bunny_steam_achievement
{
  int			id;
  const char		*id_string;
  char			name[128];
  char			description[256];
  bool			achieved;
  int			icon;
}			t_bunny_steam_achievement;

typedef void		(*t_bunny_steam_overlay)(t_bunny_event_state state,
						 void		*data);
typedef void		(*t_bunny_steam_new_achievement)(t_bunny_steam_achievement
							 *achievement,
							 bool	group,
							 int	curprogress,
							 int	totprogress,
							 void	*data);
typedef void		(*t_bunny_steam_stats)(void		*data);

typedef struct		s_bunny_steam_configuration
{
  t_bunny_steam_achievement *achievement_list;
  size_t		nbr_achievement;

  t_bunny_steam_overlay	overlay;
  t_bunny_steam_new_achievement	new_achievements;
  t_bunny_steam_stats	stats_received;
}			t_bunny_steam_configuration;

typedef struct		s_bunny_steam
{
  const uint64_t	game_id;
  const char * const	username;
  const t_bunny_steam_configuration * const configuration;
  const char		*last_error;
}			t_bunny_steam;

bool			bunny_connect_to_steam(uint64_t		game_id,
					       t_bunny_steam	*steam);
void			bunny_close_steam(t_bunny_steam		*steam);
void			bunny_steam_call_callbacks(void);
bool			bunny_steam_set_achievement(t_bunny_steam *steam,
						    const char	*id);
bool			bunny_steam_request_stats(void);
# define		bunny_steam_get_stats(st, na, ou)	\
  (_Generic((ou),						\
	    int*: bunny_steam_get_int_stats,			\
	    float*: bunny_steam_get_float_stats			\
	    )((st), (na), (ou)))

bool			bunny_steam_get_int_stats(t_bunny_steam	*steam,
						  const char	*name,
						  int		*out);
bool			bunny_steam_get_float_stats(t_bunny_steam *steam,
						    const char	*name,
						    int		*out);

#endif	/*			__LAPIN_STEAM_H__			*/
