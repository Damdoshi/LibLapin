/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** Bibliotheque Lapin
** History for objects in network game.
** Made with Allan and Macroboy Y in mind.
*/

#ifndef				__LAPIN_HISTORY_H__
# define			__LAPIN_HISTORY_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

typedef void			t_bunny_event_history;
typedef struct			s_bunny_historical_event
{
  uint64_t			tick;
  uint64_t			length;
  void				*data;
}				t_bunny_historical_event;

t_bunny_event_history		*bunny_new_event_history(void);
void				bunny_delete_event_history(t_bunny_event_history *history);
uint64_t			bunny_history_count_events(t_bunny_event_history *history,
							   uint64_t		current_tick);
uint64_t			bunny_history_get_events(t_bunny_event_history	*history,
							 uint64_t		tick,
							 t_bunny_historical_event *evt);
bool				bunny_history_add_event(t_bunny_event_history	*history,
							uint64_t		tick,
							size_t			event_len,
							void			*event);

typedef struct			s_bunny_historic_state
{
  bool				key_frame; // Inserted by an authority - should not be recomputed
  double			seconds;
  uint64_t			tick;
  char				data[__ZERO_LENGTH__];
}				t_bunny_historic_state;
# define			bunny_historic_state_get_data(state, type)	\
  ((type*)(&(state)->data[0]))

typedef void			(*t_history_march)(t_bunny_historic_state	*next,
						   t_bunny_historic_state	*current,
						   void				*data);

typedef struct			s_bunny_historic_element
{
  t_bunny_historic_state	*status;
  size_t			status_array_length;
  size_t			status_length;
  size_t			last_status;

  // The last registered status time
  uint64_t			last_tick;
  // The last key frame time
  uint64_t			last_key_frame_tick;
  // The last currently computed tick
  uint64_t			last_computed_tick;

  t_history_march		apply_history_march;
}				t_bunny_historic_element;

t_bunny_historic_element	*bunny_new_historic_element(t_history_march		march,
							    size_t			time_buffer_len,
							    size_t			state_size);
void				bunny_delete_historic_element(t_bunny_historic_element	*elem);

bool				bunny_history_add_key_frame(t_bunny_historic_element	*elem,
							    void			*data);
void				bunny_history_compute(t_bunny_historic_element		*elem,
						      t_bunny_event_history		*events,
						      uint64_t				tick);
bool				bunny_historic_element_rewind(t_bunny_historic_element	*elem,
							      uint64_t			tick);

#endif	/*			__LAPIN_HISTORY_H__			*/
