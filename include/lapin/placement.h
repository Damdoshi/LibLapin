/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file placement.h
** This header contains structure that are useful to place elements on screen
** or to store datas about them.
*/

#ifndef				__LAPIN_PLACEMENT_H__
# define			__LAPIN_PLACEMENT_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The t_bunny_position structure represents a position in a 2D space.
** It is useful to access to memory space or tiles, but not to
** register position of elements in a virtual and smooth space.
** Use t_bunny_accurate_position instead.
*/
typedef struct			s_bunny_position
{
  int				x;
  int				y;
}				t_bunny_position;

/*!
** The t_bunny_size structure represents the size of an element in
** a 2D space. It is useful to describe size of elements in memory or
** low resolution element size.
** If you wish more precision, use t_bunny_accurate_size instead.
*/
typedef t_bunny_position	t_bunny_size;

/*!
** The t_bunny_accurate_position represents a position in a 2D
** space. It is useful to describe elements in a virtual and smooth space.
** Using t_bunny_accurate_position allows you to use float or double
** to represent speed or any kind of physical concept that need to
** be precise in order to not being restrictive.
** For example, having a t_bunny_accurate_position element on
** screen with double for x and y speed allows it to move in every
** direction at any speed.
*/
typedef struct			s_bunny_accurate_position
{
  double			x;
  double			y;
}				t_bunny_accurate_position;

/*!
** The t_bunny_accurate_size represents the size of an element in
** a 2D space with precision.
*/
typedef t_bunny_accurate_position t_bunny_accurate_size;

/*!
** The t_bunny_area structure describes an area in a 2D space.
** It may be used to check collision with fixed elements like tiles,
** that are often int-accurate only.
*/
typedef struct			s_bunny_area
{
  int				x;
  int				y;
  int				w;
  int				h;
}				t_bunny_area;

/*!
** The t_bunny_accurate_area structure describes an area in a 2D space.
** It may be used to check collision between different areas.
*/
typedef struct			s_bunny_accurate_area
{
  double			x;
  double			y;
  double			w;
  double			h;
}				t_bunny_accurate_area;


# if				defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L

typedef struct s_bunny_clipable	t_bunny_clipable;
typedef struct s_bunny_pixelarray t_bunny_pixelarray;
typedef struct s_bunny_font	t_bunny_font;

/*!
** Get the effective width on screen of the sent clipable.
** It consists in its clip size multiplied by its scale.
** Can also retrieve the width of window.
** \param clip The clip or window to measure
** \return The width on screen of the clip
*/
#  define			bunny_real_width(clip)		\
  _Generic((clip),						\
	   t_bunny_buffer*:					\
	   clip->width,						\
	   t_bunny_window*:					\
	   clip->buffer.width,					\
	   t_bunny_clipable*:					\
	   ((clip)->clip_width * (clip)->scale.x),		\
	   t_bunny_pixelarray*:					\
	   ((clip)->clipable.clip_width				\
	    * (clip)->clipable.scale.x),			\
	   t_bunny_font*:					\
	   ((clip)->clipable.clip_width				\
	    * (clip)->clipable.scale.x)				\
	   )

/*!
** Get the effective height on screen of the sent clipable.
** It consists in its clip size multiplied by its scale.
** Can also retrieve the height of a window.
** \param clip The clip or window to measure
** \return The height on screen of the clip
*/
#  define			bunny_real_height(clip)		\
  _Generic((clip),						\
	   t_bunny_buffer*:					\
	   clip->height,					\
	   t_bunny_window*:					\
	   clip->buffer.height,					\
	   t_bunny_clipable*:					\
	   ((clip)->clip_height * (clip)->scale.y),		\
	   t_bunny_pixelarray*:					\
	   ((clip)->clipable.clip_height			\
	    * (clip)->clipable.scale.y),			\
	   t_bunny_font*:					\
	   ((clip)->clipable.clip_height			\
	    * (clip)->clipable.scale.y)				\
	   )
# endif
#endif	/*			__LAPIN_PLACEMENT_H__		*/

