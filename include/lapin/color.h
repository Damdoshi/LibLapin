/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2026
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_COLOR_H__
# define			__LAPIN_COLOR_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/**
 * @doc
 * @doc-symbol color
 * @doc-kind module
 * @doc-module color
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Provides color constants, component helpers and color configuration loading.
 * @description LibLapin colors are 32-bit ARGB values. The macros of this module build colors component by component, extract components and expose common color constants.
 * @header lapin/color.h
 *
 * @doc-lang fr
 * @brief Fournit des constantes de couleur, des assistants de composants et le chargement de couleurs depuis la configuration.
 * @description Les couleurs de la LibLapin sont des valeurs ARGB sur 32 bits. Les macros de ce module construisent des couleurs composant par composant, extraient des composants et exposent des constantes de couleur courantes.
 * @header lapin/color.h
 */

/**
 * @doc
 * @doc-symbol t_bunny_rgb
 * @doc-kind enum
 * @doc-module color
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Gives the component indices used by t_bunny_color.
 * @description t_bunny_rgb values are indexes in the argb and mod arrays of t_bunny_color. The byte order follows the integer representation used by the LibLapin color macros.
 * @value RED_CMP Index of the red component.
 * @value GREEN_CMP Index of the green component.
 * @value BLUE_CMP Index of the blue component.
 * @value ALPHA_CMP Index of the alpha component.
 * @see t_bunny_color, COLOR, ALPHA
 *
 * @doc-lang fr
 * @brief Donne les indices de composants utilisés par t_bunny_color.
 * @description Les valeurs de t_bunny_rgb sont les indices dans les tableaux argb et mod de t_bunny_color. L'ordre des octets suit la représentation entière utilisée par les macros de couleur de la LibLapin.
 * @value RED_CMP Indice du composant rouge.
 * @value GREEN_CMP Indice du composant vert.
 * @value BLUE_CMP Indice du composant bleu.
 * @value ALPHA_CMP Indice du composant alpha.
 * @see t_bunny_color, COLOR, ALPHA
 */
typedef enum			e_bunny_rgb
  {
    RED_CMP			= 0,
    GREEN_CMP			= 1,
    BLUE_CMP			= 2,
    ALPHA_CMP			= 3
  }				t_bunny_rgb;

# ifdef				TRANSPARENT
#  undef			TRANSPARENT
# endif

/**
 * @doc
 * @doc-symbol TRANSPARENT
 * @doc-kind macro
 * @doc-module color
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents transparent color.
 * @description TRANSPARENT is a 32-bit ARGB color constant representing 0, fully transparent black.
 * @see t_bunny_color, COLOR
 *
 * @doc-lang fr
 * @brief Représente une couleur transparente.
 * @description TRANSPARENT est une constante de couleur ARGB sur 32 bits représentant 0, c’est-à-dire du noir totalement transparent.
 * @see t_bunny_color, COLOR
 */
# define			TRANSPARENT		((uint32_t)0)


/**
 * @doc
 * @doc-symbol BLACK
 * @doc-kind macro
 * @doc-module color
 * @doc-order 130
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents opaque black.
 * @description BLACK is a 32-bit ARGB color constant representing black with full alpha.
 * @description <div style="width: 200px; height: 50px; background-color: #000000;"></div>
 * @see t_bunny_color, COLOR
 *
 * @doc-lang fr
 * @brief Représente le noir opaque.
 * @description BLACK est une constante de couleur ARGB sur 32 bits représentant du noir avec un alpha complet.
 * @description <div style="width: 200px; height: 50px; background-color: #000000;"></div>
 * @see t_bunny_color, COLOR
 */
# define			BLACK			((uint32_t)(255 << (ALPHA_CMP * 8)))


