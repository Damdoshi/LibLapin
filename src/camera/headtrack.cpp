//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		"lapin_private.h"

bool			bunny_camera_headtrack(const t_bunny_capture	*capture,
					       t_bunny_area		*head)
{
  static cv::CascadeClassifier classifier_face;
  std::vector<cv::Rect>	faces;
  cv::Mat		gray;

  cv::cvtColor(*(cv::Mat*)capture, gray, CV_BGR2GRAY);
  classifier_face.detectMultiScale(gray, faces, 1.3, 3);
  if (faces.size() == 0)
    return (false);
  head->x = faces[0].x;
  head->y = faces[0].y;
  head->w = faces[0].width;
  head->h = faces[0].height;
  return (true);
}

