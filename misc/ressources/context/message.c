#include		"program.h"
#include		"CONTEXT.h"

t_bunny_response	CONTEXT_message(int		fd,
					const void	*buffer,
					size_t		size,
					t_CONTEXT	*CONTEXT)
{
  (void)fd;
  (void)buffer;
  (void)size;
  (void)CONTEXT;
  return (GO_ON);
}

