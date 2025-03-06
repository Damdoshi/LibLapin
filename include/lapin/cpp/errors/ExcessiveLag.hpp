// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Macroboy Y

#ifndef				__BUNNY_EXCESSIVE_LAG_HPP__
# define			__BUNNY_EXCESSIVE_LAG_HPP__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<string>
# include			<sstream>

namespace			hbs
{
  class				ExcessiveLag : public std::range_error
  {
  lprivate:
    std::string			msg;

  public:
    const char			*what(void) const throw()
    {
      return (msg.c_str());
    }
    ExcessiveLag(Tick		world_tick,
		 Tick		last_known_frame,
		 Tick		oldest_tick,
		 size_t		capacity) throw()
      : range_error("")
    {
      std::stringstream		ss;

      ss << "Cannot rewind object [with capacity = " << capacity << "] "
	 << "with last known frame tick " << last_known_frame << " "
	 << "and oldest known frame tick " << oldest_tick << " "
	 << "to world hour " << world_tick
	 << std::endl;
      msg = ss.str();
    }
    virtual ~ExcessiveLag(void) {}
  };
}

#endif

