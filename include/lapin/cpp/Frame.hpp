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

/**
 * @doc
 * @doc-symbol frame
 * @doc-kind module
 * @doc-module frame
 * @doc-order 0
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores rewindable C++ object states indexed by world ticks.
 * @description $Thbs::Frame@ is an exclusively C++ template API, available from C++ through $L#include <lapin.h>@. Template parameters are: $SStorage@, the serialisable state type stored at each tick; and $SCapacity@, the number of remembered states, defaulting to $CMAX_HISTORY@. $SStorage@ must inherit from $Thbs::Serialisable@. This module replaces the old C history idea with a C++ object-oriented time-frame helper.
 * @header lapin/cpp/Frame.hpp
 *
 * @doc-lang fr
 * @brief Stocke des états C++ rembobinables indexés par ticks de monde.
 * @description $Thbs::Frame@ est une API template exclusivement C++, accessible en C++ via $L#include <lapin.h>@. Les paramètres templates sont : $SStorage@, le type d'état sérialisable stocké à chaque tick ; et $SCapacity@, le nombre d'états mémorisés, valant $CMAX_HISTORY@ par défaut. $SStorage@ doit hériter de $Thbs::Serialisable@. Ce module remplace l'ancienne idée de history C par un outil temporel orienté objet en C++.
 * @header lapin/cpp/Frame.hpp
 */

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
/**
 * @doc
 * @doc-symbol hbs::Serialisable
 * @doc-kind type
 * @doc-module frame
 * @doc-order 10
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Base class required by $Thbs::Frame@ storage objects.
 * @description A state type stored in $Thbs::Frame@ must inherit from $Thbs::Serialisable@ and implement $SWrite@ so old states can be recorded when they are evicted from the frame buffer. This type is only available from C++.
 * @see hbs::Frame
 *
 * @doc-lang fr
 * @brief Classe de base requise par les objets stockés dans $Thbs::Frame@.
 * @description Un type d'état stocké dans $Thbs::Frame@ doit hériter de $Thbs::Serialisable@ et implémenter $SWrite@ afin que les anciens états puissent être enregistrés lorsqu'ils sont expulsés du tampon de frames. Ce type n'est disponible qu'en C++.
 * @see hbs::Frame
 */
  class				Serialisable
  {
  public:
/**
 * @doc
 * @doc-symbol hbs::Serialisable::Write
 * @doc-kind function
 * @doc-module frame
 * @doc-order 20
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Serialises this object to an output stream.
 * @param os Stream receiving the serialised representation.
 * @return-success Returns $Sos@.
 *
 * @doc-lang fr
 * @brief Sérialise cet objet vers un flux de sortie.
 * @param os Flux recevant la représentation sérialisée.
 * @return-success Renvoie $Sos@.
 */
    virtual std::ostream	&Write(std::ostream	&os) const = 0;

/**
 * @doc
 * @doc-symbol hbs::Serialisable::Serialisable
 * @doc-kind function
 * @doc-module frame
 * @doc-order 30
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates a serialisable base object.
 *
 * @doc-lang fr
 * @brief Crée un objet de base sérialisable.
 */
    Serialisable(void) {}
/**
 * @doc
 * @doc-symbol hbs::Serialisable::~Serialisable
 * @doc-kind function
 * @doc-module frame
 * @doc-order 40
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Destroys a serialisable object through its base class.
 *
 * @doc-lang fr
 * @brief Détruit un objet sérialisable via sa classe de base.
 */
    virtual ~Serialisable(void) {}
    friend inline std::ostream	&::operator<<(std::ostream &os,
					      hbs::Serialisable const &ser);
  };

# ifndef			MAX_HISTORY
#  define			MAX_HISTORY		256
# endif
/**
 * @doc
 * @doc-symbol MAX_HISTORY
 * @doc-kind macro
 * @doc-module frame
 * @doc-order 60
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Default number of stored states in $Thbs::Frame@.
 * @description Define $CMAX_HISTORY@ before including LibLapin to override the default $Thbs::Frame@ capacity.
 *
 * @doc-lang fr
 * @brief Nombre d'états stockés par défaut dans $Thbs::Frame@.
 * @description Définissez $CMAX_HISTORY@ avant d'inclure la LibLapin pour changer la capacité par défaut de $Thbs::Frame@.
 */
