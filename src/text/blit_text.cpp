// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include		"lapin_private.h"

void			__blit_text_gfx(t_bunny_buffer			*output,
					const t_bunny_clipable		*fnt,
					const t_bunny_position		*ps,
					const t_bunny_shader		*shader)
{
  // currently only handle a single line
  struct bunny_gfx_font	*font = (struct bunny_gfx_font*)fnt;
  t_bunny_area		rect;
  t_bunny_position	pos;
  int			chr_per_line;
  size_t		*type = (size_t*)fnt;
  size_t		t;
  int			i;

  t = *type;
  *type = GRAPHIC_RAM;
  
  memcpy(&rect, &font->rect, sizeof(rect));
  chr_per_line = font->width / font->rect.w;

  pos.x = ps->x - font->origin.x;
  pos.y = ps->y - font->origin.y;

  for (i = 0; font->string[i]; ++i)
    {
      font->rect.x = (font->string[i] % chr_per_line) * font->rect.w;
      font->rect.y = (font->string[i] / chr_per_line) * font->rect.h;
      pos.x += font->rect.w;
      bunny_blit_shader(output, fnt, &pos, shader);
    }

  memcpy(&font->rect, &rect, sizeof(font->rect));
  *type = t;
}

void			__blit_text_ttf(t_bunny_buffer			*output,
					const t_bunny_clipable		*ttf,
					const t_bunny_position		*pos,
					const t_bunny_shader		*shader)
{
  // currently only handle a single line
  struct bunny_window	*tar = (struct bunny_window*)output;
  struct bunny_ttf	*font = (struct bunny_ttf*)ttf;

  (void)shader;

  if (tar->type != WINDOW && tar->type != GRAPHIC_RAM)
    return ;
  sf::RenderTarget	*target = tar->window;

  font->text.setString(std::string(font->string));
  font->text.setFillColor
    (sf::Color
     (font->color_mask.argb[RED_CMP],
      font->color_mask.argb[GREEN_CMP],
      font->color_mask.argb[BLUE_CMP],
      font->color_mask.argb[ALPHA_CMP]
      ));
  font->text.setFont(font->font);
  font->text.setPosition(sf::Vector2f(pos->x - font->origin.x, pos->y - font->origin.y));
  font->text.scale(font->scale.x, font->scale.y);
  font->text.rotate(font->rotation);
  target->draw(font->text);
}

