// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdio.h>
#include		"lapin_private.h"

#define			LINEMEM_SIZE			512

struct			cstring
{
  const char		*str;
  size_t		len;
};

static int		get_unicode_len(const char	*str)
{
  if (!(*str & 0x80)) // Unicode character
    return (1);
  if ((*str & 0xE0) == 0xC0) // 110x xxxx
    return (2);
  if ((*str & 0xF0) == 0xE0) // 1110 xxxx
    return (3);
  if ((*str & 0xF8) == 0xF0) // 1111 0xxx
    return (4);
  return (1);
}

static size_t		get_char_width(t_bunny_font	*font,
				       const char	*str,
				       size_t		i)
{
  struct bunny_ttf_font	*ttf;
  struct bunny_gfx_font	*gfx;
  int			len = get_unicode_len(&str[i]);
  std::string		x(str, i, len);
  std::basic_string<sf::Uint32> conv;

  sf::Utf8::toUtf32(x.begin(), x.end(), std::back_inserter(conv));

  if ((ttf = (struct bunny_ttf_font*)font)->type == TTF_TEXT)
    return (ttf->font->getGlyph
	    (conv[0], font->glyph_size.y, false, 1).advance + font->interglyph_space.x);
  gfx = (struct bunny_gfx_font*)font;
  return (gfx->glyph_size.x + font->interglyph_space.x);
}

static size_t		count_word(const char		*str,
				   size_t		len)
{
  size_t		cnt, i;

  cnt = 0;
  for (i = 1; str[i + 1] && i < len; )
    {
      if (str[i - 1] == ' ' && str[i] != ' ')
	cnt += 1;
      i += get_unicode_len(&str[i]);
    }
  return (cnt ? cnt : 1);
}

static size_t		total_len(t_bunny_font		*font,
				  const char		*str,
				  size_t		len)
{
  size_t		cnt, i;

  cnt = 0;
  for (i = 0; str[i] && i < len; )
    {
      cnt += get_char_width(font, str, i);
      i += get_unicode_len(&str[i]);
    }
  return (cnt);
}

static size_t		sum_letter_space(t_bunny_font	*font,
					 const char	*str,
					 size_t		len)
{
  size_t		cnt, i;
  bool			space;

  cnt = 0;
  space = false;
  for (i = 0; str[i] && i < len; )
    {
      if (str[i] != ' ')
	{
	  cnt += get_char_width(font, str, i);
	  space = false;
	}
      else if (space == false)
	{
	  space = true;
	  cnt += get_char_width(font, str, i);
	}
      i += get_unicode_len(&str[i]);
    }
  return (cnt);
}

static void		remove_trailing(struct cstring	*line)
{
  size_t		i;

  while (line->str[0] == ' ' || line->str[0] == '\n' || line->str[0] == '\r')
    {
      line->str = &line->str[1];
      line->len -= 1;
    }
  for (i = line->len; i > 0 &&
	 (line->str[i] == ' ' || line->str[i] == '\n' || line->str[i] == '\r');
       --i);
  if (line->str[i])
    line->len = i + (int)(i != 0);
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
  for (i = 0; font->string[i] && line < LINEMEM_SIZE - 1; ++i)
    if (font->string[i] == '\n')
      {
	hcnt = 0;
	line += 1;
	linemem[line].str = &font->string[i];
	linemem[line - 1].len = linemem[line].str - linemem[line - 1].str; 
      }
    else if ((hcnt += get_char_width(font, font->string, i)) >= font->clipable.clip_width)
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
	    while (font->string[i] && font->string[i] == ' ')
	      i += 1;
	  }
	hcnt = 0;
      }
  if (line > 0)
    linemem[line].len = &font->string[i] - linemem[line - 1].str;
  else
    linemem[line].len = i;
  linemem[line + 1].str = NULL;
  for (i = 0; linemem[i].str; ++i)
    remove_trailing(&linemem[i]);
  return (line);
}

