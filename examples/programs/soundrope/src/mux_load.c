/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Sound Rope
*/

#include		<stdio.h>
#include		"sound_rope.h"

bool			sound_rope_mux_load(t_sound_rope		*rope)
{
  t_bunny_list		*ieff;
  double		full_duration;
  t_bunny_effect	*eff;
  size_t		i;

  full_duration = 0;
  assert(ieff = bunny_new_list());
  for (i = 0; i < rope->input_files->nmemb; ++i)
    if ((eff = bunny_load_effect(bunny_vector_data(rope->input_files, i, char*))) == NULL)
      {
	fprintf(stderr, "Cannot open file %s.\n",
		bunny_vector_data(rope->input_files, i, char*));
	return (false);
      }
    else
      {
	full_duration += eff->duration + rope->silence_separator;
	assert(bunny_list_push_back(ieff, eff));
      }
  assert(rope->input_effects = bunny_list_tie(ieff, char*));

  bunny_delete_list(ieff);
  full_duration += rope->silence_separator;
  if ((rope->output_effect = bunny_new_effect(full_duration)) == NULL)
    {
      fprintf(stderr, "Not enough memory to handle all those files.\n");
      return false;
    }
  return true;
}
