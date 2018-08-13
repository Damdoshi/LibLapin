/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
**
** Bibliotheque Lapin
*/

#ifdef			__LAPIN_PRIVATE_STEAM_H__
# define		__LAPIN_PRIVATE_STEAM_H__

struct			bunny_steam
{
  uint64_t		game_id;
  const char		*username;
  t_bunny_steam_overlay	overlay;

  STEAM_CALLBACK(bunny_steam, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived);
  STEAM_CALLBACK(bunny_steam, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored);
  STEAM_CALLBACK(bunny_steam, OnAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored);


  STEAM_CALLBACK(bunny_steam, OnGameOverlayActivated, GameOverlayActivated_t);
};

#endif	/*		__LAPIN_PRIVATE_STEAM_H__	*/
