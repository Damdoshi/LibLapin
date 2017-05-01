//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

bool			bunny_capture_to_picture(t_bunny_camera		*camera,
						 t_bunny_picture	*pic)
{
  t_bunny_pixelarray	*pix;

  if ((pix = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height)) == NULL)
    return (false);
  if (bunny_capture_to_pixelarray(camera, pix) == false)
    {
      bunny_delete_clipable(&pix->clipable);
      return (false);
    }
  bunny_blit(&pic->buffer, &pix->clipable, NULL);
  bunny_delete_clipable(&pix->clipable);
  return (true);
}

