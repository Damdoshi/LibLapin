// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#ifndef			__LAPIN_NETWORK_HPP__
# define		__LAPIN_NETWORK_HPP__
# include		<sys/select.h>
# include		<poll.h>
# include		"network/descriptor.hpp"

class			Network
{
protected:
  struct pollfd		pollfd[FD_SETSIZE];
  size_t		nbr_pollfd;

std:queue<Communication>
  
public:
  
};

#endif	//		__LAPIN_NETWORK_HPP__
