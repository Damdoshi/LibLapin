//
//
//
//
//
//

#include		"private/ocv.h"
#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_capture
 * @doc-kind function
 * @doc-module camera
 * @doc-order 220
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Records a new frame from a camera into an existing capture.
 * @param camera The camera to read from.
 * @param capture The capture object that receives the new frame.
 * @log This function writes logs in the "camera" domain.
 * @see bunny_new_capture, bunny_capture_to_pixelarray
 *
 * @doc-lang fr
 * @brief Enregistre une nouvelle image d'une caméra dans une capture existante.
 * @param camera La caméra à lire.
 * @param capture L'objet capture qui reçoit la nouvelle image.
 * @log Cette fonction écrit des logs dans le domaine "camera".
 * @see bunny_new_capture, bunny_capture_to_pixelarray
 */

void			bunny_capture(t_bunny_camera		*camera,
				      t_bunny_capture		*capture)
{
  cv::VideoCapture	*cap = (cv::VideoCapture*)camera;
  cv::Mat		*mat = (cv::Mat*)capture;

  *cap >> *mat;
  scream_log_if("%p camera, %p capture", "camera", camera, capture);
}

