// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN					"%u width, %u height -> %p"

extern bool		gl_normal_map;

/**
 * @doc-symbol bunny_new_picture
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 130
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a new picture stored by the graphic backend.
 * @description The returned object must be destroyed with bunny_delete_clipable. If normal-map support is enabled, a matching normal render target is also prepared.
 * @param wid The width in pixels.
 * @param hei The height in pixels.
 * @return-success A valid t_bunny_picture.
 * @return-failure NULL if allocation or backend creation fails.
 * @error ENOMEM Out of memory.
 * @log Logs are written with the "ressource" and "graphics" labels.
 * @see t_bunny_picture, bunny_load_picture, bunny_delete_clipable
 *
 * @doc-lang fr
 * @brief Crée une nouvelle picture stockée par le moteur graphique.
 * @description L’objet renvoyé doit être détruit avec bunny_delete_clipable. Si le support des normal maps est activé, une cible de rendu normale correspondante est aussi préparée.
 * @param wid La largeur en pixels.
 * @param hei La hauteur en pixels.
 * @return-success Un t_bunny_picture valide.
 * @return-failure NULL si l’allocation ou la création côté backend échoue.
 * @error ENOMEM Mémoire insuffisante.
 * @log Les logs sont écrits avec les labels "ressource" et "graphics".
 * @see t_bunny_picture, bunny_load_picture, bunny_delete_clipable
 */
t_bunny_picture		*bunny_new_picture(unsigned int		width,
					   unsigned int		height)
{
  struct bunny_picture	*pic;

  if ((pic = new (std::nothrow) struct bunny_picture) == NULL)
    goto Fail;
  if ((pic->texture = new (std::nothrow) sf::RenderTexture({width, height})) == NULL)
    goto FailStruct;
  pic->ntexture = NULL;

  pic->texture->clear(sf::Color(0, 0, 0, 0));
  pic->texture->display();
  pic->texture->setSmooth(false);

  if (gl_normal_map)
    {
      if ((pic->ntexture = new (std::nothrow) sf::RenderTexture({width, height})) == NULL)
	goto FailTexture;
      pic->ntexture->clear(sf::Color(128, 128, 255, 255));
      pic->ntexture->display();
      pic->ntexture->setSmooth(false);
    }

  pic->tex = &pic->texture->getTexture();
  pic->ntex = pic->ntexture ? &pic->ntexture->getTexture() : NULL;
  if ((pic->sprite = new (std::nothrow) sf::Sprite(*pic->tex)) == NULL)
    goto FailNormalTexture;
  pic->type = GRAPHIC_RAM;
  pic->width = width;
  pic->height = height;

  pic->rect.x = 0;
  pic->rect.y = 0;
  pic->rect.w = width;
  pic->rect.h = height;
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

  pic->res_id = 0;

  scream_log_if(PATTERN, "ressource,graphics", width, height, pic);
  return ((t_bunny_picture*)pic);

 FailNormalTexture:
  if (pic->ntexture)
    delete pic->ntexture;
 FailTexture:
  delete pic->texture;
 FailStruct:
  delete pic;
 Fail:
  scream_error_if(return (NULL), ENOMEM, PATTERN, "ressource,graphics", width, height, (void*)NULL);
  return (NULL);
}
