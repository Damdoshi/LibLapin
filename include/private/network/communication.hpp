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
  class			IOException : public std::runtime_error
  {
  public:
    IOException(const std::string &str) : runtime_error(str) {}
      ~IOException() {}
  };

  
  template <typename	T>
  struct		Pair
  {
    Info const		&info;
    T const		&data;
  };

  struct		Communication
  {
    enum		Type
      {
	CONNECTED,
	DISCONNECTED,
	DATA
      };

    Info		info;
    Type		type;
    std::vector<char>	datas;

    Communication(const Info		&_info,
		  bool			log)
      : info(_info),
	type(log ? CONNECTED : DISCONNECTED),
	datas(0)
    {}
    Communication(const Info		&_info,
		  size_t		len = 0)
      : info(_info),
	type(DATA),
	datas(len)
    {}
    Communication(const Info		&_info,
		  const char		*data,
		  size_t		len)
      : info(_info),
	type(DATA),
	datas(data, data + len)
    {}		  
  };
}

#endif	//		__LAPIN_NETWORK_COMMUNICATION_HPP__
