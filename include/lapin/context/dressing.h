/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

#ifndef		__LAPIN_DRESSING_SCREEN_H__
# define	__LAPIN_DRESSING_SCREEN_H__
# if		!defined(__LAPIN_H__)
#  error	You cannot include this file directly.
# endif

/*
** ******************************************************************
** ************************ DRESSING SCREEN *************************
** ******************************************************************
**
** This context is a context for dressing games.
*/

typedef struct	s_bunny_dressing
{
  t_bunny_font	*dressing_name;
  t_bunny_sprite **clothes;
  t_bunny_sprite **on_character_clothes;
  size_t	nbr_clothes;
  t_bunny_position clothe_position;
  int		depth;
}		t_bunny_dressing;

typedef struct	s_bunny_dressing_character
{
  t_bunny_font	*character_name;
  t_bunny_picture *background;
  t_bunny_sprite *character;
  t_bunny_dressing *dressing;
  t_bunny_sprite **displayed_clothes;
  size_t	nbr_dressing; // Both size of dressing and displayed_clothes
}		t_bunny_dressing_character;

typedef struct	s_bunny_dressing_screen
{
  t_bunny_context_runtime_info head;
  t_bunny_dressing_character *characters;
  size_t	nbr_characters;
  const char	_private[512];
}		t_bunny_dressing_screen;

extern const t_bunny_context gl_bunny_dressing_context;

bool		bunny_init_dressing_context_file(const char	*file,
						 t_bunny_dressing_screen *cnt);

bool		bunny_init_dressing_context_conf(t_bunny_configuration *conf,
						 t_bunny_dressing_screen *cnt);

# define	bunny_init_dressing_context(data, cnt)			\
  _Generic((data),							\
	   const char*: bunny_init_dressing_context_file,		\
	   char*: bunny_init_dressing_context_file,			\
	   t_bunny_configuration*: bunny_init_dressing_context_conf	\
	   )(data, cnt)

void		bunny_clear_dressing_context(t_bunny_dressing_screen *cnt);

#endif	/*	__LAPIN_DRESSING_SCREEN_H__			*/
