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

/**
 * @doc
 * @doc-symbol worldclock
 * @doc-kind module
 * @doc-module worldclock
 * @doc-order 0
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Counts simulation ticks for C++ time-aware helpers.
 * @description $Thbs::WorldClock@ is an exclusively C++ API, available from C++ through $L#include <lapin.h>@. It stores the current world tick and provides monotonic forward movement, controlled rewinds and arithmetic operators used by $Thbs::Frame@. This module has no C API equivalent.
 * @header lapin/cpp/WorldClock.hpp
 *
 * @doc-lang fr
 * @brief Compte les ticks de simulation pour les outils C++ dépendants du temps.
 * @description $Thbs::WorldClock@ est une API exclusivement C++, accessible en C++ via $L#include <lapin.h>@. Elle stocke le tick courant du monde et fournit une progression monotone vers l'avant, des retours contrôlés et des opérateurs arithmétiques utilisés par $Thbs::Frame@. Ce module n'a pas d'équivalent dans l'API C.
 * @header lapin/cpp/WorldClock.hpp
 */

namespace		hbs
{
  // Enough for 9 billion years of game at 60FPS
/**
 * @doc
 * @doc-symbol hbs::Tick
 * @doc-kind type
 * @doc-module worldclock
 * @doc-order 10
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Unsigned tick counter used by the C++ timing helpers.
 * @description $Thbs::Tick@ is large enough for extremely long simulations and is used as the exchange type of $Thbs::WorldClock@ and $Thbs::Frame@. This type is only available from C++.
 *
 * @doc-lang fr
 * @brief Compteur de tick non signé utilisé par les outils temporels C++.
 * @description $Thbs::Tick@ est suffisamment grand pour des simulations extrêmement longues et sert de type d'échange à $Thbs::WorldClock@ et $Thbs::Frame@. Ce type n'est disponible qu'en C++.
 */
  typedef uint64_t	Tick;

/**
 * @doc
 * @doc-symbol hbs::WorldClock
 * @doc-kind type
 * @doc-module worldclock
 * @doc-order 100
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores the current world tick.
 * @description $Thbs::WorldClock@ is a small C++ clock object. It can advance normally, rewind to an older tick and reset to zero. $Sgreatest_tick@ is kept internally so objects such as $Thbs::Frame@ can distinguish ordinary progression from a rewind.
 * @see hbs::Tick
 * @see hbs::Frame
 *
 * @doc-lang fr
 * @brief Stocke le tick courant du monde.
 * @description $Thbs::WorldClock@ est un petit objet d'horloge C++. Il peut avancer normalement, revenir vers un tick plus ancien et être remis à zéro. $Sgreatest_tick@ est conservé en interne pour que des objets comme $Thbs::Frame@ puissent distinguer la progression normale d'un retour en arrière.
 * @see hbs::Tick
 * @see hbs::Frame
 */
  class			WorldClock
  {
    Tick		tick;
    Tick		greatest_tick;

