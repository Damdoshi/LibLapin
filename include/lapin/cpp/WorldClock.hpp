// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Macroboy Y

#ifndef			__BUNNY_WORLD_CLOCK_HPP__
# define		__BUNNY_WORLD_CLOCK_HPP__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif
# include		<sys/types.h>
# include		"base.hpp"

namespace		hbs
{
  // Enough for 9 billion years of game at 60FPS
  typedef uint64_t	Tick;
  
  class			WorldClock
  {
    Tick		tick;
    Tick		greatest_tick;

  public:
    operator		Tick(void) const
    {
      return (tick);
    }
    WorldClock		&operator=(Tick	t)
    {
      if (t < tick)
	tick = t;
      else if (t > tick)
	{
	  tick = t;
	  if (tick > greatest_tick)
	    greatest_tick = tick;
	}
      return (*this);
    }
    int			operator<=>(Tick	t) const
    {
      if (tick < t)
	return (-(t - tick));
      return (tick - t);
    }

    Tick		operator++(void)
    {
      *this = tick + 1;
      return (tick);
    }
    Tick		operator++(int)
    {
      Tick		tmp = tick;

      *this = tick + 1;
      return (tmp);
    }
    WorldClock		&operator+=(int	v)
    {
      if (v < 0)
	return (*this -= -v);
      *this = tick + v;
      return (*this);
    }
    WorldClock		&operator-=(int	v)
    {
      if (v < 0)
	return (*this += -v);
      if (tick < (hbs::Tick)v)
	return (*this = 0);
      *this = tick - v;
      return (*this);
    }
    void		Reset(void)
    {
      tick = greatest_tick = 0;
    }
    WorldClock(void)
      : tick(0), greatest_tick(0)
    {}
    ~WorldClock(void)
    {}
  };
}

#endif	//	__BUNNY_WORLD_CLOCK_HPP__
