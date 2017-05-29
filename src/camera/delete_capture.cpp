//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

void			bunny_delete_capture(t_bunny_capture	*capture)
{
  cv::Mat		*mat = (cv::Mat*)capture;

  delete mat;
}