/**
 * @doc
 * @doc-symbol RED
 * @doc-kind macro
 * @doc-module color
 * @doc-order 140
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents opaque red.
 * @description RED is a 32-bit ARGB color constant representing red with full alpha.
 * @description <div style="width: 200px; height: 50px; background-color: #FF0000;"></div>
 * @see t_bunny_color, COLOR
 *
 * @doc-lang fr
 * @brief Représente le rouge opaque.
 * @description RED est une constante de couleur ARGB sur 32 bits représentant du rouge avec un alpha complet.
 * @description <div style="width: 200px; height: 50px; background-color: #FF0000;"></div>
 * @see t_bunny_color, COLOR
 */
# define			RED			((uint32_t)(BLACK | (255 << RED_CMP * 8)))

/**
 * @doc
 * @doc-symbol GREEN
 * @doc-kind macro
 * @doc-module color
 * @doc-order 160
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents opaque green.
 * @description GREEN is a 32-bit ARGB color constant representing green with full alpha.
 * @description <div style="width: 200px; height: 50px; background-color: #00FF00;"></div>
 * @see t_bunny_color, COLOR
 *
 * @doc-lang fr
 * @brief Représente le vert opaque.
 * @description GREEN est une constante de couleur ARGB sur 32 bits représentant du vert avec un alpha complet.
 * @description <div style="width: 200px; height: 50px; background-color: #00FF00;"></div>
 * @see t_bunny_color, COLOR
 */
# define			GREEN			((uint32_t)(BLACK | (255 << GREEN_CMP * 8)))

/**
 * @doc
 * @doc-symbol BLUE
 * @doc-kind macro
 * @doc-module color
 * @doc-order 180
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents opaque blue.
 * @description BLUE is a 32-bit ARGB color constant representing blue with full alpha.
 * @description <div style="width: 200px; height: 50px; background-color: #0000FF;"></div>
 * @see t_bunny_color, COLOR
 *
 * @doc-lang fr
 * @brief Représente le bleu opaque.
 * @description BLUE est une constante de couleur ARGB sur 32 bits représentant du bleu avec un alpha complet.
 * @description <div style="width: 200px; height: 50px; background-color: #0000FF;"></div>
 * @see t_bunny_color, COLOR
 */
# define			BLUE			((uint32_t)(BLACK | (255 << BLUE_CMP * 8)))


/**
 * @doc
 * @doc-symbol PURPLE
 * @doc-kind macro
 * @doc-module color
 * @doc-order 200
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents opaque purple.
 * @description PURPLE is a 32-bit ARGB color constant representing red and blue with full alpha.
 * @description <div style="width: 200px; height: 50px; background-color: #FF00FF;"></div>
 * @see t_bunny_color, COLOR
 *
 * @doc-lang fr
 * @brief Représente le violet opaque.
 * @description PURPLE est une constante de couleur ARGB sur 32 bits représentant du rouge et du bleu avec un alpha complet.
 * @description <div style="width: 200px; height: 50px; background-color: #FF00FF;"></div>
 * @see t_bunny_color, COLOR
 */
# define			PURPLE			((uint32_t)(RED | BLUE))

/**
 * @doc
 * @doc-symbol TEAL
 * @doc-kind macro
 * @doc-module color
 * @doc-order 220
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents opaque teal.
 * @description TEAL is a 32-bit ARGB color constant representing green and blue with full alpha.
 * @description <div style="width: 200px; height: 50px; background-color: #00FFFF;"></div>
 * @see t_bunny_color, COLOR
 *
 * @doc-lang fr
 * @brief Représente le cyan-vert opaque.
 * @description TEAL est une constante de couleur ARGB sur 32 bits représentant du vert et du bleu avec un alpha complet.
 * @description <div style="width: 200px; height: 50px; background-color: #00FFFF;"></div>
 * @see t_bunny_color, COLOR
 */
# define			TEAL			((uint32_t)(GREEN | BLUE))

