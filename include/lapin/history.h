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
  int64_t			tick;
  size_t			length;
  void				*data;
}				t_bunny_historical_event;

t_bunny_event_history		*bunny_new_event_history(void);
void				bunny_delete_event_history(t_bunny_event_history *history);
int64_t				bunny_history_count_events_since(t_bunny_event_history *history,
								 int64_t	current_tick);
int64_t				bunny_history_count_events_of(t_bunny_event_history *history,
							      int64_t		current_tick);
int64_t				bunny_history_get_events_since(t_bunny_event_history *history,
							       int64_t		tick,
							       t_bunny_historical_event *evt);
int64_t				bunny_history_get_events_of(t_bunny_event_history *history,
							    int64_t		tick,
							    t_bunny_historical_event *evt);
bool				bunny_history_add_event(t_bunny_event_history	*history,
							int64_t			tick,
							size_t			event_len,
							void			*event);

void				bunny_history_clear_before(t_bunny_event_history *history,
							   int64_t		tick);
// Can only be achieved on server side (the only that have the full event history)
// It may be used to replay complete games.
t_bunny_event_history		*bunny_read_event_history(t_bunny_configuration	*cnf);
bool				bunny_save_event_history(t_bunny_event_history	*his,
							 t_bunny_configuration	*cnf);
// To debug save/read
bool				bunny_history_compare(t_bunny_event_history	*a,
						      t_bunny_event_history	*b);

#pragma				pack(8)
typedef struct			s_bunny_historic_state
{
  bool				key_frame; // Inserted by an authority - should not be recomputed
  int64_t			tick;
  char				data[__ZERO_LENGTH__];
}				t_bunny_historic_state;
#pragma				pack()

typedef bool			(*t_history_march)(void				*next,
						   void				*current,
						   int64_t			tick,
						   t_bunny_historical_event	*events,
						   size_t			events_size,
						   void				*data);

typedef struct			s_bunny_historic_element
{
  // A round buffer with a variable size struct - CANNOT BE ACCESSED DIRECTLY
  t_bunny_historic_state	*status;
  // The length of the status array
  size_t			status_array_length;
  // The size of a the status inside status[x].data
  size_t			status_length;

  // The tick that match the status at index last_status
  int64_t			last_tick;
  // The last key frame time
  int64_t			last_key_frame_tick;
  t_history_march		apply_history_march;
}				t_bunny_historic_element;

// Time buffer len: how many ticks can be stored. State size: the size in bytes of a complete status
t_bunny_historic_element	*bunny_new_historic_element(t_history_march		march,
							    size_t			time_buffer_len,
							    size_t			state_size);
void				bunny_delete_historic_element(t_bunny_historic_element	*elem);

// Add a key frame at the sent tick. It must be in the past.
bool				bunny_historic_element_add_key_frame(t_bunny_historic_element	*elem,
								     int64_t		tick,
								     void		*data);

// Compute all status from the last computed tick to the sent tick
int				bunny_historic_element_compute(t_bunny_historic_element	*elem,
							       int64_t			tick,
							       t_bunny_event_history	*events,
							       void			*data);

// Retrieve the status associated to the sent tick. NULL if in future or uncomputed
t_bunny_historic_state		*bunny_historic_element_get_tick(t_bunny_historic_element *elem,
								 int64_t		tick);

// Retrieve last computed status
void				*bunny_historic_element_last_status(t_bunny_historic_element *elem);

// Rewing to the sent tick, cannot go before the last key frame
bool				bunny_historic_element_rewind(t_bunny_historic_element	*elem,
							      int64_t			tick);

typedef void			(*t_bunny_historic_dump)(int64_t			tick,
							 void				*state);
void				bunny_historic_element_dump(t_bunny_historic_element	*elem,
							    t_bunny_historic_dump	dump);

#endif	/*			__LAPIN_HISTORY_H__			*/
