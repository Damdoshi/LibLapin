/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
**
**
** Bibliotheque Lapin
*/


#ifndef		__VALLOCK_HPP__
# define	__VALLOCK_HPP__

template <typename T>
class		ValLock
{
private:
  T		&ptr;
  T		val;

public:
  operator	T (void) const
  {
    return (val);
  }
  ValLock(T	&p)
    : ptr(p),
      val(p)
  {}
  ~ValLock(void)
  {
    ptr = val;
  }
};

#endif	//	__VALLOCK_HPP__
