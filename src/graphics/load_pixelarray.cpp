// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Lapin Library

#include		"lapin_private.h"

t_bunny_pixelarray	*bunny_load_pixelarray(const char		*file)
{
  t_bunny_picture	*pic;
  t_bunny_pixelarray	*pix;
  
  if ((pic = bunny_load_picture(file)) == NULL)
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

