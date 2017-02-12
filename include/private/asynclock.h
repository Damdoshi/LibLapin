/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_ASYNCLOCK_H__
# define			__LAPIN_PRIVATE_ASYNCLOCK_H__

struct				bunny_trap
{
  struct bunny_trap		*next;
  struct bunny_trap		*prev;
  char				remove_it;
  char				__unused1;
  char				__unused2;
  char				__unused3;
  double			start_time;
  double			duration;
  t_bunny_trap_function		func;
  void				*param;
};

extern sf::Clock		gl_bunny_current_time;
extern struct bunny_trap	*gl_bunny_trap_head[4];

void				__bunny_delete_trap(struct bunny_trap	*trap,
						    t_bunny_call_order	order);

#endif	/*			__LAPIN_PRIVATE_ASYNCLOCK_H__	*/
