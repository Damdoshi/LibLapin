/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file sprite.h
** A sprite is an animated picture.
** This module handle sprite description
** configuration file and bring functions
** to manipulates sprites and display them.
*/

#ifndef			__LAPIN_SPRITE_H__
# define		__LAPIN_SPRITE_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif
# include		<string.h>

/*!
** This enumeration describe the way the animation
** in sprite are browsed.
** It can be from left to right, and then loop.
** It can be from right to left, and then loop.
** It can be from left to right to left, and then loop.
*/
typedef enum		e_bunny_frame_browsing
  {
    BFB_LEFT_TO_RIGHT,
    BFB_RIGHT_TO_LEFT,
    BFB_BACK_AND_FORTH
  }			t_bunny_frame_browsing;

/*!
** The t_bunny_animation structure describe an animation.
** An animation must be several clips followed one before
** another.
** Each line is a single animation, the first frame position
** on sprite sheet is described in position.
** The frame itself repetition is present, so each frame
** does not have to stand the same amount of time.
** The delay is a value in second that indicates how
** many second the frame stand for a single display.
** Animation repeat indicates how many time the animation
** must be repeated entirely before being considered terminated.
** For animation repeat, -1 indicates infinite repetition.
** The next_animation describe which animation must
** be followed after the current one. -1 indicates
** it is not followed by another animation.
*/
typedef struct		s_bunny_animation
{
  uint64_t		hash;
  double		delay;
  uint32_t		nbr_frame;
  t_bunny_position	position;
  t_bunny_size		intertile;
  int			*frame_repetition; // nbr_frame long
  int			*collision_shapes; // nbr_frame long
  t_bunny_frame_browsing browsing;
  int32_t		animation_repeat;
  int32_t		next_animation;
}			t_bunny_animation;

/*!
** The t_bunny_sprite structure is a children of t_bunny_clipable
** so it can be used by any function that handle a t_bunny_clipable.
** It contains an animation array and informations about which
** frame is currently being used to display.
*/
# ifdef			__MINGW32__
#  pragma		pack(4)
# endif
typedef struct		s_bunny_sprite
{
  t_bunny_clipable	clipable;
  const size_t		_private[3];
  t_bunny_animation	*animation;	// [int -> anim]
  size_t		nbr_animation;
  t_bunny_map		*hashname_id;	// [hash("") -> int]
  t_bunny_collision_shapes *collision_shapes;
  uint32_t		nbr_collision;
  uint64_t		current_animation_hash;
  int32_t		current_animation;
  uint32_t		current_frame_repeat;
  uint32_t		current_repeat;
  uint32_t		current_frame;
  double		current_time;
  bool			stop_repeat;
  bool			draw_collision_shapes;
}			t_bunny_sprite;
# pragma		pack()

/*!
** bunny_load_sprite takes a configuration file as parameter.
** The content of the configuration file is described in formats/sprite.
** It returns a t_bunny_sprite on success, NULL on error.
** \param file A configuration file of sprite format.
** \return A valid t_bunny_sprite or NULL on error.
*/
t_bunny_sprite		*bunny_load_sprite(const char			*file);
t_bunny_sprite		*_bunny_read_sprite(t_bunny_configuration	*cnf,
					    const char			*file);

t_bunny_sprite		*_bunny_fill_sprite(t_bunny_sprite		*spr,
					    t_bunny_configuration	*cnf,
					    const char			*file);

# define		bunny_read_sprite(cnf)				\
  _bunny_read_sprite(cnf, NULL)
# define		bunny_fill_sprite(spr, cnf)			\
  _bunny_fill_sprite(spr, cnf, NULL)

t_bunny_sprite		*bunny_duplicate_sprite(t_bunny_sprite		*duplicate);

/*!
** The bunny_sprite_animate function animates the sent sprite, taking
** the elapsed time (in seconds) into consideration.
** The sent sprite is modified accordingly to this elapsed time, so
** the next time you display it, it may be different.
** \param sprite The sprite to animate
** \param elapsed The elapsed time in seconds.
*/
void			bunny_sprite_animate(t_bunny_sprite		*sprite,
					     double			elapsed);
void			bunny_sprite_animate_date(t_bunny_sprite	*sprite,
						  double		current_date);
void			bunny_sprite_animate_now(t_bunny_sprite		*sprite);

/*!
** This function returns true if the animation is terminated.
** \param sprite The sprite to check.
** \return True if the animation is terminated.
*/
bool			bunny_sprite_is_still(t_bunny_sprite		*sprite);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Set the current sprite animation to the sent sprite.
** The animation can be sent as string (the animation name) or as
** id. The id is the named hashed into a 64 bits long integer.
** The hash value can be obtained throught the bunny_sprite_animation_name
** function.
** \param The sprite to set the animation to.
** \param anim The animation to set to the sprite.
** \return True if the animation was set. False if the animation does not exists.
*/
#  define		bunny_sprite_set_animation(spr, anim)		\
  _Generic((anim),							\
	   const char*: bunny_sprite_set_animation_name,		\
	   char*: bunny_sprite_set_animation_name,			\
	   uint64_t: bunny_sprite_set_animation_id,			\
	   int: bunny_sprite_set_animation_id				\
	   )(spr, anim)
#  define		bunny_sprite_shift_animation(spr, anim)		\
  _Generic((anim),							\
	   const char*: bunny_sprite_shift_animation_name,		\
	   char*: bunny_sprite_shift_animation_name,			\
	   uint64_t: bunny_sprite_shift_animation_id,			\
	   int: bunny_sprite_shift_animation_id				\
	   )(spr, anim)
