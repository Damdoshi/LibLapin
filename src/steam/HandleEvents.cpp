// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	BunnySteam::HandleEvents(void		*data)
{
  user_data = data;
  callbacks();

  if (overlay_response != GO_ON)
    return (overlay_response);

  if (achievement_received != GO_ON)
    return (achievement_received);
  if (achievement_stored != GO_ON)
    return (achievement_stored);

  if (stats_received != GO_ON)
    return (stats_received);
  if (stats_stored != GO_ON)
    return (stats_stored);

  return (GO_ON);
}

