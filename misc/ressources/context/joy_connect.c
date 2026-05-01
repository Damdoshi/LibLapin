#include		"program.h"
#include		"CONTEXT.h"

t_bunny_response	CONTEXT_joy_connect(t_bunny_event_state		state,
					    int				joyid,
					    const t_bunny_joystick	*joystick,
					    t_CONTEXT			*CONTEXT)
{
  (void)state;
  (void)joyid;
  (void)joystick;
  (void)CONTEXT;
  return (GO_ON);
}
