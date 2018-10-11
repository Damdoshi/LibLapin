// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_dressed_sprite	*bunny_load_dressed_sprite(const char	*file,
						   t_bunny_map	*wardrobe)
{
  struct bunny_dressed_sprite *sprite;
  t_bunny_configuration	*config;
  t_bunny_configuration	*closets;
  t_bunny_configuration	*nod;
  const char		*tmp;
  int			len;
  int			i;

  if ((config = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  if ((sprite = new (std::nothrow) bunny_dressed_sprite) == NULL)
    goto DeleteConfiguration;
  if ((sprite->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteDressedSprite;
  if (_bunny_fill_sprite((t_bunny_sprite*)sprite, config, file) == NULL)
    goto DeleteDressedSprite;
  sprite->type = DRESSED_SPRITE;
  sprite->have_wardrobe = !!wardrobe;

  len = bunny_configuration_casesf(config, "Closets");
  if ((sprite->closets = bunny_new_vector(len, t_bunny_closet*)) == NULL)
    goto DeleteDressedSprite;
  if ((sprite->clothes = bunny_new_vector(len, t_bunny_clothe*)) == NULL)
    goto DeleteCloset;

  if (bunny_configuration_getf_node(config, &closets, "Closets"))
    for (nod = bunny_configuration_first(closets), i = 0;
	 nod != bunny_configuration_end(closets);
	 nod = bunny_configuration_next(nod), ++i)
      {
	if (bunny_configuration_getf_string(nod, &tmp, "."))
	  bunny_vector_data(sprite->closets, i, t_bunny_closet*)
	    = bunny_load_closet(tmp, wardrobe);
	else
	  bunny_vector_data(sprite->closets, i, t_bunny_closet*)
	    = bunny_read_closet(nod, wardrobe);
	if (bunny_vector_data(sprite->closets, i, t_bunny_closet*) == NULL)
	  goto DeleteAllClosets;
      }
  // Clothes - sprites that are only reference to closets
  if (bunny_configuration_getf_node(config, &closets, "Clothes"))
    for (nod = bunny_configuration_first(closets);
	 nod != bunny_configuration_end(closets);
	 nod = bunny_configuration_next(nod))
      {
	if (bunny_configuration_getf_string(nod, &tmp, "[0]") == false)
	  goto DeleteAllClosets;
	for (i = 0; i < (int)sprite->closets->nmemb; ++i)
	  if (strcmp(bunny_vector_data(sprite->closets, i, t_bunny_closet*)->name, tmp) == 0)
	    break ;
	if (i == (int)sprite->closets->nmemb)
	  goto DeleteAllClosets;
	t_bunny_closet *clt = bunny_vector_data(sprite->closets, i, t_bunny_closet*);

	if (bunny_configuration_getf_string(nod, &tmp, "[1]") == false)
	  goto DeleteAllClosets;
	for (i = 0; i < (int)clt->clothes->nmemb; ++i)
	  if (strcmp(bunny_vector_data(clt->clothes, i, t_bunny_closet*)->name, tmp) == 0)
	    break ;
	if (i == (int)clt->clothes->nmemb)
	  goto DeleteAllClosets;
	bunny_vector_data(sprite->clothes, i, t_bunny_clothe*)
	  = bunny_vector_data(clt->clothes, i, t_bunny_clothe*);
      }

  return ((t_bunny_dressed_sprite*)sprite);
 DeleteAllClosets:
  // TODO: Free clothes that were reserved for the dressed sprite...
  bunny_delete_vector(sprite->clothes);
 DeleteCloset:
  bunny_delete_vector(sprite->closets);
 DeleteDressedSprite:
  delete sprite;
 DeleteConfiguration:
  bunny_delete_configuration(config);
  return (NULL);
}

