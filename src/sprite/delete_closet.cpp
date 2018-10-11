// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			bunny_delete_closet(t_bunny_closet	*closet)
{
  t_bunny_clothe	*clo;
  size_t		i;

  for (i = 0; i < closet->clothes->nmemb; ++i)
    if ((clo = bunny_vector_data(closet->clothes, i, t_bunny_clothe*)) != NULL)
      {
	bunny_free((void*)clo->name);
	bunny_delete_clipable(&clo->sprite->clipable);
	bunny_free(clo);
      }
  if (closet->name)
    bunny_free((void*)closet->name);
  bunny_free(closet);
}

