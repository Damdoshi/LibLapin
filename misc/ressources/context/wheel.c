#include			"program.h"
#include			"CONTEXT.h"

t_bunny_response		CONTEXT_wheel(int			wheel,
					      int			delta,
					      t_CONTEXT			*CONTEXT)
{
  (void)wheel;
  (void)delta;
  (void)CONTEXT;
  return (GO_ON);
}
