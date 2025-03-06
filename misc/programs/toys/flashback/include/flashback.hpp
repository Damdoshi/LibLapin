
#ifndef			FLASHBACK_HPP
# define		FLASHBACK_HPP
# include		<vector>
# include		"lapin.h"

using			bapos = t_bunny_accurate_position;
using			bpos = t_bunny_position;

struct			Flashback;

class			BallBase : public hbs::Serialisable
{
public:
  bapos			position = {0, 0};
  bapos			speed = {0, 0};
  bapos			size = {2, 2};
  unsigned int		color;

  BallBase		&operator=(const BallBase &bb)
  {
    if (this == &bb)
      return (*this);
    position = bb.position;
    speed = bb.speed;
    size = bb.size;
    color = bb.color;
    return (*this);
  }
  
  std::ostream		&Write(std::ostream	&os) const
  {
    os << "["
       << position.x << ","
       << position.y << ","
       << speed.x << ","
       << speed.y << ","
       << size.x << ","
       << size.y << ","
       << color
       << "]";
    return (os);
  }

  BallBase(const Flashback &fb);
  
  BallBase(void) {}
  BallBase(const BallBase &bb)
  {
    *this = bb;
  }
  virtual ~BallBase(void) {}
};

class		BouncerBase : public BallBase
{
public:
  BouncerBase	&operator=(const BouncerBase &bb)
  {
    BallBase::operator=(bb);
    return (*this);
  }
  BouncerBase(void) = default;
  BouncerBase(const BouncerBase &bb)
  {
    *this = bb;
  }
  BouncerBase(const Flashback	&fb,
	      unsigned int	col,
	      int c);
  virtual ~BouncerBase(void) {}
};
  
using Ball = hbs::Frame<BallBase>;
using Bouncer = hbs::Frame<BouncerBase>;

struct			Flashback
{
  t_bunny_window	*window;
  hbs::WorldClock	wclock;
  std::vector<Ball>	balls;
  std::vector<Bouncer>	bouncers;
  hbs::Tick		oldest;
};

#endif	//		FLASHBACK_HPP
