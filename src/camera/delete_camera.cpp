//
//
//
//
//

#include		"private/ocv.h"
#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_delete_camera
 * @doc-kind function
 * @doc-module camera
 * @doc-order 140
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Closes and destroys an opened camera.
 * @param camera The camera handle to close.
 * @log This function writes logs in the "camera" domain.
 * @see bunny_new_camera
 *
 * @doc-lang fr
 * @brief Ferme et détruit une caméra ouverte.
 * @param camera Le handle de caméra à fermer.
 * @log Cette fonction écrit des logs dans le domaine "camera".
 * @see bunny_new_camera
 */

void			bunny_delete_camera(t_bunny_camera		*camera)
{
  cv::VideoCapture	*cam = (cv::VideoCapture*)camera;

  scream_log_if("%p", "camera", camera);
  delete cam;
}

