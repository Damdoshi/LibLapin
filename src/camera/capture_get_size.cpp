//
//
//
//
//

#include		"private/ocv.h"
#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_capture_get_size
 * @doc-kind function
 * @doc-module camera
 * @doc-order 200
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Retrieves the size of a camera capture.
 * @param capture The capture to inspect.
 * @param out The output size in pixels.
 * @see bunny_new_capture, bunny_capture_new_pixelarray
 *
 * @doc-lang fr
 * @brief Récupère la taille d'une capture de caméra.
 * @param capture La capture à inspecter.
 * @param out La taille de sortie en pixels.
 * @see bunny_new_capture, bunny_capture_new_pixelarray
 */

void			bunny_capture_get_size(const t_bunny_capture	*capture,
					       t_bunny_position		*out)
{
  const cv::Mat		*mat = (cv::Mat*)capture;

  out->x = mat->cols;
  out->y = mat->rows;
}

