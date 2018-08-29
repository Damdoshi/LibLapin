// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

void				_bunny_delete_clipable(t_bunny_clipable	*clip)
{
  size_t			*type = (size_t*)clip;

  switch (*type)
    {
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)clip;

	if (pic->res_id && !RessourceManager.disable_manager)
	  RessourceManager.TryRemove(ResManager::SF_RENDERTEXTURE, pic->res_id, pic);
	else
	  delete pic->texture;
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
	delete gfx->texture;
	delete gfx;
	scream_log_if("%p", "graphics", clip);
	return ;
      }
    case SPRITE:
      {
	struct bunny_sprite	*pic = (struct bunny_sprite*)clip;
	size_t			i;

	if (pic->res_id && !RessourceManager.disable_manager)
	  RessourceManager.TryRemove(ResManager::SF_RENDERTEXTURE, pic->res_id, pic);
	else
	  delete pic->texture;
	delete pic->sprite;
	for (i = 0; i < bunny_vector_size(pic->animation); ++i)
	  {
	    t_bunny_animation	&a = bunny_vector_data(pic->animation, i, t_bunny_animation);

	    if (a.frame_repetition)
	      bunny_delete_vector(a.frame_repetition);
	  }
	bunny_delete_vector(pic->animation);
	bunny_delete_map(pic->hashname_id);
	delete pic;
	scream_log_if("%p", "graphics", clip);
	return ;
      }
    default:
      scream_error_if(return, EINVAL, "%p", "graphics", clip);
    }
}
