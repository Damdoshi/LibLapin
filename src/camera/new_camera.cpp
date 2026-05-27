//
//
//
//
//

#include		"private/ocv.h"
#include		"lapin_private.h"

#define			PATTERN		"%d -> %p"


/**
 * @doc
 * @doc-symbol bunny_new_camera
 * @doc-kind function
 * @doc-module camera
 * @doc-order 120
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Opens the camera identified by its system id.
 * @description The id is forwarded to the underlying video backend. On many machines, id 0 is the built-in webcam.
 * @param cam_id The id of the camera to open.
 * @return-case success A valid t_bunny_camera handle.
 * @return-case failure NULL if the camera cannot be allocated or opened.
 * @error ENOMEM The camera object could not be allocated or opened.
 * @log This function writes logs in the "camera" domain.
 * @see bunny_delete_camera, bunny_new_capture
 *
 * @doc-lang fr
 * @brief Ouvre la caméra identifiée par son id système.
 * @description L'id est transmis au backend vidéo sous-jacent. Sur beaucoup de machines, l'id 0 correspond à la webcam intégrée.
 * @param cam_id L'id de la caméra à ouvrir.
 * @return-case success Un handle t_bunny_camera valide.
 * @return-case failure NULL si la caméra ne peut pas être allouée ou ouverte.
 * @error ENOMEM L'objet caméra n'a pas pu être alloué ou ouvert.
 * @log Cette fonction écrit des logs dans le domaine "camera".
 * @see bunny_delete_camera, bunny_new_capture
 */

t_bunny_camera		*bunny_new_camera(int	id)
{
  cv::VideoCapture	*cam = NULL;

  try
    {
      cam = new cv::VideoCapture(id, cv::CAP_V4L2);
    }
  catch (...)
    {
      scream_error_if(return (NULL), ENOMEM, PATTERN, "camera", id, cam);
    }
  if (cam->isOpened())
    {
      //cam->set(CAP_PROP_FOURCC, cv::VIdeoWriter::fourcc('M', 'J', 'P', 'G'));
      //cam->set(cv::CAP_PROP_FPS, 1);
      scream_log_if(PATTERN, "camera", id, cam);
      return ((t_bunny_camera*)cam);
    }
  delete cam;
  cam = NULL;
  scream_error_if(return (NULL), ENOMEM, PATTERN, "camera", id, cam);
}

