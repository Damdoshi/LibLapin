//
//
//
//
//

#include		"private/ocv.h"
#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_capture_new_picture
 * @doc-kind function
 * @doc-module camera
 * @doc-order 260
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Converts a capture into a new picture.
 * @description This function uses a temporary pixelarray before creating the picture.
 * @param capture The capture to convert.
 * @return-case success A newly allocated t_bunny_picture containing the captured image.
 * @return-case failure NULL if allocation or conversion fails.
 * @error ENOMEM The intermediate pixelarray or the picture could not be allocated.
 * @log This function writes logs in the "camera" domain.
 * @see bunny_capture_new_pixelarray, bunny_capture_to_picture
 *
 * @doc-lang fr
 * @brief Convertit une capture en nouvelle picture.
 * @description Cette fonction utilise un pixelarray temporaire avant de créer la picture.
 * @param capture La capture à convertir.
 * @return-case success Une t_bunny_picture nouvellement allouée contenant l'image capturée.
 * @return-case failure NULL si l'allocation ou la conversion échoue.
 * @error ENOMEM Le pixelarray intermédiaire ou la picture n'a pas pu être alloué.
 * @log Cette fonction écrit des logs dans le domaine "camera".
 * @see bunny_capture_new_pixelarray, bunny_capture_to_picture
 */

t_bunny_picture		*bunny_capture_new_picture(t_bunny_capture	*capture)
{
  t_bunny_picture	*pic;
  t_bunny_pixelarray	*pix;

  if ((pix = bunny_capture_new_pixelarray(capture)) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %p", "camera", capture, pix);
  if ((pic = bunny_new_picture(pix->clipable.buffer.width, pix->clipable.buffer.height)) == NULL)
    {
      bunny_delete_clipable(&pix->clipable);
      scream_error_if(return (NULL), bunny_errno, "%p -> %p", "camera", capture, pic);
    }
  bunny_blit(&pic->buffer, &pix->clipable, NULL);
  bunny_delete_clipable(&pix->clipable);
  scream_log_if("%p -> %p", "camera", capture, pic);
  return (pic);
}

