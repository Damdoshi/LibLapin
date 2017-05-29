//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

bool			bunny_capture_to_pixelarray(t_bunny_camera		*camera,
						    t_bunny_pixelarray		*pix)
{
  t_bunny_position	pos;
  cv::Mat		*mat = (cv::Mat*)bunny_new_capture(camera);
  int			i, j;

  if (mat == NULL)
    return (false);
  if (mat->cols == pix->clipable.buffer.width && mat->rows == pix->clipable.buffer.height)
    {
      memcpy(pix->pixels, mat->data, mat->cols * mat->rows * sizeof(t_bunny_color));
      delete mat;
      return (true);
    }
  for (j = 0; j < pix->clipable.buffer.height; ++j)
    {
      pos.y = ((double)j / pix->clipable.buffer.height) * mat->cols;
      for (i = 0; i < pix->clipable.buffer.width; ++i)
	{
	  pos.x = ((double)i / pix->clipable.buffer.width) * mat->cols;
	  ((unsigned int*)pix->pixels)[i + j * pix->clipable.buffer.width] =
	    ((unsigned int*)mat->data)[pos.x + pos.y * mat->cols];
	}
    }
  delete mat;
  return (true);
}

