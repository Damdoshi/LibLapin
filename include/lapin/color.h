/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_COLOR_H__
# define			__LAPIN_COLOR_H__
# if				!defined(__LAPIN_ADVANCED_H__) && !defined(__LAPIN_BASIC_H__)
#  error This file must not be included alone.
# endif
# include			<stdint.h>

typedef enum			e_bunny_rgb
  {
    RED_CMP			= 0,
    GREEN_CMP			= 1,
    BLUE_CMP			= 2,
    ALPHA_CMP			= 3
  }				t_bunny_rgb;

typedef union			u_bunny_color
{
  uint32_t			full;
  uint8_t			argb[4];
  int8_t			mod[4];
}				t_bunny_color;

# endif	/*			__LAPIN_COLOR_H__		*/
