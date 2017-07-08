// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Lapin Library

#include		"lapin_private.h"

#define			PATTERN		"%p memory, %zu length -> %p"

t_bunny_pixelarray	*bunny_read_pixelarray(const void		*buf,
					       size_t			len)
{
  t_bunny_picture	*pic;
  t_bunny_pixelarray	*pix;
  int			err;
  
  if ((pic = bunny_read_picture(buf, len)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, buf, len, (void*)NULL);
  if ((pix = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height)) == NULL)
    {
      err = bunny_errno;
      bunny_delete_clipable(pic);
      scream_error_if(return (NULL), err, PATTERN, buf, len, (void*)NULL);
    }
  bunny_blit(&pix->clipable.buffer, pic, NULL);
  bunny_delete_clipable(pic);
  scream_log_if(PATTERN, buf, len, pix);
  return (pix);
}

