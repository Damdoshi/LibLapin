/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_TEXT_H__
# define			__LAPIN_TEXT_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<stdbool.h>

/*!
** Useful to precise on which side you want to align.
** Yes, there is a vertical align, not like CSS.
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
** The t_bunny_font structure is a t_bunny_clipable that display the
** text precised in the text field.
** A behavior which is different from the basic clipable is that
** if crop is false (it is by default), then instead of clipping
** the text, letters which make a new line and go one.
**
** halign and valign are useful to set the root of the text, horizontaly
** and verticaly.
*/
typedef struct			s_bunny_font
{
  t_bunny_clipable		clipable;
  const size_t			_private[3];
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

t_bunny_font			*bunny_load_font(unsigned int			width,
						 unsigned int			height,
						 const char			*file,
						 const t_bunny_position		*siz);

/*!
**
*/
bool				bunny_set_text_attribute(const char		*conf_file,
							 t_bunny_font		**font,
							 t_bunny_configuration **config,
							 bool			is_ttf);

/*!
** The t_bunny_vector_font_line_coord contains two sets of coordinates that
** represent a complete line. It is used by the t_bunny_letter structure
** in order to store coordinates of the gl_vector font.
*/
typedef struct			s_bunny_vector_font_line_coord
{
  int				x0;
  int				y0;
  int				x1;
  int				y1;
}				t_bunny_vector_font_line_coord;

/*!
** The t_bunny_letter structure contains the amount of lines for a letter
** of the gl_vector font, and an array of nb_edge t_bunny_vector_font_line_coord.
*/
typedef struct			s_bunny_letter
{
  int				nb_edge;
  t_bunny_vector_font_line_coord edge[5];
}				t_bunny_letter;

/*!
** The vector font symbol tab.
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
    LAST_BUNNY_FONT
  }				t_bunny_letter_tab;


/*!
** The gl_vector constant is a collection of letters, which are a collection of
** lines. Drawing thoses lines makes appeir a letter. The gl_vector contains
** letters in this order: a-z0-9!. There is a enumeration that describe completly
** how the gl_vector is made in the enum.h file: t_bunny_letter_tab.
*/
extern const t_bunny_letter	gl_vector_font[LAST_BUNNY_FONT];

#endif	/*			__LAPIN_TEXT_H__	*/
