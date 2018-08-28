// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<SFML/Graphics.hpp>
#include		"lapin_private.h"

typedef t_bunny_accurate_position t_aposition;
typedef t_bunny_position t_position;

typedef bool		(*t_tile_collide)(int		x,
					  int		y,
					  int		tx,
					  int		ty);

t_my_tile_collide	gl_bunny_my_tile_collide = NULL;

bool			square_collide(int		x,
				       int		y,
				       int		tx,
				       int		ty)
{
  (void)x;
  (void)y;
  (void)tx;
  (void)ty;
  return (true);
}

bool			circle_collide(int		x,
				       int		y,
				       int		tx,
				       int		ty)
{
  double		dx, dy;

  dx = x - tx / 2;
  dy = y - ty / 2;
  return (sqrt(pow(dx, 2) + pow(dy, 2)) < (tx > ty ? tx / 2 : ty / 2));
}

t_tile_collide		tile_collide[] =
  {
    square_collide,
    circle_collide
  };

/*
** Comment faire?
** Utiliser bunny_set_geometry avec le carousel (un point central et des contours
**
** Lancer des rayons moins dense, et utiliser les coordonnées pour le contour
** au lieu d'être exhaustif et d'avoir des trous partout.
**
** La distance entre le point central et l'exterieur donne l'opacité du point.
*/

bool			bunny_tilemap_raytrace(const t_bunny_tilemap	*tmap,
					       int			layer,
					       const t_bunny_normal_light *light,
					       size_t			nbr_light,
					       t_bunny_picture		*_pic,
					       double			light_str)
{
  if (_pic->buffer.width != tmap->clipable.buffer.width ||
      _pic->buffer.height != tmap->clipable.buffer.height ||
      tmap->nbr_layers <= layer)
    return (false);

  static const double	fullcircle = 2 * M_PI;
  static const double	quantum = fullcircle / 90;
  sf::VertexArray	vtab(sf::TriangleFan, 91);
  struct bunny_picture	*pic = (struct bunny_picture*)_pic;
  sf::RenderStates	states;

  // Do not care about color. Only alpha is importand and it must
  // always add transpency, as multiple lights may be drawn
  states.blendMode = sf::BlendMode
    (sf::BlendMode::Zero,
     sf::BlendMode::Zero,
     sf::BlendMode::Add,
     sf::BlendMode::One,
     sf::BlendMode::One,
     sf::BlendMode::Add
     );
  for (size_t l = 0; l < nbr_light; ++l)
    if (light[l].active)
      {
	vtab[0].position.x = (light[l].x - tmap->camera.x) * tmap->zoom.x;
	vtab[0].position.y = (light[l].y - tmap->camera.y) * tmap->zoom.y;
	vtab[0].color = sf::Color::Transparent;

	// This may be threaded
	for (int i = 0; i * quantum < fullcircle; ++i)
	  {
	    t_aposition vec = {
	      cos(i * quantum) * tmap->tile_size.x * 0.2,
	      sin(i * quantum) * tmap->tile_size.y * 0.2
	    };
	    t_aposition pos;
	    double j;

	    for (j = 0; j < light_str * light[l].light_attenuation; ++j)
	      {
		t_position tpos;
		unsigned int tile;

		pos.x = j * vec.x + light[l].x - tmap->camera.x;
		pos.y = j * vec.y + light[l].y - tmap->camera.y;
		tpos.x = pos.x / tmap->tile_size.x;
		tpos.y = pos.y / tmap->tile_size.y;
		tile = tmap->tiles
		  [layer * tmap->map_size.x * tmap->map_size.y
		   + tpos.x + tpos.y * tmap->map_size.x];
		if (tile && tile < sizeof(tile_collide) / sizeof(tile_collide[0]))
		  {
		    if (tile_collide[tile]
			(pos.x - tpos.x * tmap->tile_size.x,
			 pos.y - tpos.y * tmap->tile_size.y,
			 tmap->tile_size.x,
			 tmap->tile_size.y
			 ))
		      break ;
		  }
		else if (gl_bunny_my_tile_collide
			 (tile,
			  pos.x - tpos.x * tmap->tile_size.x,
			  pos.y - tpos.y * tmap->tile_size.y,
			  tmap->tile_size.x,
			  tmap->tile_size.y
			  ))
		  break ;
	      }
	    vtab[i + 1].position.x = pos.x * tmap->zoom.x;
	    vtab[i + 1].position.y = pos.y * tmap->zoom.y;
	    vtab[i + 1].color = sf::Color(0, 0, 0, (j / light_str) * 255);
	  }
	pic->texture->draw(vtab, states);
      }
  return (true);
}
