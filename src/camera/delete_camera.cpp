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

void			bunny_delete_camera(t_bunny_camera		*camera)
{
  cv::VideoCapture	*cam = (cv::VideoCapture*)camera;

  scream_log_if("%p", "camera", camera);
  delete cam;
}

