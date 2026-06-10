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
    bunny_sprite_animate(clothe->sprite, *(double*)p);
}

static void		_set_frame(struct bunny_sprite			&spr,
				   t_bunny_animation			&anim,
				   size_t				cfr)
{
  if (anim.browsing == BFB_LEFT_TO_RIGHT ||
      (anim.browsing == BFB_BACK_AND_FORTH && cfr < anim.nbr_frame))
    spr.rect.x =
      anim.position.x +
      (spr.rect.w + anim.intertile.x)
      * cfr
      + anim.intertile.x
      ;
  else if (anim.browsing == BFB_RIGHT_TO_LEFT || anim.browsing == BFB_RANDOM)
    spr.rect.x =
      anim.position.x +
      ((spr.rect.w + anim.intertile.x) *
       (anim.nbr_frame - cfr - 1))
      + anim.intertile.x
      ;
  else if (anim.browsing == BFB_BACK_AND_FORTH && spr.current_frame >= anim.nbr_frame)
    spr.rect.x =
      anim.position.x +
      ((spr.rect.w + anim.intertile.x) *
       (2 * anim.nbr_frame - cfr - 1))
      + anim.intertile.x
      ;

  spr.rect.y = anim.position.y + anim.intertile.y;
}


/**
 * @doc
 * @doc-symbol bunny_sprite_animate
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 180
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Advances a sprite animation by an elapsed duration.
 * @param sprite Sprite to update.
 * @see bunny_sprite_animate_elapsed, bunny_sprite_animate_now
 *
 * @doc-lang fr
 * @brief Fait avancer l'animation d'un sprite selon une durée écoulée.
 * @param sprite Sprite à mettre à jour.
 * @see bunny_sprite_animate_elapsed, bunny_sprite_animate_now
 */
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

  if (sprite.animation == NULL || sprite.current_animation == -1 || sprite.stop_repeat)
    {
      sprite.current_time = 0;
      return ;
    }

  sprite.current_time += elapsed;
  anim = &sprite.animation[sprite.current_animation];
  while (sprite.current_time > anim->delay)
    {
      sprite.current_time -= anim->delay;
      if (anim->frame_repetition == NULL)
	frep = 1;
      else
	frep = anim->frame_repetition[sprite.current_frame];

      if (++sprite.current_frame_repeat >= frep)
	{
	  sprite.current_frame_repeat = 0;
	  sprite.random = rand() % anim->nbr_frame;
	  if (++sprite.current_frame >=
	      anim->nbr_frame * (anim->browsing == BFB_BACK_AND_FORTH ? 2 : 1)
	      )
	    {
	      sprite.current_frame = 0;
	      if (sprite.stop_repeat
		  || anim->animation_repeat == -1
		  || ++sprite.current_repeat >= anim->animation_repeat)
		{
		  sprite.current_repeat = 0;
		  sprite.current_animation = (int32_t)anim->next_animation;
		  if (sprite.stop_repeat == false)
		    {
		      if (sprite.current_animation != -1)
			{
			  anim = &sprite.animation[sprite.current_animation];
			  sprite.current_animation_hash = anim->hash;
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
  if (anim->browsing == BFB_RANDOM)
    _set_frame(sprite, *anim, sprite.random);
  else
    _set_frame(sprite, *anim, sprite.current_frame);
  return ;
}

// ca marche pas ca en fait...

/**
 * @doc
 * @doc-symbol bunny_sprite_animate_date
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 182
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Advances a sprite animation from an absolute current date.
 * @param sprite Sprite to update.
 * @see bunny_sprite_animate
 *
 * @doc-lang fr
 * @brief Fait avancer l'animation d'un sprite depuis une date courante absolue.
 * @param sprite Sprite à mettre à jour.
 * @see bunny_sprite_animate
 */
void			bunny_sprite_animate_date(t_bunny_sprite	*spr,
						  double		now)
{
  struct bunny_sprite	&sprite = *(struct bunny_sprite*)spr;

  bunny_sprite_animate(spr, now - sprite.current_time);
}


/**
 * @doc
 * @doc-symbol bunny_sprite_animate_elapsed
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 184
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Advances a sprite animation by an elapsed duration.
 * @param spr Sprite to update.
 * @see bunny_sprite_animate
 *
 * @doc-lang fr
 * @brief Fait avancer l'animation d'un sprite selon une durée écoulée.
 * @param spr Sprite à mettre à jour.
 * @see bunny_sprite_animate
 */
void			bunny_sprite_animate_elapsed(t_bunny_sprite	*spr,
						     double		elapsed)
{
  bunny_sprite_animate(spr, elapsed);
}


/**
 * @doc
 * @doc-symbol bunny_sprite_animate_now
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 186
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Advances a sprite animation using the current LibLapin delay.
 * @param sprite Sprite to update.
 * @see bunny_sprite_animate
 *
 * @doc-lang fr
 * @brief Fait avancer l'animation d'un sprite avec le délai courant de la LibLapin.
 * @param sprite Sprite à mettre à jour.
 * @see bunny_sprite_animate
 */
void			bunny_sprite_animate_now(t_bunny_sprite		*spr)
{
  bunny_sprite_animate(spr, bunny_get_delay());
}

