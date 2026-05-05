// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

/**
 * @doc-symbol bunny_delete_clipable
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 170
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Destroys a clipable graphic object.
 * @description Use the public bunny_delete_clipable macro rather than calling _bunny_delete_clipable directly. It accepts pictures, pixelarrays, sprites, fonts, tilemaps, parallax and cinematic objects.
 * @param clp The clipable-compatible object to destroy.
 * @error EINVAL The object kind is not recognized.
 * @log Logs are written with the "graphics" label.
 * @see t_bunny_clipable, bunny_new_picture, bunny_new_pixelarray
 *
 * @doc-lang fr
 * @brief Détruit un objet graphique clipable.
 * @description Utilisez la macro publique bunny_delete_clipable plutôt que d’appeler directement _bunny_delete_clipable. Elle accepte les pictures, pixelarrays, sprites, polices, tilemaps, parallax et cinématiques.
 * @param clp L’objet compatible clipable à détruire.
 * @error EINVAL Le type de l’objet n’est pas reconnu.
 * @log Les logs sont écrits avec le label "graphics".
 * @see t_bunny_clipable, bunny_new_picture, bunny_new_pixelarray
 */
void				_bunny_delete_clipable(t_bunny_clipable	*clip)
{
  size_t			*type = (size_t*)clip;

  if (!clip)
    return ;
  switch (*type)
    {
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)clip;

	if (pic->res_id && !RessourceManager.disable_manager)
	  RessourceManager.TryRemove(ResManager::SF_RENDERTEXTURE, pic->res_id, pic);
	else
	  delete pic->texture;
	if (pic->ntexture)
	  delete pic->ntexture;
	delete pic->sprite;
	delete pic;
	scream_log_if("%p", "graphics", clip);
	return ;
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray	*pic = (struct bunny_pixelarray*)clip;

	if (pic->res_id && !RessourceManager.disable_manager)
	  {
	    RessourceManager.TryRemove(ResManager::SF_TEXTURE, pic->res_id, pic);
	    RessourceManager.TryRemove(ResManager::SF_IMAGE, pic->res_id, pic);
	    RessourceManager.TryRemove(ResManager::BUNNY_PIXELS, pic->res_id, pic);
	  }
	else if (getenv("TECHNOCORE") == NULL)
	  {
	    delete pic->tex;
	    delete pic->image;
	    bunny_free(pic->rawpixels);
	  }
	if (pic->ntexture)
	  delete pic->ntexture;
	delete pic->sprite;
	delete pic;
	scream_log_if("%p", "graphics", clip);
	return ;
      }
    case TTF_TEXT:
      {
	struct bunny_ttf_font	*ttf = (struct bunny_ttf_font*)clip;

	if (ttf->conf_string)
	  bunny_free(ttf->conf_string);
	if (!RessourceManager.disable_manager)
	  RessourceManager.TryRemove(ResManager::SF_FONT, ttf->res_id, ttf);
	else
	  delete ttf->font;
	delete ttf->text;
	delete ttf->sprite;
	if (ttf->ntexture)
	  delete ttf->ntexture;
	delete ttf->texture;
	delete ttf;
	scream_log_if("%p", "graphics", clip);
	return ;
      }
    case GRAPHIC_TEXT:
      {
	struct bunny_gfx_font	*gfx = (struct bunny_gfx_font*)clip;

	if (gfx->conf_string)
	  bunny_free(gfx->conf_string);
	bunny_delete_clipable(gfx->gfx);
	delete gfx->sprite;
	if (gfx->ntexture)
	  delete gfx->ntexture;
	delete gfx->texture;
	delete gfx;
	scream_log_if("%p", "graphics", clip);
	return ;
      }
    case DRESSED_SPRITE:
      {
	struct bunny_dressed_sprite *pic = (struct bunny_dressed_sprite*)clip;

	bunny_delete_map(pic->clothes);
	bunny_delete_map(pic->closets);
	[[fallthrough]];
      }
    case SPRITE:
      {
	struct bunny_sprite	*pic = (struct bunny_sprite*)clip;
	size_t			i;

	if (pic->res_id && !RessourceManager.disable_manager)
	  RessourceManager.TryRemove(ResManager::SF_RENDERTEXTURE, pic->res_id, pic);
	else if (pic->texture)
	  delete pic->texture;
	if (pic->ntexture)
	  delete pic->ntexture;
	if (pic->sprite)
	  delete pic->sprite;
	for (i = 0; i < pic->nbr_animation; ++i)
	  {
	    t_bunny_animation	&a = pic->animation[i];

	    if (a.frame_repetition)
	      bunny_free(a.frame_repetition);
	  }
	if (pic->animation)
	  bunny_free(pic->animation);
	if (pic->hashname_id)
	  bunny_delete_map(pic->hashname_id);
	delete pic;
	scream_log_if("%p", "graphics", clip);
	return ;
      }
    case PARALLAX:
      {
	struct bunny_parallax	*px = (struct bunny_parallax*)clip;

	for (size_t i = 0; i < px->nbr_layers; ++i)
	  if (px->layers[i].picture)
	    bunny_delete_clipable(px->layers[i].picture);
	bunny_free(px->layers);
	px->type = GRAPHIC_RAM;
	bunny_delete_clipable(clip);
	return ;
      }
    case TILEMAP:
      {
	struct bunny_tilemap	*tm = (struct bunny_tilemap*)clip;

	if (tm->duplicated_tilemap == false)
	  {
	    if (tm->layers)
	      {
		for (int i = 0; i < tm->nbr_layers; ++i)
		  bunny_delete_layer(&tm->layers[i]);
		bunny_free(tm->layers);
	      }
	    if (tm->tilesets)
	      {
		for (int i = 0; i < tm->nbr_tilesets; ++i)
		  bunny_delete_tileset(&tm->tilesets[i]);
		bunny_free(tm->tilesets);
	      }
	  }
	bunny_delete_clipable(tm->working);
	tm->type = GRAPHIC_RAM;
	bunny_delete_clipable(clip);
	return ;
      }
    case CINEMATIC:
      {
	bunny_delete_cinematic((t_bunny_cinematic*)clip);
	return ;
      }
    default:
      scream_error_if(return, EINVAL, "%p", "graphics", clip);
    }
}
