/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/


/**
 * @doc
 * @doc-symbol placement
 * @doc-kind module
 * @doc-module placement
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Defines coordinates, sizes, areas and small placement helpers.
 * @description The placement module contains integer and floating-point structures used to describe positions, sizes and rectangles in two or three dimensions. It also exposes helpers for reading such values from configuration nodes and for resizing clipables.
 * @header lapin/placement.h
 *
 * @doc-lang fr
 * @brief Définit les coordonnées, tailles, zones et petits assistants de placement.
 * @description Le module placement contient des structures entières et flottantes utilisées pour décrire des positions, tailles et rectangles en deux ou trois dimensions. Il expose aussi des assistants pour lire ces valeurs depuis des noeuds de configuration et pour redimensionner des clipables.
 * @header lapin/placement.h
 */
/*!
** \file placement.h
** This header contains structure that are useful to place elements on screen
** or to store datas about them.
*/

#ifndef				__LAPIN_PLACEMENT_H__
# define			__LAPIN_PLACEMENT_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The t_bunny_position structure represents a position in a 2D space.
** It is useful to access to memory space or tiles, but not to
** register position of elements in a virtual and smooth space.
** Use t_bunny_accurate_position instead.
*/

/**
 * @doc
 * @doc-symbol t_bunny_position
 * @doc-kind struct
 * @doc-module placement
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents an integer 2D position.
 * @description t_bunny_position is used by LibLapin APIs whenever this kind of placement value is needed.
 * @field x X coordinate.
 * @field y Y coordinate.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 *
 * @doc-lang fr
 * @brief Représente une position 2D entière.
 * @description t_bunny_position est utilisé par les API de la LibLapin lorsqu'une valeur de placement de ce type est nécessaire.
 * @field x Coordonnée X.
 * @field y Coordonnée Y.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 */
typedef struct			s_bunny_position
{
  int				x;
  int				y;
}				t_bunny_position;

/*!
** The t_bunny_size structure represents the size of an element in
** a 2D space. It is useful to describe size of elements in memory or
** low resolution element size.
** If you wish more precision, use t_bunny_accurate_size instead.
*/

/**
 * @doc
 * @doc-symbol t_bunny_size
 * @doc-kind type
 * @doc-module placement
 * @doc-order 120
 * @doc-since 9
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents an integer 2D size.
 * @description t_bunny_size is used by LibLapin APIs whenever this kind of placement value is needed.
 * @description This type is an alias of t_bunny_position.
 * @field x Width.
 * @field y Height.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 *
 * @doc-lang fr
 * @brief Représente une taille 2D entière.
 * @description t_bunny_size est utilisé par les API de la LibLapin lorsqu'une valeur de placement de ce type est nécessaire.
 * @description Ce type est un alias de t_bunny_position.
 * @field x Largeur.
 * @field y Hauteur.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 */
typedef t_bunny_position	t_bunny_size;

/*!
** The t_bunny_accurate_position represents a position in a 2D
** space. It is useful to describe elements in a virtual and smooth space.
** Using t_bunny_accurate_position allows you to use float or double
** to represent speed or any kind of physical concept that need to
** be precise in order to not being restrictive.
** For example, having a t_bunny_accurate_position element on
** screen with double for x and y speed allows it to move in every
** direction at any speed.
*/

/**
 * @doc
 * @doc-symbol t_bunny_accurate_position
 * @doc-kind struct
 * @doc-module placement
 * @doc-order 140
 * @doc-since 6
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents a floating-point 2D position.
 * @description t_bunny_accurate_position is used by LibLapin APIs whenever this kind of placement value is needed.
 * @field x X coordinate.
 * @field y Y coordinate.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 *
 * @doc-lang fr
 * @brief Représente une position 2D flottante.
 * @description t_bunny_accurate_position est utilisé par les API de la LibLapin lorsqu'une valeur de placement de ce type est nécessaire.
 * @field x Coordonnée X.
 * @field y Coordonnée Y.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 */
typedef struct			s_bunny_accurate_position
{
  double			x;
  double			y;
}				t_bunny_accurate_position;

/*!
** The t_bunny_accurate_size represents the size of an element in
** a 2D space with precision.
*/

