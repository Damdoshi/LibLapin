/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file window.h
** The window module contains what you need to open, close and manipulates windows.
** Getting informations from the system and control a few elements from it like
** mouse is also in this module.
*/

#ifndef				__LAPIN_WINDOW_H__
# define			__LAPIN_WINDOW_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/**
 * @doc
 * @doc-symbol window
 * @doc-kind module
 * @doc-module window
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Opens and manages windows and screen-related services.
 * @description The Window module is about opening and managing windows and system-related things that go through windows. It also handles some screen-related features.
 * @header lapin/window.h
 *
 * @doc-lang fr
 * @brief Ouvre et manipule les fenêtres ainsi que les services liés à l'écran.
 * @description Le module Window sert à ouvrir et manipuler des fenêtres, ainsi que les éléments liés au système qui passent par elles. Il gère également certaines fonctionnalités relatives aux écrans.
 * @header lapin/window.h
 */

/**
 * @doc
 * @doc-symbol t_bunny_window_style
 * @doc-kind enum
 * @doc-module window
 * @doc-order 105
 * @doc-since 3
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Describes how a window should be created by bunny_start_style.
 * @description t_bunny_window_style is a bitmask enumeration. Most values can be combined with the binary OR operator to ask the system for several window decorations at the same time.
 * @description FULLSCREEN is intended to be used as a fullscreen creation mode. ANTIALIASING is a LibLapin flag that can be added to another style to request antialiasing when the render window is created.
 * @value NO_BORDER Creates a window without title bar, border, resize button or close button.
 * @value TITLEBAR Adds a title bar to the window. The title bar usually displays the window name and allows the user to move the window.
 * @value RESIZE_BUTTON Adds the resize or maximize decoration when the window manager supports it.
 * @value CLOSE_BUTTON Adds the close button decoration when the window manager supports it. The system may still provide other ways to close a window.
 * @value FULLSCREEN Creates a fullscreen window.
 * @value DEFAULT_WIN_STYLE The style used by bunny_start for a regular window.
 * @value ANTIALIASING Requests antialiasing when creating the window.
 * @see bunny_start_style, bunny_start
 *
 * @doc-lang fr
 * @brief Décrit la manière dont une fenêtre doit être créée par bunny_start_style.
 * @description t_bunny_window_style est une énumération utilisable comme masque binaire. La plupart des valeurs peuvent être combinées avec l'opérateur OU binaire afin de demander plusieurs décorations de fenêtre en même temps au système.
 * @description FULLSCREEN est prévu pour être utilisé comme mode de création plein écran. ANTIALIASING est un drapeau propre à la LibLapin qui peut être ajouté à un autre style pour demander de l'antialiasing lors de la création de la fenêtre de rendu.
 * @value NO_BORDER Crée une fenêtre sans barre de titre, bordure, bouton de redimensionnement ou bouton de fermeture.
 * @value TITLEBAR Ajoute une barre de titre à la fenêtre. La barre de titre affiche généralement le nom de la fenêtre et permet à l'utilisateur de la déplacer.
 * @value RESIZE_BUTTON Ajoute la décoration de redimensionnement ou de maximisation lorsque le gestionnaire de fenêtres le permet.
 * @value CLOSE_BUTTON Ajoute la décoration de bouton de fermeture lorsque le gestionnaire de fenêtres le permet. Le système peut tout de même proposer d'autres moyens de fermer une fenêtre.
 * @value FULLSCREEN Crée une fenêtre plein écran.
 * @value DEFAULT_WIN_STYLE Le style utilisé par bunny_start pour une fenêtre standard.
 * @value ANTIALIASING Demande de l'antialiasing lors de la création de la fenêtre.
 * @see bunny_start_style, bunny_start
 */
typedef enum			e_bunny_window_style
  {
    NO_BORDER			= 0,
    TITLEBAR			= 1,
    RESIZE_BUTTON		= 2,
    CLOSE_BUTTON		= 4,
    FULLSCREEN			= 8,
    DEFAULT_WIN_STYLE		= TITLEBAR | RESIZE_BUTTON | CLOSE_BUTTON,
    ANTIALIASING		= 16,
    DEPTH_BUFFER		= 32
  }				t_bunny_window_style;

