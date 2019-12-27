/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Sound Rope
** Keep several sounds in bondage in a single file
*/

#ifndef			__SOUND_ROPE_H__
# define		__SOUND_ROPE_H__
# include		<lapin.h>
# include		<assert.h>
# include		<stdio.h>
# include		<string.h>

typedef struct		s_sound_rope
{
  t_bunny_window	*win;
  int			index;
  double		zoom;

  t_bunny_vector	*input_files;
  t_bunny_vector	*input_effects;
  char			*output_sound_file;
  char			*output_configuration_file;
  t_bunny_configuration_type output_format;
  t_bunny_effect	*output_effect;
  double		silence_separator;
  int			cli_mode;
  t_bunny_configuration	*target;
  t_bunny_sound_sprite	*sprite;
}			t_sound_rope;

/* From several files to a single one */
bool			sound_rope_mux_load(t_sound_rope		*rope);
bool			sound_rope_mux_generate(t_sound_rope		*rope);

/* Load a single file */
bool			sound_rope_load(t_sound_rope			*rope);

/* GUI */

/* Save */
bool			sound_rope_save(t_sound_rope			*rope);

#endif	/*		__SOUND_ROPE_H__				*/
