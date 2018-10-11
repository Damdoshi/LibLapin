// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static t_bunny_clothe	*bunny_load_clothe(const char	*name,
					   const char	*file)
{
  t_bunny_clothe	*clothe;

  if ((clothe = (t_bunny_clothe*)bunny_malloc(sizeof(*clothe))) == NULL)
    return (NULL);
  if ((clothe->name = bunny_strdup(name)) == NULL)
    goto DeleteClothe;
  if ((clothe->sprite = bunny_load_sprite(file)) == NULL)
    goto DeleteName;
  return (clothe);

 DeleteName:
  bunny_free((void*)clothe->name);
 DeleteClothe:
  bunny_free(clothe);
  return (NULL);
}

static t_bunny_clothe	*bunny_read_clothe(const char	*name,
					   t_bunny_configuration *cnf)
{
  t_bunny_clothe	*clothe;

  if ((clothe = (t_bunny_clothe*)bunny_malloc(sizeof(*clothe))) == NULL)
    return (NULL);
  if ((clothe->name = bunny_strdup(name)) == NULL)
    goto DeleteClothe;
  if ((clothe->sprite = bunny_read_sprite(cnf)) == NULL)
    goto DeleteName;
  return (clothe);

 DeleteName:
  bunny_free((void*)clothe->name);
 DeleteClothe:
  bunny_free(clothe);
  return (NULL);
}

t_bunny_closet		*bunny_read_closet(t_bunny_configuration *config,
					   t_bunny_map	*wardrobe)
{
  t_bunny_configuration	*clothe;
  t_bunny_closet	*closet;
  const char		*tmps;
  int			tmp;

  if ((closet = (t_bunny_closet*)bunny_malloc(sizeof(*closet))) == NULL)
    return (NULL);
  if (bunny_configuration_getf_string(config, &tmps, "Name") == false)
    goto DeleteCloset;
  if ((closet->name = bunny_strdup(tmps)) == NULL)
    goto DeleteCloset;
  if (bunny_configuration_getf_int(config, &closet->position.x, "Position[0]") == false)
    goto DeleteName;
  if (bunny_configuration_getf_int(config, &closet->position.y, "Position[1]") == false)
    goto DeleteName;
  if (bunny_configuration_getf_int(config, &closet->depth, "Depth") == false)
    goto DeleteName;
  if ((tmp = bunny_configuration_casesf(config, "Sprites")) == 0)
    goto DeleteName;
  if ((closet->clothes = bunny_new_vector(tmp, t_bunny_sprite*)) == NULL)
    goto DeleteName;
  for (tmp = 0; tmp < (int)closet->clothes->nmemb; ++tmp)
    {
      if (bunny_configuration_getf_string(config, &tmps, "Sprites[%d][0]", tmp) == false)
	{
	  const char *name;

	  if (bunny_configuration_getf_string(config, &name, "Sprites[%d][1]", tmp) == false)
	    goto DeleteClothes;
	  if (bunny_configuration_getf_node(config, &clothe, "Sprites[%d][0]", tmp) == false)
	    goto DeleteClothes;
	  if ((bunny_vector_data(closet->clothes, tmp, t_bunny_clothe*) =
	       bunny_read_clothe(name, clothe)) == NULL)
	    goto DeleteClothes;
	}
      else
	{
	  const char *name;

	  if (bunny_configuration_getf_string(config, &name, "Sprites[%d][1]", tmp) == false)
	    goto DeleteClothes;
	  if ((bunny_vector_data(closet->clothes, tmp, t_bunny_clothe*) =
	       bunny_load_clothe(name, tmps)) == NULL)
	    goto DeleteClothes;
	}
    }
  if (wardrobe)
    {
      t_bunny_closet	*previous;

      previous = (t_bunny_closet*)
	bunny_map_set_data(wardrobe, closet->name, closet, t_bunny_closet*);
      if (previous == NULL)
	goto DeleteClothes;
      if (previous != closet)
	bunny_delete_closet(previous);
    }
  return (closet);

 DeleteClothes:
  for (tmp = 0; tmp < (int)closet->clothes->nmemb; ++tmp)
    {
      t_bunny_clothe *clo;

      if ((clo = bunny_vector_data(closet->clothes, tmp, t_bunny_clothe*)) != NULL)
	{
	  bunny_delete_clipable(&clo->sprite->clipable);
	  bunny_free((void*)clo->name);
	}
    }
  bunny_delete_vector(closet->clothes);
 DeleteName:
  bunny_free((void*)closet->name);
 DeleteCloset:
  bunny_free(closet);
  return (NULL);
}

t_bunny_closet		*bunny_load_closet(const char	*file,
					   t_bunny_map	*wardrobe)
{
  t_bunny_configuration	*config;
  t_bunny_closet	*closet;

  if ((config = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  closet = bunny_read_closet(config, wardrobe);
  bunny_delete_configuration(config);
  return (closet);
}

