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

/**
 * @doc
 * @doc-symbol sprite
 * @doc-kind module
 * @doc-module sprite
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Handles animated clipable sprite sheets.
 * @description Sprites are clipable pictures with named animations, frame timing, collision shapes and optional dressed-sprite helpers for layered equipment/clothes.
 * @header lapin/sprite.h
 *
 * @doc-lang fr
 * @brief Gère des sprites animés basés sur des spritesheets clipables.
 * @description Les sprites sont des images clipables avec animations nommées, timings de frames, formes de collision et aides optionnelles de sprites habillés pour des couches d'équipement/vêtements.
 * @header lapin/sprite.h
 */

/**
 * @doc
 * @doc-symbol t_bunny_frame_browsing
 * @doc-kind enum
 * @doc-module sprite
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Describes how animation frames are traversed.
 * @value BFB_LEFT_TO_RIGHT Frames are played from first to last.
 * @value BFB_RIGHT_TO_LEFT Frames are played from last to first.
 * @value BFB_BACK_AND_FORTH Frames go forward then backward.
 * @value BFB_RANDOM Frames are selected randomly.
 * @see t_bunny_animation
 *
 * @doc-lang fr
 * @brief Décrit comment les frames d'une animation sont parcourues.
 * @value BFB_LEFT_TO_RIGHT Les frames sont jouées de la première à la dernière.
 * @value BFB_RIGHT_TO_LEFT Les frames sont jouées de la dernière à la première.
 * @value BFB_BACK_AND_FORTH Les frames avancent puis reculent.
 * @value BFB_RANDOM Les frames sont choisies aléatoirement.
 * @see t_bunny_animation
 */
