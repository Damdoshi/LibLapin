// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Macroboy Y

#ifndef		BUNNY_RANGED_VALUE_HPP
# define	BUNNY_RANGED_VALUE_HPP
# if		!defined(__LAPIN_H__)
#  error	You cannot include this file directly.
# endif
# include	<string>
# include	<iostream>
# include	"base.hpp"
# include	"errors/NotInRange.hpp"

namespace	hbs
{
  enum class	ExcessStrategy
    {
      THROW,
      LOOP,
      CLAMP
    };
  // [Min; Max[
  template <typename T, T Min, T Max, ExcessStrategy ES = ExcessStrategy::THROW>
  class		RangedValue
  {
  lprivate:
    T		val;

  public:
    linline operator T (void) const
    {
      return (val);
    }
    linline const T *operator&(void) const
    {
      return (&val);
    }
    linline T operator=(const T		&i)
    {
      if (i < Min)
	{
	  if (ES == ExcessStrategy::THROW)
	    throw NotInRange(i, Min, Max);
	  if (ES == ExcessStrategy::CLAMP)
	    return (val = Min);
	  return (*this = Max - ((Min - i) % (Max - Min)));
	}
      if (i >= Max)
	{
	  if (ES == ExcessStrategy::THROW)
	    throw NotInRange(i, Min, Max);
	  if (ES == ExcessStrategy::CLAMP)
	    return (val = Max - 1);
	  return (val = ((i - Max) % (Max - Min) + Min));
	}
      return (val = i);
    }
    linline T operator+(const T		&i) const
    {
      return (val + i);
    }
    linline T operator-(const T		&i) const
    {
      return (val - i);
    }
    linline T operator*(const T		&i) const
    {
      return (val * i);
    }
    linline T operator/(const T		&i) const
    {
      return (val / i);
    }
    linline T operator%(const T		&i) const
    {
      return (val % i);
    }
    linline auto operator+(const RangedValue<T, Min, Max, ES> &i) const
    {
      return (RangedValue<T, Min, Max, ES>{val + i.val});
    }
    linline auto operator-(const RangedValue<T, Min, Max, ES> &i) const
    {
      return (RangedValue<T, Min, Max, ES>{val - i.val});
    }
    linline auto operator*(const RangedValue<T, Min, Max, ES> &i) const
    {
      return (RangedValue<T, Min, Max, ES>{val * i.val});
    }
    linline auto operator/(const RangedValue<T, Min, Max, ES> &i) const
    {
      return (RangedValue<T, Min, Max, ES>{val / i.val});
    }
    linline auto operator%(const RangedValue<T, Min, Max, ES> &i) const
    {
      return (RangedValue<T, Min, Max, ES>{val % i.val});
    }
    linline auto &operator++(void)
    {
      *this = val + 1;
      return (*this);
    }
    linline auto operator++(int)
    {
      auto tmp{val};
	    
      ++(*this);
      return (tmp);
    }
    linline auto &operator--(void)
    {
      *this = val - 1;
      return (*this);
    }
    linline auto operator--(int)
    {
      auto tmp{val};

      --(*this);
      return (tmp);
    }
    
    linline auto &operator+=(const T	&i)
    {
      *this = val + i;
      return (*this);
    }
    linline auto &operator-=(const T	&i)
    {
      *this = val - i;
      return (*this);
    }
    linline auto &operator*=(const T	&i)
    {
      *this = val * i;
      return (*this);
    }
    linline auto &operator/=(const T	&i)
    {
      *this = val / i;
      return (*this);
    }
    linline auto &operator%=(const T	&i)
    {
      *this = val % i;
      return (*this);
    }
    linline operator std::string (void) const
    {
      std::stringstream ss;

      ss << val;
      return (ss.str());
    }

    RangedValue(void)
    {
      val = 0;
    }
    RangedValue(const T			&v)
    {
      *this = v;
    }
    ~RangedValue(void) {}
  };
}

#endif	//	BUNNY_RANGED_VALUE_HPP
