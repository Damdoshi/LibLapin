//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

#define			PATTERN		"%p capture, %p pix -> %s"

bool			bunny_capture_to_pixelarray(t_bunny_capture		*cap,
						    t_bunny_pixelarray		*pix)
{
  t_bunny_position	pos;
  cv::Mat		*mat = (cv::Mat*)cap;
  int			i, j;

  if (mat == NULL)
    scream_error_if(return (false), EINVAL, PATTERN, "camera", cap, pix, "false");
  for (j = 0; j < pix->clipable.buffer.height; ++j)
    {
      pos.y = ((double)j / pix->clipable.buffer.height) * mat->rows;
      for (i = 0; i < pix->clipable.buffer.width; ++i)
	{
	  t_bunny_color	col;
	  cv::Vec3b	vec;

	  pos.x = ((double)i / pix->clipable.buffer.width) * mat->cols;
	  vec = mat->at<cv::Vec3b>(pos.y,  pos.x);
	  col.argb[ALPHA_CMP] = 255;
	  col.argb[RED_CMP] = vec[2]; // OpenCV pictures are BGR ordered
	  col.argb[GREEN_CMP] = vec[1];
	  col.argb[BLUE_CMP] = vec[0];
	  ((unsigned int*)pix->pixels)[i + j * pix->clipable.buffer.width] = col.full;
	}
    }
  scream_log_if(PATTERN, "camera", cap, pix, "true");
  return (true);
}

