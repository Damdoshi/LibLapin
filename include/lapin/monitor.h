/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2025
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

// Registers a pointer - pay attention to avoid giving local variables addresses instead
// you know you will not leave the current scope with monitoring on.
bool			_bunny_monitor_setf(t_bunny_monitored_type	type,
					    void			*data,
					    const char			*pattern,
					    ...);

# if			defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#  define		bunny_monitor_setf(data, pattern, ...)		\
  _Generic								\
  ((data),								\
   char**: _bunny_monitor_setf(BMT_STRING, data, pattern, ##__VA_ARGS__), \
   int*: _bunny_monitor_setf(BMT_INTEGER, data, pattern, ##__VA_ARGS__), \
   double*: _bunny_monitor_setf(BMT_DOUBLE, data, pattern, ##__VA_ARGS__) \
   )
# endif
# define		bunny_monitor_removef(pattern, ...)		\
  _bunny_monitor_setf(BMT_STRING, NULL, pattern, ##__VA_ARGS__)

bool			bunny_monitor_duplicate_layer(void);
bool			bunny_monitor_new_layer(void);
bool			bunny_monitor_pop_layer(void);
bool			bunny_monitor_clear_layer(void);
bool			bunny_monitor_clear(void);

void			bunny_monitor_print(int				fd,
					    const char			*glob);
void			bunny_monitor_display(t_bunny_font		*textarea,
					      const char		*glob);



#endif	/*		__LAPIN_MONITOR_H__			*/
