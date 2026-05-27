// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p memory, %zu length, %s file -> %p"

/**
 * @doc-symbol bunny_read_picture_id
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 150
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Reads an encoded image from memory into a picture and optionally associates it with a resource identifier.
 * @description When from_file is not NULL, it is used by the resource manager as the origin identifier for the loaded data.
 * @param pic The memory buffer containing the encoded image.
 * @param l The size of pic in bytes.
 * @param from_file The optional resource identifier.
 * @return-success A loaded t_bunny_picture.
 * @return-failure NULL on failure.
 * @error ENOMEM Out of memory.
 * @log Logs are written with the "ressource" and "graphics" labels.
 * @see bunny_read_picture, bunny_load_picture
 *
 * @doc-lang fr
 * @brief Lit une image encodée en mémoire vers une picture et peut l’associer à un identifiant de ressource.
 * @description Lorsque from_file n’est pas NULL, il est utilisé par le gestionnaire de ressources comme identifiant d’origine des données chargées.
 * @param pic Le buffer mémoire contenant l’image encodée.
 * @param l La taille de pic en octets.
 * @param from_file L’identifiant de ressource optionnel.
 * @return-success Un t_bunny_picture chargé.
 * @return-failure NULL en cas d’échec.
 * @error ENOMEM Mémoire insuffisante.
 * @log Les logs sont écrits avec les labels "ressource" et "graphics".
 * @see bunny_read_picture, bunny_load_picture
 */
t_bunny_picture		*bunny_read_picture_id(const void	*_pic,
					       size_t		len,
					       const char	*file)
{
  struct bunny_picture	*pic;
  sf::Texture		txt;
  uint64_t		hash;

  hash = file ? bunny_hash(BH_FNV, file, strlen(file)) : 0;
  if (_bunny_is_psd_buffer(_pic, len))
    return (_bunny_load_psd_picture_from_memory(_pic, len, file));

  if ((pic = new (std::nothrow) struct bunny_picture) == NULL)
    goto ReturnNull;
  pic->ntexture = NULL;
  pic->ntex = NULL;

  if (RessourceManager.disable_manager ||
      file == NULL ||
      (pic->texture = (sf::RenderTexture*)
       RessourceManager.TryGet(ResManager::SF_RENDERTEXTURE, hash)) == NULL)
    {
      // We use a temporary texture because RenderTexture cannot load files.
      if (txt.loadFromMemory(_pic, len) == false)
	goto DeleteStructure;
      sf::Sprite		spr(txt);

      if ((pic->texture = new (std::nothrow) sf::RenderTexture({txt.getSize().x, txt.getSize().y})) == NULL)
	goto DeleteStructure;

      pic->texture->clear(sf::Color(0, 0, 0, 0));
      pic->texture->draw(spr);
      pic->texture->display();
    }

  if (RessourceManager.disable_manager == false)
    RessourceManager.AddToPool(ResManager::SF_RENDERTEXTURE, file, hash, pic, pic->texture);

  pic->res_id = hash;
  pic->tex = &pic->texture->getTexture();
  pic->ntex = pic->ntexture ? &pic->ntexture->getTexture() : NULL;
  if ((pic->sprite = new (std::nothrow) sf::Sprite(*pic->tex)) == NULL)
    goto DeleteRenderTexture;

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
  pic->glactive = false;

  scream_log_if(PATTERN, "ressource,graphics", _pic, len, file, pic);
  return ((t_bunny_picture*)pic);

 DeleteRenderTexture:
  delete pic->texture;
 DeleteStructure:
  delete pic;
 ReturnNull:
  scream_error_if(return (NULL), ENOMEM, PATTERN, "ressource,graphics", _pic, len, file, (void*)NULL);
  return (NULL);
}
