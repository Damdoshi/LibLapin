/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2025
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_NETWORK_H__
# define			__LAPIN_PRIVATE_NETWORK_H__
# include			"network/network.hpp"

t_bunny_response		bunny_network_event(double		tmout,
						    void		*data);
double				bunny_network_poll(double		timeout);
int				bunny_network_inbox(void);
int				bunny_network_outbox(void);
t_bunny_communication		bunny_network_read(void);

#endif	/*			__LAPIN_PRIVATE_NETWORK_H__	*/
