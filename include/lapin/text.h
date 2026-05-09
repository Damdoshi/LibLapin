/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file text.h
** Text rendering helpers.
**
** The text module exposes t_bunny_font, a clipable object able to render either
** TrueType fonts or bitmap fonts into an internal texture. Fonts can be loaded
** directly or described through a bunny configuration file.
*/

#ifndef				__LAPIN_TEXT_H__
# define			__LAPIN_TEXT_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<stdbool.h>

/*!
** Alignment selector for t_bunny_font.
**
** BAL_LEFT, BAL_MIDDLE and BAL_RIGHT are used with t_bunny_font::halign.
** BAL_TOP, BAL_MIDDLE and BAL_BOTTOM are used with t_bunny_font::valign.
** BAL_JUSTIFY stretches the text by widening spaces between words or lines,
** depending on whether it is used horizontally or vertically.
*/
typedef enum			e_bunny_align
  {
    BAL_LEFT			= 0,
    BAL_TOP			= BAL_LEFT,

    BAL_MIDDLE			= 1,

    BAL_RIGHT			= 2,
    BAL_BOTTOM			= BAL_RIGHT,

    BAL_JUSTIFY			= 3
  }				t_bunny_align;

/*!
** Text box with an integrated font renderer.
**
** A t_bunny_font is compatible with APIs that accept a t_bunny_clipable,
** t_bunny_picture or t_bunny_buffer, because its first field is a clipable.
** Despite its name, the structure represents the rendered text box: the
** embedded clipable is the drawing target, not the font resource itself.
**
** It can use either a TrueType font or a bitmap font. Some attributes, such as
** outline and outline_size, are only available with TrueType fonts. Bitmap font
** coloring works as a mask and behaves best with white, gray or black glyphs.
**
** If clipable.clip_width / clipable.clip_height do not crop the whole surface,
** overflowing text may continue on following lines instead of being clipped.
** halign and valign choose the horizontal and vertical anchor of the text.
*/
# ifdef				__MINGW32__
#  pragma			pack(4)
# endif
typedef struct			s_bunny_font
{
  t_bunny_clipable		clipable;
  const size_t			_private[4];
  const char			*string;
  size_t			string_offset;
  size_t			string_len;
  t_bunny_align			halign;
  t_bunny_align			valign;
  unsigned int			color;
  unsigned int			outline;
  double			outline_size;
  t_bunny_position		offset;
  t_bunny_size  		glyph_size;
  t_bunny_size  		interglyph_space;
}				t_bunny_font;
# pragma			pack()

/*!
** Create a t_bunny_font fully configured from a configuration file.
**
** The file describes both the text box and the underlying font resource. The
** returned object must be released with bunny_delete_clipable.
**
** \param file The configuration file to load.
** \return A valid t_bunny_font on success, NULL on error.
*/
t_bunny_font			*bunny_load_text(const char			*file);

/*!
** Create a t_bunny_font from an already loaded configuration node.
**
** This is the configuration-node variant of bunny_load_text. The returned
** object must be released with bunny_delete_clipable.
**
** \param cnf The configuration node describing the text box.
** \return A valid t_bunny_font on success, NULL on error.
*/
t_bunny_font			*bunny_read_textbox(t_bunny_configuration	*cnf);

/*!
** Create a t_bunny_font from a font file or bitmap font.
**
** Supported direct resources are TrueType fonts and picture based fonts such as
** PNG, 24-bit BMP and JPG. If file is a configuration file, width, height and
** siz are ignored; bunny_load_text is the simpler entry point for that case.
**
** Picture fonts must contain 128 glyph clips arranged on a regular grid using
** siz. Unused glyphs may be left empty, but their slots must still exist. The
** returned object must be released with bunny_delete_clipable.
**
** \param width Width of the text box backing picture.
** \param height Height of the text box backing picture.
** \param file Font, bitmap font or configuration file to load.
** \param siz Glyph size for bitmap fonts; TrueType fonts mainly use siz->y.
** \return A valid t_bunny_font on success, NULL on error.
*/
t_bunny_font			*bunny_load_font(unsigned int			width,
					 unsigned int			height,
					 const char			*file,
					 const t_bunny_position		*siz);

