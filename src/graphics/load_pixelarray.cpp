// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Lapin Library

#include		"lapin_private.h"

#define			PATTERN		"%s file -> %p"

t_bunny_pixelarray	*bunny_load_pixelarray(const char		*file)
{
  t_bunny_picture	*pic;
  t_bunny_pixelarray	*pix;
  int			err;
  
  if ((pic = bunny_load_picture(file)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, file, pic);
  if ((pix = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height)) == NULL)
    {
      err = bunny_errno;
      bunny_delete_clipable(pic);
      scream_error_if(return (NULL), err, PATTERN, file, pix);
    }
  bunny_blit(&pix->clipable.buffer, pic, NULL);
  bunny_delete_clipable(pic);
  scream_log_if(PATTERN, file, pix);
  return (pix);
}

