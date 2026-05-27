#include		"program.h"
#include		"CONTEXT.h"

t_bunny_response	CONTEXT_display(t_CONTEXT	*CONTEXT)
{
  ///
  for (size_t i_ = 0; CONTEXT->program->window[i_]; ++i_)
    {
      bunny_blit(&CONTEXT->program->window[i_]->buffer, CONTEXT->program->screen[i_], NULL);
      bunny_display(CONTEXT->program->window[i_]);
    }
  return (GO_ON);
}

