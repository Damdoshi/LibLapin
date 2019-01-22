// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	BunnySteam::Start(uint64_t		id)
{
  if (id != 0 && SteamAPI_RestartAppIfNecessary(id))
    return (EXIT_ON_SUCCESS);
  if (SteamAPI_Init() == false)
    return (EXIT_ON_ERROR);
  game_id = id;

  //
  if ((apps = SteamApps()) == NULL ||
      (user = SteamUser()) == NULL ||
      (stats = SteamUserStats()) == NULL)
    {
      Stop();
      return (EXIT_ON_ERROR);
    }
  callbacks = SteamAPI_RunCallbacks;

  //
  username = SteamFriends()->GetPersonaName();
  language = apps->GetCurrentGameLanguage();

  ext_username = username.c_str();
  ext_language = language.c_str();
  return (GO_ON);
}