/**
 * @doc
 * @doc-symbol t_bunny_accurate_size
 * @doc-kind type
 * @doc-module placement
 * @doc-order 160
 * @doc-since 9
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents a floating-point 2D size.
 * @description t_bunny_accurate_size is used by LibLapin APIs whenever this kind of placement value is needed.
 * @description This type is an alias of t_bunny_accurate_position.
 * @field x Width.
 * @field y Height.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 *
 * @doc-lang fr
 * @brief Représente une taille 2D flottante.
 * @description t_bunny_accurate_size est utilisé par les API de la LibLapin lorsqu'une valeur de placement de ce type est nécessaire.
 * @description Ce type est un alias de t_bunny_accurate_position.
 * @field x Largeur.
 * @field y Hauteur.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 */
typedef t_bunny_accurate_position t_bunny_accurate_size;

/*!
** The t_bunny_area structure describes an area in a 2D space.
** It may be used to check collision with fixed elements like tiles,
** that are often int-accurate only.
*/

/**
 * @doc
 * @doc-symbol t_bunny_area
 * @doc-kind struct
 * @doc-module placement
 * @doc-order 180
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents an integer 2D rectangle.
 * @description t_bunny_area is used by LibLapin APIs whenever this kind of placement value is needed.
 * @field x X coordinate of the top-left corner.
 * @field y Y coordinate of the top-left corner.
 * @field w Width.
 * @field h Height.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 *
 * @doc-lang fr
 * @brief Représente un rectangle 2D entier.
 * @description t_bunny_area est utilisé par les API de la LibLapin lorsqu'une valeur de placement de ce type est nécessaire.
 * @field x Coordonnée X.
 * @field y Coordonnée Y.
 * @field w Largeur.
 * @field h Hauteur.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 */
typedef struct			s_bunny_area
{
  int				x;
  int				y;
  int				w;
  int				h;
}				t_bunny_area;

/*!
** The t_bunny_accurate_area structure describes an area in a 2D space.
** It may be used to check collision between different areas.
*/

/**
 * @doc
 * @doc-symbol t_bunny_accurate_area
 * @doc-kind struct
 * @doc-module placement
 * @doc-order 200
 * @doc-since 6
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents a floating-point 2D rectangle.
 * @description t_bunny_accurate_area is used by LibLapin APIs whenever this kind of placement value is needed.
 * @field x X coordinate of the top-left corner.
 * @field y Y coordinate of the top-left corner.
 * @field w Width.
 * @field h Height.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 *
 * @doc-lang fr
 * @brief Représente un rectangle 2D flottant.
 * @description t_bunny_accurate_area est utilisé par les API de la LibLapin lorsqu'une valeur de placement de ce type est nécessaire.
 * @field x Coordonnée X.
 * @field y Coordonnée Y.
 * @field w Largeur.
 * @field h Hauteur.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 */
typedef struct			s_bunny_accurate_area
{
  double			x;
  double			y;
  double			w;
  double			h;
}				t_bunny_accurate_area;


/**
 * @doc
 * @doc-symbol t_bunny_zposition
 * @doc-kind struct
 * @doc-module placement
 * @doc-order 210
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Represents an integer 3D position.
 * @description t_bunny_zposition is used by LibLapin APIs whenever this kind of placement value is needed.
 * @field x X coordinate.
 * @field y Y coordinate.
 * @field z Z coordinate.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 *
 * @doc-lang fr
 * @brief Représente une position 3D entière.
 * @description t_bunny_zposition est utilisé par les API de la LibLapin lorsqu'une valeur de placement de ce type est nécessaire.
 * @field x Coordonnée X.
 * @field y Coordonnée Y.
 * @field z Coordonnée Z.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 */
typedef struct			s_bunny_zposition
{
  int				x;
  int				y;
  int				z;
}				t_bunny_zposition;


/**
 * @doc
 * @doc-symbol t_bunny_accurate_zposition
 * @doc-kind struct
 * @doc-module placement
 * @doc-order 212
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Represents a floating-point 3D position.
 * @description t_bunny_accurate_zposition is used by LibLapin APIs whenever this kind of placement value is needed.
 * @field x X coordinate.
 * @field y Y coordinate.
 * @field z Z coordinate.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 *
 * @doc-lang fr
 * @brief Représente une position 3D flottante.
 * @description t_bunny_accurate_zposition est utilisé par les API de la LibLapin lorsqu'une valeur de placement de ce type est nécessaire.
 * @field x Coordonnée X.
 * @field y Coordonnée Y.
 * @field z Coordonnée Z.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 */
