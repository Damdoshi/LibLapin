/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_CONTAINER_H__
# define			__LAPIN_CONTAINER_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<stdarg.h>

typedef bool			(*t_bunny_constructor)(void		*data,
						       void		*add);
typedef bool			(*t_bunny_destructor)(void		*data);

# include			"container/stack.h"
# include			"container/astack.h"
# include			"container/queue.h"
# include			"container/list.h"
# include			"container/map.h"
# include			"container/vector.h"
# include			"container/pool.h"
# include			"container/bitfield.h"


#endif	/*			__LAPIN_CONTAINER_H__			*/
