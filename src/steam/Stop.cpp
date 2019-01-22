// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			BunnySteam::Stop(void)
{
  SteamAPI_Shutdown();

  game_id = 0;

  username.clear();
  language.clear();
  last_error.clear();

  ext_username = username.c_str();
  ext_language = language.c_str();
  ext_last_error = last_error.c_str();

  statistics.clear();
  achievements.clear();

  apps = NULL;
  user = NULL;
  stats = NULL;
  callbacks = NULL;
  user_data = NULL;

  overlay_response = GO_ON;
  achievement_received = GO_ON;
  achievement_stored = GO_ON;
  stats_received = GO_ON;
  stats_stored = GO_ON;
}

