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
  struct		WriteRequest
  {
    std::vector<char>	data;
    t_bunny_written	wt = NULL;
    void		*wtdata = NULL;

    WriteRequest(const char *start, const char *end, t_bunny_written w, void *wtd)
      : data(start, end), wt(w), wtdata(wtd)
    {}
  };
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
    t_bunny_comtype	type;
    Info		info;
    double		time;
    char		*data;
    size_t		size;
    int			errno_code = 0;

    std::vector<char>	datas;
    t_bunny_written	wt;
    void		*wtdata;

    Communication()
    {}
    Communication(t_bunny_comtype	errfunc,
		  int			errcode)
      : type(errfunc),
	errno_code(errcode)
    {}
    Communication(const Info		&_info,
		  bool			log)
      : type(log ? BCT_NETCONNECTED : BCT_NETDISCONNECTED),
	info(_info),
	datas(0)
    {}
    Communication(const Info		&_info,
		  size_t		len = 0,
		  t_bunny_written	w = NULL,
		  void			*wtd = NULL)
      : type(BCT_MESSAGE),
	info(_info),
	datas(len),
	wt(w),
	wtdata(wtd)
    {}
    Communication(const Info		&_info,
		  const char		*data,
		  size_t		len,
		  t_bunny_written	w = NULL,
		  void			*wtd = NULL)
      :	type(BCT_MESSAGE),
	info(_info),
	datas(data, data + len),
	wt(w),
	wtdata(wtd)
    {}
  };
}

#endif	//		__LAPIN_NETWORK_COMMUNICATION_HPP__