/**
 * @doc
 * @doc-symbol YELLOW
 * @doc-kind macro
 * @doc-module color
 * @doc-order 240
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents opaque yellow.
 * @description YELLOW is a 32-bit ARGB color constant representing red and green with full alpha.
 * @description <div style="width: 200px; height: 50px; background-color: #FFFF00;"></div>
 * @see t_bunny_color, COLOR
 *
 * @doc-lang fr
 * @brief Représente le jaune opaque.
 * @description YELLOW est une constante de couleur ARGB sur 32 bits représentant du rouge et du vert avec un alpha complet.
 * @description <div style="width: 200px; height: 50px; background-color: #FFFF00;"></div>
 * @see t_bunny_color, COLOR
 */
# define			YELLOW			((uint32_t)(RED | GREEN))


/**
 * @doc
 * @doc-symbol WHITE
 * @doc-kind macro
 * @doc-module color
 * @doc-order 260
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents opaque white.
 * @description WHITE is a 32-bit ARGB color constant representing red, green and blue with full alpha.
 * @description <div style="width: 200px; height: 50px; background-color: #FFFFFF;"></div>
 * @see t_bunny_color, COLOR
 *
 * @doc-lang fr
 * @brief Représente le blanc opaque.
 * @description WHITE est une constante de couleur ARGB sur 32 bits représentant du rouge, du vert et du bleu avec un alpha complet.
 * @description <div style="width: 200px; height: 50px; background-color: #FFFFFF;"></div>
 * @see t_bunny_color, COLOR
 */
# define			WHITE			((uint32_t)(RED | GREEN | BLUE))


/**
 * @doc
 * @doc-symbol PINK
 * @doc-kind macro
 * @doc-module color
 * @doc-order 280
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents LibLapin pink.
 * @description PINK is a 32-bit ARGB color constant representing the old LibLapin pink.
 * @description <div style="width: 200px; height: 50px; background-color: #FF7777;"></div>
 * @see t_bunny_color, COLOR
 *
 * @doc-lang fr
 * @brief Représente le rose LibLapin.
 * @description PINK est une constante de couleur ARGB sur 32 bits représentant le rose de l'ancienne LibLapin.
 * @description <div style="width: 200px; height: 50px; background-color: #FF7777;"></div>
 * @see t_bunny_color, COLOR
 */
# define			PINK			((uint32_t)0xFF7777FF)

/**
 * @doc
 * @doc-symbol PINK2
 * @doc-kind macro
 * @doc-module color
 * @doc-order 300
 * @doc-since 6
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents Damdoshi pink.
 * @description PINK2 is a 32-bit ARGB color constant representing the alternate LibLapin pink. Ma couleur préférée <3
 * @description <div style="width: 200px; height: 50px; background-color: #FF69B4;"></div>
 * @see t_bunny_color, COLOR
 *
 * @doc-lang fr
 * @brief Représente le rose Damdoshi.
 * @description PINK2 est une constante de couleur ARGB sur 32 bits représentant le rose alternatif de la LibLapin. My favorite color <3
 * @description <div style="width: 200px; height: 50px; background-color: #FF69B4;"></div>
 * @see t_bunny_color, COLOR
 */
# define			PINK2			((uint32_t)0xFFB469FF)

/**
 * @doc
 * @doc-symbol TO_ALPHA
 * @doc-kind macro
 * @doc-module color
 * @doc-order 320
 * @doc-since 0
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Builds an alpha component from an 8-bit value.
 * @param a The alpha value.
 * @return-success The alpha component shifted to its ARGB position.
 * @see COLOR, t_bunny_rgb
 *
 * @doc-lang fr
 * @brief Construit un composant alpha depuis une valeur sur 8 bits.
 * @param a La valeur alpha.
 * @return-success Le composant alpha décalé à sa position ARGB.
 * @see COLOR, t_bunny_rgb
 */
# define			TO_ALPHA(a)			(((int)(a) & 0xFF) << (ALPHA_CMP * 8))

