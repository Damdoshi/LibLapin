// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

struct			props
{
  double		v_space;
};

static size_t		get_char_width(t_bunny_font	*font,
				       size_t		i)
{
  struct bunny_ttf_font	*ttf;
  struct bunny_gfx_font	*gfx;

  if ((ttf = (struct bunny_ttf_font)font)->type == TTF_TEXT)
    // the outline should be in t_bunny_font
    return (ttf->font.getGlyph(font->string[i], font->glyph_size.y, false, 1).advance);
  gfx = (struct bunny_gfx_font*)font;
  return (gfx->glyph_size.x);
}

static size_t		count_newline(const char	*str)
{
  size_t		i, cnt;

  for (i = 0, cnt = 0; str[i]; ++i)
    if (str[i] == '\n')
      cnt += 1;
  return (cnt);
}

static size_t		count_lines(t_bunny_font	*font)
{
  size_t		hcnt;
  size_t		start_word;
  size_t		line;
  size_t		i, j;

  if (font->hcrop == false)
    return (count_newline(font->string));

  hcnt = 0;
  line = 0;
  start_word = 0;
  for (i = 0; font->string[i]; ++i)
    if (font->string[i] == '\n')
      {
	hcnt = 0;
	line += 1;
      }
    else if ((hcnt += get_char_width(font, i)) > font->clipable.buffer.width)
      {
	line += 1;
	if (font->string[i] == ' ')
	  while (font->string[++i] && font->string[i] == ' ');
	else
	  {
	    j = i - 1;
	    while (--i > 0 && font->string[i] != ' ');
	    if (i == 0)
	      i = j;
	    line += 1;
	    hcnt = 0;
	  }
	hcnt = 0;
      }
  return (line);
}

void			_bunny_draw_text(t_bunny_font	*font)
{
  
}

