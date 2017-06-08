// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#ifndef				__LAPIN_CPP_TOOLS_HPP__
# define			__LAPIN_CPP_TOOLS_HPP__
# include			<string.h>
# include			<ostream>

# ifndef			cascade
/*!
** "cascade" means each level of the inheritance that overload the function
** must call the previous level at its end or beginning. It is here to
** allow you to specify you need this behaviour. It won't force anything.
*/
#  define			cascade					virtual
# endif

inline t_bunny_position		operator+(const t_bunny_position	&a,
					  const t_bunny_position	&b)
{
  t_bunny_position		c;

  c.x = a.x + b.x;
  c.y = a.y + b.y;
  return (c);
}
inline t_bunny_accurate_position operator+(const t_bunny_accurate_position &a,
					   const t_bunny_accurate_position &b)
{
  t_bunny_accurate_position	c;

  c.x = a.x + b.x;
  c.y = a.y + b.y;
  return (c);
}

inline t_bunny_position		operator-(const t_bunny_position	&a,
					  const t_bunny_position	&b)
{
  t_bunny_position		c;

  c.x = a.x - b.x;
  c.y = a.y - b.y;
  return (c);
}
inline t_bunny_accurate_position operator-(const t_bunny_accurate_position &a,
					   const t_bunny_accurate_position &b)
{
  t_bunny_accurate_position	c;

  c.x = a.x - b.x;
  c.y = a.y - b.y;
  return (c);
}

inline t_bunny_position		&operator+=(t_bunny_position		&a,
					    const t_bunny_position	&b)
{
  a.x += b.x;
  a.y += b.y;
  return (a);
}
inline t_bunny_accurate_position &operator+=(t_bunny_accurate_position	&a,
					     const t_bunny_accurate_position &b)
{
  a.x += b.x;
  a.y += b.y;
  return (a);
}

inline t_bunny_position		&operator-=(t_bunny_position		&a,
					    const t_bunny_position	&b)
{
  a.x -= b.x;
  a.y -= b.y;
  return (a);
}
inline t_bunny_accurate_position &operator-=(t_bunny_accurate_position	&a,
					     const t_bunny_accurate_position &b)
{
  a.x -= b.x;
  a.y -= b.y;
  return (a);
}

template <typename		V>
inline t_bunny_position		operator+(const t_bunny_position	&a,
					  V				v)
{
  t_bunny_position		c;

  c.x = a.x + v;
  c.y = a.y + v;
  return (c);
}
template <typename		V>
inline t_bunny_position		operator-(const t_bunny_position	&a,
					  V				v)
{
  t_bunny_position		c;

  c.x = a.x - v;
  c.y = a.y - v;
  return (c);
}
template <typename		V>
inline t_bunny_position		operator*(const t_bunny_position	&a,
					  V				v)
{
  t_bunny_position		c;

  c.x = a.x * v;
  c.y = a.y * v;
  return (c);
}
template <typename		V>
inline t_bunny_position		operator/(const t_bunny_position	&a,
					  V				v)
{
  t_bunny_position		c;

  c.x = a.x / v;
  c.y = a.y / v;
  return (c);
}
template <typename		V>
inline t_bunny_position		operator%(const t_bunny_position	&a,
					  V				v)
{
  t_bunny_position		c;

  c.x = a.x % v;
  c.y = a.y % v;
  return (c);
}

template <typename		V>
inline t_bunny_accurate_position operator+(const t_bunny_accurate_position &a,
					   V				v)
{
  t_bunny_accurate_position	c;

  c.x = a.x + v;
  c.y = a.y + v;
  return (c);
}
template <typename		V>
inline t_bunny_accurate_position operator-(const t_bunny_accurate_position &a,
					   V				v)
{
  t_bunny_accurate_position	c;

  c.x = a.x - v;
  c.y = a.y - v;
  return (c);
}
template <typename		V>
inline t_bunny_accurate_position operator*(const t_bunny_accurate_position &a,
					   V				v)
{
  t_bunny_accurate_position	c;

  c.x = a.x * v;
  c.y = a.y * v;
  return (c);
}
template <typename		V>
inline t_bunny_accurate_position operator/(const t_bunny_accurate_position &a,
					   V				v)
{
  t_bunny_accurate_position	c;

  c.x = a.x / v;
  c.y = a.y / v;
  return (c);
}
template <typename		V>
inline t_bunny_accurate_position operator%(const t_bunny_accurate_position &a,
					   V				v)
{
  t_bunny_accurate_position	c;

  c.x = a.x % v;
  c.y = a.y % v;
  return (c);
}

inline std::ostream		&operator<<(std::ostream		&os,
					    const t_bunny_position	&pos)
{
  os << "(" << pos.x << ", " << pos.y << ")";
  return (os);
}

inline std::ostream		&operator<<(std::ostream		&os,
					    const t_bunny_accurate_position &pos)
{
  os << "(" << pos.x << ", " << pos.y << ")";
  return (os);
}

template<typename		Chunk1,
	 typename		Chunk2>
void				bunny_raw_copy(Chunk1			&a,
					       const Chunk2		&b)
{
  memcpy((void*)&a, (void*)&b, sizeof(Chunk1) < sizeof(Chunk2) ? sizeof(Chunk1) : sizeof(Chunk2));
}

#endif	//			__LAPIN_CPP_TOOLS_HPP__

