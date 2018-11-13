/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_DRESSING_SCREEN_H__
# define		__LAPIN_DRESSING_SCREEN_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

/*
** ******************************************************************
** ************************ DRESSING SCREEN *************************
** ******************************************************************
**
** This context is a context for dressing games.
** It uses the BOX context as GUI to display buttons.
**
** It display a character on screen and boxes containing clothes associated
** to closets. It is possible to change the character clothes, to remove them
** or to change the character.
**
** A set of functions are available to do different kind of actions and this
** set may be extended. The purpose of this set is to be called throught dabsic
** managed gui boxes.
*/

/*
**
**
**
**
*/
typedef struct		s_bunny_dressing_configuration
{
  t_bunny_font		*character_font;
  t_bunny_font		*drawer_font;
}			t_bunny_dressing_configuration;

/*
**
**
**
**
*/

typedef struct		s_bunny_dressing_screen
{
  t_bunny_context_runtime_info head;
  t_bunny_map		*wardrobe;
  size_t		nbr_drawers;
  t_bunny_dressed_sprite *characters;
  size_t		nbr_characters;
  const char		_private[512];
}			t_bunny_dressing_screen;

extern const t_bunny_context gl_bunny_dressing_context;

bool		bunny_init_dressing_context_file(const char		*file,
						 t_bunny_box_system	*box,
						 t_bunny_dressing_screen *cnt);

bool		bunny_init_dressing_context_conf(t_bunny_configuration *conf,
						 t_bunny_box_system	*box,
						 t_bunny_dressing_screen *cnt);

# define	bunny_init_dressing_context(data, cnt)			\
  _Generic((data),							\
	   const char*: bunny_init_dressing_context_file,		\
	   char*: bunny_init_dressing_context_file,			\
	   t_bunny_configuration*: bunny_init_dressing_context_conf	\
	   )(data, cnt)

void		bunny_clear_dressing_context(t_bunny_dressing_screen *cnt);

#endif	/*	__LAPIN_DRESSING_SCREEN_H__			*/
