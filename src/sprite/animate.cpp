// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

static void		broadcast_animate(t_bunny_map			*nod,
					  void				*p)
{
  t_bunny_clothe	*clothe = bunny_map_data(nod, t_bunny_clothe*);

  if (clothe)
    bunny_sprite_animate(clothe->sprite, *(float*)p);
}

static void		_set_frame(struct bunny_sprite			&spr,
				   t_bunny_animation			&anim)
{
  if (anim.browsing == BFB_LEFT_TO_RIGHT ||
      (anim.browsing == BFB_BACK_AND_FORTH && spr.current_frame < anim.nbr_frame))
    spr.rect.x =
      anim.position.x +
      (spr.rect.w + anim.intertile.x)
      * spr.current_frame
      + anim.intertile.x
      ;
  else if (anim.browsing == BFB_RIGHT_TO_LEFT)
    spr.rect.x =
      anim.position.x +
      ((spr.rect.w + anim.intertile.x) *
       (anim.nbr_frame - spr.current_frame - 1))
      + anim.intertile.x
      ;
  else if (anim.browsing == BFB_BACK_AND_FORTH && spr.current_frame >= anim.nbr_frame)
    spr.rect.x =
      anim.position.x +
      ((spr.rect.w + anim.intertile.x) *
       (2 * anim.nbr_frame - spr.current_frame - 1))
      + anim.intertile.x
      ;

  spr.rect.y = anim.position.y + anim.intertile.y;
}

void			bunny_sprite_animate(t_bunny_sprite		*spr,
					     double			elapsed)
{
  struct bunny_sprite	&sprite = *(struct bunny_sprite*)spr;
  t_bunny_animation	*anim;
  unsigned int 		frep;

  if (sprite.type == DRESSED_SPRITE)
    {
      struct bunny_dressed_sprite &dressed = (struct bunny_dressed_sprite&)sprite;

      bunny_map_foreach(dressed.clothes, broadcast_animate, &elapsed);
    }

  if (sprite.current_animation == -1 || sprite.stop_repeat)
    {
      sprite.current_time = 0;
      return ;
    }

  sprite.current_time += elapsed;
  anim = &bunny_vector_data
    (sprite.animation, sprite.current_animation, t_bunny_animation);
  while (sprite.current_time > anim->delay)
    {
      sprite.current_time -= anim->delay;
      if (anim->frame_repetition == NULL)
	frep = 1;
      else
	frep = bunny_vector_data(anim->frame_repetition, sprite.current_frame, int);

      if (++sprite.current_frame_repeat >= frep)
	{
	  sprite.current_frame_repeat = 0;
	  if (++sprite.current_frame >=
	      anim->nbr_frame * (anim->browsing == BFB_BACK_AND_FORTH ? 2 : 1)
	      )
	    {
	      sprite.current_frame = 0;
	      if (sprite.stop_repeat || anim->animation_repeat == -1 || ++sprite.current_repeat >= anim->animation_repeat)
		{
		  sprite.current_repeat = 0;
		  if (anim->animation_repeat != -1)
		    sprite.current_animation = anim->next_animation;
		  if (sprite.stop_repeat == false)
		    {
		      if (sprite.current_animation != -1)
			{
			  anim = &bunny_vector_data
			    (sprite.animation, sprite.current_animation, t_bunny_animation);
			}
		      else
			{
			  // Stay still on the last frame
			  sprite.current_frame = anim->nbr_frame - 1;
			  break ;
			}
		    }
		  else
		    break ;
		}
	    }
	}
    }
  _set_frame(sprite, *anim);
  return ;
}
