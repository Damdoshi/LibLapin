// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_configuration	*bunny_init_box_environ(int		w,
						int		h)
{
  char			buffer[512];
  static const char	*screen = R"(
    [Screen
      Type="Box"
      Size=%d,%d
      Position=0,0
    ]
  )"; // "

  snprintf(&buffer[0], sizeof(buffer), screen, w, h);
  return (bunny_read_configuration(BC_DABSIC, &buffer[0], NULL));
}
