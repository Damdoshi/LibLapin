/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_BACKGROUND_TASKS_H__
# define			__LAPIN_BACKGROUND_TASKS_H__

/*
** Base mechanisms
*/

typedef t_bunny_response	(*t_bunny_backtask_act)(void			*data,
							void			*bunny_loop_data);

typedef struct			s_bunny_backtask
{
  uint64_t			footprint;
  t_bunny_backtask_act		act;
  void				*data;
}				t_bunny_backtask;

size_t				bunny_backtasks_length(void);
size_t				bunny_backtasks_execute_all(void		*bunny_loop_data);
void				bunny_backtasks_set_treshold(double		ratio);
void				bunny_backtasks_clear(void);

bool				bunny_backtasks_push_task(t_bunny_backtask_act	task,
							  void			*data,
							  uint64_t		footprint);

/*
** Future
*/

typedef struct			s_bunny_future
{
  bool				available;
  union
  {
    t_bunny_configuration	*configuration;
    t_bunny_picture		*picture;
    t_bunny_pixelarray		*pixelarray;
    t_bunny_sprite		*sprite;
    t_bunny_sound		*sound;
    t_bunny_effect		*effect;
    t_bunny_music		*music;
    t_bunny_sound_sprite	*sound_sprite;
    void			*data;
  }
}				t_bunny_future;

#endif	/*			__LAPIN_BACKGROUND_TASKS_H__			*/