typedef struct			s_bunny_accurate_zposition
{
  double			x;
  double			y;
  double			z;
}				t_bunny_accurate_zposition;


/**
 * @doc
 * @doc-symbol t_bunny_zarea
 * @doc-kind struct
 * @doc-module placement
 * @doc-order 214
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Represents an integer 3D box.
 * @description t_bunny_zarea is used by LibLapin APIs whenever this kind of placement value is needed.
 * @field x X coordinate of the origin.
 * @field y Y coordinate of the origin.
 * @field z Z coordinate of the origin.
 * @field w Width.
 * @field h Height.
 * @field d Depth.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 *
 * @doc-lang fr
 * @brief Représente une boîte 3D entière.
 * @description t_bunny_zarea est utilisé par les API de la LibLapin lorsqu'une valeur de placement de ce type est nécessaire.
 * @field x Coordonnée X.
 * @field y Coordonnée Y.
 * @field z Coordonnée Z.
 * @field w Largeur.
 * @field h Hauteur.
 * @field d Profondeur.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 */
typedef struct			s_bunny_zarea
{
  int				x;
  int				y;
  int				z;
  int				w;
  int				h;
  int				d;
}				t_bunny_zarea;


/**
 * @doc
 * @doc-symbol t_bunny_accurate_zarea
 * @doc-kind struct
 * @doc-module placement
 * @doc-order 216
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Represents a floating-point 3D box.
 * @description t_bunny_accurate_zarea is used by LibLapin APIs whenever this kind of placement value is needed.
 * @field x X coordinate of the origin.
 * @field y Y coordinate of the origin.
 * @field z Z coordinate of the origin.
 * @field w Width.
 * @field h Height.
 * @field d Depth.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 *
 * @doc-lang fr
 * @brief Représente une boîte 3D flottante.
 * @description t_bunny_accurate_zarea est utilisé par les API de la LibLapin lorsqu'une valeur de placement de ce type est nécessaire.
 * @field x Coordonnée X.
 * @field y Coordonnée Y.
 * @field z Coordonnée Z.
 * @field w Largeur.
 * @field h Hauteur.
 * @field d Profondeur.
 * @see t_bunny_position, t_bunny_area, t_bunny_accurate_position
 */
typedef struct			s_bunny_accurate_zarea
{
  double			x;
  double			y;
  double			z;
  double			w;
  double			h;
  double			d;
}				t_bunny_accurate_zarea;

# if				defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L

typedef struct s_bunny_clipable	t_bunny_clipable;
typedef struct s_bunny_pixelarray t_bunny_pixelarray;
typedef struct s_bunny_font	t_bunny_font;

/*!
** Get the effective width on screen of the sent clipable.
** It consists in its clip size multiplied by its scale.
** Can also retrieve the width of window.
** \param clip The clip or window to measure
** \return The width on screen of the clip
*/

/**
 * @doc
 * @doc-symbol bunny_real_width
 * @doc-kind macro
 * @doc-module placement
 * @doc-order 220
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Computes the displayed width of a buffer-like object.
 * @description bunny_real_width is a C11 _Generic macro. It accepts t_bunny_buffer*, t_bunny_window*, t_bunny_clipable*, t_bunny_pixelarray* and t_bunny_font*. Rotation is ignored.
 * @param clip The buffer-like object to measure.
 * @return-success The width displayed on screen, after taking clip size and scale into account when relevant.
 * @see bunny_real_height
 *
 * @doc-lang fr
 * @brief Calcule la largeur affichée d'un objet de type buffer.
 * @description bunny_real_width est une macro C11 basée sur _Generic. Elle accepte t_bunny_buffer*, t_bunny_window*, t_bunny_clipable*, t_bunny_pixelarray* et t_bunny_font*. La rotation est ignorée.
 * @param clip L'objet de type buffer à mesurer.
 * @return-success La largeur affichée à l'écran, en tenant compte de la taille de clip et de l'échelle lorsque c'est pertinent.
 * @see bunny_real_height
 */
#  define			bunny_real_width(clip)				\
  _Generic((clip),								\
	   t_bunny_buffer*:							\
	   clip->width,								\
	   t_bunny_window*:							\
	   clip->buffer.width,							\
	   t_bunny_clipable*:							\
	   ((clip)->clip_width * (clip)->scale.x),				\
	   t_bunny_pixelarray*:							\
	   ((clip)->clipable.clip_width						\
	    * (clip)->clipable.scale.x),					\
	   t_bunny_font*:							\
	   ((clip)->clipable.clip_width						\
	    * (clip)->clipable.scale.x)						\
	   )

