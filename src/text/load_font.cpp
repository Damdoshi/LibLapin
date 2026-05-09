// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			<string.h>
#include			"lapin_private.h"

#define				PATTERN		"%u width, %u height, %s file, %p (%d, %d) size -> %p"

/*!
** Load a font object that can render text into an internal clipable buffer.
**
** The file may be a TrueType font, a bitmap font image, or a configuration
** file. When a configuration file is sent, this function delegates the loading
** and attribute setup to bunny_set_font_attribute. For direct font loading,
** size contains the glyph size. Bitmap fonts expect glyphs to be arranged on
** a regular grid using this glyph size.
**
** The returned object is also a t_bunny_clipable and must be released with
** bunny_delete_clipable.
**
** \param width The width, in pixels, of the text rendering surface.
** \param height The height, in pixels, of the text rendering surface.
** \param file The font, bitmap font, or text configuration file to load.
** \param size The glyph size for direct font loading.
** \return A new t_bunny_font, or NULL on error.
*/

/**
 * @doc
 * @doc-symbol bunny_load_font
 * @doc-kind function
 * @doc-module text
 * @doc-order 140
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a font/text box from a font file, bitmap font or configuration file.
 * @param width Width of the text rendering surface.
 * @param height Height of the text rendering surface.
 * @param file Font, bitmap font or configuration file.
 * @param size Glyph size for bitmap fonts; TrueType fonts mainly use size->y.
 * @return-success Returns a newly allocated t_bunny_font.
 * @return-failure Returns NULL on error.
 * @log "ressource,text"
 * @see bunny_load_text, bunny_read_textbox, bunny_delete_clipable
 *
 * @doc-lang fr
 * @brief Crée une police/boîte de texte depuis un fichier de police, une police bitmap ou un fichier de configuration.
 * @param width Largeur de la surface de rendu du texte.
 * @param height Hauteur de la surface de rendu du texte.
 * @param file Police, police bitmap ou fichier de configuration.
 * @param size Taille des glyphes pour les polices bitmap ; les polices TrueType utilisent surtout size->y.
 * @return-success Renvoie un t_bunny_font nouvellement alloué.
 * @return-failure Renvoie NULL en cas d'erreur.
 * @log "ressource,text"
 * @see bunny_load_text, bunny_read_textbox, bunny_delete_clipable
 */
t_bunny_font			*bunny_load_font(unsigned int		width,
						 unsigned int		height,
						 const char		*file,
						 const t_bunny_position	*size)
{
  t_bunny_font			*final;

  if (bunny_which_format(file) != BC_CUSTOM)
    {
      final = NULL;
      if (bunny_set_font_attribute(file, &final, NULL) == false)
	return (NULL);
      return (final);
    }
  else if (strstr(file, ".ttf"))
    final = __bunny_load_ttf(width, height, file, size);
  else
    final = __bunny_load_gfx(width, height, file, size);
  if (final == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "ressource,text", width, height, file, size, size->x, size->y, (void*)NULL);

  // Clipable properties
  final->clipable.buffer.width = width;
  final->clipable.buffer.height = height;
  final->clipable.clip_x_position = 0;
  final->clipable.clip_y_position = 0;
  final->clipable.clip_width = width;
  final->clipable.clip_height = height;
  final->clipable.position.x = 0;
  final->clipable.position.y = 0;
  final->clipable.origin.x = 0;
  final->clipable.origin.y = 0;
  final->clipable.scale.x = 1;
  final->clipable.scale.y = 1;
  final->clipable.rotation = 0;
  final->clipable.color_mask.full = WHITE;
  final->clipable.smooth = false;
  final->clipable.mosaic = false;
  ((struct bunny_ttf_font*)final)->glactive = false;

  // Text properties
  final->string = NULL;
  final->string_offset = 0;
  final->string_len = (size_t)-1;
  final->halign = BAL_LEFT;
  final->valign = BAL_TOP;
  final->outline = 0;
  final->outline_size = 0;
  final->color = WHITE;
  final->offset.x = 0;
  final->offset.y = 0;
  final->interglyph_space.x = 0;
  final->interglyph_space.y = 0;

  scream_log_if(PATTERN, "ressource,text", width, height, file, size, size->x, size->y, final);
  return (final);
}

/*!
** Build a text box from an already loaded configuration node.
**
** The configuration is interpreted with the same fields as
** bunny_set_font_attribute. The configuration pointer may be updated by the
** loader when the underlying helper resolves or keeps the configuration.
**
** \param cnf The configuration node describing the text box.
** \return A new t_bunny_font, or NULL on error.
*/

/**
 * @doc
 * @doc-symbol bunny_read_textbox
 * @doc-kind function
 * @doc-module text
 * @doc-order 130
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a text box from an already loaded configuration node.
 * @param cnf Configuration node describing the text box.
 * @return-success Returns a newly allocated t_bunny_font.
 * @return-failure Returns NULL on error.
 * @log "ressource,text"
 * @see bunny_load_text, bunny_set_font_attribute
 *
 * @doc-lang fr
 * @brief Crée une boîte de texte depuis un nœud de configuration déjà chargé.
 * @param cnf Nœud de configuration décrivant la boîte de texte.
 * @return-success Renvoie un t_bunny_font nouvellement alloué.
 * @return-failure Renvoie NULL en cas d'erreur.
 * @log "ressource,text"
 * @see bunny_load_text, bunny_set_font_attribute
 */
t_bunny_font			*bunny_read_textbox(t_bunny_configuration *cnf)
{
  t_bunny_font			*f;

  if (bunny_set_font_attribute(NULL, &f, &cnf) == false)
    return (NULL);
  return (f);
}

/*!
** Load a text box from a configuration file.
**
** This is a convenience wrapper around bunny_load_font for configuration based
** text. The size of the rendering surface and the glyph size are expected to
** be provided by the configuration file.
**
** \param file The text configuration file to load.
** \return A new t_bunny_font, or NULL on error.
*/

/**
 * @doc
 * @doc-symbol bunny_load_text
 * @doc-kind function
 * @doc-module text
 * @doc-order 125
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Loads a text box from a configuration file.
 * @param file Text configuration file.
 * @return-success Returns a newly allocated t_bunny_font.
 * @return-failure Returns NULL on error.
 * @log "ressource,text"
 * @see bunny_read_textbox, bunny_load_font
 *
 * @doc-lang fr
 * @brief Charge une boîte de texte depuis un fichier de configuration.
 * @param file Fichier de configuration du texte.
 * @return-success Renvoie un t_bunny_font nouvellement alloué.
 * @return-failure Renvoie NULL en cas d'erreur.
 * @log "ressource,text"
 * @see bunny_read_textbox, bunny_load_font
 */
t_bunny_font			*bunny_load_text(const char		*file)
{
  return (bunny_load_font(0, 0, file, NULL));
}

