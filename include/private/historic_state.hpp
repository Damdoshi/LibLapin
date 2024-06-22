/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2022
** Pentacle Technologie 2008-2022
**
**
** Bibliotheque Lapin
*/

#ifndef					__HISTORIC_STATE_HPP__
# define				__HISTORIC_STATE_HPP__
# ifdef					__cplusplus

class					DifferentClock : public std::invalid_argument
{
public:
  DifferentClock()
    : invalid_argument
      ("Trying to assign an HistoricState to another one with a different HistoricClock")
  {}
  ~DifferentClock()
  {}
};

template <typename			Type,
	  typename			HistoricClock>
class					HistoricState
{
protected:
  std::map<int, Type>			data;
  const HistoricClock			&clock;

public:

  HistoricState<Type, HistoricClock>	&operator=(Type const	&o)
  {
    int tick = clock.GetCurrentTick();
    auto it = data.find(tick);

    if (it == data.end())
      {
	auto ret = data.emplace(o);
	data.erase(ret.first + 1, data.end());
      }
    else
      {
	it->second = o;
	data.erase(it + 1, data.end());
      }
    return (*this);
  }

  operator				Type (void) const
  {
    return (data);
  }

  HistoricState<Type, HistoricClock>	&operator=(const HistoricState<Type, HistoricClock>	&o)
  {
    if (&clock != &o.clock)
      throw DifferentClock();
    data = o.data;
    return (*this);
  }

  HistoricState(const Type		&dat,
		const HistoricClock	&hc = HistoricClock::GetDefaultClock())
    : HistoricState(hc),
      data(dat)
  {}
  HistoricState(const HistoricState	&s)
  {
    if (&s.clock != &clock)
      throw std::DifferentClock();
  }
  HistoricState(const HistoricClock	&hc = HistoricClock::GetDefaultClock())
    : HistoricState(hc.data, hc.clock)
  {}
  ~HistoricState(void)
  {}
};

# endif
#endif	//				__HISTORIC_STATE_HPP__
