// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%s file -> %p"

t_bunny_sprite		*bunny_load_sprite(const char		*file)
{
  sf::Texture		txt;
  sf::Sprite		spr;
  t_bunny_configuration	*conf;
  struct bunny_sprite	*sprite;
  const char		*res;
  uint64_t		hash;

  if ((conf = bunny_open_configuration(file, NULL)) == NULL)
    goto ExitDirectly;
  if ((sprite = new (std::nothrow) bunny_sprite) == NULL)
    goto DeleteConf;
  if ((sprite->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteBunnySprite;
  if (bunny_configuration_go_get_string(conf, &res, "RessourceFile[0]") == false)
    scream_error_if
      (goto DeleteSfSprite, BE_SYNTAX_ERROR,
       PATTERN ": A 'RessourceFile' field was expected", "ressource,sprite,syntax",
       file, (void*)NULL);

  hash = bunny_hash(BH_FNV, res, strlen(res));
  if (RessourceManager.disable_manager ||
      (sprite->texture = (sf::RenderTexture*)
       RessourceManager.TryGet(ResManager::SF_RENDERTEXTURE, hash)) == NULL)
    {
      if (txt.loadFromFile(res) == false)
	goto DeleteSfSprite;
      spr.setTexture(txt);

      if ((sprite->texture = new (std::nothrow) sf::RenderTexture) == NULL)
	goto DeleteSfSprite;
      if (sprite->texture->create(txt.getSize().x, txt.getSize().y) == false)
	{
	  delete sprite->texture;
	  goto DeleteSfSprite;
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
    goto DeleteConf;
  if (_bunny_set_sprite_attribute
      (*sprite, *(SmallConf*)conf) == false)
    goto DeleteConf;

  bunny_delete_configuration(conf);
  scream_log_if(PATTERN, "ressource,sprite", file, sprite);
  bunny_sprite_set_animation_id((t_bunny_sprite*)sprite, sprite->current_animation);
  return ((t_bunny_sprite*)sprite);

 DeleteSfSprite:
  delete sprite->sprite;
 DeleteBunnySprite:
  delete sprite;
 DeleteConf:
  bunny_delete_configuration(conf);
 ExitDirectly:
  return (NULL);
}

