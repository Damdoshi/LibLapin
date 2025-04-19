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

bool				bunny_network_poll(double		timeout);
int				bunny_network_inbox(void);
int				bunny_network_outbox(void);
bool				bunny_network_read(t_bunny_communication *com);

#endif	/*			__LAPIN_PRIVATE_NETWORK_H__	*/
