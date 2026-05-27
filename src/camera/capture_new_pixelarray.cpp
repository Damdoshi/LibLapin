//
//
//
//
//

#include		"private/ocv.h"
#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_capture_new_pixelarray
 * @doc-kind function
 * @doc-module camera
 * @doc-order 240
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Converts a capture into a new pixelarray.
 * @param capture The capture to convert.
 * @return-case success A newly allocated t_bunny_pixelarray containing the captured image.
 * @return-case failure NULL if allocation fails.
 * @error ENOMEM The pixelarray could not be allocated.
 * @log This function writes logs in the "camera" domain.
 * @see bunny_capture_to_pixelarray, bunny_capture_new_picture
 *
 * @doc-lang fr
 * @brief Convertit une capture en nouveau pixelarray.
 * @param capture La capture à convertir.
 * @return-case success Un t_bunny_pixelarray nouvellement alloué contenant l'image capturée.
 * @return-case failure NULL si l'allocation échoue.
 * @error ENOMEM Le pixelarray n'a pas pu être alloué.
 * @log Cette fonction écrit des logs dans le domaine "camera".
 * @see bunny_capture_to_pixelarray, bunny_capture_new_picture
 */

t_bunny_pixelarray	*bunny_capture_new_pixelarray(const t_bunny_capture	*capture)
{
  const cv::Mat		*mat = (cv::Mat*)capture;
  t_bunny_pixelarray	*pix;

  if ((pix = bunny_new_pixelarray(mat->cols, mat->rows)) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %p", "camera", capture, pix);
  memcpy(pix->pixels, mat->data, mat->cols * mat->rows * sizeof(t_bunny_color));
  scream_log_if("%p -> %p", "camera", capture, pix);
  return (pix);
}

