// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			bunny_dressed_sprite_wear(t_bunny_dressed_sprite	*sprite,
						  const char			*closet_name,
						  const char			*clothe_name)
{
  t_bunny_closet	*closet;
  t_bunny_clothe	*clothe;
  size_t		i, j;

  for (i = 0; i < sprite->closets->nmemb; ++i)
    {
      closet = bunny_vector_data(sprite->closets, i, t_bunny_closet*);
      if (strcmp(closet->name, closet_name) == 0)
	break ;
    }
  if (i == sprite->closets->nmemb)
    return (false);
  for (j = 0; j < closet->clothes->nmemb; ++j)
    {
      clothe = bunny_vector_data(closet->clothes, j, t_bunny_clothe*);
      if (strcmp(clothe->name, clothe_name) == 0)
	break ;
    }
  if (j == closet->clothes->nmemb)
    return (false);
  bunny_vector_data(sprite->clothes, i, t_bunny_clothe*) = clothe;
  return (true);
}

