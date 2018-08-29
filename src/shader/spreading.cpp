// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_shader		*gl_spreading_shader = NULL;

static const std::string gl_spreading_frag =
#include		"spreading.frag"
  ;

static const std::string gl_spreading_vertex =
#include		"spreading.vertex"
  ;

static void		_clean_shader(void)
{
  if (gl_spreading_shader)
    bunny_delete_shader(gl_spreading_shader);
}

t_bunny_shader		*bunny_spreading_shader(t_bunny_spreading	*bst)
{
  if (bst == NULL)
    {
      if (gl_spreading_shader)
        bunny_delete_shader(gl_spreading_shader);
      gl_spreading_shader = NULL;
      return (NULL);
    }
  if (gl_spreading_shader == NULL)
    {
      if ((gl_spreading_shader = bunny_new_shader()) == NULL)
	return (NULL);
      if (bunny_read_shader
	  (gl_spreading_shader,
	   gl_spreading_vertex.c_str(),
	   gl_spreading_frag.c_str()) == false)
	return (NULL);
      atexit(_clean_shader);
    }

  if (bst->alpha_buffer == NULL
      || bst->spread_buffer[0] == NULL
      || bst->spread_buffer[1] == NULL)
    {
      if ((bst->alpha_buffer = bunny_new_picture
	   (bst->layout->buffer.width, bst->layout->buffer.height)) == NULL)
	return (NULL);
      if ((bst->spread_buffer[0] = bunny_new_picture
	   (bst->layout->buffer.width, bst->layout->buffer.height)) == NULL)
	{
	  bunny_delete_clipable(bst->alpha_buffer);
	  return (NULL);
	}
      if ((bst->spread_buffer[1] = bunny_new_picture
	   (bst->layout->buffer.width, bst->layout->buffer.height)) == NULL)
	{
	  bunny_delete_clipable(bst->spread_buffer[0]);
	  bunny_delete_clipable(bst->alpha_buffer);
	  return (NULL);
	}
      bst->current_buffer = 1;
      bunny_flip_spreading(bst);
      bunny_clear(&bst->alpha_buffer->buffer, 0);
    }

  if (bst->random == false)
    {
      bunny_shader_set_variable(gl_spreading_shader, "Regular", BVT_1_FLOAT, 1.0);
      bunny_shader_set_variable(gl_spreading_shader, "Random", BVT_1_FLOAT, 0.0);
    }
  else
    {
      bunny_shader_set_variable(gl_spreading_shader, "Regular", BVT_1_FLOAT, 0.0);
      bunny_shader_set_variable(gl_spreading_shader, "Random", BVT_1_FLOAT, rand() / 256.0);
    }

  bunny_shader_set_variable(gl_spreading_shader, "Previous", BVT_CURRENT_TEXTURE_TYPE);
  bunny_shader_set_variable(gl_spreading_shader, "Layout", BVT_PICTURE, bst->layout);

  return (gl_spreading_shader);
}


void			bunny_blit_spreading(t_bunny_buffer		*buffer,
					     const t_bunny_position	*pos,
					     t_bunny_spreading		*spread)
{
  int			i;

  if (bunny_spreading_shader(spread) == NULL)
    return ;
  for (i = 0; i < spread->speed; ++i)
    {
      if (spread->random)
	bunny_shader_set_variable(gl_spreading_shader, "Random", BVT_1_FLOAT, rand() / 256.0);
      bunny_blit_shader(&spread->spread_buffer[spread->current_buffer]->buffer,
			spread->spread_buffer[spread->current_buffer],
			NULL,
			gl_spreading_shader);
    }

  spread->spread_buffer[spread->current_buffer]->color_mask.full = spread->color[spread->current_buffer].full;
  bunny_blit(&spread->alpha_buffer->buffer, spread->spread_buffer[spread->current_buffer], NULL);
  spread->spread_buffer[spread->current_buffer]->color_mask.full = WHITE;

  spread->alpha_buffer->rotation = spread->layout->rotation;
  spread->alpha_buffer->scale = spread->layout->scale;
  spread->alpha_buffer->origin = spread->layout->origin;
  spread->alpha_buffer->color_mask.full = spread->layout->color_mask.full;
  spread->alpha_buffer->clip_x_position = spread->layout->clip_x_position;
  spread->alpha_buffer->clip_y_position = spread->layout->clip_y_position;
  spread->alpha_buffer->clip_width = spread->layout->clip_width;
  spread->alpha_buffer->clip_height = spread->layout->clip_height;
  bunny_blit(buffer, spread->alpha_buffer, pos);
}

void			bunny_fill_spreading(t_bunny_spreading		*spread)
{
  bunny_blit(&spread->spread_buffer[spread->current_buffer]->buffer,
	     spread->layout,
	     NULL);
}

void			bunny_flip_spreading(t_bunny_spreading		*spread)
{
  spread->current_buffer = (spread->current_buffer + 1) % 2;
  bunny_clear(&spread->spread_buffer[spread->current_buffer]->buffer, 0);
  bunny_draw_spreading_source(spread);
}

void			bunny_draw_spreading_source(t_bunny_spreading	*spread)
{
  const static t_bunny_position rad = {2, 2};
  size_t		i;

  for (i = 0; i < spread->source_len; ++i)
    bunny_set_circle
      (&spread->spread_buffer[spread->current_buffer]->buffer,
       spread->sources[i],
       rad,
       WHITE
       );
}

void			bunny_clear_spreading(t_bunny_spreading		*spread)
{
  bunny_clear(&spread->alpha_buffer->buffer, 0);
  bunny_clear(&spread->spread_buffer[0]->buffer, 0);
  bunny_clear(&spread->spread_buffer[1]->buffer, 0);
}

void			bunny_delete_spreading(t_bunny_spreading	*spread)
{
  bunny_delete_clipable(spread->alpha_buffer);
  bunny_delete_clipable(spread->spread_buffer[0]);
  bunny_delete_clipable(spread->spread_buffer[1]);
  spread->alpha_buffer = NULL;
  spread->spread_buffer[0] = NULL;
  spread->spread_buffer[1] = NULL;
  spread->current_buffer = 0;
}

