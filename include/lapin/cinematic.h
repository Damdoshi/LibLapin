/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
**
** Bibliothèque Lapin
*/

#ifndef			__LAPIN_CINEMATIC_H__
# define		__LAPIN_CINEMATIC_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

typedef struct		s_bunny_cinematic
{
  t_bunny_clipable	clipable;
  const size_t		_private[4];

  struct {
    double		music;
    double		voice;
    double		effect;
  }			volumes;

  t_bunny_map		*pictures;
  t_bunny_map		*effects;
  t_bunny_map		*musics;
  t_bunny_map		*voices;
  t_bunny_map		*fonts;
  t_bunny_map		*texts;
  t_bunny_map		*commands;

  bool			repeat;
  // Bunny sequence
  t_bunny_configuration	*program;
  size_t		current_command;
  void			*stack_frame;
  char			extended_data[512]; // For your own commands.
}			t_bunny_cinematic;

// Valeurs de retours possibles:
// NULL pour aller à l'instruction suivante
// ".stay" pour rester sur l'instruction courante
// ".back" pour revenir à l'instruction d'avant
// ".skip" pour sauter la prochaine instruction
// ".reset" pour recommencer à zéro
// Autre chose pour sauter à un label, précédé d'un "!" s'il s'agit d'un
// appel de fonction, sinon c'est un simple saut.
typedef char		*(*t_bunny_cinematic_command)(t_bunny_cinematic	*cin,
						      int		argc,
						      t_bunny_configuration **argv,
						      const t_bunny_event *event,
						      double		elapsed);

t_bunny_cinematic	*bunny_load_cinematic_wh(const char		*file,
						 unsigned int		width,
						 unsigned int		height,
						 const char		*language);
t_bunny_cinematic	*bunny_load_cinematic(const char		*file,
					      const char		*language);

t_bunny_cinematic	*bunny_read_cinematic_wh(t_bunny_configuration	*cnf,
						 unsigned int		width,
						 unsigned int		height,
						 const char		*language);
t_bunny_cinematic	*bunny_read_cinematic(t_bunny_configuration	*cnf,
					      const char		*language);

t_bunny_response	bunny_cinematic(t_bunny_cinematic		*cin,
					const t_bunny_event		*event,
					double				elapsed);

void			bunny_delete_cinematic(t_bunny_cinematic	*cin);

#endif	/*		__LAPIN_CINEMATIC_H__		*/
