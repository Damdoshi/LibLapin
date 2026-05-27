//
//
//
//
//

#include		"private/ocv.h"
#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_delete_capture
 * @doc-kind function
 * @doc-module camera
 * @doc-order 180
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Destroys a camera capture.
 * @param capture The capture to delete.
 * @log This function writes logs in the "camera" domain.
 * @see bunny_new_capture
 *
 * @doc-lang fr
 * @brief Détruit une capture de caméra.
 * @param capture La capture à supprimer.
 * @log Cette fonction écrit des logs dans le domaine "camera".
 * @see bunny_new_capture
 */

void			bunny_delete_capture(t_bunny_capture	*capture)
{
  cv::Mat		*mat = (cv::Mat*)capture;

  scream_log_if("%p", "camera", capture);
  delete mat;
}

