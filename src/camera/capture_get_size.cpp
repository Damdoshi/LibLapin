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

void			bunny_capture_get_size(const t_bunny_capture	*capture,
					       t_bunny_position		*out)
{
  const cv::Mat		*mat = (cv::Mat*)capture;

  out->x = mat->cols;
  out->y = mat->rows;
}

