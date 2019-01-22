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
# include			<unordered_map>

# ifdef				__MINGW32__
#  pragma			pack(1);
# endif
class				BunnySteam
{
public:
  uint64_t			game_id = 0;
  const char			*ext_username = NULL;
  const char			*ext_language = NULL;
  const char			*ext_last_error = NULL;

protected:
  std::string			username;
  std::string			language;
  std::string			last_error;
  std::map<std::string, int>	statistics;
  std::map<std::string, bool>	achievements;

  ISteamApps			*apps = NULL;
  ISteamUser			*user = NULL;
  ISteamUserStats		*stats = NULL;
  void				(*callbacks)(void) = NULL;

  void				*user_data = NULL;
  t_bunny_response		overlay_response = GO_ON;
  t_bunny_response		achievement_received = GO_ON;
  t_bunny_response		achievement_stored = GO_ON;
  t_bunny_response		stats_received = GO_ON;
  t_bunny_response		stats_stored = GO_ON;

public:
  t_bunny_response		Start(uint64_t				game_id);
  t_bunny_response		HandleEvents(void			*data);
  void				Stop(void);

  const char                    *GetUsername(void) const;
  const char                    *GetLanguage(void) const;
  uint64_t                      GetUserId(void) const;

  bool				SetAchievement(const std::string	&name);
  bool				GetAchievement(const std::string	&name) const;
  bool				SetStatistic(const std::string		&name,
					     int			value);
  int				GetStatistic(const std::string		&name) const;

  const char * const		*AchievementList(void) const;
  const char * const		*StatisticList(void) const;

  BunnySteam(void);
  ~BunnySteam(void);

  // Steam stuff.
private:
  // "Stored" signifie que Steam a recu l'information
  // "Received" signifie que le programme a recu l'info de Steam

  STEAM_CALLBACK
  (BunnySteam,
   OverlayActivated,
   GameOverlayActivated_t
   );

  STEAM_CALLBACK
  (BunnySteam,
   AchievementStored,
   UserAchievementStored_t,
   achievement_callback
   );

  STEAM_CALLBACK
  (BunnySteam,
   StatsStored,
   UserStatsStored_t,
   stats_stored_callback
   );

  STEAM_CALLBACK
  (BunnySteam,
   StatsReceived,
   UserStatsReceived_t,
   stats_received_callback
   );
};
# pragma			pack()

extern BunnySteam		gl_bunny_steam;

#endif	/*			__LAPIN_PRIVATE_STEAM_H__	*/
