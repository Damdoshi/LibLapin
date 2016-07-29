// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Lapin Library

#include		"lapin_private.h"

bool			bunny_save_pixelarray(const t_bunny_pixelarray	*pix,
					      const char		*file)
{
  t_bunny_picture	*picture = (t_bunny_picture*)pix;
  struct bunny_pixelarray *pic = (struct bunny_pixelarray*)picture;
  int			i;
  int			j;

  for (j = picture->clip_y_position; j < picture->clip_y_position + picture->clip_height; ++j)
    for (i = picture->clip_x_position; i < picture->clip_x_position + picture->clip_width; ++i)
      {
	unsigned int	c = pic->rawpixels[i + j * pic->width];

	pic->image.setPixel
	  (i, j,
	   sf::Color
	   ((c >> (RED_CMP * 8)) & 0xFF,
	    (c >> (GREEN_CMP * 8)) & 0xFF,
	    (c >> (BLUE_CMP * 8)) & 0xFF,
	    (c >> (ALPHA_CMP * 8)) & 0xFF
	    )
	   );
      }
  return (pic->image.saveToFile(file));
}

