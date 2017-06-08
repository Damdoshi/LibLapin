//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

t_bunny_pixelarray	*bunny_capture_new_pixelarray(const t_bunny_capture	*capture)
{
  const cv::Mat		*mat = (cv::Mat*)capture;
  t_bunny_pixelarray	*pix;

  if ((pix = bunny_new_pixelarray(mat->cols, mat->rows)) == NULL)
    return (NULL);
  memcpy(pix->pixels, mat->data, mat->cols * mat->rows * sizeof(t_bunny_color));
  return (pix);
}

