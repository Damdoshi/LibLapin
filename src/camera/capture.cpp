//
//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

void			bunny_capture(t_bunny_camera		*camera,
				      t_bunny_capture		*capture)
{
  cv::VideoCapture	*cap = (cv::VideoCapture*)camera;
  cv::Mat		*mat = (cv::Mat*)capture;

  *cap >> *mat;
  scream_log_if("%p camera, %p capture", "camera", camera, capture);
}

