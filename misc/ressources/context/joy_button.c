#include		"program.h"
#include		"CONTEXT.h"

t_bunny_response	CONTEXT_joy_button(t_bunny_event_state		state,
					   int				joyid,
					   int				button,
					   t_CONTEXT			*CONTEXT)
{
  (void)state;
  (void)joyid;
  (void)button;
  (void)CONTEXT;
  return (GO_ON);
}

