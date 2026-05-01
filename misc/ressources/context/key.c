#include			"program.h"
#include			"CONTEXT.h"

t_bunny_response		CONTEXT_key(t_bunny_event_state	state,
					    t_bunny_keysym	sym,
					    t_CONTEXT		*CONTEXT)
{
  (void)state;
  (void)sym;
  (void)CONTEXT;
  return (GO_ON);
}
