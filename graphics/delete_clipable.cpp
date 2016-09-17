// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

static void			bunny_delete_fake(t_bunny_pixelarray		*pix)
{
  free(pix->pixels);
  free(pix);
}

void				bunny_delete_clipable(t_bunny_clipable	*clip)
{
  size_t			*type = (size_t*)clip;

  switch (*type)
    {
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)clip;

	delete pic->texture;
	delete pic;
	return ;
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray	*pic = (struct bunny_pixelarray*)clip;
	
	if (getenv("TECHNOCORE") != NULL)
	  {
	    bunny_delete_fake((t_bunny_pixelarray*)clip);
	    return ;
	  }
	bunny_free(pic->rawpixels);
	delete pic;
	return ;
      }
    default:
      return ;
    }
}
