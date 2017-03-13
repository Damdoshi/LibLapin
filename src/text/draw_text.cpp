// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

struct			cstring
{
  const char		*str;
  size_t		len;
};

static size_t		get_char_width(t_bunny_font	*font,
				       const char	*str,
				       size_t		i)
{
  struct bunny_ttf_font	*ttf;
  struct bunny_gfx_font	*gfx;

  if ((ttf = (struct bunny_ttf_font*)font)->type == TTF_TEXT)
    // the outline should be in t_bunny_font
    return (ttf->font.getGlyph(str[i], font->glyph_size.y, false, 1).advance);
  gfx = (struct bunny_gfx_font*)font;
  return (gfx->glyph_size.x);
}

static size_t		count_word(const char		*str,
				   size_t		len)
{
  size_t		cnt, i;

  cnt = 0;
  for (i = 0; str[i + 1] && i < len; ++i)
    if (str[i] != ' ' && str[i + 1] == ' ')
      cnt += 1;
  return (cnt);
}

static size_t		sum_letter_space(t_bunny_font	*font,
					 const char	*str,
					 size_t		len)
{
  size_t		cnt, i;

  cnt = 0;
  for (i = 0; str[i] && i < len; ++i)
    if (str[i] != ' ')
      cnt += get_char_width(font, str, i);
  return (cnt);
}

static size_t		total_len(t_bunny_font		*font,
				  const char		*str,
				  size_t		len)
{
  size_t		cnt, i;

  cnt = 0;
  for (i = 0; str[i] && i < len; ++i)
    cnt += get_char_width(font, str, i);
  return (cnt);
}

static size_t		count_lines(t_bunny_font	*font,
				    struct cstring	*linemem)
{
  ssize_t		hcnt;
  size_t		line;
  size_t		i, j;

  hcnt = 0;
  line = 0;
  linemem[0].str = font->string;
  for (i = 0; font->string[i]; ++i)
    if (font->string[i] == '\n')
      {
	hcnt = 0;
	line += 1;
	linemem[line].str = &font->string[i];
	linemem[line - 1].len = linemem[line].str - linemem[line - 1].str; 
      }
    else if ((hcnt += get_char_width(font, font->string, i)) > font->clipable.buffer.width)
      {
	if (font->string[i] == ' ')
	  {
	    while (font->string[++i] && font->string[i] == ' ');
	    line += 1;
	    linemem[line].str = &font->string[i];
	    linemem[line - 1].len = linemem[line].str - linemem[line - 1].str; 
	  }
	else
	  {
	    j = i - 1;
	    while (--i > 0 && font->string[i] != ' ');
	    if (i == 0)
	      i = j;
	    line += 1;
	    linemem[line].str = &font->string[i];
	    linemem[line - 1].len = linemem[line].str - linemem[line - 1].str; 
	    hcnt = 0;
	  }
	hcnt = 0;
      }
  linemem[line].len = &font->string[i] - linemem[line - 1].str;
  linemem[line + 1].str = NULL;
  return (line);
}

static void		put_letter(t_bunny_font		*font,
				   t_bunny_position	&pos,
				   const char		*str,
				   size_t		i)
{
  size_t		*s = (size_t*)font;

  if (*s == TTF_TEXT)
    {
      struct bunny_ttf_font *fnt = (struct bunny_ttf_font*)font;

      fnt->text.setPosition(sf::Vector2f(pos.x, pos.y));
      fnt->text.setString(std::string(str, i, 1));
      fnt->texture->draw(fnt->text);
    }
  else
    {
      struct bunny_gfx_font *fnt = (struct bunny_gfx_font*)font;
      int		n;

      n = str[i] * fnt->rect.w;
      fnt->gfx->clip_x_position = n % fnt->gfx->buffer.width;
      fnt->gfx->clip_y_position = n / fnt->gfx->buffer.height;
      bunny_blit(&font->clipable.buffer, fnt->gfx, &pos);
    }
}

void			_bunny_draw_text(t_bunny_font	*font)
{
  struct cstring	linemem[512];
  double		vpitch, hspace;
  t_bunny_position	startpos, iterat;
  int			lines, word, space;
  size_t		i, j;

  if (*((size_t*)font) == TTF_TEXT)
    {
      struct bunny_ttf_font *fnt = (struct bunny_ttf_font*)font;

      fnt->text.setOutlineThickness(fnt->outline_size);
      fnt->text.setOutlineColor(bunny_color_to_sf_color(fnt->outline_color));
      fnt->text.setFillColor(bunny_color_to_sf_color(fnt->color));
    }
  else
    {
      struct bunny_gfx_font *fnt = (struct bunny_gfx_font*)font;

      fnt->gfx->color_mask.full = fnt->color;
    }

  lines = count_lines(font, &linemem[0]);

  if (font->valign != BAL_JUSTIFY)
    {
      vpitch = font->glyph_size.y;
      if (font->valign == BAL_TOP)
	startpos.y = font->offset.y;
      if (font->valign == BAL_MIDDLE)
	startpos.y = (font->clipable.buffer.height - lines * font->glyph_size.y) / 2 + font->offset.y;
      else if (font->valign == BAL_BOTTOM)
	startpos.y = font->clipable.buffer.height - lines * font->glyph_size.y + font->offset.y;
    }
  else
    {
      if ((vpitch = font->clipable.buffer.height / lines) < font->glyph_size.y)
	vpitch = font->glyph_size.y;
      startpos.y = font->offset.y;
    }

  iterat.y = startpos.y;
  for (j = 0; linemem[j].str != NULL; ++j, iterat.y += vpitch)
    {
      if (font->halign == BAL_JUSTIFY)
	{
	  space = sum_letter_space(font, linemem[j].str, linemem[j].len);
	  word = count_word(linemem[j].str, linemem[j].len);
	  hspace = (font->clipable.buffer.width - space) / word;
	  startpos.x = font->offset.x;
	}
      else
	{
	  space = total_len(font, linemem[j].str, linemem[j].len);
	  hspace = get_char_width(font, " ", 0);
	  if (font->halign == BAL_LEFT)
	    startpos.x = font->offset.x;
	  else if (font->halign == BAL_MIDDLE)
	    startpos.x = (font->clipable.buffer.width - space) / 2 + font->offset.x;
	  else if (font->halign == BAL_RIGHT)
	    startpos.x = font->clipable.buffer.width - space + font->offset.x;
	}

      iterat.x = startpos.x;
      for (i = 0; linemem[j].str[i]; ++i)
	{
	  if (linemem[j].str[i] != ' ')
	    iterat.x += get_char_width(font, linemem[j].str, i);
	  else
	    iterat.x += hspace;

	  put_letter(font, iterat, linemem[j].str, i);
	}
    }
}

