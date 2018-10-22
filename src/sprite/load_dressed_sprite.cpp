// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/*
** Load all closets (collection of clothes with information about how to fit them on
** the dressed sprite.
*/
static bool		_bunny_load_closets(struct bunny_dressed_sprite	*sprite,
					    t_bunny_configuration	*config,
					    t_bunny_map			*wardrobe)
{
  t_bunny_configuration	*scope;
  t_bunny_configuration	*node;
  int			i;

  /*
  ** Expected is:
  ** [Closets
  **   ClosetFile="closet_file"
  **   [ClosetScope
  **   ]
  ** ]
  */
  if (bunny_configuration_getf_node(config, &scope, "Closets") == false)
    return (true);
  for (i = 0, bunny_configuration_all_children(scope, node), ++i)
    {
      const char	*file;
      t_bunny_closet	*closet;

      // The the current node string name
      if (bunny_configuration_getf_string(node, &file, "."))
	closet = bunny_load_closet(file, wardrobe);
      else
	closet = bunny_read_closet(node, wardrobe);
      if (closet == NULL)
	return (false);
      bunny_vector_data(sprite->closets, i, t_bunny_closet*) = closet;
    }
  return (true);
}

/*
** Set all requested clothes on the dressed sprite. They must came from the actual closets.
** They are only referenced.
*/
static bool		_bunny_load_clothes(struct bunny_dressed_sprite	*sprite,
					    t_bunny_configuration	*config)
{
  t_bunny_configuration	*scope;
  t_bunny_configuration	*node;
  int			i, j;

  // Clothes - sprites that are only reference to closets
  if (bunny_configuration_getf_node(config, &scope, "Clothes") == false)
    return (true);
  for (bunny_configuration_all_children(scope, node))
    {
      const char	*tmp;

      /*
      ** Expected is:
      ** [Clothes
      **   ClotheNode="ClosetName","ClotheName"
      ** ]
      */

      // Find which closet is used
      if (bunny_configuration_getf_string(node, &tmp, "[0]") == false)
	return (false);
      for (i = 0; i < (int)sprite->closets->nmemb; ++i)
	if (strcmp(bunny_vector_data(sprite->closets, i, t_bunny_closet*)->name, tmp) == 0)
	  break ;
      if (i == (int)sprite->closets->nmemb)
	return (false);
      t_bunny_closet *clt = bunny_vector_data(sprite->closets, i, t_bunny_closet*);

      // Find the clothe in the closet
      if (bunny_configuration_getf_string(node, &tmp, "[1]") == false)
	return (false);
      for (j = 0; j < (int)clt->clothes->nmemb; ++j)
	if (strcmp(bunny_vector_data(clt->clothes, j, t_bunny_clothe*)->name, tmp) == 0)
	  break ;
      if (j == (int)clt->clothes->nmemb)
	return (false);
      t_bunny_clothe *clo = bunny_vector_data(clt->clothes, j, t_bunny_clothe*);

      // Assign the clothe to the "clothe holder" in dsprite at the index of the found closet
      bunny_vector_data(sprite->clothes, i, t_bunny_clothe*) = clo;
    }
  return (true);
}

t_bunny_dressed_sprite	*_bunny_read_dressed_sprite(t_bunny_configuration	*config,
						    t_bunny_map			*wardrobe,
						    const char			*file)
{
  /////////////////////////
  // ALLOCATE BASIC SPRITE
  struct bunny_dressed_sprite *sprite;

  if ((sprite = new (std::nothrow) bunny_dressed_sprite) == NULL)
    return (NULL);
  if ((sprite->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteDressedSprite;
  if (_bunny_fill_sprite((t_bunny_sprite*)sprite, config, file) == NULL)
    goto DeleteSfSprite;
  sprite->type = DRESSED_SPRITE;
  sprite->have_wardrobe = !!wardrobe;

  ////////////////////////////////////////
  // ALLOCATE CLOSETS AND CLOTHES VECTORS
  int			len;

  if ((len = bunny_configuration_childrenf(config, "Closets")) == -1)
    {
      sprite->closets = NULL;
      sprite->clothes = NULL;
      return ((t_bunny_dressed_sprite*)sprite);
    }
  if ((sprite->closets = bunny_new_vector(len, t_bunny_closet*)) == NULL)
    goto DeleteSfSprite;
  if ((sprite->clothes = bunny_new_vector(len, t_bunny_clothe*)) == NULL)
    goto DeleteCloset;

  //////////////////////////////////
  // BROWSE CLOSETS AND ASSIGN THEM
  if (_bunny_load_closets(sprite, config, wardrobe) == false)
    goto DeleteAllClosets;
  if (_bunny_load_clothes(sprite, config) == false)
    goto DeleteAllClosets;

  return ((t_bunny_dressed_sprite*)sprite);
 DeleteAllClosets:
  // TODO: Free clothes that were reserved for the dressed sprite...
  // OR maybe not, and leave the responsability to the user.
  bunny_delete_vector(sprite->clothes);
 DeleteCloset:
  bunny_delete_vector(sprite->closets);
 DeleteSfSprite:
  delete sprite->sprite;
 DeleteDressedSprite:
  delete sprite;
  return (NULL);
}

t_bunny_dressed_sprite	*bunny_load_dressed_sprite(const char	*file,
						   t_bunny_map	*wardrobe)
{
  t_bunny_configuration	*config;
  t_bunny_dressed_sprite *sprite;

  if ((config = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  sprite = _bunny_read_dressed_sprite(config, wardrobe, file);
  bunny_delete_configuration(config);
  return (sprite);
}
