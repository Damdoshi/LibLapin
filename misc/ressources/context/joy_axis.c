#include		"program.h"
#include		"CONTEXT.h"

t_bunny_response	CONTEXT_joy_axis(int				joyid,
					 t_bunny_axis			axis,
					 float				value,
					 t_CONTEXT			*CONTEXT)
{
  (void)joyid;
  (void)axis;
  (void)value;
  (void)CONTEXT;
  return (GO_ON);
}

