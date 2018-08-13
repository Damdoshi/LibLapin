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
  char			name[128];
  bool			group;
  unsigned int		current_progress;
  unsigned int		maximum_progress;
}			t_bunny_steam_achievement;

typedef void		(*t_bunny_steam_overlay)(t_bunny_event_state state,
						 void		*data);

typedef struct		s_bunny_steam
{
  const uint64_t	game_id;
  const char * const	username;
  t_bunny_steam_overlay	overlay;
}			t_bunny_steam;

bool			bunny_connect_to_steam(t_bunny_steam	*steam)
void			bunny_close_steam(t_bunny_steam		*steam);

#endif	/*		__LAPIN_STEAM_H__			*/
