// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

// OVERLAY

void			BunnySteam::OverlayActivated(GameOverlayActivated_t	*d)
{
  if (gl_callback.steam.overlay)
    overlay_response = gl_callback.steam.overlay(d->m_bActive ? GO_UP : GO_DOWN, user_data);
  else
    overlay_response = GO_ON;
}

//////////////////////////////////////////////////////////////////////////////////////////

void			BunnySteam::AchievementStored(UserAchievementStored_t	*d)
{
  if (game_id != d->m_nGameID)
    return ;
  if (gl_callback.steam.achievement)
    achievement_stored = gl_callback.steam.achivement(SAVED, user_data);
  else
    achievement_stored = GO_ON;
}

void			BunnySteam::AchievementReceived(UserAchievementReceived_t *d)
{
  if (game_id != d->m_nGameID)
    return ;
  if (gl_callback.steam.achievement)
    achievement_received = gl_callback.steam.achievement(LOADED, user_data);
  else
    achievement_received = GO_ON;
}

//////////////////////////////////////////////////////////////////////////////////////////

void			BunnySteam::StatsStored(UserStatsStored_t		*d)
{
  if (game_id != d->m_nGameID)
    return ;
  if (gl_callback.steam.stats)
    stats_stored = gl_callback.steam.stats(SAVED, user_data);
  else
    stats_stored = GO_ON;
}

void			BunnySteam::StatsReceived(UserStatsReceived_t		*d)
{
  if (game_id != d->m_nGameID)
    return ;
  if (gl_callback.steam.stats)
    stats_received = gl_callback.steam.stats(LOADED, user_data);
  else
    stats_received = GO_ON;
}

