//
//
//
//
//

#include		"private/ocv.h"
#include		"lapin_private.h"

void			bunny_delete_capture(t_bunny_capture	*capture)
{
  cv::Mat		*mat = (cv::Mat*)capture;

  scream_log_if("%p", "camera", capture);
  delete mat;
}

