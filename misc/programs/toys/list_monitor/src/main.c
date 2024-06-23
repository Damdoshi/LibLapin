/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** LibLapin Test
*/

#include		<lapin.h>

int			main(void)
{
  const t_bunny_area	*siz = bunny_list_monitors();
  size_t		i;

  for (i = 0; siz[i].w != 0 && siz[i].h != 0; ++i)
    printf("Screen n=%zu is %dx%d at position (%d, %d).\n", i, siz[i].w, siz[i].h, siz[i].x, siz[i].y);
  return (EXIT_SUCCESS);
}

