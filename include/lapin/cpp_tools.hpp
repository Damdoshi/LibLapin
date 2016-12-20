// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#ifndef				__LAPIN_CPP_TOOLS_HPP__
# define			__LAPIN_CPP_TOOLS_HPP__

/*!
** "cascade" means each level of the inheritance that overload the function
** must call the previous level at its end or beginning. It is here to
** allow you to specify you need this behaviour. It won't force anything.
*/
# define			cascade					virtual

template<typename		Vector>
inline Vector			operator+(const Vector			&a,
					  const Vector			&b)
{
  Vector			c;

  c.x = a.x + b.x;
  c.y = a.y + b.y;
  return (c);
}

template<typename		Vector>
inline Vector			operator-(const Vector			&a,
					  const Vector			&b)
{
  Vector			c;

  c.x = a.x + b.x;
  c.y = a.y + b.y;
  return (c);
}

template<typename		Vector>
inline Vector			&operator+=(Vector			&a,
					    const Vector		&b)
{
  a.x += b.x;
  a.y += b.y;
  return (a);
}

template<typename		Vector>
inline Vector			&operator-=(Vector			&a,
					    const Vector		&b)
{
  a.x -= b.x;
  a.y -= b.y;
  return (a);
}

#endif	//			__LAPIN_CPP_TOOLS_HPP__
