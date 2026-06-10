//
//
//
//
//

#include		"private/ocv.h"
#include		"lapin_private.h"

#define			PATTERN			"%p capture, %p picture -> %s"


/**
 * @doc
 * @doc-symbol bunny_capture_to_picture
 * @doc-kind function
 * @doc-module camera
 * @doc-order 300
 * @doc-since 12
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Copies a capture into an existing picture.
 * @description The captured image is stretched to fit the destination picture. This function uses a temporary pixelarray, so bunny_capture_to_pixelarray is faster when a pixelarray is enough.
 * @param cap The capture to convert.
 * @param pic The destination picture.
 * @return-case success true if the conversion succeeded.
 * @return-case failure false if allocation or conversion fails.
 * @error ENOMEM The temporary pixelarray could not be allocated.
 * @log This function writes logs in the "camera" domain.
 * @see bunny_capture_to_pixelarray, bunny_capture_new_picture
 *
 * @doc-lang fr
 * @brief Copie une capture dans une picture existante.
 * @description L'image capturée est étirée pour correspondre à la picture de destination. Cette fonction utilise un pixelarray temporaire ; bunny_capture_to_pixelarray est donc plus rapide lorsqu'un pixelarray suffit.
 * @param cap La capture à convertir.
 * @param pic La picture de destination.
 * @return-case success true si la conversion réussit.
 * @return-case failure false si l'allocation ou la conversion échoue.
 * @error ENOMEM Le pixelarray temporaire n'a pas pu être alloué.
 * @log Cette fonction écrit des logs dans le domaine "camera".
 * @see bunny_capture_to_pixelarray, bunny_capture_new_picture
 */

bool			bunny_capture_to_picture(t_bunny_capture	*cap,
						 t_bunny_picture	*pic)
{
  t_bunny_pixelarray	*pix;

  if ((pix = bunny_new_pixelarray(pic->buffer.width, pic->buffer.height)) == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, "camera", cap, pic, "false");
  if (bunny_capture_to_pixelarray(cap, pix) == false)
    {
      bunny_delete_clipable(&pix->clipable);
      scream_error_if(return (false), bunny_errno, PATTERN, "camera", cap, pic, "false");
    }
  bunny_blit(&pic->buffer, &pix->clipable, NULL);
  bunny_delete_clipable(&pix->clipable);
  scream_log_if(PATTERN, "camera", cap, pic, "true");
  return (true);
}

