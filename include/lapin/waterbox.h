// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bunny Library

#ifndef			__BUNNY_WATERBOX_H__
# define		__BUNNY_WATERBOX_H__
# if		!defined(__LAPIN_H__)
#  error	You cannot include this file directly.
# endif

typedef enum		e_bunny_waterbox_view
  {
    BWS_HORIZONTAL,	// On regarde du coté
    BWS_VERTICAL	// On regarde du dessus ou du dessous
  }			t_bunny_waterbox_view;

typedef enum		e_bunny_waterbox_point
  {
    BWP_NONE,		// 000
    BWP_DRAIN,		// 001
    BWP_WALL,		// 010
    BWP_WATER,		// 011
    BWP_SOURCE,		// 1XX - XX + 1 water created by action
  }			t_bunny_waterbox_point;

typedef struct		s_bunny_waterbox
{
  t_bunny_color		color;
  t_bunny_size		size;
  int			depth;
  t_bunny_bitfield	*boxes[2];	// Double buffering mechanism
  int			current_box;
}			t_bunny_waterbox;

t_bunny_waterbox	*bunny_new_waterbox(int			w,
					    int			h,
					    int			d);
t_bunny_waterbox	*bunny_read_waterbox(t_bunny_configuration *cnf);
t_bunny_waterbox	*bunny_load_waterbox(const char		*cnf);

void			bunny_delete_waterbox(t_bunny_waterbox	*wb);

// Depth to -1 mean "all the way throught"
// Pixelarray and waterbox are supposed to have the same 2D size.
void			bunny_waterbox_blit(t_bunny_buffer	*px,
					    t_bunny_waterbox	*wb,
					    t_bunny_waterbox_view slice,
					    int			depth);

// Animate waterbox
void			bunny_waterbox(t_bunny_waterbox		*wb);

#endif	/*		__WATERBOX_H__	*/