/**
 * @doc
 * @doc-symbol hbs::Frame
 * @doc-kind type
 * @doc-module frame
 * @doc-order 100
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores one object state per world tick and supports rewind.
 * @description $Thbs::Frame@ keeps a circular history of $SStorage@ values associated with $Thbs::Tick@ values from a $Thbs::WorldClock@. Reading resynchronises the current state with the world clock. Writing stores the new state at the current tick. Evicted states are sent to the recorder stream.
 * @see hbs::WorldClock
 * @see hbs::RangedValue
 * @see hbs::Serialisable
 *
 * @doc-lang fr
 * @brief Stocke un état d'objet par tick de monde et permet le retour en arrière.
 * @description $Thbs::Frame@ conserve un historique circulaire de valeurs $SStorage@ associées aux valeurs $Thbs::Tick@ d'une $Thbs::WorldClock@. La lecture resynchronise l'état courant avec l'horloge du monde. L'écriture stocke le nouvel état au tick courant. Les états expulsés sont envoyés vers le flux d'enregistrement.
 * @see hbs::WorldClock
 * @see hbs::RangedValue
 * @see hbs::Serialisable
 */
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
/**
 * @doc
 * @doc-symbol hbs::Frame::Store
 * @doc-kind function
 * @doc-module frame
 * @doc-order 150
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Records an evicted frame entry.
 * @param e Pair containing the tick and the stored object state.
 * @description This protected virtual function is the extension point used to customize how old states are written when the circular buffer overwrites them. The default implementation writes a small object-like representation into the recorder stream.
 *
 * @doc-lang fr
 * @brief Enregistre une entrée de frame expulsée.
 * @param e Paire contenant le tick et l'état d'objet stocké.
 * @description Cette fonction virtuelle protégée est le point d'extension permettant de personnaliser l'écriture des anciens états lorsque le tampon circulaire les écrase. L'implémentation par défaut écrit une petite représentation de type objet dans le flux d'enregistrement.
 */
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
/**
 * @doc
 * @doc-symbol hbs::Frame::OldestTick
 * @doc-kind function
 * @doc-module frame
 * @doc-order 160
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the oldest tick still stored in the frame buffer.
 * @return-success Returns the oldest remembered $Thbs::Tick@.
 *
 * @doc-lang fr
 * @brief Renvoie le plus ancien tick encore stocké dans le tampon de frames.
 * @return-success Renvoie le plus ancien $Thbs::Tick@ mémorisé.
 */
    hbs::Tick			OldestTick(void) const
    {
      return (data[bottom].first);
    }
/**
 * @doc
 * @doc-symbol hbs::Frame::operator Storage&
 * @doc-kind function
 * @doc-module frame
 * @doc-order 170
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Accesses the current mutable state.
 * @description The frame is first resynchronised with the associated $Thbs::WorldClock@.
 * @return-success Returns a mutable reference to the current $SStorage@.
 * @return-failure Throws $Thbs::ExcessiveLag@ if the world clock rewinds before the oldest stored tick.
 *
 * @doc-lang fr
 * @brief Accède à l'état courant modifiable.
 * @description La frame est d'abord resynchronisée avec la $Thbs::WorldClock@ associée.
 * @return-success Renvoie une référence modifiable vers le $SStorage@ courant.
 * @return-failure Lance $Thbs::ExcessiveLag@ si l'horloge du monde revient avant le plus ancien tick stocké.
 */
    linline operator		Storage & (void)
    {
      Resync();
      return (data[top].second);
    }
/**
 * @doc
 * @doc-symbol hbs::Frame::operator const Storage&
 * @doc-kind function
 * @doc-module frame
 * @doc-order 180
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Accesses the current immutable state.
 * @description The frame is first resynchronised with the associated $Thbs::WorldClock@.
 * @return-success Returns a const reference to the current $SStorage@.
 * @return-failure Throws $Thbs::ExcessiveLag@ if the world clock rewinds before the oldest stored tick.
 *
 * @doc-lang fr
 * @brief Accède à l'état courant non modifiable.
 * @description La frame est d'abord resynchronisée avec la $Thbs::WorldClock@ associée.
 * @return-success Renvoie une référence constante vers le $SStorage@ courant.
 * @return-failure Lance $Thbs::ExcessiveLag@ si l'horloge du monde revient avant le plus ancien tick stocké.
 */
    linline operator		const Storage & (void) const
    {
      Resync();
      return (data[top].second);
    }
/**
 * @doc
 * @doc-symbol hbs::Frame::Now
 * @doc-kind function
 * @doc-module frame
 * @doc-order 190
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns a pointer to the current mutable state.
 * @return-success Returns a pointer to the current $SStorage@.
 * @return-failure Throws $Thbs::ExcessiveLag@ if the world clock rewinds before the oldest stored tick.
 *
 * @doc-lang fr
 * @brief Renvoie un pointeur vers l'état courant modifiable.
 * @return-success Renvoie un pointeur vers le $SStorage@ courant.
 * @return-failure Lance $Thbs::ExcessiveLag@ si l'horloge du monde revient avant le plus ancien tick stocké.
 */
    linline Storage		*Now(void)
    {
      Resync();
      return (&data[top].second);
    }
/**
 * @doc
 * @doc-symbol hbs::Frame::Now const
 * @doc-kind function
 * @doc-module frame
 * @doc-order 200
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns a pointer to the current immutable state.
 * @return-success Returns a const pointer to the current $SStorage@.
 *
 * @doc-lang fr
 * @brief Renvoie un pointeur vers l'état courant non modifiable.
 * @return-success Renvoie un pointeur constant vers le $SStorage@ courant.
 */
    linline const Storage	*Now(void) const
    {
      return (&data[top].second);
    }

