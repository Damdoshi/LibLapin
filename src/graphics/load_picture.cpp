// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%s file -> %p"

t_bunny_picture		*bunny_load_picture(const char	*file)
{
  struct bunny_picture	*pic;
  sf::Texture		txt;
  sf::Sprite		spr;
  uint64_t		hash;

  if (bunny_which_format(file) != BC_CUSTOM)
    {
      t_bunny_picture	*pc = NULL;

      if (bunny_set_clipable_attribute(file, &pc, NULL, BCT_PICTURE) == false)
	return (NULL);
      return (pc);
    }
  hash = bunny_hash(BH_FNV, file, strlen(file));

  if (gl_bunny_ressource_ciphering)
    {
      void		*data;
      size_t		siz;

      if (bunny_load_file(file, &data, &siz) == -1)
	return (NULL);
      gl_bunny_ressource_ciphering((char*)data, siz, gl_bunny_ressource_data, false);
      if ((pic = (struct bunny_picture*)
	   bunny_read_picture_id(data, siz, file)) == NULL)
	return (NULL);
      bunny_delete_file(data, file);
      return ((t_bunny_picture*)pic);
    }

  if ((pic = new (std::nothrow) struct bunny_picture) == NULL)
    goto ReturnNull;
  if ((pic->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteStructure;
  if (RessourceManager.disable_manager ||
      (pic->texture = (sf::RenderTexture*)
       RessourceManager.TryGet(ResManager::SF_RENDERTEXTURE, hash)) == NULL)
    {
      // We use a temporary texture because RenderTexture cannot load files.
      if (txt.loadFromFile(file) == false)
	goto DeleteSprite;
      spr.setTexture(txt);

      if ((pic->texture = new (std::nothrow) sf::RenderTexture) == NULL)
	goto DeleteSprite;
      if (pic->texture->create(txt.getSize().x, txt.getSize().y) == false)
	goto DeleteRenderTexture;

      pic->texture->clear(sf::Color(0, 0, 0, 0));
      pic->texture->draw(spr);
      pic->texture->display();
    }

  if (RessourceManager.disable_manager == false)
    RessourceManager.AddToPool(ResManager::SF_RENDERTEXTURE, file, hash, pic, pic->texture);

  pic->res_id = hash;
  pic->tex = &pic->texture->getTexture();
  pic->sprite->setTexture(*pic->tex);

  pic->type = GRAPHIC_RAM;
  pic->width = pic->tex->getSize().x;
  pic->height = pic->tex->getSize().y;

  pic->rect.x = 0;
  pic->rect.y = 0;
  pic->rect.w = pic->width;
  pic->rect.h = pic->height;

  pic->position.x = 0;
  pic->position.y = 0;
  pic->origin.x = 0;
  pic->origin.y = 0;
  pic->scale.x = 1;
  pic->scale.y = 1;
  pic->rotation = 0;
  pic->color_mask.full = WHITE;
  pic->smooth = false;
  pic->mosaic = false;

  scream_log_if(PATTERN, "ressource,graphics", file, pic);
  return ((t_bunny_picture*)pic);

 DeleteRenderTexture:
  delete pic->texture;
 DeleteSprite:
  delete pic->sprite;
 DeleteStructure:
  delete pic;
 ReturnNull:
  scream_error_if(return (NULL), ENOMEM, PATTERN, "ressource,graphics", file, (void*)NULL);
  return (NULL);
}