/**
 * @doc
 * @doc-symbol TO_RED
 * @doc-kind macro
 * @doc-module color
 * @doc-order 340
 * @doc-since 0
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Builds a red component from an 8-bit value.
 * @param r The red value.
 * @return-success The red component shifted to its ARGB position.
 * @see COLOR, t_bunny_rgb
 *
 * @doc-lang fr
 * @brief Construit un composant rouge depuis une valeur sur 8 bits.
 * @param r La valeur rouge.
 * @return-success Le composant rouge décalé à sa position ARGB.
 * @see COLOR, t_bunny_rgb
 */
# define			TO_RED(a)			(((int)(a) & 0xFF) << (RED_CMP * 8))

/**
 * @doc
 * @doc-symbol TO_GREEN
 * @doc-kind macro
 * @doc-module color
 * @doc-order 360
 * @doc-since 0
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Builds a green component from an 8-bit value.
 * @param g The green value.
 * @return-success The green component shifted to its ARGB position.
 * @see COLOR, t_bunny_rgb
 *
 * @doc-lang fr
 * @brief Construit un composant vert depuis une valeur sur 8 bits.
 * @param g La valeur verte.
 * @return-success Le composant vert décalé à sa position ARGB.
 * @see COLOR, t_bunny_rgb
 */
# define			TO_GREEN(a)			(((int)(a) & 0xFF) << (GREEN_CMP * 8))

/**
 * @doc
 * @doc-symbol TO_BLUE
 * @doc-kind macro
 * @doc-module color
 * @doc-order 380
 * @doc-since 0
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Builds a blue component from an 8-bit value.
 * @param b The blue value.
 * @return-success The blue component shifted to its ARGB position.
 * @see COLOR, t_bunny_rgb
 *
 * @doc-lang fr
 * @brief Construit un composant bleu depuis une valeur sur 8 bits.
 * @param b La valeur bleue.
 * @return-success Le composant bleu décalé à sa position ARGB.
 * @see COLOR, t_bunny_rgb
 */
# define			TO_BLUE(a)			(((int)(a) & 0xFF) << (BLUE_CMP * 8))

/**
 * @doc
 * @doc-symbol GET_COLOR
 * @doc-kind macro
 * @doc-module color
 * @doc-order 400
 * @doc-since 0
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Removes the alpha component from a color.
 * @param c The 32-bit ARGB color to mask.
 * @return-success The same color with its alpha byte cleared.
 * @see ALPHA, COLOR
 *
 * @doc-lang fr
 * @brief Retire le composant alpha d'une couleur.
 * @param c La couleur ARGB sur 32 bits à masquer.
 * @return-success La même couleur avec son octet alpha effacé.
 * @see ALPHA, COLOR
 */
# define			GET_COLOR(c)			((c) & ~TO_ALPHA(255))

/**
 * @doc
 * @doc-symbol ALPHA
 * @doc-kind macro
 * @doc-module color
 * @doc-order 420
 * @doc-since 0
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Replaces the alpha component of a color.
 * @param a The new alpha value.
 * @param c The source color.
 * @return-success The source color with alpha set to a.
 * @see GET_COLOR, TO_ALPHA
 *
 * @doc-lang fr
 * @brief Remplace le composant alpha d'une couleur.
 * @param a La nouvelle valeur alpha.
 * @param c La couleur source.
 * @return-success La couleur source avec l'alpha réglé à a.
 * @see GET_COLOR, TO_ALPHA
 */
# define			ALPHA(a, c)			(TO_ALPHA(a) | GET_COLOR(c))