/*!
** Create a t_bunny_font from an already available font resource.
**
** This lower level variant follows the same layout rules as bunny_load_font but
** does not perform the same file/configuration discovery path. The returned
** object must be released with bunny_delete_clipable.
**
** \param width Width of the text box backing picture.
** \param height Height of the text box backing picture.
** \param file Font or bitmap font resource to use.
** \param siz Glyph size for bitmap fonts; TrueType fonts mainly use siz->y.
** \return A valid t_bunny_font on success, NULL on error.
*/
t_bunny_font			*bunny_read_font(unsigned int			width,
					 unsigned int			height,
					 const char			*file,
					 const t_bunny_position		*siz);

/*!
** Resize the text box backing picture.
**
** \param fnt The font/text box to resize.
** \param width The new backing picture width.
** \param height The new backing picture height.
** \return True on success, false on error.
*/
bool				bunny_font_resize(t_bunny_font			*fnt,
					  unsigned int			width,
					  unsigned int			height);

/*!
** Load a font and apply text attributes from a configuration file or node.
**
** Recognized fields include RessourceFile, BoxSize or Size, GlyphSize, Text or
** String, TextOffset or StringOffset, TextLength or StringLength,
** HorizontalAlign, VerticalAlign, Color, OutlineColor, OutlineSize, Interglyph
** and Scrolling. Clipable attributes are also applied.
**
** \param conf_file Configuration file to load, or NULL when config is used.
** \param font Where to store the loaded font.
** \param config Optional configuration pointer to read from or update.
** \return True on success, false on error.
*/
bool				bunny_set_font_attribute(const char		*conf_file,
						 t_bunny_font		**font,
						 t_bunny_configuration **config);

/*!
** One line segment of the vector font.
**
** The segment goes from (x0, y0) to (x1, y1) in the 2D coordinate space used by
** gl_vector_font.
*/
typedef struct			s_bunny_vector_font_line_coord
{
  int				x0;
  int				y0;
  int				x1;
  int				y1;
}				t_bunny_vector_font_line_coord;

/*!
** Vector description of one glyph in gl_vector_font.
**
** Characters use a 0..20 coordinate range on both axes. Only the first nb_edge
** entries of edge are defined.
*/
typedef struct			s_bunny_letter
{
  int				nb_edge;
  t_bunny_vector_font_line_coord edge[6];
}				t_bunny_letter;

/*!
** Indices used to read gl_vector_font.
**
** LAST_BUNNY_FONT is the number of available glyphs and is not itself a glyph.
*/
typedef enum			e_bunny_letter_tab
  {
    BFT_A,
    BFT_B,
    BFT_C,
    BFT_D,
    BFT_E,
    BFT_F,
    BFT_G,
    BFT_H,
    BFT_I,
    BFT_J,
    BFT_K,
    BFT_L,
    BFT_M,
    BFT_N,
    BFT_O,
    BFT_P,
    BFT_Q,
    BFT_R,
    BFT_S,
    BFT_T,
    BFT_U,
    BFT_V,
    BFT_W,
    BFT_X,
    BFT_Y,
    BFT_Z,
    BFT_0,
    BFT_1,
    BFT_2,
    BFT_3,
    BFT_4,
    BFT_5,
    BFT_6,
    BFT_7,
    BFT_8,
    BFT_9,
    BFT_EXCLAMATION,
    BFT_SLASH,
    BFT_DOT,
    LAST_BUNNY_FONT
  }				t_bunny_letter_tab;


/*!
** Built-in vector font.
**
** Each entry is a set of line segments that can be drawn to display a glyph.
** The storage order is described by t_bunny_letter_tab. This font is useful for
** effects such as rotating or demoscene-like text.
*/
extern const t_bunny_letter	gl_vector_font[LAST_BUNNY_FONT];

#endif	/*			__LAPIN_TEXT_H__	*/
