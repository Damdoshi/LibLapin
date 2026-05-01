#include		"program.h"
#include		"CONTEXT.h"

t_bunny_response	CONTEXT_event_response(const t_bunny_event	*event,
					       t_CONTEXT		*CONTEXT)
{
  (void)event;
  (void)CONTEXT;
  return (GO_ON);
}
