// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

t_bunny_collide_point
bunny_collision_equation_dot(const t_bunny_equation_collision	*equ,
			     const t_bunny_dot_collision	*dot)
{
  t_bunny_accurate_position dit;
  t_bunny_collide_point ret;

  ret.radian = -1;
  ret.position.x = 0;
  ret.position.y = 0;

  if (bunny_collision_rectangle_dot((t_bunny_collision*)equ, (t_bunny_collision*)dot) == false)
    return (ret);

  // // BRING DOT INTO THE TILE COORDINATE SYSTEM // //

  // PLACE THE ORIGIN ON THE TOP LEFT CORNER
  dit.x = dot->coord.x - equ->coord[0].x;
  dit.y = dot->coord.y - equ->coord[0].y;

  // SWITCH FROM PIXEL TO % OF TILE
  dit.x /= equ->coord[1].x;
  dit.y /= equ->coord[1].y;

  // SWITCH FROM % OF TILE TO % OF AMPLITUDE
  dit.x *= equ->amplitude.x;
  dit.y *= equ->amplitude.y;

  // CHANGE THE ORIGIN OR THE DIRECTION
  if (equ->origin_at_center)
    {
      dit.x -= equ->amplitude.x / 2;
      dit.y -= equ->amplitude.y / 2;
      if (equ->flipx)
	dit.x *= -1;
      if (equ->flipy)
	dit.y *= -1;
    }
  else
    {
      if (equ->flipx)
	dit.x = equ->amplitude.x - dit.x;
      if (equ->flipy)
	dit.y = equ->amplitude.y - dit.y;
    }

  // // RESOLVE THE EQUATION // //
  t_bunny_accurate_position tmp[2];

  tmp[0].y = equ->a * dit.x * dit.x + equ->b * dit.x + equ->c;
  if (dit.y < tmp[0].y)
    return (ret);

  tmp[0].x = dit.x;
  //tmp[0].y = /;
  tmp[1].x = (dit.x += 0.1);
  tmp[1].y = equ->a * dit.x * dit.x + equ->b * dit.x + equ->c;

  // IMPACT POSITION IN EQUATION SCALE
  ret.position.x = tmp[0].x;
  ret.position.y = tmp[0].y;


  // RESTORE THE ORIGIN
  if (equ->origin_at_center)
    {
      if (equ->flipx)
	{
	  tmp[0].x *= -1;
	  tmp[1].x *= -1;
	}
      if (equ->flipy)
	{
	  tmp[0].y *= -1;
	  tmp[1].y *= -1;
	}
      tmp[0].x += equ->amplitude.x / 2;
      tmp[0].y += equ->amplitude.y / 2;
      tmp[1].x += equ->amplitude.x / 2;
      tmp[1].y += equ->amplitude.y / 2;
    }
  else
    {
      if (equ->flipx)
	{
	  tmp[0].x = equ->amplitude.x - tmp[0].x;
	  tmp[1].x = equ->amplitude.x - tmp[1].x;
	}
      if (equ->flipy)
	{
	  tmp[0].y = equ->amplitude.y - tmp[0].y;
	  tmp[1].y = equ->amplitude.y - tmp[1].y;
	}
    }

  // GET THE ANGLE AFTER ALL TRANSFORMATION
  ret.radian = atan2(tmp[1].y - tmp[0].y, tmp[1].x - tmp[0].x) + 2.5 * M_PI;
  if ((equ->flipx && equ->flipy) || (!equ->flipx && !equ->flipy))
    ret.radian += M_PI;

  // SWITCH FROM % OF ORIGIN TO PIXELS
  ret.position.x = tmp[0].x * (equ->coord[1].x / equ->amplitude.x) + equ->coord[0].x;
  ret.position.y = tmp[0].y * (equ->coord[1].y / equ->amplitude.y) + equ->coord[0].y;
  return (ret);
}

