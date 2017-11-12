/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

/*!
** \file monitor.h
** A small debugging tool that allow variable registration and display.
*/

#ifndef			__LAPIN_MONITOR_H__
# define		__LAPIN_MONITOR_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

/*!
** Specify the type of the variable you sent the address.
*/
typedef enum		e_bunny_monitored_type
  {
    BMT_STRING,
    BMT_INTEGER,
    BMT_DOUBLE
  }			t_bunny_monitored_type;

/*!
** Add a value into the debug monitor. No copies are done, neither for the name
** nor the pointer!
** \param name The name of the variable you sent.
** \param type The type of the variable. Serve to display it well.
** \param ptr The address of the variable you want to monitor:
**  char*
**  int*,
**  double*
** \return True if everything went well.
*/
bool			_bunny_add_monitored_value(const char		*name,
						   t_bunny_monitored_type type,
						   const void		*ptr);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ == 201112L
/*!
** Add a value into the debug monitor. No copies are done, neither for the name
** nor the pointer!
** \param name The name of the variable you sent.
** \param ptr The address of the variable you want to monitor:
**  char*
**  int*,
**  double*
** \return True if everything went well.
*/
#  define		bunny_add_monitored_value(name, ptr)		\
  _Generic								\
  ((ptr),								\
   char*: _bunny_add_monitored_value(name, BMT_STRING, ptr),		\
   int*: _bunny_add_monitored_value(name, BMT_INTEGER, ptr),		\
   double*: _bunny_add_monitored_value(name, BMT_DOUBLE, ptr)		\
   )
# endif

/*!
** Remove a monitor that was inserted into the system.
** \param name The name of the monitored value you want to remove. NULL to remove them
** all.
** \return True if it was found and removed.
*/
bool			bunny_remove_monitored_value(const char		*name);

/*!
** Display inside the sent text area monitored value(s).
** Space may be insufficient. Tweaking the textarea to display whatever you
** like is on your charge.
** Use the bunny_big_buffer.
** \param textarea The area where the value(s) will be displayed.
** \param n The name of the value to display or NULL to display all.
** You can also use * as last character to display all values associated with
** a name starting with what's before the *.
*/
void			bunny_display_monitored_value(t_bunny_font	*textarea,
						      const char	*n);

/*!
** Write at the sent file descriptor monitored value(s).
** Use the bunny_big_buffer.
** \param fd The file descriptor where to write
** \param n The name of the value to print or NULL to print all.
** You can also use * as last character to print all values associated with
** a name starting with what's before the *.
** \return The amount of bytes written or -1 on error.
*/
ssize_t			bunny_print_monitored_value(int			fd,
						    const char		*n);
  
#endif	/*		__LAPIN_MONITOR_H__			*/
