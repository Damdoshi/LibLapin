//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

#define			PATTERN		"%d -> %p"

t_bunny_camera		*bunny_new_camera(int	id)
{
  cv::VideoCapture	*cam = NULL;

  try
    {
      cam = new cv::VideoCapture(id, cv::CAP_V4L2);
    }
  catch (...)
    {
      scream_error_if(return (NULL), ENOMEM, PATTERN, "camera", id, cam);
    }
  if (cam->isOpened())
    {
      scream_log_if(PATTERN, "camera", id, cam);
      return ((t_bunny_camera*)cam);
    }
  delete cam;
  cam = NULL;
  scream_error_if(return (NULL), ENOMEM, PATTERN, "camera", id, cam);
}

