// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include		"lapin_private.h"

bool			bunny_start_record(t_bunny_recorder		*recorder)
{
  struct bunny_recorder	*rec = (struct bunny_recorder*)recorder;

  if (rec->recorder->start(rec->sample_per_second) == false)
    return (false);
  return (rec->recording = true);
}
