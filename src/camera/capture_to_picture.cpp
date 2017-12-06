//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

#define			PATTERN			"%p capture, %p picture -> %s"

bool			bunny_capture_to_picture(t_bunny_capture	*cap,
						 t_bunny_picture	*pic)
{
  t_bunny_pixelarray	*pix;

  if ((pix = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height)) == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, "camera", cap, pic, "false");
  if (bunny_capture_to_pixelarray(cap, pix) == false)
    {
      bunny_delete_clipable(&pix->clipable);
      scream_error_if(return (false), bunny_errno, PATTERN, "camera", cap, pic, "false");
    }
  bunny_blit(&pic->buffer, &pix->clipable, NULL);
  bunny_delete_clipable(&pix->clipable);
  scream_log_if(PATTERN, "camera", cap, pic, "true");
  return (true);
}

