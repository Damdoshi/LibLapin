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

/*!
** The t_bunny_window represents an opened window. It contains
** a t_bunny_buffer with size informations and also a name.
*/
typedef struct			s_bunny_window
{
  t_bunny_buffer		buffer;
  const char * const		name;
}				t_bunny_window;

/*!
** Open a new window. The function need informations about size, if the window must
** be fullscreen or not and its name. If the window must be opened in a fullscreen
** fashion, then, its size must match a valid fullscreen resolution. It highly depends
** of the system your program will run, but a lot of standards resolution work everywhere:
** - 640x480 - 800x600 - 1024x768 . . . 1920x1080, for example
** \param wid The width of the new window
** \param hei The height of the new window
** \param ful If the window must be opened fullscreen (true) or not (false).
** \param nam The name of the window
** \return A pointer on a t_bunny_window. Returns NULL on error.
*/
t_bunny_window			*bunny_start(unsigned int			wid,
					     unsigned int			hei,
					     bool				ful,
					     const char				*nam);

/*!
** Destroy the given window. Restore the previous resolution if the window was
** fullscreen and if the resolution was changed when it was launched.
** \param win The window to destroy.
*/
void				bunny_stop(t_bunny_window			*win);

/*!
** Refresh the content of the window on screen.
** \param win The window to refresh.
*/
void				bunny_display(const t_bunny_window		*win);

/*!
** Return the current resolution of the screen/desktop. This size is valid as
** fullscreen window resolution.
** \return A t_bunny_size with x and y fields for width and height of the screen.
*/
const t_bunny_size		*bunny_get_screen_resolution(void);

/*!
** The t_bunny_window_style enumeration is a collection of values that will
** allow you, throught the bunny_start_style function, to open a window with
** a specific aspect. You can mix these values thanks to a binary or |.
*/
typedef enum			e_bunny_window_style
  {
    NO_BORDER			= 0,
    TITLEBAR			= 1,
    RESIZE_BUTTON		= 2,
    CLOSE_BUTTON		= 4,
    FULLSCREEN			= 9,
    DEFAULT_WIN_STYLE		= TITLEBAR | RESIZE_BUTTON | CLOSE_BUTTON
  }				t_bunny_window_style;

/*!
** bunny_start_style works the same way as bunny_start but allow you to specify
** more precisly the aspect of the window you need.
** See bunny_start for more informations.
** \param wid The width of the window.
** \param hei The height of the window.
** \param sty The style of the window. May be any t_bunny_window_style values
** or any composition made with these value. Note that FULLSCREEN must be
** exclusive.
** \param nam The name of the window.
** \return A pointer on a t_bunny_window. Returns NULL on error.
*/
t_bunny_window			*bunny_start_style(unsigned int			wid,
						   unsigned int			hei,
						   t_bunny_window_style		sty,
						   const char			*nam);

/*!
** The bunny_set_key_repeat function activate or deactivate the key repetition
** when someone is holding a key pressed down. The repetition is useful in software
** where typing text is needed. In video game, it should be disabled.
** The key repeat is true by default.
** \param win The window where to activate or deactivate the key repetition.
** \param active True to active, false to disable.
*/
void				bunny_set_key_repeat(const t_bunny_window	*win,
						     bool			active);

/*!
** The bunny_set_mouse_visibility function make the mouse appeir or disappeir when
** moving on the top of a sent window.
** \param win The window where to change the mouse visibility
** \param True to make the mouse appeir when on top of win, false to make hidden it.
*/
void				bunny_set_mouse_visibility(const t_bunny_window	*win,
							   bool			visible);

/*!
** Place the mouse cursor at the sent position, relatively to the top left corner
** of the sent window.
** \param win The window on which you wish to set the mouse position.
** \param x The horizontal position where the cursor will be moved.
** \param y The vertical position where the cursor will be moved.
*/
void				bunny_set_mouse_position_window(const t_bunny_window *win,
								int		x,
								int		y);

/*!
** Place the mouse cursor at the sent position, relatively to the top left corner
** of the desktop.
** \param x The horizontal position where the cursor will be moved.
** \param y The horizontal position where the cursor will be moved.
*/
void				bunny_set_mouse_position(int			x,
							 int			y);

/*!
** Ask to the system the focus for the current window. The system may refuse.
** \param win The window that need the focus.
*/
void				bunny_request_focus(const t_bunny_window	*win);

/*!
** Ask the system to move the window on the desktop.
** \param win The window to move.
** \param pos The position on the desktop.
*/
void				bunny_move_window(t_bunny_window		*win,
						  t_bunny_position		pos);

/*!
** Resize the sent window.
** \param win The window to resize.
** \param siz The new size of the window
*/
void				bunny_resize_window(t_bunny_window		*win,
						    t_bunny_size		siz);

#endif	/*			__LAPIN_WINDOW_H__		*/
