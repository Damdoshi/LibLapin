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

#define			PATTERN		"%p -> %p"

t_bunny_capture		*bunny_new_capture(t_bunny_camera		*camera)
{
  cv::VideoCapture	*cap = (cv::VideoCapture*)camera;
  cv::Mat		*mat = NULL;

  try
    {
      mat = new cv::Mat;
    }
  catch (...)
    {
      scream_error_if(return (NULL), ENOMEM, PATTERN, "camera", camera, mat);
      return (NULL);
    }
  *cap >> *mat;
  scream_log_if(PATTERN, "camera", camera, mat);
  return ((t_bunny_capture*)mat);
}

