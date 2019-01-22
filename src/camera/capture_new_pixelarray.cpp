//
//
//
//
//

#include		<opencv2/opencv.hpp>
#ifndef			BUNNY_CAMERA
# define		BUNNY_CAMERA
#endif
#define                 __LAPIN_PRIVATE_STEAM_H__
#include		"lapin_private.h"

t_bunny_pixelarray	*bunny_capture_new_pixelarray(const t_bunny_capture	*capture)
{
  const cv::Mat		*mat = (cv::Mat*)capture;
  t_bunny_pixelarray	*pix;

  if ((pix = bunny_new_pixelarray(mat->cols, mat->rows)) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %p", "camera", capture, pix);
  memcpy(pix->pixels, mat->data, mat->cols * mat->rows * sizeof(t_bunny_color));
  scream_log_if("%p -> %p", "camera", capture, pix);
  return (pix);
}

