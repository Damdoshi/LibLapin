// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	"lapin_private.h"

const char      *BunnySteam::GetUsername(void) const
{
  return (ext_username);
}

const char      *BunnySteam::GetLanguage(void) const
{
  return (ext_language);
}

uint64_t        BunnySteam::GetUserId(void) const
{
  return (user->GetSteamID().GetAccountID());
}

