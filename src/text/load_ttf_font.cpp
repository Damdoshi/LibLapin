// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include		"lapin_private.h"

t_bunny_font		*bunny_load_ttf_font(const char			*file)
{
  struct bunny_ttf	*ttf;

  if ((ttf = new (std::nothrow) struct bunny_ttf) == NULL)
    goto Fail;
  if (ttf->font.loadFromFile(file) == false)
    goto FailStruct;

  ttf->text.setFont(ttf->font);

  ttf->type = TTF_TEXT;
  ttf->width = 0;
  ttf->height = 0;
  ttf->rect.x = 0;
  ttf->rect.y = 0;
  ttf->rect.w = ttf->width;
  ttf->rect.h = ttf->height;
  ttf->position.x = 0;
  ttf->position.y = 0;
  ttf->origin.x = 0;
  ttf->origin.y = 0;
  ttf->scale.x = 1;
  ttf->scale.y = 1;
  ttf->rotation = 0;
  ttf->color_mask.full = WHITE;

  ttf->string = NULL;
  ttf->hcrop = false;
  ttf->vcrop = false;
  ttf->justify = false;
  ttf->halign = BAL_LEFT;
  ttf->valign = BAL_TOP;
  ttf->outline = 0;

  BUNNY_LOG(fprintf(stderr, "%s: Returning %p.\n", __PRETTY_FUNCTION__, ttf));

  return ((t_bunny_font*)ttf);

 FailStruct:
  delete ttf;
 Fail:
  return (NULL);
}

