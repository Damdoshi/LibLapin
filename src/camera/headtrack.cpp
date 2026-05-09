//
//
//
//
//

#include		"private/ocv.h"
#include		<fcntl.h>
#include		<unistd.h>
#include		"lapin_private.h"

#ifndef			CV_BGR2GRAY
# define		CV_BGR2GRAY		cv::COLOR_BGR2GRAY
#endif /*		CV_BGR2GRAY */

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

#define			PATTERN		"%p capture, %p head -> %s"


/**
 * @doc
 * @doc-symbol bunny_camera_headtrack
 * @doc-kind function
 * @doc-module camera
 * @doc-order 320
 * @doc-since 12
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Detects a face in a camera capture.
 * @description The detected area is an approximation around the first face found by the embedded OpenCV cascade.
 * @param capture The capture to analyze.
 * @param head The area filled with the detected head rectangle.
 * @return-case success true if a face was found.
 * @return-case failure false if no face was found or if the classifier resource cannot be generated.
 * @error BE_CANT_GENERATE_RESSOURCE The temporary classifier file could not be generated.
 * @log This function writes logs in the "camera" domain.
 * @see bunny_stabilize_headtrack
 *
 * @doc-lang fr
 * @brief Détecte un visage dans une capture de caméra.
 * @description La zone détectée est une approximation autour du premier visage trouvé par la cascade OpenCV embarquée.
 * @param capture La capture à analyser.
 * @param head La zone remplie avec le rectangle de tête détecté.
 * @return-case success true si un visage est trouvé.
 * @return-case failure false si aucun visage n'est trouvé ou si la ressource du classifieur ne peut pas être générée.
 * @error BE_CANT_GENERATE_RESSOURCE Le fichier temporaire du classifieur n'a pas pu être généré.
 * @log Cette fonction écrit des logs dans le domaine "camera".
 * @see bunny_stabilize_headtrack
 */

bool			bunny_camera_headtrack(const t_bunny_capture	*capture,
					       t_bunny_area		*head)
{
  static FileDumper	fdump;
  static cv::CascadeClassifier classifier_face;
  std::vector<cv::Rect>	faces;
  cv::Mat		gray;

  if (fdump.dead())
    scream_error_if
      (return (false),
       BE_CANT_GENERATE_RESSOURCE, PATTERN, "camera",
       capture, head, "false");

  if (fdump.is_loaded() == false)
    {
      classifier_face.load("./bcht.xml");
      fdump.is_loaded(true);
    }

  cv::cvtColor(*(cv::Mat*)capture, gray, CV_BGR2GRAY);
  //classifier_face.detectMultiScale(gray, faces, 1.3, 3);
  classifier_face.detectMultiScale(gray, faces, 3.3, 2);

  if (faces.size() == 0)
    {
      scream_log_if(PATTERN, "camera", capture, head, "false");
      return (false);
    }
  head->x = faces[0].x + faces[0].width * 0.2;
  head->y = faces[0].y + faces[0].width * 0.2;
  head->w = faces[0].width * 1.4;
  head->h = faces[0].height * 1.4;
  scream_log_if(PATTERN, "camera", capture, head, "true");
  return (true);
}

