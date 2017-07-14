// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

#define				PATTERN \
  "%p picture, %d form, %p vertex_array, %p texture"

void				bunny_set_geometry(t_bunny_buffer		*buffer,
						   t_bunny_geometry		geometry,
						   t_bunny_vertex_array		*array,
						   t_bunny_clipable		*picture)
{
  size_t			*typ = (size_t*)buffer;
  sf::VertexArray		vert;
  size_t			i;

  if (*typ != SYSTEM_RAM && *typ != GRAPHIC_TEXT)
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
		sf::RenderStates state = sf::RenderStates::Default;

		vert.setPrimitiveType((sf::PrimitiveType)geometry);
		state.texture = &tex->texture->getTexture();
		win->window->draw(vert, state);
	      }
	  }
	scream_log_if(PATTERN, buffer, geometry, array, picture);
	return ;
      }
    case TTF_TEXT:
    case GRAPHIC_RAM:
    case GRAPHIC_TEXT:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)buffer;

	if (pic->res_id != 0)
	  bunny_make_clipable_unique((t_bunny_clipable*)buffer);
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

		vert.setPrimitiveType((sf::PrimitiveType)geometry);
		state.texture = &tex->texture->getTexture();
		pic->texture->draw(vert, state);
	      }
	  }
	scream_log_if(PATTERN, buffer, geometry, array, picture);
	return ;
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray	*pix = (struct bunny_pixelarray*)buffer;

	if (gl_bunny_my_geometry == NULL)
	  fprintf(stderr, "gl_bunny_my_geometry is not set.\n");
	else if (picture == NULL)
	  {
	    if (pix->res_id != 0)
	      bunny_make_clipable_unique((t_bunny_clipable*)buffer);
	    gl_bunny_my_geometry((t_bunny_pixelarray*)pix, geometry, array, NULL);
	  }
	else
	  {
	    typ = (size_t*)picture;

	    if (*typ == GRAPHIC_RAM)
	      fprintf(stderr, "Warning: gl_bunny_my_geometry's 4th parameter is a t_bunny_picture.\n");
	    else
	      {
		if (pix->res_id != 0)
		  bunny_make_clipable_unique((t_bunny_clipable*)buffer);
		gl_bunny_my_geometry((t_bunny_pixelarray*)pix, geometry, array, (t_bunny_pixelarray*)picture);
	      }
	  }
	scream_log_if(PATTERN, buffer, geometry, array, picture);
	return ;
      }
    default:
      scream_error_if(return, EINVAL, PATTERN, buffer, geometry, array, picture);
    }
}
