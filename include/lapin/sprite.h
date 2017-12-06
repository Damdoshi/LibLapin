/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_SPRITE_H__
# define		__LAPIN_SPRITE_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif
# include		<string.h>

/*!
**
**
**
**
**
*/
typedef enum		e_bunny_frame_browsing
  {
    BFB_LEFT_TO_RIGHT,
    BFB_RIGHT_TO_LEFT,
    BFB_BACK_AND_FORTH
  }			t_bunny_frame_browsing;

/*!
**
**
**
**
**
*/
typedef struct		s_bunny_animation
{
  uint64_t		hash;
  double		delay;
  uint32_t		nbr_frame;
  t_bunny_position	position;
  t_bunny_vector	*frame_repetition;
  t_bunny_frame_browsing browsing;
  int32_t		animation_repeat;
  int32_t		next_animation;
}			t_bunny_animation;

/*!
**
**
**
*/
typedef struct		s_bunny_sprite
{
  t_bunny_clipable	clipable;
  size_t		_private[3];
  t_bunny_vector	*animation;	// [int -> anim]
  t_bunny_map		*hashname_id;	// [hash("") -> int]
  int32_t		current_animation;
  uint32_t		current_frame_repeat;
  uint32_t		current_repeat;
  uint32_t		current_frame;
  double		current_time;
  bool			stop_repeat;
}			t_bunny_sprite;

/*!
**
**
*/
t_bunny_sprite		*bunny_load_sprite(const char		*file);

/*!
**
**
*/
void			bunny_sprite_animate(t_bunny_sprite	*sprite,
					     double		elapsed);

/*!
**
**
*/
bool			bunny_sprite_is_still(t_bunny_sprite	*sprite);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
**
**
*/
#  define		bunny_sprite_set_animation(spr, anim)	\
  _Generic((anim),						\
	   const char*: bunny_sprite_set_animation_name,	\
	   char*: bunny_sprite_set_animation_name,		\
	   uint64_t: bunny_sprite_set_animation_id,		\
	   int: bunny_sprite_set_animation_id			\
	   )(spr, anim)
# endif

/*!
**
**
*/
bool			bunny_sprite_set_animation_name(t_bunny_sprite *sprite,
							const char *anim);

/*!
**
**
*/
void			bunny_sprite_stop_repeat(t_bunny_sprite *sprite);

/*!
**
**
*/
bool			bunny_sprite_set_animation_id(t_bunny_sprite *sprite,
						      uint64_t	anim);

/*!
**
**
*/
uint64_t		bunny_sprite_get_animation(t_bunny_sprite *sprite);

/*!
**
**
*/
# define		bunny_sprite_animation_name(name)	\
  bunny_hash(BH_DJB2, name, strlen(name))

#endif	/*		__LAPIN_SPRITE_H__			*/
