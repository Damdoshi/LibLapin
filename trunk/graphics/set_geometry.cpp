// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

void				bunny_set_geometry(t_bunny_buffer		*buffer,
						   t_bunny_geometry		geometry,
						   t_bunny_vertex_array		*array,
						   t_bunny_clipable		*picture)
{
  size_t			*typ = (size_t*)buffer;
  sf::VertexArray		vert;
  size_t			i;

  if (*typ != SYSTEM_RAM)
    {
      vert.resize(array->length);
      for (i = 0; i < array->length; ++i)
	{
	  vert[i].position.x = array->vertex[i].pos.x;
	  vert[i].position.y = array->vertex[i].pos.y;
	  if (picture == NULL)
	    {
	      t_color		*col = (t_color*)&array->vertex[i].color;

	      vert[i].color.r = col->argb[RED_CMP];
	      vert[i].color.g = col->argb[GREEN_CMP];
	      vert[i].color.b = col->argb[BLUE_CMP];
	      vert[i].color.a = col->argb[ALPHA_CMP];
	    }
	  else
	    {
	      vert[i].texCoords.x = array->vertex[i].tex.x;
	      vert[i].texCoords.y = array->vertex[i].tex.y;
	    }
	}
    }
  switch (*typ)
    {
    case WINDOW:
      {
	struct bunny_window	*win = (struct bunny_window*)buffer;

	if (picture == NULL)
	  win->window->draw(&vert[0], vert.getVertexCount(), (sf::PrimitiveType)geometry);
	else
	  {
	    struct bunny_picture *tex = (struct bunny_picture*)picture;

	    if (tex->type == SYSTEM_RAM)
	      fprintf(stderr, "Warning: bunny_set_geometry's 4th parameter must be a t_bunny_picture "
		      " if used on a t_bunny_window or a t_bunny_picture.\n");
	    else
	      {
		sf::RenderStates state;

		state.texture = &tex->texture->getTexture();
		win->window->draw(vert, state);
	      }
	  }
	return ;
      }
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)buffer;

	if (picture == NULL)
	  pic->texture->draw(&vert[0], vert.getVertexCount(), (sf::PrimitiveType)geometry);
	else
	  {
	    struct bunny_picture *tex = (struct bunny_picture*)picture;

	    if (tex->type == SYSTEM_RAM)
	      fprintf(stderr, "Warning: bunny_set_geometry's 4th parameter must be a t_bunny_picture "
		      " if used on a t_bunny_window or a t_bunny_picture.\n");
	    else
	      {
		sf::RenderStates state;

		state.texture = &tex->texture->getTexture();
		pic->texture->draw(vert, state);
	      }
	  }
	return ;
      }
    default:
      {
	t_bunny_pixelarray	*pix = (t_bunny_pixelarray*)buffer;

	if (gl_bunny_my_geometry == NULL)
	  fprintf(stderr, "gl_bunny_my_geometry is not set.\n");
	else if (picture == NULL)
	  gl_bunny_my_geometry(pix, geometry, array, NULL);
	else
	  {
	    typ = (size_t*)picture;

	    if (*typ == GRAPHIC_RAM)
	      fprintf(stderr, "Warning: gl_bunny_my_geometry's 4th parameter is a t_bunny_picture.\n");
	    else
	      gl_bunny_my_geometry(pix, geometry, array, (t_bunny_pixelarray*)picture);
	  }
	return ;
      }
    }
}
