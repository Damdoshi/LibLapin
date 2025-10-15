// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Macroboy Y

#ifndef			__DIM_ITERATOR_HPP__
# define		__DIM_ITERATOR_HPP__

namespace		hbs
{
  template <typename	T>
  class			DimIterator
  {
  protected:
    T			val;
    T			max;
    T			step;

  public:
    operator		bool (void) const
    {
      if (step < 0)
	return (val > max);
      return (val < max);
    }
    operator		T (void) const
    {
      if (step < 0)
	return (val > max);
      return (val);
    }
    DimIterator		&operator++(int)
    {
      val += step;
      return (*this);
    }
    DimIterator		&operator++(void)
    {
      val += step;
      return (*this);
    }

    DimIterator(T	_start,
		T	_max,
		T	_step = 1)
      : val(_start),
	max(max),
	step(_start < _max ? _step : -_step)
    {}
    ~DimIterator(void) {}
  };
}

#endif	//		__DIM_ITERATOR_HPP__
