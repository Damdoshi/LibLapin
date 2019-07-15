// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN	"%s file, %ud width, %ud height -> %p"

static t_bunny_tilemap	*bunny_load_tilemap_whc(const char	*file,
						unsigned int	width,
						unsigned int	height,
						t_bunny_configuration *conf)
{
  sf::Texture		txt;
  sf::Sprite		spr;
  struct bunny_tilemap	*tmap;
  int			length;

  if ((tmap = new (std::nothrow) bunny_tilemap) == NULL)
    goto DeleteConfiguration;
  if ((tmap->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteTilemap;
  if ((tmap->texture = new (std::nothrow) sf::RenderTexture) == NULL)
    goto DeleteSfSprite;
  if (tmap->texture->create(width, height) == false)
    goto DeleteSfTexture;

  length = sqrt(width * width + height * height) * 1.05;
  if ((tmap->working = bunny_new_picture(length, length)) == NULL)
    goto DeleteSfTexture;

  tmap->tex = &tmap->texture->getTexture();
  tmap->sprite->setTexture(*tmap->tex);

  tmap->type = TILEMAP;
  tmap->width = tmap->tex->getSize().x;
  tmap->height = tmap->tex->getSize().y;

  tmap->rect.x = 0;
  tmap->rect.y = 0;
  tmap->rect.w = tmap->width;
  tmap->rect.h = tmap->height;

  tmap->position.x = 0;
  tmap->position.y = 0;
  tmap->origin.x = 0;
  tmap->origin.y = 0;
  tmap->scale.x = 1;
  tmap->scale.y = 1;
  tmap->rotation = 0;
  tmap->color_mask.full = WHITE;
  tmap->smooth = false;
  tmap->mosaic = false;

  tmap->layer_clip[0] = -1;
  tmap->layer_clip[1] = -1;
  tmap->nbr_layers = 0;
  tmap->layers = NULL;
  tmap->tilesets = NULL;
  tmap->nbr_tilesets = 0;
  tmap->map_size.x = tmap->map_size.y = 0;
  tmap->tile_size.x = tmap->tile_size.y = 0;
  tmap->camera.x = tmap->camera.y = 0;
  tmap->zoom.x = tmap->zoom.y = 1;
  tmap->tile_rotation = 0;
  tmap->lock_borders = false;
  tmap->loop[0] = false;
  tmap->loop[1] = false;
  tmap->last_step = bunny_get_current_time();

  tmap->working->origin.x = tmap->working->buffer.width / 2.0;
  tmap->working->origin.y = tmap->working->buffer.height / 2.0;
  tmap->working->position.x = tmap->width / 2.0;
  tmap->working->position.y = tmap->height / 2.0;

  tmap->working_target_diff.x = (tmap->working->buffer.width - tmap->width) / 2;
  tmap->working_target_diff.y = (tmap->working->buffer.height - tmap->height) / 2;

  if (bunny_set_clipable_attribute
      (NULL, (t_bunny_clipable**)&tmap, &conf, BCT_PICTURE) == false)
    goto DeleteWorking;

  switch (bunny_which_format(file))
    {
    case BC_DABSIC:
      // Dabsic format
      if (__bunny_load_dabsic_tilemap(conf, tmap) == NULL)
	goto DeleteWorking;
      break ;
    case BC_XML:
      if (__bunny_load_tmx_tilemap(conf, tmap) == NULL)
	goto DeleteWorking;
      break ;
    default:
      break ;
    }

  tmap->res_id = 0;
  tmap->duplicated_tilemap = false;

  bunny_delete_configuration(conf);
  scream_log_if(PATTERN, "ressource,tilemap", file, width, height, tmap);
  return ((t_bunny_tilemap*)tmap);

 DeleteWorking:
  bunny_delete_clipable(tmap->working);
 DeleteSfTexture:
  delete tmap->texture;
 DeleteSfSprite:
  delete tmap->sprite;
 DeleteTilemap:
  delete tmap;
 DeleteConfiguration:
  bunny_delete_configuration(conf);
  return (NULL);
}

t_bunny_tilemap		*bunny_load_tilemap_wh(const char	*file,
					       unsigned int	width,
					       unsigned int	height)
{
  t_bunny_configuration	*conf;

  if ((conf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  return (bunny_load_tilemap_whc(file, width, height, conf));
}

t_bunny_tilemap		*bunny_load_tilemap(const char		*file)
{
  t_bunny_configuration	*conf;
  int			width;
  int			height;

  if ((conf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  if (bunny_configuration_getf_int(conf, &width, "Size[0]") == false)
    {
      bunny_delete_configuration(conf);
      return (NULL);
    }
  if (bunny_configuration_getf_int(conf, &height, "Size[1]") == false)
    {
      bunny_delete_configuration(conf);
      return (NULL);
    }
  return (bunny_load_tilemap_whc(file, width, height, conf));
}