/*!
** Get the effective height on screen of the sent clipable.
** It consists in its clip size multiplied by its scale.
** Can also retrieve the height of a window.
** \param clip The clip or window to measure
** \return The height on screen of the clip
*/

/**
 * @doc
 * @doc-symbol bunny_real_height
 * @doc-kind macro
 * @doc-module placement
 * @doc-order 240
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Computes the displayed height of a buffer-like object.
 * @description bunny_real_height is a C11 _Generic macro. It accepts t_bunny_buffer*, t_bunny_window*, t_bunny_clipable*, t_bunny_pixelarray* and t_bunny_font*. Rotation is ignored.
 * @param clip The buffer-like object to measure.
 * @return-success The height displayed on screen, after taking clip size and scale into account when relevant.
 * @see bunny_real_width
 *
 * @doc-lang fr
 * @brief Calcule la hauteur affichée d'un objet de type buffer.
 * @description bunny_real_height est une macro C11 basée sur _Generic. Elle accepte t_bunny_buffer*, t_bunny_window*, t_bunny_clipable*, t_bunny_pixelarray* et t_bunny_font*. La rotation est ignorée.
 * @param clip L'objet de type buffer à mesurer.
 * @return-success La hauteur affichée à l'écran, en tenant compte de la taille de clip et de l'échelle lorsque c'est pertinent.
 * @see bunny_real_width
 */
#  define			bunny_real_height(clip)				\
  _Generic((clip),								\
	   t_bunny_buffer*:							\
	   clip->height,							\
	   t_bunny_window*:							\
	   clip->buffer.height,							\
	   t_bunny_clipable*:							\
	   ((clip)->clip_height * (clip)->scale.y),				\
	   t_bunny_pixelarray*:							\
	   ((clip)->clipable.clip_height					\
	    * (clip)->clipable.scale.y),					\
	   t_bunny_font*:							\
	   ((clip)->clipable.clip_height					\
	    * (clip)->clipable.scale.y)						\
	   )
# endif

# ifdef				__cplusplus
#  include			"lapin/cpp_guard.hpp"
# endif


/**
 * @doc
 * @doc-symbol bunny_size_configuration
 * @doc-kind macro
 * @doc-module placement
 * @doc-order 300
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Reads an integer size from a configuration field.
 * @description bunny_size_configuration is an alias around bunny_position_configuration.
 * @param field The configuration field name.
 * @param pos The size structure to fill.
 * @param cnf The configuration node to read from.
 * @see bunny_position_configuration
 *
 * @doc-lang fr
 * @brief Lit une taille entière depuis un champ de configuration.
 * @description bunny_size_configuration est un alias autour de bunny_position_configuration.
 * @param field Le nom du champ de configuration.
 * @param pos La structure de taille à remplir.
 * @param cnf Le noeud de configuration à lire.
 * @see bunny_position_configuration
 */

/**
 * @doc
 * @doc-symbol bunny_size
 * @doc-kind macro
 * @doc-module placement
 * @doc-order 420
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Builds a t_bunny_size value.
 * @description bunny_size is an alias around bunny_position.
 * @param x The width.
 * @param y The height.
 * @see bunny_position
 *
 * @doc-lang fr
 * @brief Construit une valeur t_bunny_size.
 * @description bunny_size est un alias autour de bunny_position.
 * @param x La largeur.
 * @param y La hauteur.
 * @see bunny_position
 */
# define	bunny_size_configuration(a, b, c)				\
  bunny_position_configuration(a, b, c)

/**
 * @doc
 * @doc-symbol bunny_size_bind_configuration
 * @doc-kind macro
 * @doc-module placement
 * @doc-order 310
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Reads and binds an integer size from a configuration field.
 * @description bunny_size_bind_configuration is an alias around bunny_position_bind_configuration.
 * @param field The configuration field name.
 * @param pos The size structure to fill and bind.
 * @param cnf The configuration node to read from and bind to.
 * @see bunny_position_bind_configuration
 *
 * @doc-lang fr
 * @brief Lit et lie une taille entière depuis un champ de configuration.
 * @description bunny_size_bind_configuration est un alias autour de bunny_position_bind_configuration.
 * @param field Le nom du champ de configuration.
 * @param pos La structure de taille à remplir et lier.
 * @param cnf Le noeud de configuration à lire et auquel lier.
 * @see bunny_position_bind_configuration
 */
