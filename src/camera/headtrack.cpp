//
//
//
//
//

#include		<opencv2/opencv.hpp>
#include		<fcntl.h>
#include		<unistd.h>
#include		"lapin_private.h"

struct			FileDumper
{
  static const std::string haar;
  bool			loaded;
  bool			deadx;

  bool			is_loaded(bool		lod = false)
  {
    if (lod)
      loaded = true;
    return (loaded);
  }
  bool			dead(void)
  {
    return (deadx);
  }

  FileDumper(void)
    : loaded(false),
      deadx(false)
  {
    int			fd;

    if ((fd = open("./bcht.xml", O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
      {
	deadx = true;
	return ;
      }
    if (write(fd, haar.c_str(), haar.size()) != (ssize_t)haar.size())
      deadx = true;
    close(fd);
  }
  ~FileDumper(void)
  {
    unlink("./bcht.xml");
  }
};

const std::string	FileDumper::haar =
#include		"haarcascade_frontalface_alt.xml"
  ;

bool			bunny_camera_headtrack(const t_bunny_capture	*capture,
					       t_bunny_area		*head)
{
  static FileDumper	fdump;
  static cv::CascadeClassifier classifier_face;
  std::vector<cv::Rect>	faces;
  cv::Mat		gray;

  if (fdump.dead())
    return (false);

  if (fdump.is_loaded() == false)
    {
      classifier_face.load("./bcht.xml");
      fdump.is_loaded(true);
    }

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

