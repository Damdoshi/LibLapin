/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file color.h
** The color module contains symbolic constants useful to manage colors
** and use them in a easy way.
*/

#ifndef				__LAPIN_COLOR_H__
# define			__LAPIN_COLOR_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The t_bunny_rgb enumeration contains the index
** inside a color of every color components.
*/
typedef enum			e_bunny_rgb
  {
    RED_CMP			= 0,
    GREEN_CMP			= 1,
    BLUE_CMP			= 2,
    ALPHA_CMP			= 3
  }				t_bunny_rgb;

# define			BLACK			((uint32_t)(255 << (ALPHA_CMP * 8)))

# define			RED			((uint32_t)(BLACK | (255 << RED_CMP * 8)))
# define			GREEN			((uint32_t)(BLACK | (255 << GREEN_CMP * 8)))
# define			BLUE			((uint32_t)(BLACK | (255 << BLUE_CMP * 8)))

# define			PURPLE			((uint32_t)(RED | BLUE))
# define			TEAL			((uint32_t)(GREEN | BLUE))
# define			YELLOW			((uint32_t)(RED | GREEN))

# define			WHITE			((uint32_t)(RED | GREEN | BLUE))

# define			PINK			((uint32_t)0xFF7777FF)
/*!
** My favorite color <3
*/
# define			PINK2			((uint32_t)0xFFB469FF)

/*!
** The TO_ALPHA macro transforms the given parameter into an alpha component for a color.
** For example, TO_ALPHA(42) will return 0x2a000000 (0x2a being 42 in hex)
*/
# define			TO_ALPHA(a)			(((a) & 0xFF) << (ALPHA_CMP * 8))
/*!
** The GET_COLOR macro removes the alpha component of the given color.
** For example, TO_ALPHA(WHITE) will return 0x00FFFFFF (WHITE being 0xFFFFFFFF)
*/
# define			GET_COLOR(c)			((c) & ~TO_ALPHA(255))
/*!
** The ALPHA macro generates set the alpha component of the color given in c to a.
** For example, ALPHA(128, RED) will return 0x800000FF (0x80 being 128 in hex and RED being 0xFF0000FF).
*/
# define			ALPHA(a, c)			(TO_ALPHA(a) | GET_COLOR(c))

/*!
** The t_bunny_color union represents a pixel color.
** This union allow you to manipulate the color in different
** convenient ways.
**
** The first way is throught the "full" attribute:
** The full attribute allow you to copy, erase or
** assign the complete color in one single operation like this:
** - clr.full = BLACK;
** - clr2.full = clr.full;
**
** The second way is throught the argb array.
** The arbg array allow you to access to every color components
** separately. Combined with the t_bunny_rgb, it allows
** you to write clear code about what you are managing.
** - clr.full = clrx.full;
** - clr.argb[RED_CMP] = 0;
**
** The third way is throught the mod array.
** The mod array look likes the argb array but is
** different in its usage. The argb array is useful
** to set or read color components. The mod array
** is useful to modify other colors, as a "color speed"
** or offset.
** The mod array being an array of signed integers allows
** these offets to be negative.
** - back_color.argb[GREEN_CMP] += color_modifier.mod[GREEN_CMP]
*/
typedef union			u_bunny_color
{
  uint32_t			full;
  uint8_t			argb[4];
  int8_t			mod[4];
}				t_bunny_color;

# endif	/*			__LAPIN_COLOR_H__		*/
