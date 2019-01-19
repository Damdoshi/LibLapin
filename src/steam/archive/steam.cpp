// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	<steam_api.h>
#undef		BUNNY_CAMERA
#include	"lapin_private.h"

bunny_steam::bunny_steam(void)
  : configuration(NULL),
    stats_were_received(false),
    m_CallbackAchievementStored(this, &bunny_steam::OnUserAchievementStored),
    m_CallbackUserStatsStored(this, &bunny_steam::OnUserStatsStored),
    m_CallbackUserStatsReceived(this, &bunny_steam::OnUserStatsReceived)
{}

bunny_steam::~bunny_steam(void)
{}
