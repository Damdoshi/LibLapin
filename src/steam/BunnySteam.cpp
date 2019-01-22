// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include			"lapin_private.h"

BunnySteam			gl_bunny_steam;

BunnySteam::BunnySteam(void)
  : achievement_callback(this, &BunnySteam::AchievementStored),
    stats_stored_callback(this, &BunnySteam::StatsStored),
    stats_received_callback(this, &BunnySteam::StatsReceived)
{
  if (this != &gl_bunny_steam)
    throw std::logic_error{"Only a single instance of BunnySteam is allow and it is gl_bunny_steam"};
}

BunnySteam::~BunnySteam(void)
{
  if (game_id)
    Stop();
}

