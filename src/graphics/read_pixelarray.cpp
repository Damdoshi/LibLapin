// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Lapin Library

#include		"lapin_private.h"

t_bunny_pixelarray	*bunny_read_pixelarray(const void		*buf,
					       size_t			len)
{
  t_bunny_picture	*pic;
  t_bunny_pixelarray	*pix;
  
  if ((pic = bunny_read_picture(buf, len)) == NULL)
    return (NULL);
  if ((pix = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height)) == NULL)
    {
      bunny_delete_clipable(pic);
      return (NULL);
    }
  bunny_blit(&pix->clipable.buffer, pic, NULL);
  bunny_delete_clipable(pic);
  return (pix);
}

