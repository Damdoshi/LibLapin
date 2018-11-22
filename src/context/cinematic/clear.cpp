// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

void			bunny_clear_cinematic(t_bunny_cinematic_screen	*scr)
{
  if (scr->cinematic)
    {
      bunny_delete_configuration(scr->cinematic);
      scr->cinematic = NULL;
    }
  if (scr->standard_command)
    {
      bunny_delete_map(scr->standard_command);
      scr->standard_command = NULL;
    }

  bunny_empty_cinematic(scr);

  if (scr->pictures)
    {
      bunny_delete_map(scr->pictures);
      scr->pictures = NULL;
    }
  if (scr->voices)
    {
      bunny_delete_map(scr->voices);
      scr->voices = NULL;
    }
  if (scr->effects)
    {
      bunny_delete_map(scr->effects);
      scr->effects = NULL;
    }
  if (scr->musics)
    {
      bunny_delete_map(scr->musics);
      scr->musics = NULL;
    }
}

