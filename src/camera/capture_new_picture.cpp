//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

t_bunny_picture		*bunny_capture_new_picture(t_bunny_capture	*capture)
{
  t_bunny_picture	*pic;
  t_bunny_pixelarray	*pix;

  if ((pix = bunny_capture_new_pixelarray(capture)) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %p", capture, pix);
  if ((pic = bunny_new_picture(pix->clipable.buffer.width, pix->clipable.buffer.height)) == NULL)
    {
      bunny_delete_clipable(&pix->clipable);
      scream_error_if(return (NULL), bunny_errno, "%p -> %p", capture, pic);
    }
  bunny_blit(&pic->buffer, &pix->clipable, NULL);
  bunny_delete_clipable(&pix->clipable);
  scream_log_if("%p -> %p", capture, pic);
  return (pic);
}

