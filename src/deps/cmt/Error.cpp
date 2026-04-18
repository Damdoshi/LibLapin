// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		<iostream>
#include		"Communicator.hpp"

void			bpt::NetCom::Communicator::Error(ErrorType	error)
{
  const char		*errortext[LAST_ERROR] =
    {
      "Internal error.",
      "NetCom() fail.",
      "NewConnexion fail.",
      "WriteOnNetwork fail.",
      "ReadOnNetwork fail."
    };
  std::cerr << "NetCom: " << errortext[error] << std::endl;
}
