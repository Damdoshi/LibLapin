// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Macroboy Y

#ifndef		__NOT_IN_RANGE_HPP__
# define	__NOT_IN_RANGE_HPP__
# if		!defined(__LAPIN_H__)
#  error	You cannot include this file directly.
# endif
# include	<sstream>
# include	<exception>

namespace	hbs
{
  template <typename T>
  class		NotInRange : public std::logic_error
  {
  lprivate:
    std::string	msg;
    
  public:
    const char	*what(void) const throw()
    {
      return (msg.c_str());
    }
    NotInRange(T  		v,
	       T		min,
	       T		max) throw()
      : logic_error(typeid(*this).name())
    {
      std::stringstream		ss;

      ss << "Value " << v << " is not in [" << min << "; " << max << "["
	 << std::endl;
      msg = ss.str();
    }
    virtual ~NotInRange(void) {}
  };
}

#endif