/**
 * @doc
 * @doc-symbol t_bunny_window
 * @doc-kind struct
 * @doc-module window
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level 0
 *
 * @doc-lang en
 * @brief Represents an opened window.
 * @description t_bunny_window starts with a t_bunny_buffer, so it can be used everywhere a t_bunny_buffer is expected. The buffer contains the width and height of the drawing surface.
 * @description A window is opened with bunny_start or bunny_start_style and closed with bunny_stop. Windows are write-only from the program point of view: draw into them, then call bunny_display to show the result on screen.
 * @field buffer The common buffer header. It contains the window size and allows the window to be used as a t_bunny_buffer.
 * @field name The name sent to bunny_start or bunny_start_style when the window was opened.
 * @field style The t_bunny_window_style used when the window was created.
 * @field position The last known desktop position of the window.
 * @see bunny_start, bunny_start_style, bunny_stop, bunny_display
 *
 * @doc-lang fr
 * @brief Représente une fenêtre ouverte.
 * @description t_bunny_window commence par un t_bunny_buffer, ce qui permet de l'utiliser partout où un t_bunny_buffer est attendu. Le buffer contient la largeur et la hauteur de la surface de dessin.
 * @description Une fenêtre est ouverte avec bunny_start ou bunny_start_style et fermée avec bunny_stop. Du point de vue du programme, une fenêtre est en écriture seule : dessinez dedans, puis appelez bunny_display pour afficher le résultat à l'écran.
 * @field buffer L'en-tête de buffer commun. Il contient la taille de la fenêtre et permet d'utiliser la fenêtre comme un t_bunny_buffer.
 * @field name Le nom envoyé à bunny_start ou bunny_start_style lors de l'ouverture de la fenêtre.
 * @field style Le t_bunny_window_style utilisé lors de la création de la fenêtre.
 * @field position La dernière position connue de la fenêtre sur le bureau.
 * @see bunny_start, bunny_start_style, bunny_stop, bunny_display
 */
typedef struct			s_bunny_window
{
  t_bunny_buffer		buffer;
  const char * const		name;
  const int			style;
  const t_bunny_position	position;
}				t_bunny_window;

t_bunny_window			*bunny_start(unsigned int			width,
					     unsigned int			height,
					     bool				fullscreen,
					     const char				*name);

void				bunny_stop(t_bunny_window			*window);

void				bunny_display(const t_bunny_window		*window);

const t_bunny_size		*bunny_get_screen_resolution(void);

const t_bunny_area		*bunny_list_monitors(void);

const t_bunny_area		*bunny_list_autonomous_monitors(void);

t_bunny_position		bunny_get_monitors_origin(void);

t_bunny_window			*bunny_start_style(unsigned int			width,
						   unsigned int			height,
						   t_bunny_window_style		style,
						   const char			*name);

t_bunny_window			**bunny_begin(const char			*file);
t_bunny_window			**bunny_beginc(const char			*file,
					       size_t				*nbr_win);
t_bunny_window			**bunny_begin_configuration(t_bunny_configuration *cnf);

void				bunny_end(t_bunny_window			**windows);

const t_bunny_size		*bunny_get_fullscreen_modes(void);

void				bunny_set_key_repeat(t_bunny_window		*window,
					     bool			repeat);

void				bunny_set_mouse_visibility(const t_bunny_window	*window,
							   bool			visible);

void				bunny_set_mouse_position_window(const t_bunny_window *window,
								int		x,
								int		y);

void				bunny_set_mouse_position(int			x,
							 int			y);

void				bunny_request_focus(const t_bunny_window	*window);

void				bunny_move_window(t_bunny_window		*window,
					  t_bunny_position		position);

t_bunny_position		bunny_get_window_position(const t_bunny_window	*window);

void				bunny_resize_window(t_bunny_window		*window,
					    t_bunny_size		size);

void				bunny_vertical_sync(t_bunny_window		*window,
					    bool			enabled);

struct s_bunny_pixelarray;
void				bunny_set_window_icon(t_bunny_window		*window,
					      struct s_bunny_pixelarray	*icon);

t_bunny_window			*bunny_single_fullscreen(const char		*name);

t_bunny_window			**bunny_all_fullscreen(const char		*name);

#endif	/*			__LAPIN_WINDOW_H__		*/
