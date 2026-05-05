// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Lapin Library

#include		"lapin_private.h"

#define			PATTERN		"%p picture, %s file -> %s"

/**
 * @doc-symbol bunny_save_picture
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 155
 * @doc-since 0
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Saves a picture into an image file.
 * @description The exact output capabilities, including alpha preservation, depend on the selected file format and backend support.
 * @param buf The picture to save.
 * @param file The destination file path.
 * @return-success true if the file was written.
 * @return-failure false if saving fails.
 * @error errno The backend or filesystem error reported by the save operation.
 * @log Logs are written with the "ressource" and "graphics" labels.
 * @see bunny_load_picture, bunny_read_picture_id
 *
 * @doc-lang fr
 * @brief Sauvegarde une picture dans un fichier image.
 * @description Les capacités exactes de sortie, notamment la conservation de l’alpha, dépendent du format choisi et du support du backend.
 * @param buf La picture à sauvegarder.
 * @param file Le chemin du fichier de destination.
 * @return-success true si le fichier a été écrit.
 * @return-failure false si la sauvegarde échoue.
 * @error errno L’erreur du backend ou du système de fichiers signalée par l’opération de sauvegarde.
 * @log Les logs sont écrits avec les labels "ressource" et "graphics".
 * @see bunny_load_picture, bunny_read_picture_id
 */
bool			bunny_save_picture(const t_bunny_picture	*picture,
					   const char			*file)
{
  struct bunny_picture	*pic = (struct bunny_picture*)picture;
  sf::Image		img = pic->tex->copyToImage();

  if (img.saveToFile(file) == false)
    scream_error_if(return (false), errno, PATTERN, "ressource,graphics", picture, file, "false");
  scream_log_if(PATTERN, "ressource,graphics", picture, file, "true");
  return (true);
}