/**
 * @doc
 * @doc-symbol hbs::Frame::operator=
 * @doc-kind function
 * @doc-module frame
 * @doc-order 210
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Stores a new state at the current world tick.
 * @param sto State to store.
 * @description If the current tick already owns an entry, this entry is replaced. Otherwise a new entry is pushed into the circular history, possibly recording the evicted future slot.
 * @return-success Returns the stored state.
 *
 * @doc-lang fr
 * @brief Stocke un nouvel état au tick courant du monde.
 * @param sto État à stocker.
 * @description Si le tick courant possède déjà une entrée, elle est remplacée. Sinon une nouvelle entrée est poussée dans l'historique circulaire, en enregistrant éventuellement l'emplacement futur expulsé.
 * @return-success Renvoie l'état stocké.
 */
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

/**
 * @doc
 * @doc-symbol hbs::Frame::Frame
 * @doc-kind function
 * @doc-module frame
 * @doc-order 110
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates an empty frame history bound to a world clock.
 * @param wc World clock used to index states.
 * @param os Recorder stream receiving evicted states.
 *
 * @doc-lang fr
 * @brief Crée un historique de frame vide lié à une horloge de monde.
 * @param wc Horloge de monde utilisée pour indexer les états.
 * @param os Flux d'enregistrement recevant les états expulsés.
 */
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
/**
 * @doc
 * @doc-symbol hbs::Frame::Frame(storage)
 * @doc-kind function
 * @doc-module frame
 * @doc-order 120
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates a frame history and stores an initial state.
 * @param wc World clock used to index states.
 * @param os Recorder stream receiving evicted states.
 * @param sto Initial state to store at the current tick.
 *
 * @doc-lang fr
 * @brief Crée un historique de frame et stocke un état initial.
 * @param wc Horloge de monde utilisée pour indexer les états.
 * @param os Flux d'enregistrement recevant les états expulsés.
 * @param sto État initial à stocker au tick courant.
 */
    Frame(const WorldClock	&wc,
	  std::ostream		&os,
	  const Storage		&sto)
      : Frame(wc, os)
    {
      *this = sto;
    }
/**
 * @doc
 * @doc-symbol hbs::Frame::Frame(copy)
 * @doc-kind function
 * @doc-module frame
 * @doc-order 130
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Copies an existing frame history.
 * @param f Frame history to copy.
 * @description The copied frame keeps references to the same world clock and recorder stream as $Sf@.
 *
 * @doc-lang fr
 * @brief Copie un historique de frame existant.
 * @param f Historique de frame à copier.
 * @description La frame copiée conserve des références vers la même horloge de monde et le même flux d'enregistrement que $Sf@.
 */
    Frame(const Frame<Storage, Capacity> &f)
      : data(f.data),
	world_clock(f.world_clock),
	recorder(f.recorder),
	top(f.top),
	bottom(f.bottom)
    {}
/**
 * @doc
 * @doc-symbol hbs::Frame::Frame(args)
 * @doc-kind function
 * @doc-module frame
 * @doc-order 140
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Creates a frame and constructs the initial state from arguments.
 * @param wc World clock used to index states.
 * @param os Recorder stream receiving evicted states.
 * @param args Arguments forwarded to $SStorage@ construction.
 *
 * @doc-lang fr
 * @brief Crée une frame et construit l'état initial depuis des arguments.
 * @param wc Horloge de monde utilisée pour indexer les états.
 * @param os Flux d'enregistrement recevant les états expulsés.
 * @param args Arguments transmis à la construction de $SStorage@.
 */
    template <typename ...Arg>
    Frame(const WorldClock	&wc,
	  std::ostream		&os,
	  Arg...		args)
      : Frame(wc, os)
    {
      *this = Storage{std::forward<Arg>(args)...};
    }
/**
 * @doc
 * @doc-symbol hbs::Frame::~Frame
 * @doc-kind function
 * @doc-module frame
 * @doc-order 220
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Destroys a frame history.
 *
 * @doc-lang fr
 * @brief Détruit un historique de frame.
 */
    virtual ~Frame(void)
    {}
  };
}

/**
 * @doc
 * @doc-symbol operator<<(std::ostream&, hbs::Serialisable const&)
 * @doc-kind function
 * @doc-module frame
 * @doc-order 50
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Writes a serialisable object to a stream.
 * @param os Output stream.
 * @param ser Serialisable object to write.
 * @return-success Returns $Sos@ after calling $Sser.Write(os)@.
 *
 * @doc-lang fr
 * @brief Écrit un objet sérialisable dans un flux.
 * @param os Flux de sortie.
 * @param ser Objet sérialisable à écrire.
 * @return-success Renvoie $Sos@ après appel à $Sser.Write(os)@.
 */
inline std::ostream		&operator<<(std::ostream &os,
					    hbs::Serialisable const &ser)
{
  return (ser.Write(os));
}


#endif	//			__BUNNY_FRAME_HPP__
