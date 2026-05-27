//
//
//
//
//

#include		"private/ocv.h"
#include		"lapin_private.h"

#define			PATTERN		"%p capture, %p pix -> %s"


/**
 * @doc
 * @doc-symbol bunny_capture_to_pixelarray
 * @doc-kind function
 * @doc-module camera
 * @doc-order 280
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Copies a capture into an existing pixelarray.
 * @description The captured image is stretched to fit the destination pixelarray.
 * @param cap The capture to convert.
 * @param pix The destination pixelarray.
 * @return-case success true if the conversion succeeded.
 * @return-case failure false if cap is NULL or the conversion cannot be performed.
 * @error EINVAL The capture is NULL.
 * @log This function writes logs in the "camera" domain.
 * @see bunny_capture_new_pixelarray, bunny_capture_to_picture
 *
 * @doc-lang fr
 * @brief Copie une capture dans un pixelarray existant.
 * @description L'image capturée est étirée pour correspondre au pixelarray de destination.
 * @param cap La capture à convertir.
 * @param pix Le pixelarray de destination.
 * @return-case success true si la conversion réussit.
 * @return-case failure false si cap vaut NULL ou si la conversion ne peut pas être effectuée.
 * @error EINVAL La capture vaut NULL.
 * @log Cette fonction écrit des logs dans le domaine "camera".
 * @see bunny_capture_new_pixelarray, bunny_capture_to_picture
 */

bool			bunny_capture_to_pixelarray(t_bunny_capture		*cap,
						    t_bunny_pixelarray		*pix)
{
  t_bunny_position	pos;
  cv::Mat		*mat = (cv::Mat*)cap;
  int			i, j;

  if (mat == NULL)
    scream_error_if(return (false), EINVAL, PATTERN, "camera", cap, pix, "false");
  for (j = 0; j < pix->clipable.buffer.height; ++j)
    {
      pos.y = ((double)j / pix->clipable.buffer.height) * mat->rows;
      for (i = 0; i < pix->clipable.buffer.width; ++i)
	{
	  t_bunny_color	col;
	  cv::Vec3b	vec;

	  pos.x = ((double)i / pix->clipable.buffer.width) * mat->cols;
	  vec = mat->at<cv::Vec3b>(pos.y,  pos.x);
	  col.argb[ALPHA_CMP] = 255;
	  col.argb[RED_CMP] = vec[2]; // OpenCV pictures are BGR ordered
	  col.argb[GREEN_CMP] = vec[1];
	  col.argb[BLUE_CMP] = vec[0];
	  ((unsigned int*)pix->pixels)[i + j * pix->clipable.buffer.width] = col.full;
	}
    }
  scream_log_if(PATTERN, "camera", cap, pix, "true");
  return (true);
}

