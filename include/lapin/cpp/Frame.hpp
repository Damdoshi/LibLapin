// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Macroboy Y

#ifndef				__BUNNY_FRAME_HPP__
# define			__BUNNY_FRAME_HPP__
# include			<cstring>
# include			<cstddef>
# include			<tuple>
# include			<array>
# include			<utility>
# include			"errors/ExcessiveLag.hpp"
# include			"RangedValue.hpp"
# include			"WorldClock.hpp"

// Forwards
namespace			hbs
{
  class				Serialisable;
}
inline std::ostream		&operator<<(std::ostream &os,
					    hbs::Serialisable const &ser);

// Now, we go
namespace			hbs
{
  class				Serialisable
  {
  public:
    virtual std::ostream	&Write(std::ostream	&os) const = 0;

    Serialisable(void) {}
    virtual ~Serialisable(void) {}
    friend inline std::ostream	&::operator<<(std::ostream &os,
					      hbs::Serialisable const &ser);
  };

# ifndef			MAX_HISTORY
#  define			MAX_HISTORY		256
# endif
  template <typename		Storage,
	    size_t		Capacity = MAX_HISTORY>
  class				Frame
  {
  private:
    static_assert(std::is_base_of<Serialisable, Storage>::value, "Storage must inherit from Serialisable");

  protected:
    // Pile que l'on ne dépile qu'en cas de lag.
    std::array<
    std::pair<
	hbs::Tick, Storage
	>,
      Capacity
    >				data;
    const WorldClock		&world_clock;
    // Pour enregistrer les états qu'on va re ecrire.
    std::ostream		&recorder;
    mutable RangedValue<
      int, 0, Capacity, ExcessStrategy::LOOP
      >				top;
    mutable RangedValue<
      int, 0, Capacity, ExcessStrategy::LOOP
      >				bottom;
    
    linline void		Resync(void)
    {
      hbs::Tick			now = world_clock;
      auto			tmp = top;

      if (data[tmp].first == now)
	return ;
      if (data[tmp].first < now)
	{
	  // On rapatrie l'état passé à l'heure actuelle
	  data[++top] = {now, data[tmp].second};
	  if (top == bottom)
	    bottom = top + 1;
	  return ;
	}
      // On repart dans le passé
      while (now < data[tmp].first)
	{
	  if (tmp == bottom)
	    throw hbs::ExcessiveLag
	      (world_clock,
	       data[top].first,
	       data[bottom].first,
	       Capacity
	       );
	  tmp -= 1;
	}
      top = tmp;
    }
    virtual void		Store(const std::pair<hbs::Tick, Storage> &e)
    {
      recorder << "{'tick':" << e.first << ", 'status':";
      recorder << e.second;
      recorder << "}";
    }
    void			Store(size_t			frame)
    {
      Store(data[frame]);
    }

  public:
    hbs::Tick			OldestTick(void) const
    {
      return (data[bottom].first);
    }
    linline operator		Storage & (void)
    {
      Resync();
      return (data[top].second);
    }
    linline operator		const Storage & (void) const
    {
      Resync();
      return (data[top].second);
    }
    linline Storage		*Now(void)
    {
      Resync();
      return (&data[top].second);
    }
    linline const Storage	*Now(void) const
    {
      return (&data[top].second);
    }

    linline Storage		&operator=(const Storage	&sto)
    {
      Tick			tick = world_clock;

      if (tick == data[top].first)
	return (data[top].second = sto);
      if (data[top + 1].first != 0)
	Store(top + 1);
      data[++top] = {tick, sto};
      return (data[top].second);
    }

    Frame(const WorldClock	&wc,
	  std::ostream		&os)
      : world_clock(wc),
	recorder(os),
	top(0),
	bottom(0)
    {
      for (size_t i = 0; i < Capacity; ++i)
	data[i].first = 0;
    }
    Frame(const WorldClock	&wc,
	  std::ostream		&os,
	  const Storage		&sto)
      : Frame(wc, os)
    {
      *this = sto;
    }
    Frame(const Frame<Storage, Capacity> &f)
      : data(f.data),
	world_clock(f.world_clock),
	recorder(f.recorder),
	top(f.top),
	bottom(f.bottom)
    {}
    template <typename ...Arg>
    Frame(const WorldClock	&wc,
	  std::ostream		&os,
	  Arg...		args)
      : Frame(wc, os)
    {
      *this = Storage{std::forward<Arg>(args)...};
    }
    virtual ~Frame(void)
    {}
  };
}

inline std::ostream		&operator<<(std::ostream &os,
					    hbs::Serialisable const &ser)
{
  return (ser.Write(os));
}


#endif	//			__BUNNY_FRAME_HPP__
