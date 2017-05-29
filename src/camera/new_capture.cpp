//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

t_bunny_capture		*bunny_new_capture(t_bunny_camera		*camera)
{
  cv::VideoCapture	*cap = (cv::VideoCapture*)camera;
  cv::Mat		*mat;

  try
    {
      mat = new cv::Mat;
    }
  catch (...)
    {
      return (NULL);
    }
  *cap >> *mat;
  return ((t_bunny_capture*)mat);
}

