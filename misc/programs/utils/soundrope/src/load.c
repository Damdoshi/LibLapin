/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Sound Rope
*/

#include		"sound_rope.h"

bool			sound_rope_load(t_sound_rope	*rope)
{
  if ((rope->sprite = bunny_load_sound_sprite
       (bunny_vector_data(rope->input_files, 0, char*))) == NULL)
    return (false);
  if ((rope->target = bunny_open_configuration
       (bunny_vector_data(rope->input_files, 0, char*), NULL))
      == NULL)
    {
      bunny_delete_sound(rope->sprite);
      return (false);
    }
  return (true);
}
