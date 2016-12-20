// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// LibLapin

#include		"lapin_private.h"

#ifdef			LAPIN_ALLOCATOR_DEACTIVATED
# undef			bunny_malloc
# undef			bunny_calloc
# undef			bunny_realloc
# undef			bunny_free
#endif

extern int		memory_check;

void			bunny_set_memory_check(bool		chk)
{
  memory_check = chk;
}