/**
 * @doc
 * @doc-symbol COLOR
 * @doc-kind macro
 * @doc-module color
 * @doc-order 440
 * @doc-since 0
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Composes a 32-bit ARGB color from four components.
 * @param a The alpha component.
 * @param r The red component.
 * @param g The green component.
 * @param b The blue component.
 * @return-success A 32-bit color containing all sent components.
 * @see ALPHA, GRAY, ALPHA_GRAY
 *
 * @doc-lang fr
 * @brief Compose une couleur ARGB sur 32 bits depuis quatre composants.
 * @param a Le composant alpha.
 * @param r Le composant rouge.
 * @param g Le composant vert.
 * @param b Le composant bleu.
 * @return-success Une couleur sur 32 bits contenant tous les composants envoyés.
 * @see ALPHA, GRAY, ALPHA_GRAY
 */
# define			COLOR(a, r, g, b)		\
  (TO_ALPHA(a) | TO_RED(r) | TO_GREEN(g) | TO_BLUE(b))

/**
 * @doc
 * @doc-symbol ALPHA_GRAY
 * @doc-kind macro
 * @doc-module color
 * @doc-order 460
 * @doc-since 12
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Composes a gray color with a chosen alpha value.
 * @param a The alpha component.
 * @param g The gray level used for red, green and blue.
 * @return-success A 32-bit ARGB gray color.
 * @see GRAY, COLOR
 *
 * @doc-lang fr
 * @brief Compose une couleur grise avec une valeur alpha choisie.
 * @param a Le composant alpha.
 * @param g Le niveau de gris utilisé pour le rouge, le vert et le bleu.
 * @return-success Une couleur grise ARGB sur 32 bits.
 * @see GRAY, COLOR
 */
# define			ALPHA_GRAY(a, g)		\
  COLOR(a, (g), (g), (g))

/**
 * @doc
 * @doc-symbol GRAY
 * @doc-kind macro
 * @doc-module color
 * @doc-order 480
 * @doc-since 12
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Composes a fully opaque gray color.
 * @param g The gray level used for red, green and blue.
 * @return-success A 32-bit ARGB gray color with alpha 255.
 * @see ALPHA_GRAY, COLOR
 *
 * @doc-lang fr
 * @brief Compose une couleur grise totalement opaque.
 * @param g Le niveau de gris utilisé pour le rouge, le vert et le bleu.
 * @return-success Une couleur grise ARGB sur 32 bits avec alpha 255.
 * @see ALPHA_GRAY, COLOR
 */
# define			GRAY(g)				\
  COLOR(255, (g), (g), (g))


/**
 * @doc
 * @doc-symbol t_bunny_color
 * @doc-kind union
 * @doc-module color
 * @doc-order 110
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Represents a pixel color in several convenient forms.
 * @description t_bunny_color can be manipulated as one 32-bit integer, as four unsigned ARGB components or as four signed modifiers used to alter another color.
 * @field full Complete 32-bit ARGB color.
 * @field argb Component array indexed with t_bunny_rgb values.
 * @field mod Signed component array useful as color offsets or speeds.
 * @see t_bunny_rgb, COLOR, ALPHA
 *
 * @doc-lang fr
 * @brief Représente une couleur de pixel sous plusieurs formes pratiques.
 * @description t_bunny_color peut être manipulée comme un entier complet sur 32 bits, comme quatre composants ARGB non signés ou comme quatre modificateurs signés servant à altérer une autre couleur.
 * @field full Couleur ARGB complète sur 32 bits.
 * @field argb Tableau de composants indexé avec les valeurs de t_bunny_rgb.
 * @field mod Tableau de composants signés utile comme offsets ou vitesses de couleur.
 * @see t_bunny_rgb, COLOR, ALPHA
 */
typedef union			u_bunny_color
{
  uint32_t			full;
  uint8_t			argb[4];
  int8_t			mod[4];
}				t_bunny_color;

t_bunny_decision		bunny_color_configuration(const char		*fieldname,
							  t_bunny_color		*col,
							  t_bunny_configuration	*cnf);
t_bunny_decision		bunny_color_bind_configuration(const char	*fieldname,
							       t_bunny_color	*col,
							       t_bunny_configuration *cnf);

# endif	/*			__LAPIN_COLOR_H__		*/
