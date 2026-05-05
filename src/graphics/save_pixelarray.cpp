// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		"lapin_private.h"

#define			PATTERN		"%p picture, %s file -> %s"

/**
 * @doc-symbol bunny_save_pixelarray
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 110
 * @doc-since 5
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Saves a pixelarray into an image file.
 * @description The exact output capabilities, including alpha preservation, depend on the selected file format and backend support.
 * @param buf The pixelarray to save.
 * @param file The destination file path.
 * @return-success true if the file was written.
 * @return-failure false if saving fails.
 * @error errno The backend or filesystem error reported by the save operation.
 * @log Logs are written with the "ressource" and "graphics" labels.
 * @see bunny_load_pixelarray, bunny_read_pixelarray_id
 *
 * @doc-lang fr
 * @brief Sauvegarde un pixelarray dans un fichier image.
 * @description Les capacités exactes de sortie, notamment la conservation de l’alpha, dépendent du format choisi et du support du backend.
 * @param buf Le pixelarray à sauvegarder.
 * @param file Le chemin du fichier de destination.
 * @return-success true si le fichier a été écrit.
 * @return-failure false si la sauvegarde échoue.
 * @error errno L’erreur du backend ou du système de fichiers signalée par l’opération de sauvegarde.
 * @log Les logs sont écrits avec les labels "ressource" et "graphics".
 * @see bunny_load_pixelarray, bunny_read_pixelarray_id
 */
bool			bunny_save_pixelarray(const t_bunny_pixelarray	*pix,
					      const char		*file)
{
  t_bunny_picture	*picture = (t_bunny_picture*)pix;
  struct bunny_pixelarray *pic = (struct bunny_pixelarray*)picture;
  int			i;
  int			j;

  for (j = picture->clip_y_position; j < picture->clip_y_position + picture->clip_height; ++j)
    for (i = picture->clip_x_position; i < picture->clip_x_position + picture->clip_width; ++i)
      {
	unsigned int	c = pic->rawpixels[i + j * pic->width];

	pic->image->setPixel
	  ({i, j},
	   sf::Color
	   ((c >> (RED_CMP * 8)) & 0xFF,
	    (c >> (GREEN_CMP * 8)) & 0xFF,
	    (c >> (BLUE_CMP * 8)) & 0xFF,
	    (c >> (ALPHA_CMP * 8)) & 0xFF
	    )
	   );
      }
#warning How to cipher when writing?
  if (pic->image->saveToFile(file) == false)
    scream_error_if(return (false), errno, PATTERN, "ressource,graphics", pix, file, "false");
  scream_log_if(PATTERN, "ressource,graphics", pix, file, "true");
  return (true);
}