# define	bunny_size_bind_configuration(a, b, c)				\
  bunny_position_bind_configuration(a, b, c)
t_bunny_decision bunny_position_configuration(const char			*field,
					      t_bunny_position			*pos,
					      t_bunny_configuration		*cnf);
t_bunny_decision bunny_position_bind_configuration(const char			*field,
						   t_bunny_position		*pos,
						   t_bunny_configuration	*cnf);


/**
 * @doc
 * @doc-symbol bunny_accurate_size_configuration
 * @doc-kind macro
 * @doc-module placement
 * @doc-order 340
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Reads a floating-point size from a configuration field.
 * @description bunny_accurate_size_configuration is an alias around bunny_accurate_position_configuration.
 * @param field The configuration field name.
 * @param pos The size structure to fill.
 * @param cnf The configuration node to read from.
 * @see bunny_accurate_position_configuration
 *
 * @doc-lang fr
 * @brief Lit une taille flottante depuis un champ de configuration.
 * @description bunny_accurate_size_configuration est un alias autour de bunny_accurate_position_configuration.
 * @param field Le nom du champ de configuration.
 * @param pos La structure de taille à remplir.
 * @param cnf Le noeud de configuration à lire.
 * @see bunny_accurate_position_configuration
 */

/**
 * @doc
 * @doc-symbol bunny_accurate_size
 * @doc-kind macro
 * @doc-module placement
 * @doc-order 440
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Builds a t_bunny_accurate_size value.
 * @description bunny_accurate_size is an alias around bunny_accurate_position.
 * @param x The width.
 * @param y The height.
 * @see bunny_accurate_position
 *
 * @doc-lang fr
 * @brief Construit une valeur t_bunny_accurate_size.
 * @description bunny_accurate_size est un alias autour de bunny_accurate_position.
 * @param x La largeur.
 * @param y La hauteur.
 * @see bunny_accurate_position
 */
# define	bunny_accurate_size_configuration(a, b, c)			\
  bunny_accurate_position_configuration(a, b, c)

/**
 * @doc
 * @doc-symbol bunny_accurate_size_bind_configuration
 * @doc-kind macro
 * @doc-module placement
 * @doc-order 350
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Reads and binds a floating-point size from a configuration field.
 * @description bunny_accurate_size_bind_configuration is an alias around bunny_accurate_position_bind_configuration.
 * @param field The configuration field name.
 * @param pos The size structure to fill and bind.
 * @param cnf The configuration node to read from and bind to.
 * @see bunny_accurate_position_bind_configuration
 *
 * @doc-lang fr
 * @brief Lit et lie une taille flottante depuis un champ de configuration.
 * @description bunny_accurate_size_bind_configuration est un alias autour de bunny_accurate_position_bind_configuration.
 * @param field Le nom du champ de configuration.
 * @param pos La structure de taille à remplir et lier.
 * @param cnf Le noeud de configuration à lire et auquel lier.
 * @see bunny_accurate_position_bind_configuration
 */
# define	bunny_accurate_size_bind_configuration(a, b, c)			\
  bunny_accurate_position_bind_configuration(a, b, c)
t_bunny_decision bunny_accurate_position_configuration(const char		*field,
						       t_bunny_accurate_position *pos,
						       t_bunny_configuration	*cnf);
t_bunny_decision bunny_accurate_position_bind_configuration(const char		*field,
							    t_bunny_accurate_position *pos,
							    t_bunny_configuration *cnf);

t_bunny_position		bunny_position(int				x,
					       int				y);
# define			bunny_size(x, y)				bunny_position(x, y)
t_bunny_accurate_position	bunny_accurate_position(double			x,
							double			y);
# define			bunny_accurate_size(x, y)			bunny_accurate_position(x, y)
t_bunny_area			bunny_area(int					x,
					   int					y,
					   int					w,
					   int					h);
t_bunny_accurate_area		bunny_accurate_area(double			x,
						    double			y,
						    double			w,
						    double			h);


struct s_bunny_clipable;
void				bunny_maximize_inside(struct s_bunny_clipable	*to_resize,
						      const struct s_bunny_clipable *container);

# ifdef				__cplusplus
#  include			"lapin/cpp_guard_end.hpp"
# endif
#endif	/*			__LAPIN_PLACEMENT_H__				*/

