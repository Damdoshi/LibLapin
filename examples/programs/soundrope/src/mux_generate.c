/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Sound Rope
*/

#include		"sound_rope.h"

bool			sound_rope_mux_generate(t_sound_rope	*rope)
{
  t_bunny_configuration	*cnf;
  int			index;
  size_t		i;

  if ((rope->target = cnf = bunny_new_configuration()) == NULL)
    return (false);
  assert(bunny_configuration_setf(cnf, rope->output_sound_file, "RessourceFile"));

  for (index = 0, i = 0; i < rope->input_effects->nmemb; ++i)
    {
      t_bunny_effect	*oeff = rope->output_effect;
      t_bunny_effect	*ieff = bunny_vector_data(rope->input_effects, i, t_bunny_effect*);
      char		*str;
      int		off;
      int		start;

      if ((str = strrchr(bunny_vector_data(rope->input_files, i, char*), '.')) != NULL)
	*str = '\0';
      str = bunny_vector_data(rope->input_files, i, char*);
      assert(bunny_configuration_setf(cnf, (double)index / SAMPLE_PER_SECONDS,
				      "Slices.%s.Index", str));
      start = index;

      off = ieff->sample_per_second * ieff->duration;
      memcpy(&oeff->sample[index], ieff->sample, off);
      index += off;

      off = rope->silence_separator * SAMPLE_PER_SECONDS;
      memset(&oeff->sample[index], 0, off);
      index += off;

      assert(bunny_configuration_setf(cnf, ((double)(index - start)) / SAMPLE_PER_SECONDS,
				      "Slices.%s.Duration", str));

      assert(bunny_configuration_setf(cnf, 0, "Slices.%s.ActiveStart", str));
      assert(bunny_configuration_setf(cnf, ((double)(index - start)) / SAMPLE_PER_SECONDS,
					    "Slices.%s.ActiveDuration", str));

      if (bunny_which_format(bunny_vector_data(rope->input_files, i, char*)) != BC_CUSTOM)
	{
	  assert(bunny_configuration_setf
		 (cnf,
		  bunny_vector_data(rope->input_effects, i, t_bunny_sound*)->volume,
		  "Slices.%s.Volume", str)
		 );
	  assert(bunny_configuration_setf
		 (cnf,
		  bunny_vector_data(rope->input_effects, i, t_bunny_sound*)->pitch,
		  "Slices.%s.Pitch", str)
		 );
	  assert(bunny_configuration_setf
		 (cnf,
		  bunny_vector_data(rope->input_effects, i, t_bunny_sound*)->loop ? 1 : 0,
		  "Slices.%s.Loop", str)
		 );
	  assert(bunny_configuration_setf
		 (cnf,
		  bunny_vector_data(rope->input_effects, i, t_bunny_sound*)->position[0],
		  "Slices.%s.Position[0]", str)
		 );
	  assert(bunny_configuration_setf
		 (cnf,
		  bunny_vector_data(rope->input_effects, i, t_bunny_sound*)->position[1],
		  "Slices.%s.Position[1]", str)
		 );
	  assert(bunny_configuration_setf
		 (cnf,
		  bunny_vector_data(rope->input_effects, i, t_bunny_sound*)->position[2],
		  "Slices.%s.Position[2]", str)
		 );
	  assert(bunny_configuration_setf
		 (cnf,
		  bunny_vector_data(rope->input_effects, i, t_bunny_sound*)->attenuation,
		  "Slices.%sAttenuation", str)
		 );
	}
    }
  assert(bunny_save_effect(rope->output_effect, rope->output_sound_file));
  assert(bunny_save_configuration(BC_DABSIC, rope->output_configuration_file, rope->target));
  if ((rope->sprite = bunny_read_sound_sprite(rope->target)) == NULL)
    return (false);
  return (true);
}

