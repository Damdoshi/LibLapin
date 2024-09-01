// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#ifndef			__LAPIN_NETWORK_COMMUNICATION_HPP__
# define		__LAPIN_NETWORK_COMMUNICATION_HPP__
# include		<vector>
# include		"info.hpp"

namespace		network
{
  struct		Communication
  {
    Info		info;
    std::vector<char>	datas;

    Communication(const Info		&_info,
		  size_t		len = 0)
      : info(_info),
	datas(len)
    {}
  };
}

#endif	//		__LAPIN_NETWORK_COMMUNICATION_HPP__
