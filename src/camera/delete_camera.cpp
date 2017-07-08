//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

void			bunny_delete_camera(t_bunny_camera		*camera)
{
  cv::VideoCapture	*cam = (cv::VideoCapture*)camera;

  scream_log_if("%p", camera);
  delete cam;
}

