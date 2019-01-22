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

void			bunny_delete_capture(t_bunny_capture	*capture)
{
  cv::Mat		*mat = (cv::Mat*)capture;

  scream_log_if("%p", "camera", capture);
  delete mat;
}

