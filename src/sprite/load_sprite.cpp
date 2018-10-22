// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%s file -> %p"

struct bunny_sprite	*_bunny_new_sprite(void)
{
  struct bunny_sprite	*sprite;

  if ((sprite = new (std::nothrow) bunny_sprite) == NULL)
    return (NULL);
  if ((sprite->sprite = new (std::nothrow) sf::Sprite) == NULL)
    {
      delete sprite;
      return (NULL);
    }
  sprite->texture = NULL;
  return (sprite);
}

t_bunny_sprite		*_bunny_fill_sprite(t_bunny_sprite	*_spr,
					    t_bunny_configuration *conf,
					    const char		*file)
{
  struct bunny_sprite	*sprite = (struct bunny_sprite*)_spr;
  sf::Texture		txt;
  sf::Sprite		spr;
  const char		*res;
  uint64_t		hash;

  if (bunny_configuration_go_get_string(conf, &res, "RessourceFile[0]") == false)
    scream_error_if
      (return (NULL), BE_SYNTAX_ERROR,
       PATTERN ": A 'RessourceFile' field was expected", "ressource,sprite,syntax",
       file, (void*)NULL);

  hash = bunny_hash(BH_FNV, res, strlen(res));
  if (RessourceManager.disable_manager ||
      (sprite->texture = (sf::RenderTexture*)
       RessourceManager.TryGet(ResManager::SF_RENDERTEXTURE, hash)) == NULL)
    {
      if (txt.loadFromFile(res) == false)
	return (NULL);
      spr.setTexture(txt);

      if ((sprite->texture = new (std::nothrow) sf::RenderTexture) == NULL)
	return (NULL);
      if (sprite->texture->create(txt.getSize().x, txt.getSize().y) == false)
	{
	  delete sprite->texture;
	  return (NULL);
	}

      sprite->texture->clear(sf::Color(0, 0, 0, 0));
      sprite->texture->draw(spr);
      sprite->texture->display();
    }

  if (RessourceManager.disable_manager == false)
    RessourceManager.AddToPool
      (ResManager::SF_RENDERTEXTURE, file, hash, sprite, sprite->texture);

  sprite->res_id = hash;

  sprite->tex = &sprite->texture->getTexture();
  sprite->sprite->setTexture(*sprite->tex);

  sprite->type = SPRITE;
  sprite->width = sprite->tex->getSize().x;
  sprite->height = sprite->tex->getSize().y;

  sprite->rect.x = 0;
  sprite->rect.y = 0;
  sprite->rect.w = sprite->width;
  sprite->rect.h = sprite->height;

  sprite->position.x = 0;
  sprite->position.y = 0;
  sprite->origin.x = 0;
  sprite->origin.y = 0;
  sprite->scale.x = 1;
  sprite->scale.y = 1;
  sprite->rotation = 0;
  sprite->color_mask.full = WHITE;

  if (bunny_set_clipable_attribute
      (NULL, (t_bunny_clipable**)&sprite, &conf, BCT_SPRITE) == false)
    return (NULL);
  if (_bunny_set_sprite_attribute
      (*sprite, *(SmallConf*)conf) == false)
    return (NULL);

  scream_log_if(PATTERN, "ressource,sprite", file, sprite);
  bunny_sprite_set_animation_id
    ((t_bunny_sprite*)sprite,
     bunny_vector_data
     (sprite->animation, sprite->current_animation, t_bunny_animation).hash
     );
  return ((t_bunny_sprite*)sprite);
}

t_bunny_sprite		*_bunny_read_sprite(t_bunny_configuration *conf,
					    const char		*file)
{
  struct bunny_sprite	*sprite;

  if ((sprite = _bunny_new_sprite()) == NULL)
    return (NULL);
  if (_bunny_fill_sprite((t_bunny_sprite*)sprite, conf, file) == NULL)
    {
      //delete sprite->texture;
      delete sprite->sprite;
      delete sprite;
      return (NULL);
    }
  return ((t_bunny_sprite*)sprite);
}

t_bunny_sprite		*bunny_load_sprite(const char		*file)
{
  t_bunny_configuration	*conf;
  t_bunny_sprite	*spr;

  if ((conf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  if ((spr = _bunny_read_sprite(conf, file)) == NULL)
    {
      bunny_delete_configuration(conf);
      return (NULL);
    }
  return (spr);
}

