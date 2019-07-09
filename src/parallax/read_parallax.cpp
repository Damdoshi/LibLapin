// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_parallax	*bunny_read_parallax_wh(t_bunny_configuration	*cnf,
						unsigned int		width,
						unsigned int		height)
{
  struct bunny_parallax	*px;

  if ((px = new (std::nothrow) struct bunny_parallax) == NULL)
    return (NULL);
  if (!bunny_configuration_getf_bool(cnf, &px->lock_viewpoint, "LockViewpoint"))
    px->lock_viewpoint = true;
  if ((px->nbr_layers = bunny_configuration_casesf(cnf, "Layers")) == 0)
    goto DeleteParallax;
  if (bunny_position_configuration("ViewSize", &px->inside_size, cnf) != BD_OK)
    goto DeleteParallax;
  px->viewpoint.x = px->inside_size.x / 2;
  px->viewpoint.y = px->inside_size.y / 2;
  if (bunny_accurate_position_configuration("ViewPoint", &px->viewpoint, cnf) == BD_ERROR)
    goto DeleteParallax;

  if ((px->sprite = new (std::nothrow) sf::Sprite) == NULL)
    goto DeleteParallax;
  if ((px->texture = new (std::nothrow) sf::RenderTexture) == NULL)
    goto DeleteSprite;
  if (px->texture->create(width, height) == false)
    goto DeleteTexture;
  px->res_id = 0;
  px->texture->clear(sf::Color(0, 0, 0, 0));
  px->texture->display();
  px->tex = &px->texture->getTexture();
  px->sprite->setTexture(*px->tex);
  px->type = PARALLAX;
  px->width = width;
  px->height = height;
  px->rect.x = 0;
  px->rect.y = 0;
  px->rect.w = width;
  px->rect.h = height;
  px->position.x = 0;
  px->position.y = 0;
  px->origin.x = 0;
  px->origin.y = 0;
  px->scale.x = 1.0;
  px->scale.y = 1.0;
  px->rotation = 0;
  px->color_mask.full = WHITE;
  px->smooth = false;
  px->mosaic = false;

  if (bunny_set_clipable_attribute(NULL, (t_bunny_clipable**)&px, &cnf, BCT_PARALLAX) == false)
    goto DeleteTexture;
  if ((px->layers = (t_bunny_parallax_layer*)bunny_calloc(px->nbr_layers, sizeof(*px->layers))) == NULL)
    goto DeleteTexture;
  for (size_t i = 0; i < px->nbr_layers; ++i)
    {
      t_bunny_parallax_layer &layer = px->layers[i];
      const char	*file;

      // Try to load picture from file
      if (bunny_configuration_getf_string(cnf, &file, "Layers[%zu].Picture", i) == false)
	{
	  t_bunny_configuration	*nod;

	  // Try to load picture from the actual node
	  if (bunny_configuration_getf_node(cnf, &nod, "Layers[%zu].Picture", i) == false)
	    goto DeleteLayers;
	  if (!bunny_set_clipable_attribute(NULL, &layer.picture, &nod, BCT_PICTURE))
	    goto DeleteLayers;
	}
      else if ((layer.picture = bunny_load_picture(file)) == NULL)
	goto DeleteLayers;
      if (!bunny_configuration_getf_string(cnf, &file, "Layers[%zu].Mode", i))
	layer.mode = BPM_CENTERED;
      else
	{
	  const char	*modes[] = {"center", "fill", "maximize", "stretch"};
	  size_t	j;

	  for (j = 0; j < NBRCELL(modes) && bunny_strcasecmp(modes[j], file); ++j);
	  if (j == NBRCELL(modes))
	    goto DeleteLayers;
	  layer.mode = (t_bunny_parallax_mode)j;
	}

      layer.local = false;
      layer.loop_x = false;
      layer.loop_y = false;
      layer.speed_lock = false;
      layer.speed_ratio.x = 1.0;
      layer.speed_ratio.y = 1.0;

      bunny_configuration_getf_bool(cnf, &layer.local, "Layers[%zu].Local", i);

      bunny_configuration_getf_bool(cnf, &layer.loop_x, "Layers[%zu].LoopX", i);
      bunny_configuration_getf_bool(cnf, &layer.loop_y, "Layers[%zu].LoopY", i);
      bunny_configuration_getf_bool(cnf, &layer.loop_x, "Layers[%zu].Loop[0]", i);
      bunny_configuration_getf_bool(cnf, &layer.loop_y, "Layers[%zu].Loop[1]", i);

      if (layer.local)
	continue ;

      bunny_configuration_getf_bool(cnf, &layer.speed_lock, "Layers[%zu].SpeedLock", i);

      t_bunny_position	real_size = {
	.x = layer.picture->clip_width * layer.picture->scale.x,
	.y = layer.picture->clip_height * layer.picture->scale.y,
      };

      if (layer.loop_x)
	{
	  bunny_configuration_getf_double
	    (cnf, &layer.speed_ratio.x, "Layers[%zu].Speed[0]", i);
	  bunny_configuration_getf_double
	    (cnf, &layer.speed_ratio.x, "Layers[%zu].SpeedX", i);
	}
      else if (layer.speed_lock == false)
	layer.speed_ratio.x = (double)px->inside_size.x / real_size.x;

      if (layer.loop_y)
	{
	  bunny_configuration_getf_double
	    (cnf, &layer.speed_ratio.y, "Layers[%zu].Speed[1]", i);
	  bunny_configuration_getf_double
	    (cnf, &layer.speed_ratio.y, "Layers[%zu].SpeedY", i);
	}
      else if (layer.speed_lock == false)
	layer.speed_ratio.y = (double)real_size.y / px->inside_size.y;
    }

  return ((t_bunny_parallax*)px);
 DeleteLayers:
  for (size_t i = 0; i < px->nbr_layers; ++i)
    if (px->layers[i].picture)
      bunny_delete_clipable(px->layers[i].picture);
  bunny_free(px->layers);
 DeleteTexture:
  delete px->texture;
 DeleteSprite:
  delete px->sprite;
 DeleteParallax:
  delete px;
  return (NULL);
}

t_bunny_parallax	*bunny_read_parallax(t_bunny_configuration	*cnf)
{
  int			w, h;

  if (bunny_configuration_getf_int(cnf, &w, "CameraSize[0]") == false)
    return (NULL);
  if (bunny_configuration_getf_int(cnf, &h, "CameraSize[1]") == false)
    return (NULL);
  return (bunny_read_parallax_wh(cnf, w, h));
}