typedef enum		e_bunny_frame_browsing
  {
    BFB_LEFT_TO_RIGHT,
    BFB_RIGHT_TO_LEFT,
    BFB_BACK_AND_FORTH,
    BFB_RANDOM
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

/**
 * @doc
 * @doc-symbol t_bunny_animation
 * @doc-kind struct
 * @doc-module sprite
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Describes one animation inside a sprite sheet.
 * @field hash Hashed animation name.
 * @field delay Duration of one frame step in seconds.
 * @field nbr_frame Number of frames in the animation.
 * @field position Position of the first frame in the sprite sheet.
 * @field intertile Spacing between frames in the sprite sheet.
 * @field frame_repetition Optional repetition count per frame.
 * @field collision_shapes Optional collision shape index per frame.
 * @field browsing Frame traversal mode.
 * @field animation_repeat Number of whole animation repetitions, or -1 for infinite looping.
 * @field next_animation Next animation index to play, or -1 when none is chained.
 * @see t_bunny_frame_browsing, t_bunny_sprite
 *
 * @doc-lang fr
 * @brief Décrit une animation dans une spritesheet.
 * @field hash Nom d'animation haché.
 * @field delay Durée d'une étape de frame en secondes.
 * @field nbr_frame Nombre de frames de l'animation.
 * @field position Position de la première frame dans la spritesheet.
 * @field intertile Espacement entre frames dans la spritesheet.
 * @field frame_repetition Nombre de répétitions optionnel par frame.
 * @field collision_shapes Index optionnel de forme de collision par frame.
 * @field browsing Mode de parcours des frames.
 * @field animation_repeat Nombre de répétitions de l'animation entière, ou -1 pour une boucle infinie.
 * @field next_animation Index de la prochaine animation à jouer, ou -1 si aucune n'est chaînée.
 * @see t_bunny_frame_browsing, t_bunny_sprite
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

/**
 * @doc
 * @doc-symbol t_bunny_sprite
 * @doc-kind struct
 * @doc-module sprite
 * @doc-order 140
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents an animated clipable sprite.
 * @description The first field is a t_bunny_clipable, so a sprite can be passed to drawing functions that accept clipables, pictures or buffers. Internal animation state is updated by bunny_sprite_animate.
 * @field clipable Base clipable object used for drawing.
 * @field animation Animation array.
 * @field nbr_animation Number of animations.
 * @field hashname_id Map from animation name hash to animation index.
 * @field collision_shapes Collision shape array.
 * @field nbr_collision Number of collision shapes.
 * @field current_animation_hash Hash of the current animation name.
 * @field current_animation Current animation index.
 * @field current_frame_repeat Number of repetitions already spent on the current frame.
 * @field current_repeat Number of repetitions already spent on the current animation.
 * @field current_frame Current frame index.
 * @field current_time Accumulated animation time.
 * @field stop_repeat Whether the current animation should stop instead of repeating.
 * @field draw_collision_shapes Whether collision shapes should be drawn for debugging.
 * @see bunny_load_sprite, bunny_sprite_animate, bunny_delete_clipable
 *
 * @doc-lang fr
 * @brief Représente un sprite animé clipable.
 * @description Le premier champ est un t_bunny_clipable, donc un sprite peut être passé aux fonctions de dessin qui acceptent des clipables, pictures ou buffers. L'état interne d'animation est mis à jour par bunny_sprite_animate.
 * @field clipable Objet clipable de base utilisé pour le dessin.
 * @field animation Tableau des animations.
 * @field nbr_animation Nombre d'animations.
 * @field hashname_id Map du hash de nom d'animation vers l'index d'animation.
 * @field collision_shapes Tableau de formes de collision.
 * @field nbr_collision Nombre de formes de collision.
 * @field current_animation_hash Hash du nom de l'animation courante.
 * @field current_animation Index de l'animation courante.
 * @field current_frame_repeat Nombre de répétitions déjà passées sur la frame courante.
 * @field current_repeat Nombre de répétitions déjà passées sur l'animation courante.
 * @field current_frame Index de la frame courante.
 * @field current_time Temps d'animation accumulé.
 * @field stop_repeat Indique si l'animation courante doit s'arrêter au lieu de se répéter.
 * @field draw_collision_shapes Indique si les formes de collision doivent être dessinées pour le debug.
 * @see bunny_load_sprite, bunny_sprite_animate, bunny_delete_clipable
 */
typedef struct		s_bunny_sprite
{
  t_bunny_clipable	clipable;
  const size_t		_private[4];
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


/**
 * @doc
 * @doc-symbol bunny_read_sprite
 * @doc-kind macro
 * @doc-module sprite
 * @doc-order 170
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Builds a sprite from an already loaded configuration node.
 * @param cnf Sprite configuration node.
 * @return-success Returns a newly allocated sprite.
 * @return-failure Returns NULL on error.
 * @see bunny_load_sprite, bunny_fill_sprite
 *
 * @doc-lang fr
 * @brief Construit un sprite depuis un nœud de configuration déjà chargé.
 * @param cnf Nœud de configuration du sprite.
 * @return-success Renvoie un sprite nouvellement alloué.
 * @return-failure Renvoie NULL en cas d'erreur.
 * @see bunny_load_sprite, bunny_fill_sprite
 */
# define		bunny_read_sprite(cnf)				\
  _bunny_read_sprite(cnf, NULL)

/**
 * @doc
 * @doc-symbol bunny_fill_sprite
 * @doc-kind macro
 * @doc-module sprite
 * @doc-order 175
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Fills an already allocated sprite from a configuration node.
 * @param spr Sprite to fill.
 * @param cnf Sprite configuration node.
 * @return-success Returns spr on success.
 * @return-failure Returns NULL on error.
 * @see bunny_read_sprite, bunny_load_sprite
 *
 * @doc-lang fr
 * @brief Remplit un sprite déjà alloué depuis un nœud de configuration.
 * @param spr Sprite à remplir.
 * @param cnf Nœud de configuration du sprite.
 * @return-success Renvoie spr en cas de succès.
 * @return-failure Renvoie NULL en cas d'erreur.
 * @see bunny_read_sprite, bunny_load_sprite
 */
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
void			bunny_sprite_animate_elapsed(t_bunny_sprite	*spr,
						     double		elapsed);
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

/**
 * @doc
 * @doc-symbol bunny_sprite_set_animation
 * @doc-kind macro
 * @doc-module sprite
 * @doc-order 220
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Selects a sprite animation by name or hash with C11 generic dispatch.
 * @param spr Sprite to update.
 * @param anim Animation name as char pointer or animation hash as integer.
 * @return-success Returns true if the animation exists and was selected.
 * @return-failure Returns false if the animation does not exist.
 * @see bunny_sprite_set_animation_name, bunny_sprite_set_animation_id
 *
 * @doc-lang fr
 * @brief Sélectionne une animation de sprite par nom ou hash via dispatch générique C11.
 * @param spr Sprite à mettre à jour.
 * @param anim Nom d'animation sous forme de char pointer ou hash d'animation sous forme d'entier.
 * @return-success Renvoie true si l'animation existe et a été sélectionnée.
 * @return-failure Renvoie false si l'animation n'existe pas.
 * @see bunny_sprite_set_animation_name, bunny_sprite_set_animation_id
 */
#  define		bunny_sprite_set_animation(spr, anim)		\
  _Generic((anim),							\
	   const char*: bunny_sprite_set_animation_name,		\
	   char*: bunny_sprite_set_animation_name,			\
	   uint64_t: bunny_sprite_set_animation_id,			\
	   int: bunny_sprite_set_animation_id				\
	   )(spr, anim)

/**
 * @doc
 * @doc-symbol bunny_sprite_shift_animation
 * @doc-kind macro
 * @doc-module sprite
 * @doc-order 230
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Schedules or shifts to another animation by name or hash with C11 generic dispatch.
 * @param spr Sprite to update.
 * @param anim Animation name as char pointer or animation hash as integer.
 * @return-success Returns true if the animation exists and the shift was accepted.
 * @return-failure Returns false if the animation does not exist.
 * @see bunny_sprite_shift_animation_name, bunny_sprite_shift_animation_id
 *
 * @doc-lang fr
 * @brief Programme ou décale vers une autre animation par nom ou hash via dispatch générique C11.
 * @param spr Sprite à mettre à jour.
 * @param anim Nom d'animation sous forme de char pointer ou hash d'animation sous forme d'entier.
 * @return-success Renvoie true si l'animation existe et que le changement est accepté.
 * @return-failure Renvoie false si l'animation n'existe pas.
 * @see bunny_sprite_shift_animation_name, bunny_sprite_shift_animation_id
 */
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

/**
 * @doc
 * @doc-symbol bunny_sprite_animation_name
 * @doc-kind macro
 * @doc-module sprite
 * @doc-order 210
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Converts an animation name to its sprite hash.
 * @param name Animation name string.
 * @return-success Returns the DJB2 hash used by sprite animation lookup.
 * @see bunny_sprite_set_animation_id, bunny_sprite_get_animation
 *
 * @doc-lang fr
 * @brief Convertit un nom d'animation en hash de sprite.
 * @param name Chaîne de nom d'animation.
 * @return-success Renvoie le hash DJB2 utilisé par la recherche d'animation de sprite.
 * @see bunny_sprite_set_animation_id, bunny_sprite_get_animation
 */
# define		bunny_sprite_animation_name(name)		\
  bunny_hash(BH_DJB2, name, strlen(name))

/*
** Simply a named sprite.
*/

/**
 * @doc
 * @doc-symbol t_bunny_clothe
 * @doc-kind struct
 * @doc-module sprite
 * @doc-order 400
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Associates a name with a sprite used as a wearable layer.
 * @field name Clothe name.
 * @field sprite Sprite displayed when this clothe is worn.
 * @see t_bunny_closet, t_bunny_dressed_sprite
 *
 * @doc-lang fr
 * @brief Associe un nom à un sprite utilisé comme couche habillable.
 * @field name Nom du vêtement.
 * @field sprite Sprite affiché lorsque ce vêtement est porté.
 * @see t_bunny_closet, t_bunny_dressed_sprite
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

/**
 * @doc
 * @doc-symbol t_bunny_closet
 * @doc-kind struct
 * @doc-module sprite
 * @doc-order 410
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Groups several clothes that share the same dressed-sprite slot.
 * @field name Closet name.
 * @field clothes Map from clothe-name hash to t_bunny_clothe pointer.
 * @field position Position offset used by clothes in this closet.
 * @field depth Rendering depth of this closet.
 * @see t_bunny_clothe, bunny_load_closet, t_bunny_dressed_sprite
 *
 * @doc-lang fr
 * @brief Regroupe plusieurs vêtements partageant le même emplacement de sprite habillé.
 * @field name Nom du placard.
 * @field clothes Map du hash de nom de vêtement vers un pointeur t_bunny_clothe.
 * @field position Décalage de position utilisé par les vêtements de ce placard.
 * @field depth Profondeur de rendu de ce placard.
 * @see t_bunny_clothe, bunny_load_closet, t_bunny_dressed_sprite
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

/**
 * @doc
 * @doc-symbol bunny_new_wardrobe
 * @doc-kind macro
 * @doc-module sprite
 * @doc-order 450
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates an empty wardrobe map for dressed sprites.
 * @return-success Returns a newly allocated map using string keys.
 * @return-failure Returns NULL on allocation failure.
 * @see bunny_delete_wardrobe, bunny_load_closet
 *
 * @doc-lang fr
 * @brief Crée une map de garde-robe vide pour les sprites habillés.
 * @return-success Renvoie une map nouvellement allouée utilisant des clés chaînes.
 * @return-failure Renvoie NULL en cas d'échec d'allocation.
 * @see bunny_delete_wardrobe, bunny_load_closet
 */
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

/**
 * @doc
 * @doc-symbol t_bunny_dressed_sprite
 * @doc-kind struct
 * @doc-module sprite
 * @doc-order 500
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Represents a sprite composed of a base sprite and wearable layers.
 * @field sprite Base sprite.
 * @field closets Available closets indexed by name hash.
 * @field clothes Currently worn clothes indexed by closet name hash.
 * @see bunny_load_dressed_sprite, bunny_dressed_sprite_wear, bunny_render_dressed_sprite
 *
 * @doc-lang fr
 * @brief Représente un sprite composé d'un sprite de base et de couches habillables.
 * @field sprite Sprite de base.
 * @field closets Placards disponibles indexés par hash de nom.
 * @field clothes Vêtements actuellement portés indexés par hash de nom de placard.
 * @see bunny_load_dressed_sprite, bunny_dressed_sprite_wear, bunny_render_dressed_sprite
 */
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

/**
 * @doc
 * @doc-symbol bunny_read_dressed_sprite
 * @doc-kind macro
 * @doc-module sprite
 * @doc-order 520
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Builds a dressed sprite from a configuration node.
 * @param cnf Dressed-sprite configuration node.
 * @param wardrobe Optional wardrobe where loaded closets can be shared.
 * @return-success Returns a newly allocated dressed sprite.
 * @return-failure Returns NULL on error.
 * @see bunny_load_dressed_sprite
 *
 * @doc-lang fr
 * @brief Construit un sprite habillé depuis un nœud de configuration.
 * @param cnf Nœud de configuration du sprite habillé.
 * @param wardrobe Garde-robe optionnelle où les placards chargés peuvent être partagés.
 * @return-success Renvoie un sprite habillé nouvellement alloué.
 * @return-failure Renvoie NULL en cas d'erreur.
 * @see bunny_load_dressed_sprite
 */
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
