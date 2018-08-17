// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	<steam_api.h>
#undef		BUNNY_CAMERA
#include	"lapin_private.h"

void		bunny_steam::OnGameOverlayActivated(GameOverlayActivated_t *d)
{
  if (this->configuration->overlay)
    this->configuration->overlay(d->m_bActive ? GO_UP : GO_DOWN, gl_loop_data);
}

void		bunny_steam::OnUserAchievementStored(UserAchievementStored_t *d)
{
  if (game_id != d->m_nGameID
      || configuration->new_achievements == NULL
      || configuration->achievement_list == NULL
      || configuration->nbr_achievement == 0
      )
    return ;
  size_t	i;

  for (i = 0;
       i < configuration->nbr_achievement
	 && strcmp
	 (configuration->achievement_list[i].id_string,
	  d->m_rgchAchievementName) != 0;
       ++i);
  if (i == configuration->nbr_achievement)
    return ;
  configuration->new_achievements
    (&configuration->achievement_list[i],
     d->m_bGroupAchievement,
     d->m_nCurProgress,
     d->m_nMaxProgress,
     gl_loop_data
     );
}

void		bunny_steam::OnUserStatsReceived(UserStatsReceived_t *d)
{
  if (game_id != d->m_nGameID
      || configuration->stats_received == false
      || stats_were_received == false
      )
    return ;
  if (d->m_eResult != k_EResultOK)
    {
      stats_were_received = false;
      last_error = "Request stat failed";
      return ;
    }
  size_t	i;

  stats_were_received = true;
  for (i = 0; i < configuration->nbr_achievement; ++i)
    {
      t_bunny_steam_achievement *a = &configuration->achievement_list[i];

      SteamUserStats()->GetAchievement(a->id_string, &a->achieved);
    }
  configuration->stats_received(gl_loop_data);
}

