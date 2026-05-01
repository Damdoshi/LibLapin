#include		"program.h"
#include		"CONTEXT.h"

t_bunny_response	CONTEXT_connect(int			fd,
					t_bunny_event_state	state,
					t_CONTEXT		*CONTEXT)
{
  (void)fd;
  (void)state;
  (void)CONTEXT;
  return (GO_ON);
}

