/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_STEAM_H__
# define			__LAPIN_PRIVATE_STEAM_H__
# include			<stddef.h>
# include			<steam_api.h>

class				bunny_steam
{
 public:
  uint64_t			game_id;
  const char			*username;
  const t_bunny_steam_configuration *configuration;
  const char			*last_error;
  //
  bool				stats_were_received;

  ISteamUser			*user;
  ISteamUserStats		*stats;

  STEAM_CALLBACK(bunny_steam, OnGameOverlayActivated, GameOverlayActivated_t);
  STEAM_CALLBACK(bunny_steam, OnUserAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored);
  STEAM_CALLBACK(bunny_steam, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored);
  STEAM_CALLBACK(bunny_steam, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived);

  bunny_steam(void);
  ~bunny_steam(void);
};

#endif	/*			__LAPIN_PRIVATE_STEAM_H__	*/
