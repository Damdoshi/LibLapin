// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

#define				PATTERN \
  "%p picture, %d form, %p vertex_array, %p texture"

static void			_cpy_vertex_info(t_bunny_clipable		*picture,
						 sf::Vertex			&dest,
						 t_bunny_vertex			&src)
{
  if (picture == NULL)
    {
      t_color		*col = (t_color*)&src.color;
      
      dest.color.r = col->argb[RED_CMP];
      dest.color.g = col->argb[GREEN_CMP];
      dest.color.b = col->argb[BLUE_CMP];
      dest.color.a = col->argb[ALPHA_CMP];
    }
  else
    {
      dest.texCoords.x = src.tex.x;
      dest.texCoords.y = src.tex.y;
    }
}

static void			_manage_vertex_triangles(t_bunny_clipable	*picture,
							 sf::VertexArray	&points,
							 t_bunny_vertex_array	*array,
							 size_t			&points_index,
							 std::vector<size_t>	target)
{
  points[points_index].position.x = array->vertex[target[0]].pos.x;
  points[points_index].position.y = array->vertex[target[0]].pos.y;
  _cpy_vertex_info(picture, points[points_index], array->vertex[target[0]]);
  points_index += 1;
  points[points_index].position.x = array->vertex[target[1]].pos.x;
  points[points_index].position.y = array->vertex[target[1]].pos.y;
  _cpy_vertex_info(picture, points[points_index], array->vertex[target[1]]);
  points_index += 1;
  points[points_index].position.x = array->vertex[target[2]].pos.x;
  points[points_index].position.y = array->vertex[target[2]].pos.y;
  _cpy_vertex_info(picture, points[points_index], array->vertex[target[2]]);
  points_index += 1;
}

static void			_manage_vertex_quads(t_bunny_clipable		*picture,
						     sf::VertexArray		&points,
						     t_bunny_vertex_array	*array,
						     size_t			&points_index,
						     size_t			&array_index)
{
  _manage_vertex_triangles(picture, points, array, points_index, {array_index, array_index + 1, array_index + 3});
  _manage_vertex_triangles(picture, points, array, points_index, {array_index + 1, array_index + 2, array_index + 3});
  array_index += 4;
}
						     

void				bunny_set_geometry(t_bunny_buffer		*buffer,
						   t_bunny_geometry		geometry,
						   t_bunny_vertex_array		*array,
						   t_bunny_clipable		*picture)
{
  size_t			*typ = (size_t*)buffer;
  sf::VertexArray		vert;
 
  if (*typ != SYSTEM_RAM && *typ != GRAPHIC_TEXT)
    {
      if (geometry == BGY_QUADS)
	vert.resize(array->length * 2);
      else
	vert.resize(array->length);
      
      size_t			vert_index;
      size_t			array_index;

      vert_index = 0;
      array_index = 0;
      while (array_index < array->length)
	{
	  if (geometry == BGY_QUADS)
	    _manage_vertex_quads(picture, vert, array, vert_index, array_index);
	  else
	    {
	      vert[vert_index].position.x = array->vertex[array_index].pos.x;
	      vert[vert_index].position.y = array->vertex[array_index].pos.y;
	      _cpy_vertex_info(picture, vert[vert_index], array->vertex[array_index]);
	      vert_index += 1;
	      array_index += 1;
	    }
	}
      if (geometry == BGY_QUADS)
	geometry = BGY_TRIANGLES;
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
	scream_log_if(PATTERN, "graphics", buffer, geometry, array, picture);
	return ;
      }
    case DRESSED_SPRITE:
    case SPRITE:
    case TTF_TEXT:
    case GRAPHIC_RAM:
    case GRAPHIC_TEXT:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)buffer;

	if (pic->res_id != 0)
	  bunny_make_clipable_unique((t_bunny_clipable*)buffer);
	if (picture == NULL)
	  {
	    if (gl_full_blit == false)
	      pic->texture->draw
		(&vert[0], vert.getVertexCount(),
		 (sf::PrimitiveType)geometry, sf::RenderStates(sf::BlendNone));
	    else
	      pic->texture->draw
		(&vert[0], vert.getVertexCount(), (sf::PrimitiveType)geometry);
	  }
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
	scream_log_if(PATTERN, "graphics", buffer, geometry, array, picture);
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
	scream_log_if(PATTERN, "graphics", buffer, geometry, array, picture);
	return ;
      }
    default:
      scream_error_if(return, EINVAL, PATTERN, "graphics", buffer, geometry, array, picture);
    }
}