# endif

/*!
** Set the current sprite animation to the sent sprite.
** The animation name under its string format is used.
** You may see the sprite configuration format to see which node it must
** match.
** \param sprite The sprite to set the animation to.
** \param anim The animation to set to the sprite.
** \return True if the animation was set. False if the animation does not exists.
*/
bool			bunny_sprite_set_animation_name(t_bunny_sprite	*sprite,
							const char	*anim);

bool			bunny_sprite_shift_animation_name(t_bunny_sprite *sprite,
							  const char	*anim);

/*!
** Indicates that the animation should not loop anymore. The repeatition
** concerned by this stop is the whole animation repeat.
** This function serves one purpose: being certain that the animation is
** at its final step before starting another one. Because seing for exemple
** a jump animation being terminated and then started again before finally
** seing the landing animation could be very ugly and amateurish.
** \param sprite The sprite with the animation to stop.
*/
void			bunny_sprite_stop_repeat(t_bunny_sprite		*sprite);

/*!
** Set the current sprite animation to the sent sprite.
** The animation name under its hash format is used.
** It can be generated with the name under string format sent to
** bunny_sprite_animation_name.
** \param sprite The sprite to set the animation to.
** \param anim The animation to set to the sprite.
** \return True if the animation was set. False if the animation does not exists.
*/
bool			bunny_sprite_set_animation_id(t_bunny_sprite	*sprite,
						      uint64_t		anim);

bool			bunny_sprite_shift_animation_id(t_bunny_sprite	*sprite,
							uint64_t	anim);

/*!
** Return the current animation name under its hash format.
** \param sprite The sprite to inspect
** \return The name under its hash format.
*/
uint64_t		bunny_sprite_get_animation(const t_bunny_sprite *sprite);
const t_bunny_collision_shapes *bunny_sprite_get_collision(const t_bunny_sprite *sprite);

int			bunny_sprite_collide(const t_bunny_sprite	*a,
					     const t_bunny_sprite	*b,
					     t_bunny_string_couple	*couple,
					     size_t			len);

/*!
** Return the hash format of the sent name.
** \param name The name under string format.
** \return The name under hash format.
*/
# define		bunny_sprite_animation_name(name)		\
  bunny_hash(BH_DJB2, name, strlen(name))

/*
** Simply a named sprite.
*/
typedef struct		s_bunny_clothe
{
  const char		*name;
  t_bunny_sprite	*sprite;
}			t_bunny_clothe;

/*
** A closet is a collection of clothes associated with a name.
** A closet contains clothes that share a position and a depth
** on a dressed sprite. This position can visually change
** by changing clothe origin.
**
** Some easy to understand name for closet: panties, stockings, bra, top, etc.
*/
typedef struct		s_bunny_closet
{
  const char		*name;
  t_bunny_map		*clothes; // [clothe name hash djb2 -> t_bunny_clothe*]
  t_bunny_position	position;
  int			depth;
}			t_bunny_closet;

/// If wardrobe is not NULL, the closet is added to wardrobe. Return the new closet.
t_bunny_closet		*bunny_load_closet(const char			*file,
					   t_bunny_map			*wardrobe);
/// If wardrobe is not NULL, the closet is added to wardrobe. Return the new closet.
t_bunny_closet		*bunny_read_closet(t_bunny_configuration	*cnf,
					   t_bunny_map			*wardrobe);
void			bunny_delete_closet(t_bunny_closet		*closet);
# define		bunny_new_wardrobe()				\
  bunny_new_map((t_bunny_map_cmp)strcmp,				\
		(t_bunny_map_dup)bunny_strdup,				\
		(t_bunny_map_del)bunny_free,				\
		NULL)
void			bunny_delete_wardrobe(t_bunny_map		*wardrobe);

/*
**
**
**
*/
# ifdef			__MINGW32__
#  pragma		pack(4)
# endif
typedef struct		s_bunny_dressed_sprite
{
  t_bunny_sprite	sprite;
  char			_private[sizeof(t_bunny_collision)];
  t_bunny_map		*closets; // [closet name hash djb2 -> t_bunny_closet*]
  t_bunny_map		*clothes; // [closet name hash djb2 -> t_bunny_clothe*]
}			t_bunny_dressed_sprite;
# pragma		pack()

t_bunny_dressed_sprite	*bunny_load_dressed_sprite(const char		*file,
						   t_bunny_map		*wardrobe);
t_bunny_dressed_sprite	*_bunny_read_dressed_sprite(t_bunny_configuration *cnf,
						    t_bunny_map		*wardrobe,
						    const char		*file);
# define		bunny_read_dressed_sprite(cnf, wardrobe)	\
  _bunny_read_dressed_sprite(cnf, wardrobe, NULL)

/// Produce a sprite sheet with all clothes on (so it is faster to blit)
t_bunny_sprite		*bunny_render_dressed_sprite(t_bunny_dressed_sprite *sprite);

bool			bunny_dressed_sprite_wear(t_bunny_dressed_sprite *sprite,
						  const char		*closet,
						  const char		*clothe);

bool			bunny_fix_single_picture_clothe(t_bunny_dressed_sprite *sprite,
							t_bunny_closet	*closet);

#endif	/*		__LAPIN_SPRITE_H__			*/
