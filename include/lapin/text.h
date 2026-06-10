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

/**
 * @doc
 * @doc-symbol text
 * @doc-kind module
 * @doc-module text
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Renders text through t_bunny_font clipable objects.
 * @description The text module can use TrueType fonts, bitmap fonts and configuration-described text boxes. A t_bunny_font is also a clipable object and can be drawn like other graphics resources.
 * @header lapin/text.h
 *
 * @doc-lang fr
 * @brief Rend du texte avec des objets clipables t_bunny_font.
 * @description Le module text peut utiliser des polices TrueType, des polices bitmap et des textboxes décrites par configuration. Un t_bunny_font est aussi un objet clipable et peut être dessiné comme les autres ressources graphiques.
 * @header lapin/text.h
 */

/**
 * @doc
 * @doc-symbol t_bunny_align
 * @doc-kind enum
 * @doc-module text
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Selects horizontal or vertical text alignment.
 * @value BAL_LEFT Left horizontal alignment. It is also BAL_TOP for vertical alignment.
 * @value BAL_TOP Alias of BAL_LEFT for vertical alignment.
 * @value BAL_MIDDLE Centered horizontal or vertical alignment.
 * @value BAL_RIGHT Right horizontal alignment. It is also BAL_BOTTOM for vertical alignment.
 * @value BAL_BOTTOM Alias of BAL_RIGHT for vertical alignment.
 * @value BAL_JUSTIFY Justified horizontal or vertical alignment.
 * @see t_bunny_font
 *
 * @doc-lang fr
 * @brief Sélectionne l'alignement horizontal ou vertical du texte.
 * @value BAL_LEFT Alignement horizontal à gauche. C'est aussi BAL_TOP pour l'alignement vertical.
 * @value BAL_TOP Alias de BAL_LEFT pour l'alignement vertical.
 * @value BAL_MIDDLE Alignement horizontal ou vertical centré.
 * @value BAL_RIGHT Alignement horizontal à droite. C'est aussi BAL_BOTTOM pour l'alignement vertical.
 * @value BAL_BOTTOM Alias de BAL_RIGHT pour l'alignement vertical.
 * @value BAL_JUSTIFY Alignement horizontal ou vertical justifié.
 * @see t_bunny_font
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

/**
 * @doc
 * @doc-symbol t_bunny_font
 * @doc-kind struct
 * @doc-module text
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a rendered text box backed by a font resource.
 * @description The first field is a t_bunny_clipable, so a font can be drawn with normal clipable drawing functions. Despite its name, this structure represents the text box and its render target more than the font resource alone.
 * @field clipable Base clipable used as the text rendering target.
 * @field string Text to display.
 * @field string_offset First character index displayed from string.
 * @field string_len Maximum number of characters displayed from string.
 * @field halign Horizontal alignment.
 * @field valign Vertical alignment.
 * @field color Text color.
 * @field outline Outline color for TrueType fonts.
 * @field outline_size Outline width for TrueType fonts.
 * @field offset Drawing offset.
 * @field glyph_size Glyph size.
 * @field interglyph_space Additional space between glyphs.
 * @see bunny_load_text, bunny_load_font, bunny_delete_clipable
 *
 * @doc-lang fr
 * @brief Représente une boîte de texte rendue à partir d'une ressource de police.
 * @description Le premier champ est un t_bunny_clipable, donc une police peut être dessinée avec les fonctions de dessin clipable habituelles. Malgré son nom, cette structure représente davantage la boîte de texte et sa cible de rendu que la seule ressource de police.
 * @field clipable Clipable de base utilisé comme cible de rendu du texte.
 * @field string Texte à afficher.
 * @field string_offset Premier index de caractère affiché depuis string.
 * @field string_len Nombre maximal de caractères affichés depuis string.
 * @field halign Alignement horizontal.
 * @field valign Alignement vertical.
 * @field color Couleur du texte.
 * @field outline Couleur de contour pour les polices TrueType.
 * @field outline_size Épaisseur du contour pour les polices TrueType.
 * @field offset Décalage de dessin.
 * @field glyph_size Taille des glyphes.
 * @field interglyph_space Espace additionnel entre glyphes.
 * @see bunny_load_text, bunny_load_font, bunny_delete_clipable
 */
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

/**
 * @doc
 * @doc-symbol t_bunny_vector_font_line_coord
 * @doc-kind struct
 * @doc-module text
 * @doc-order 160
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores one line segment of the built-in vector font.
 * @field x0 Start point x coordinate.
 * @field y0 Start point y coordinate.
 * @field x1 End point x coordinate.
 * @field y1 End point y coordinate.
 * @see t_bunny_letter, gl_vector_font
 *
 * @doc-lang fr
 * @brief Stocke un segment de ligne de la police vectorielle intégrée.
 * @field x0 Coordonnée x du point de départ.
 * @field y0 Coordonnée y du point de départ.
 * @field x1 Coordonnée x du point d'arrivée.
 * @field y1 Coordonnée y du point d'arrivée.
 * @see t_bunny_letter, gl_vector_font
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

/**
 * @doc
 * @doc-symbol t_bunny_letter
 * @doc-kind struct
 * @doc-module text
 * @doc-order 180
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Describes one glyph of the built-in vector font.
 * @field nb_edge Number of line segments used by the glyph.
 * @field edge Segment array. Only the first nb_edge entries are valid.
 * @see t_bunny_vector_font_line_coord, gl_vector_font
 *
 * @doc-lang fr
 * @brief Décrit un glyphe de la police vectorielle intégrée.
 * @field nb_edge Nombre de segments utilisés par le glyphe.
 * @field edge Tableau de segments. Seules les nb_edge premières entrées sont valides.
 * @see t_bunny_vector_font_line_coord, gl_vector_font
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

/**
 * @doc
 * @doc-symbol t_bunny_letter_tab
 * @doc-kind enum
 * @doc-module text
 * @doc-order 200
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Indexes glyphs inside gl_vector_font.
 * @description Values BFT_A to BFT_Z cover uppercase letters, BFT_0 to BFT_9 cover digits, and the remaining entries cover punctuation provided by the built-in vector font.
 * @value LAST_BUNNY_FONT Number of glyphs stored in gl_vector_font.
 * @see gl_vector_font, t_bunny_letter
 *
 * @doc-lang fr
 * @brief Indexe les glyphes dans gl_vector_font.
 * @description Les valeurs BFT_A à BFT_Z couvrent les lettres majuscules, BFT_0 à BFT_9 couvrent les chiffres, et les entrées restantes couvrent la ponctuation fournie par la police vectorielle intégrée.
 * @value LAST_BUNNY_FONT Nombre de glyphes stockés dans gl_vector_font.
 * @see gl_vector_font, t_bunny_letter
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

/**
 * @doc
 * @doc-symbol gl_vector_font
 * @doc-kind variable
 * @doc-module text
 * @doc-order 220
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Built-in vector font glyph table.
 * @description Each glyph is represented by a small set of line segments in a 0..20 coordinate system.
 * @see t_bunny_letter, t_bunny_letter_tab
 *
 * @doc-lang fr
 * @brief Table des glyphes de la police vectorielle intégrée.
 * @description Chaque glyphe est représenté par un petit ensemble de segments dans un repère 0..20.
 * @see t_bunny_letter, t_bunny_letter_tab
 */
extern const t_bunny_letter	gl_vector_font[LAST_BUNNY_FONT];

#endif	/*			__LAPIN_TEXT_H__	*/
