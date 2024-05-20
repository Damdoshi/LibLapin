// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Lapin Library

#include		"lapin_private.h"

#define			PATTERN		"%p picture, %s file -> %s"

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

