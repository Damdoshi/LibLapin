// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_init_cinematic(t_bunny_cinematic_screen	*scr)
{
  t_bunny_map	**map;

  bunny_clear_cinematic(scr);

  for (map = &scr->standard_command; map <= &scr->musics; ++map)
    if ((*map = bunny_new_map(string_map)) == NULL)
      {
	bunny_clear_cinematic(scr);
	return (false);
      }
  /*
  struct {
    const char	*name;
    t_bunny_sequence_command cmd;
  }		cincom = {
    {"play", (t_bunny_sequence_command)bunny_cinematic_play},
    {"text", (t_bunny_sequence_command)bunny_cinematic_text},
  };

  for (size_t i = 0; i < sizeof(cincom) / sizeof(cincom[0]); ++i)
    if (_bunny_map_set_data(scr->standard_command, cincom[0].name, cincom[0].cmd) == NULL)
      {
	bunny_clear_cinematic(scr);
	return (false);
      }
  */
  return (true);
}