  public:
/**
 * @doc
 * @doc-symbol hbs::WorldClock::operator hbs::Tick
 * @doc-kind function
 * @doc-module worldclock
 * @doc-order 130
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reads the current tick.
 * @return-success Returns the current $Thbs::Tick@ value.
 *
 * @doc-lang fr
 * @brief Lit le tick courant.
 * @return-success Renvoie la valeur $Thbs::Tick@ courante.
 */
    operator		Tick(void) const
    {
      return (tick);
    }
/**
 * @doc
 * @doc-symbol hbs::WorldClock::operator=
 * @doc-kind function
 * @doc-module worldclock
 * @doc-order 140
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Sets the current tick.
 * @param t New tick value.
 * @description Assigning a greater value advances the world and updates the greatest reached tick. Assigning a lower value rewinds the current tick without lowering the remembered greatest tick.
 * @return-success Returns this clock.
 *
 * @doc-lang fr
 * @brief Modifie le tick courant.
 * @param t Nouvelle valeur de tick.
 * @description Affecter une valeur plus grande avance le monde et met à jour le plus grand tick atteint. Affecter une valeur plus petite revient en arrière sans diminuer le plus grand tick mémorisé.
 * @return-success Renvoie cette horloge.
 */
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
/**
 * @doc
 * @doc-symbol hbs::WorldClock::operator<=>
 * @doc-kind function
 * @doc-module worldclock
 * @doc-order 150
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Compares the current tick with another tick and returns their signed distance.
 * @param t Tick to compare with the current world tick.
 * @return-success Returns a negative value when the clock is before $St@, zero when equal and a positive value when after $St@.
 *
 * @doc-lang fr
 * @brief Compare le tick courant à un autre tick et renvoie leur distance signée.
 * @param t Tick à comparer au tick courant du monde.
 * @return-success Renvoie une valeur négative quand l'horloge est avant $St@, zéro quand ils sont égaux et une valeur positive quand elle est après $St@.
 */
    int			operator<=>(Tick	t) const
    {
      if (tick < t)
	return (-(t - tick));
      return (tick - t);
    }

/**
 * @doc
 * @doc-symbol hbs::WorldClock::operator++
 * @doc-kind function
 * @doc-module worldclock
 * @doc-order 160
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Advances the world clock by one tick.
 * @return-success Returns the new current tick.
 *
 * @doc-lang fr
 * @brief Avance l'horloge du monde d'un tick.
 * @return-success Renvoie le nouveau tick courant.
 */
    Tick		operator++(void)
    {
      *this = tick + 1;
      return (tick);
    }
/**
 * @doc
 * @doc-symbol hbs::WorldClock::operator++(int)
 * @doc-kind function
 * @doc-module worldclock
 * @doc-order 170
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Advances the world clock by one tick and returns the previous tick.
 * @return-success Returns the tick value before the increment.
 *
 * @doc-lang fr
 * @brief Avance l'horloge du monde d'un tick et renvoie l'ancien tick.
 * @return-success Renvoie la valeur du tick avant l'incrément.
 */
    Tick		operator++(int)
    {
      Tick		tmp = tick;

      *this = tick + 1;
      return (tmp);
    }
/**
 * @doc
 * @doc-symbol hbs::WorldClock::operator+=
 * @doc-kind function
 * @doc-module worldclock
 * @doc-order 180
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Moves the clock forward by several ticks.
 * @param v Signed number of ticks to add. Negative values are delegated to $Soperator-=@.
 * @return-success Returns this clock.
 *
 * @doc-lang fr
 * @brief Avance l'horloge de plusieurs ticks.
 * @param v Nombre signé de ticks à ajouter. Les valeurs négatives sont déléguées à $Soperator-=@.
 * @return-success Renvoie cette horloge.
 */
    WorldClock		&operator+=(int	v)
    {
      if (v < 0)
	return (*this -= -v);
      *this = tick + v;
      return (*this);
    }
/**
 * @doc
 * @doc-symbol hbs::WorldClock::operator-=
 * @doc-kind function
 * @doc-module worldclock
 * @doc-order 190
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Rewinds the clock by several ticks.
 * @param v Signed number of ticks to subtract. Negative values are delegated to $Soperator+=@.
 * @description Rewinding below zero clamps the current tick to zero.
 * @return-success Returns this clock.
 *
 * @doc-lang fr
 * @brief Recule l'horloge de plusieurs ticks.
 * @param v Nombre signé de ticks à soustraire. Les valeurs négatives sont déléguées à $Soperator+=@.
 * @description Un retour avant zéro place le tick courant à zéro.
 * @return-success Renvoie cette horloge.
 */
    WorldClock		&operator-=(int	v)
    {
      if (v < 0)
	return (*this += -v);
      if (tick < (hbs::Tick)v)
	return (*this = 0);
      *this = tick - v;
      return (*this);
    }
/**
 * @doc
 * @doc-symbol hbs::WorldClock::Reset
 * @doc-kind function
 * @doc-module worldclock
 * @doc-order 200
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Resets the world clock to zero.
 * @description Both the current tick and the greatest reached tick are reset.
 *
 * @doc-lang fr
 * @brief Remet l'horloge du monde à zéro.
 * @description Le tick courant et le plus grand tick atteint sont tous les deux remis à zéro.
 */
    void		Reset(void)
    {
      tick = greatest_tick = 0;
    }
/**
 * @doc
 * @doc-symbol hbs::WorldClock::WorldClock
 * @doc-kind function
 * @doc-module worldclock
 * @doc-order 110
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a world clock initialized at tick zero.
 *
 * @doc-lang fr
 * @brief Crée une horloge de monde initialisée au tick zéro.
 */
    WorldClock(void)
      : tick(0), greatest_tick(0)
    {}
/**
 * @doc
 * @doc-symbol hbs::WorldClock::~WorldClock
 * @doc-kind function
 * @doc-module worldclock
 * @doc-order 120
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Destroys a world clock.
 *
 * @doc-lang fr
 * @brief Détruit une horloge de monde.
 */
    ~WorldClock(void)
    {}
  };
}

#endif	//	__BUNNY_WORLD_CLOCK_HPP__
