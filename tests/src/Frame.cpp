// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2023
//
// Macroboy Y

#include		<assert.h>
#include		<iostream>
#include		"Frame.hpp"

hbs::WorldClock		wclock;

class			BaseStuff : public hbs::Serialisable
{
private:
  std::string		name = "";
  double		reals = 0;
    int			integers = 0;

  std::ostream		&Write(std::ostream	&os) const
  {
    os << "{'name': '" << name << "', 'reals':" << reals << ", 'integers': " << integers << "}";
    return (os);
  }

public:
  void			DoStuff(int		x)
  {
    name = name + name;
    reals *= x;
    integers += x;
  }

  BaseStuff		&operator=(const BaseStuff	&o)
  {
    if (this == &o)
      return (*this);
    name = o.name;
    reals = o.reals;
    integers = o.integers;
    return (*this);
  }
  BaseStuff(void) {}
  BaseStuff(const BaseStuff &s)
  {
    *this = s;
  }

  BaseStuff(const std::string &str, double a, int b)
    : name(str)
    , reals(a)
    , integers(b)
  {}
  virtual ~BaseStuff(void) {}
};

template <typename	Storage>
class			FrameFinaliser : public hbs::Frame<Storage>
{
public:
  FrameFinaliser() : hbs::Frame<Storage>(wclock, std::cerr) {}
  FrameFinaliser(const Storage &sto) : hbs::Frame<Storage>(wclock, std::cerr, sto) {}
  FrameFinaliser(const FrameFinaliser &l) : hbs::Frame<Storage>(*(Storage*)&l) {}
  template <typename ...Arg>
  FrameFinaliser(Arg... args) : hbs::Frame<Storage>(wclock, std::cerr, std::forward<Arg>(args)...) {}
  ~FrameFinaliser(void) {}
};

using Stuff = FrameFinaliser<BaseStuff>;

int			main(void)
{
  Stuff			stuff("a", 2.0, 4);
  BaseStuff		*bstuff;

  std::cout << wclock << std::endl;
  bstuff = stuff.Now();
  std::cout << bstuff << std::endl << *bstuff << std::endl;
  bstuff->DoStuff(2);
  bstuff = stuff.Now();
  std::cout << bstuff << std::endl << *bstuff << std::endl;
  
  wclock++;
  std::cout << wclock << std::endl;
  bstuff = stuff.Now();
  std::cout << bstuff << std::endl << *bstuff << std::endl;
  bstuff->DoStuff(2);
  bstuff = stuff.Now();
  std::cout << bstuff << std::endl << *bstuff << std::endl;

  wclock = 0;
  std::cout << wclock << std::endl;
  bstuff = stuff.Now();
  std::cout << bstuff << std::endl << *bstuff << std::endl;

  wclock = 1;
  std::cout << wclock << std::endl;
  bstuff = stuff.Now();
  std::cout << bstuff << std::endl << *bstuff << std::endl;
  
  return (0);
}

