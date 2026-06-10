//
//
//
//
//

#include		"private/ocv.h"
#include		"lapin_private.h"

#define			PATTERN		"%p -> %p"


/**
 * @doc
 * @doc-symbol bunny_new_capture
 * @doc-kind function
 * @doc-module camera
 * @doc-order 160
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Creates a capture and fills it with the current camera frame.
 * @param camera The camera used to retrieve the first frame.
 * @return-case success A valid t_bunny_capture handle.
 * @return-case failure NULL if the capture cannot be allocated.
 * @error ENOMEM The capture object could not be allocated.
 * @log This function writes logs in the "camera" domain.
 * @see bunny_delete_capture, bunny_capture
 *
 * @doc-lang fr
 * @brief Crée une capture et la remplit avec l'image courante de la caméra.
 * @param camera La caméra utilisée pour récupérer la première image.
 * @return-case success Un handle t_bunny_capture valide.
 * @return-case failure NULL si la capture ne peut pas être allouée.
 * @error ENOMEM L'objet capture n'a pas pu être alloué.
 * @log Cette fonction écrit des logs dans le domaine "camera".
 * @see bunny_delete_capture, bunny_capture
 */

t_bunny_capture		*bunny_new_capture(t_bunny_camera		*camera)
{
  cv::VideoCapture	*cap = (cv::VideoCapture*)camera;
  cv::Mat		*mat = NULL;

  try
    {
      mat = new cv::Mat;
    }
  catch (...)
    {
      scream_error_if(return (NULL), ENOMEM, PATTERN, "camera", camera, mat);
      return (NULL);
    }
  *cap >> *mat;
  scream_log_if(PATTERN, "camera", camera, mat);
  return ((t_bunny_capture*)mat);
}

