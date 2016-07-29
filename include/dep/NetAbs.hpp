// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// LibLapin

#ifndef				__NETABS_HPP__
# define			__NETABS_HPP__
# ifdef				_WIN32
# include			"NetWin.hpp"

namespace			bpt
{
  namespace			NetAbs
  {
    class			NetAbs : public NetWin
    {};
  }
}

# else
# include			"NetUnix.hpp"

namespace			bpt
{
  namespace			NetAbs
  {
    class			NetAbs : public NetUnix
    {};
  }
}

# endif	//			_WIN32
#endif	//			__NETABS_HPP__
