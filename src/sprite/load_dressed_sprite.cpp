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
      t_bunny_hash	hs;
      const char	*file;
      t_bunny_closet	*closet;

      // The the current node string name
      if (bunny_configuration_getf_string(node, &file, "."))
	closet = bunny_load_closet(file, wardrobe);
      else
	{
	  closet = bunny_read_closet(node, wardrobe);
	  file = closet->name;
	}
      if (closet == NULL)
	return (false);

      hs = bunny_hash(BH_DJB2, file, strlen(file));
      if (bunny_map_set_data(sprite->closets, hs, closet, t_bunny_closet*) == NULL)
	{
	  bunny_delete_closet(closet);
	  return (false);
	}
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

  // Clothes - sprites that are only reference to closets
  if (bunny_configuration_getf_node(config, &scope, "Clothes") == false)
    return (true);
  for (bunny_configuration_all_children(scope, node))
    {
      t_bunny_closet	*clt;
      t_bunny_clothe	*clo;
      const char	*tmp;
      t_bunny_hash	hst, hso;

      /*
      ** Expected is:
      ** [Clothes
      **   ClotheNode="ClosetName","ClotheName"
      ** ]
      */

      // Find which closet is used
      if (bunny_configuration_getf_string(node, &tmp, "[0]") == false)
	return (false);
      hst = bunny_hash(BH_DJB2, tmp, strlen(tmp));
      if ((clt = bunny_map_get_data(sprite->closets, hst, t_bunny_closet*)) == NULL)
	return (false);

      // Find the clothe in the closet
      if (bunny_configuration_getf_string(node, &tmp, "[1]") == false)
	return (false);
      hso = bunny_hash(BH_DJB2, tmp, strlen(tmp));
      if ((clo = bunny_map_get_data(clt->clothes, hso, t_bunny_clothe*)) == NULL)
	return (false);

      // Assign the clothe to the "clothe holder" in dsprite at the index of the found closet
      if (bunny_map_set_data(sprite->clothes, hst, clo, t_bunny_clothe*) == NULL)
	return (false);
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
  if ((sprite->closets = bunny_new_map(NULL, NULL, NULL, NULL)) == NULL)
    goto DeleteSfSprite;
  if ((sprite->clothes = bunny_new_map(NULL, NULL, NULL, NULL)) == NULL)
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
  bunny_delete_map(sprite->clothes);
 DeleteCloset:
  bunny_delete_map(sprite->closets);
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
