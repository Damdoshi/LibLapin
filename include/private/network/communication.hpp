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

# define		istcp(a)					\
  ((a) != BP_UDP_IMMEDIATE && (a) != BP_UDP_RELIABLE)
# define		isudp(a) (!istcp(a))
# define		isimmediate(a)					\
  ((a) == BP_UDP_IMMEDIATE || (a) == BP_TCP_IMMEDIATE || (a) == BP_UDP_RELIABLE)

namespace		network
{
  using Protocol = t_bunny_protocol;

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
    Info		info;
    T const		&data;
  };

  struct		Communication
  {
    t_bunny_comtype	type = BCT_NOTHING;
    Info		info;
    double		time = 0;
    char		*data = NULL;
    size_t		size = 0;
    int			errno_code = 0;

    bool		free_data = true;
    t_bunny_written	wt = NULL;
    void		*wtdata = NULL;

    void		DoNotFreeData(void)
    {
      free_data = false;
    }

    Communication	&operator=(Communication	&&com)
    {
      if (this == &com)
	return (*this);
      if (free_data && data != NULL)
	bunny_free(data);
      type = com.type;
      info = com.info;
      time = com.time;
      data = com.data;
      size = com.size;
      errno_code = com.errno_code;
      free_data = com.free_data;
      com.free_data = false;
      com.data = NULL;
      wt = com.wt;
      wtdata = com.wtdata;
      return (*this);
    }

    Communication(void)
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
	time(bunny_get_current_time())
    {}
    Communication(const Info		&_info,
		  size_t		len = 0,
		  t_bunny_written	w = NULL,
		  void			*wtd = NULL)
      : type(BCT_MESSAGE),
	info(_info),
	wt(w),
	wtdata(wtd)
    {
      if (len)
	if ((data = (char*)bunny_malloc(len)) == NULL)
	  throw std::bad_alloc();
      size = len;
    }
    Communication(const Info		&_info,
		  const char		*dat,
		  size_t		len,
		  t_bunny_written	w = NULL,
		  void			*wtd = NULL)
      :	type(BCT_MESSAGE),
	info(_info),
	wt(w),
	wtdata(wtd)
    {
      if (len)
	{
	  if (!(data = (char*)bunny_malloc(len)))
	    throw std::bad_alloc();
	  memcpy(data, dat, len);
	}
      size = len;
    }
    ~Communication(void)
    {
      // Do NOT free data if it is data for user. The user must do it.
      if (free_data && data != NULL)
	bunny_free(data);
    }
  };
}

#endif	//		__LAPIN_NETWORK_COMMUNICATION_HPP__
