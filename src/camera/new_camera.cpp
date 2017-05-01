//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

t_bunny_camera		*bunny_new_camera(int	id)
{
  cv::VideoCapture	*cam;

  try
    {
      cam = new cv::VideoCapture(id);
    }
  catch (...)
    {
      return (NULL);
    }
  if (cam->isOpened())
    return ((t_bunny_camera*)cam);
  delete cam;
  return (NULL);
}