static int		put_letter(t_bunny_font		*font,
				   t_bunny_position	&pos,
				   const char		*str,
				   size_t		i,
				   int			outl)
{
  size_t		*s = (size_t*)font;
  int			len = get_unicode_len(&str[i]);

  if (*s == TTF_TEXT)
    {
      struct bunny_ttf_font *fnt = (struct bunny_ttf_font*)font;
      std::basic_string<sf::Uint32>			conv;
      std::string					x(str, i, len);

      sf::Utf8::toUtf32(x.begin(), x.end(), std::back_inserter(conv));
      fnt->text->setPosition(sf::Vector2f(pos.x, pos.y));
      fnt->text->setString(sf::String(conv));
      fnt->texture->draw(*fnt->text);
    }
  else
    {
      struct bunny_gfx_font *fnt = (struct bunny_gfx_font*)font;
      t_bunny_position	tpos;
      int		n;

      n = str[i] * fnt->gfx->clip_width;
      fnt->gfx->clip_x_position = n % fnt->gfx->buffer.width;
      fnt->gfx->clip_y_position = n / fnt->gfx->buffer.width;

      if (outl == 0)
	{
	  t_bunny_color	tmp = fnt->gfx->color_mask;

	  fnt->gfx->color_mask.full = fnt->outline_color;
	  for (int l = -font->outline_size; l <= font->outline_size; ++l)
	    for (int m = -font->outline_size; m <= font->outline_size; ++m)
	      {
		if (l == 0 && m == 0)
		  continue ;
		tpos = pos;
		tpos.x += l;
		tpos.y += m;
		bunny_blit(&font->clipable.buffer, fnt->gfx, &tpos);
	      }
	  fnt->gfx->color_mask = tmp;
	}
      else
	{
	  tpos.x = pos.x + font->outline_size / 2;
	  tpos.y = pos.y + font->outline_size / 2;
	  bunny_blit(&font->clipable.buffer, fnt->gfx, &tpos);
	}
    }
  return (len);
}

void			put_text(t_bunny_font		*font,
				 struct cstring		*linemem,
				 double			vpitch,
				 t_bunny_position	startpos,
				 t_bunny_position	iterat,
				 int			bis)
{
  size_t		i, j, k;
  double		hspace;
  int			word;
  int			space;

  for (j = 0, k = 0; linemem[j].str != NULL; ++j, iterat.y += vpitch)
    {
      if (font->halign == BAL_JUSTIFY)
	{
	  space = sum_letter_space(font, linemem[j].str, linemem[j].len);
	  word = count_word(linemem[j].str, linemem[j].len);
	  hspace = (font->clipable.clip_width - space) / word;
	  startpos.x = font->offset.x;
	}
      else
	{
	  space = total_len(font, linemem[j].str, linemem[j].len);
	  hspace = get_char_width(font, " ", 0);
	  if (font->halign == BAL_LEFT)
	    startpos.x = font->offset.x;
	  else if (font->halign == BAL_MIDDLE)
	    startpos.x = (font->clipable.clip_width - space) / 2 + font->offset.x;
	  else if (font->halign == BAL_RIGHT)
	    startpos.x = font->clipable.clip_width - space + font->offset.x;
	  else
	    startpos.x = 0; // Never happen
	}

      iterat.x = startpos.x;
      for (i = 0; linemem[j].str[i] && i < linemem[j].len; )
	if (linemem[j].str[i] != '\n')
	  {
	    int		adv = 0;

	    if (k >= font->string_offset && k < font->string_len)
	      adv = put_letter(font, iterat, linemem[j].str, i, bis);

	    if (linemem[j].str[i] != ' ')
	      iterat.x += get_char_width(font, linemem[j].str, i);
	    else
	      iterat.x += hspace;

	    if (++k > font->string_len)
	      return ;
	    i += adv;
	  }
	else
	  ++i;

      if (*(size_t*)font == TTF_TEXT || font->outline_size == 0)
	break ;
    }
}

void			_bunny_draw_text(t_bunny_font	*font)
{
  struct cstring	linemem[LINEMEM_SIZE];
  double		vpitch;
  t_bunny_position	startpos, iterat;
  int			lines;

  if (font->string == NULL)
    return ;
  if (*((size_t*)font) == TTF_TEXT)
    {
      struct bunny_ttf_font *fnt = (struct bunny_ttf_font*)font;

      fnt->text->setOutlineThickness(fnt->outline_size);
      fnt->text->setOutlineColor(bunny_color_to_sf_color(fnt->outline_color));
      fnt->text->setFillColor(bunny_color_to_sf_color(fnt->color));
    }
  else
    {
      struct bunny_gfx_font *fnt = (struct bunny_gfx_font*)font;

      fnt->gfx->color_mask.full = fnt->color;
    }

  lines = count_lines(font, &linemem[0]);

  if (font->valign != BAL_JUSTIFY)
    {
      vpitch = font->glyph_size.y + font->interglyph_space.y;
      if (font->valign == BAL_TOP)
	startpos.y = font->offset.y;
      else if (font->valign == BAL_MIDDLE)
	startpos.y = (font->clipable.clip_height - (lines + 1.5) * font->glyph_size.y) / 2
	  + font->offset.y;
      else if (font->valign == BAL_BOTTOM)
	startpos.y = font->clipable.clip_height - (lines + 1) * font->glyph_size.y
	  + font->offset.y;
      else
	startpos.y = 0; // Never happen

      iterat.y = startpos.y;
    }
  else
    {
      if ((vpitch = font->clipable.clip_height / (lines + 2)) < font->glyph_size.y)
	vpitch = font->glyph_size.y + font->interglyph_space.y;
      startpos.y = font->offset.y;

      iterat.y = startpos.y + vpitch;
    }

  for (int bis = 0; bis < 2; ++bis)
    put_text(font, linemem, vpitch, startpos, iterat, bis);
}

