#include			"program.h"
#include			"CONTEXT.h"

t_bunny_response		CONTEXT_click(t_bunny_event_state	state,
					      t_bunny_mouse_button	but,
					      t_CONTEXT			*CONTEXT)
{
  (void)state;
  (void)but;
  (void)CONTEXT;
  return (GO_ON);
}

