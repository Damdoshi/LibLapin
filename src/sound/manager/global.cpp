// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#define		__LAPIN_H__
#include	<stdlib.h>
#include	<stdint.h>

typedef void	t_bunny_configuration;

#define		__SRC_SOUND_MANAGER_GLOBAL_CPP__
#include	"lapin/sound.h"
#include	"lapin/sound_manager.h"
#include	"private/sound.h"

extern "C"
{
  struct bunny_sound_manager gl_bunny_sound_manager =
    {
      { NULL, NULL, NULL },
      100,
      { 100.0, 100.0, 100.0 },
      1.0,
      {   1.0,   1.0,   1.0 },
      {},
      {}
    };
}
