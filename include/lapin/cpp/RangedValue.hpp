// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Macroboy Y

#ifndef		BUNNY_RANGED_VALUE_HPP
# define	BUNNY_RANGED_VALUE_HPP
# if		!defined(__LAPIN_H__)
#  error	You cannot include this file directly.
# endif
# include	<string>
# include	<iostream>
# include	"base.hpp"
# include	"errors/NotInRange.hpp"

/**
 * @doc
 * @doc-symbol rangedvalue
 * @doc-kind module
 * @doc-module rangedvalue
 * @doc-order 0
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stores a value constrained to a compile-time range.
 * @description $Thbs::RangedValue@ is an exclusively C++ template API, available from C++ through $L#include <lapin.h>@. Template parameters are: $ST@, the stored arithmetic type; $SMin@, the inclusive lower bound; $SMax@, the exclusive upper bound; and $SES@, the excess strategy used when assigning a value outside $S[Min; Max[@. This module has no C API equivalent.
 * @header lapin/cpp/RangedValue.hpp
 *
 * @doc-lang fr
 * @brief Stocke une valeur contrainte dans un intervalle connu à la compilation.
 * @description $Thbs::RangedValue@ est une API template exclusivement C++, accessible en C++ via $L#include <lapin.h>@. Les paramètres templates sont : $ST@, le type arithmétique stocké ; $SMin@, la borne inférieure incluse ; $SMax@, la borne supérieure exclue ; et $SES@, la stratégie appliquée lorsqu'une valeur sort de $S[Min; Max[@. Ce module n'a pas d'équivalent dans l'API C.
 * @header lapin/cpp/RangedValue.hpp
 */

namespace	hbs
{
/**
 * @doc
 * @doc-symbol hbs::ExcessStrategy
 * @doc-kind enum
 * @doc-module rangedvalue
 * @doc-order 10
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Describes how $Thbs::RangedValue@ reacts to assignments outside its range.
 * @field THROW Throw $Thbs::NotInRange@ when the assigned value is outside the range.
 * @field LOOP Wrap the value inside the range.
 * @field CLAMP Clamp the value to the nearest valid bound.
 * @see hbs::RangedValue
 *
 * @doc-lang fr
 * @brief Décrit la réaction de $Thbs::RangedValue@ aux affectations hors intervalle.
 * @field THROW Lance $Thbs::NotInRange@ quand la valeur affectée est hors intervalle.
 * @field LOOP Ramène la valeur dans l'intervalle par bouclage.
 * @field CLAMP Bloque la valeur sur la borne valide la plus proche.
 * @see hbs::RangedValue
 */
  enum class	ExcessStrategy
    {
      THROW,
      LOOP,
      CLAMP
    };
  // [Min; Max[
/**
 * @doc
 * @doc-symbol hbs::RangedValue
 * @doc-kind type
 * @doc-module rangedvalue
 * @doc-order 100
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Value wrapper constrained to $S[Min; Max[@.
 * @description $Thbs::RangedValue@ behaves like a small arithmetic value while validating every assignment through its excess strategy. The upper bound $SMax@ is exclusive. This type is only available from C++.
 * @see hbs::ExcessStrategy
 * @see hbs::NotInRange
 *
 * @doc-lang fr
 * @brief Enveloppe de valeur contrainte dans $S[Min; Max[@.
 * @description $Thbs::RangedValue@ se comporte comme une petite valeur arithmétique tout en validant chaque affectation au moyen de sa stratégie de dépassement. La borne supérieure $SMax@ est exclue. Ce type n'est disponible qu'en C++.
 * @see hbs::ExcessStrategy
 * @see hbs::NotInRange
 */
  template <typename T, T Min, T Max, ExcessStrategy ES = ExcessStrategy::THROW>
  class		RangedValue
  {
  lprivate:
    T		val;

  public:
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator T
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 140
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reads the contained value.
 * @return-success Returns the current value as $ST@.
 *
 * @doc-lang fr
 * @brief Lit la valeur contenue.
 * @return-success Renvoie la valeur courante sous forme de $ST@.
 */
    linline operator T (void) const
    {
      return (val);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator&
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 150
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Returns the address of the contained value.
 * @return-success Returns a const pointer to the internal value.
 *
 * @doc-lang fr
 * @brief Renvoie l'adresse de la valeur contenue.
 * @return-success Renvoie un pointeur constant vers la valeur interne.
 */
    linline const T *operator&(void) const
    {
      return (&val);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator=
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 160
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Assigns a new value while enforcing the configured range.
 * @param i Value to assign.
 * @return-success Returns the stored value after validation, wrapping or clamping.
 * @return-failure Throws $Thbs::NotInRange@ when $SES@ is $CExcessStrategy::THROW@ and $Si@ is outside $S[Min; Max[@.
 *
 * @doc-lang fr
 * @brief Affecte une nouvelle valeur en respectant l'intervalle configuré.
 * @param i Valeur à affecter.
 * @return-success Renvoie la valeur stockée après validation, bouclage ou blocage.
 * @return-failure Lance $Thbs::NotInRange@ quand $SES@ vaut $CExcessStrategy::THROW@ et que $Si@ sort de $S[Min; Max[@.
 */
    linline T operator=(const T		&i)
    {
      if (i < Min)
	{
	  if (ES == ExcessStrategy::THROW)
	    throw NotInRange(i, Min, Max);
	  if (ES == ExcessStrategy::CLAMP)
	    return (val = Min);
	  return (*this = Max - ((Min - i) % (Max - Min)));
	}
      if (i >= Max)
	{
	  if (ES == ExcessStrategy::THROW)
	    throw NotInRange(i, Min, Max);
	  if (ES == ExcessStrategy::CLAMP)
	    return (val = Max - 1);
	  return (val = ((i - Max) % (Max - Min) + Min));
	}
      return (val = i);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator+(T)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 170
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Adds a raw value without changing this object.
 * @param i Value to add.
 * @return-success Returns $Sval + i@ as a raw $ST@.
 *
 * @doc-lang fr
 * @brief Ajoute une valeur brute sans modifier cet objet.
 * @param i Valeur à ajouter.
 * @return-success Renvoie $Sval + i@ sous forme de $ST@ brut.
 */
    linline T operator+(const T		&i) const
    {
      return (val + i);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator-(T)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 180
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Subtracts a raw value without changing this object.
 * @param i Value to subtract.
 * @return-success Returns $Sval - i@ as a raw $ST@.
 *
 * @doc-lang fr
 * @brief Soustrait une valeur brute sans modifier cet objet.
 * @param i Valeur à soustraire.
 * @return-success Renvoie $Sval - i@ sous forme de $ST@ brut.
 */
    linline T operator-(const T		&i) const
    {
      return (val - i);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator*(T)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 190
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Multiplies by a raw value without changing this object.
 * @param i Value to multiply by.
 * @return-success Returns $Sval * i@ as a raw $ST@.
 *
 * @doc-lang fr
 * @brief Multiplie par une valeur brute sans modifier cet objet.
 * @param i Valeur par laquelle multiplier.
 * @return-success Renvoie $Sval * i@ sous forme de $ST@ brut.
 */
    linline T operator*(const T		&i) const
    {
      return (val * i);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator/(T)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 200
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Divides by a raw value without changing this object.
 * @param i Divisor.
 * @return-success Returns $Sval / i@ as a raw $ST@.
 *
 * @doc-lang fr
 * @brief Divise par une valeur brute sans modifier cet objet.
 * @param i Diviseur.
 * @return-success Renvoie $Sval / i@ sous forme de $ST@ brut.
 */
    linline T operator/(const T		&i) const
    {
      return (val / i);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator%(T)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 210
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Computes the remainder with a raw value without changing this object.
 * @param i Divisor used by the modulo operation.
 * @return-success Returns $Sval % i@ as a raw $ST@.
 *
 * @doc-lang fr
 * @brief Calcule le reste avec une valeur brute sans modifier cet objet.
 * @param i Diviseur utilisé par l'opération modulo.
 * @return-success Renvoie $Sval % i@ sous forme de $ST@ brut.
 */
    linline T operator%(const T		&i) const
    {
      return (val % i);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator+(RangedValue)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 220
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Adds another ranged value and validates the result in a new ranged value.
 * @param i Other ranged value.
 * @return-success Returns a new $Thbs::RangedValue@ containing the validated sum.
 *
 * @doc-lang fr
 * @brief Ajoute une autre valeur bornée et valide le résultat dans une nouvelle valeur bornée.
 * @param i Autre valeur bornée.
 * @return-success Renvoie un nouveau $Thbs::RangedValue@ contenant la somme validée.
 */
    linline auto operator+(const RangedValue<T, Min, Max, ES> &i) const
    {
      return (RangedValue<T, Min, Max, ES>{val + i.val});
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator-(RangedValue)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 230
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Subtracts another ranged value and validates the result in a new ranged value.
 * @param i Other ranged value.
 * @return-success Returns a new $Thbs::RangedValue@ containing the validated difference.
 *
 * @doc-lang fr
 * @brief Soustrait une autre valeur bornée et valide le résultat dans une nouvelle valeur bornée.
 * @param i Autre valeur bornée.
 * @return-success Renvoie un nouveau $Thbs::RangedValue@ contenant la différence validée.
 */
    linline auto operator-(const RangedValue<T, Min, Max, ES> &i) const
    {
      return (RangedValue<T, Min, Max, ES>{val - i.val});
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator*(RangedValue)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 240
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Multiplies by another ranged value and validates the result in a new ranged value.
 * @param i Other ranged value.
 * @return-success Returns a new $Thbs::RangedValue@ containing the validated product.
 *
 * @doc-lang fr
 * @brief Multiplie par une autre valeur bornée et valide le résultat dans une nouvelle valeur bornée.
 * @param i Autre valeur bornée.
 * @return-success Renvoie un nouveau $Thbs::RangedValue@ contenant le produit validé.
 */
    linline auto operator*(const RangedValue<T, Min, Max, ES> &i) const
    {
      return (RangedValue<T, Min, Max, ES>{val * i.val});
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator/(RangedValue)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 250
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Divides by another ranged value and validates the result in a new ranged value.
 * @param i Other ranged value used as divisor.
 * @return-success Returns a new $Thbs::RangedValue@ containing the validated quotient.
 *
 * @doc-lang fr
 * @brief Divise par une autre valeur bornée et valide le résultat dans une nouvelle valeur bornée.
 * @param i Autre valeur bornée utilisée comme diviseur.
 * @return-success Renvoie un nouveau $Thbs::RangedValue@ contenant le quotient validé.
 */
    linline auto operator/(const RangedValue<T, Min, Max, ES> &i) const
    {
      return (RangedValue<T, Min, Max, ES>{val / i.val});
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator%(RangedValue)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 260
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Computes the remainder with another ranged value and validates the result in a new ranged value.
 * @param i Other ranged value used as divisor.
 * @return-success Returns a new $Thbs::RangedValue@ containing the validated remainder.
 *
 * @doc-lang fr
 * @brief Calcule le reste avec une autre valeur bornée et valide le résultat dans une nouvelle valeur bornée.
 * @param i Autre valeur bornée utilisée comme diviseur.
 * @return-success Renvoie un nouveau $Thbs::RangedValue@ contenant le reste validé.
 */
    linline auto operator%(const RangedValue<T, Min, Max, ES> &i) const
    {
      return (RangedValue<T, Min, Max, ES>{val % i.val});
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator++
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 270
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Increments the value through the configured range strategy.
 * @return-success Returns this ranged value.
 *
 * @doc-lang fr
 * @brief Incrémente la valeur en appliquant la stratégie d'intervalle configurée.
 * @return-success Renvoie cette valeur bornée.
 */
    linline auto &operator++(void)
    {
      *this = val + 1;
      return (*this);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator++(int)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 280
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Increments the value and returns the previous raw value.
 * @return-success Returns the value before increment as $ST@.
 *
 * @doc-lang fr
 * @brief Incrémente la valeur et renvoie l'ancienne valeur brute.
 * @return-success Renvoie la valeur avant incrément sous forme de $ST@.
 */
    linline auto operator++(int)
    {
      auto tmp{val};
	    
      ++(*this);
      return (tmp);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator--
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 290
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Decrements the value through the configured range strategy.
 * @return-success Returns this ranged value.
 *
 * @doc-lang fr
 * @brief Décrémente la valeur en appliquant la stratégie d'intervalle configurée.
 * @return-success Renvoie cette valeur bornée.
 */
    linline auto &operator--(void)
    {
      *this = val - 1;
      return (*this);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator--(int)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 300
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Decrements the value and returns the previous raw value.
 * @return-success Returns the value before decrement as $ST@.
 *
 * @doc-lang fr
 * @brief Décrémente la valeur et renvoie l'ancienne valeur brute.
 * @return-success Renvoie la valeur avant décrément sous forme de $ST@.
 */
    linline auto operator--(int)
    {
      auto tmp{val};

      --(*this);
      return (tmp);
    }
    
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator+=
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 310
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Adds a raw value and stores the validated result.
 * @param i Value to add.
 * @return-success Returns this ranged value.
 *
 * @doc-lang fr
 * @brief Ajoute une valeur brute et stocke le résultat validé.
 * @param i Valeur à ajouter.
 * @return-success Renvoie cette valeur bornée.
 */
    linline auto &operator+=(const T	&i)
    {
      *this = val + i;
      return (*this);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator-=
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 320
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Subtracts a raw value and stores the validated result.
 * @param i Value to subtract.
 * @return-success Returns this ranged value.
 *
 * @doc-lang fr
 * @brief Soustrait une valeur brute et stocke le résultat validé.
 * @param i Valeur à soustraire.
 * @return-success Renvoie cette valeur bornée.
 */
    linline auto &operator-=(const T	&i)
    {
      *this = val - i;
      return (*this);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator*=
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 330
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Multiplies by a raw value and stores the validated result.
 * @param i Value to multiply by.
 * @return-success Returns this ranged value.
 *
 * @doc-lang fr
 * @brief Multiplie par une valeur brute et stocke le résultat validé.
 * @param i Valeur par laquelle multiplier.
 * @return-success Renvoie cette valeur bornée.
 */
    linline auto &operator*=(const T	&i)
    {
      *this = val * i;
      return (*this);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator/=
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 340
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Divides by a raw value and stores the validated result.
 * @param i Divisor.
 * @return-success Returns this ranged value.
 *
 * @doc-lang fr
 * @brief Divise par une valeur brute et stocke le résultat validé.
 * @param i Diviseur.
 * @return-success Renvoie cette valeur bornée.
 */
    linline auto &operator/=(const T	&i)
    {
      *this = val / i;
      return (*this);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator%=
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 350
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Applies modulo with a raw value and stores the validated result.
 * @param i Divisor used by the modulo operation.
 * @return-success Returns this ranged value.
 *
 * @doc-lang fr
 * @brief Applique le modulo avec une valeur brute et stocke le résultat validé.
 * @param i Diviseur utilisé par l'opération modulo.
 * @return-success Renvoie cette valeur bornée.
 */
    linline auto &operator%=(const T	&i)
    {
      *this = val % i;
      return (*this);
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::operator std::string
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 360
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Converts the current value to a string.
 * @return-success Returns the value formatted through $Tstd::stringstream@.
 *
 * @doc-lang fr
 * @brief Convertit la valeur courante en chaîne.
 * @return-success Renvoie la valeur formatée au moyen de $Tstd::stringstream@.
 */
    linline operator std::string (void) const
    {
      std::stringstream ss;

      ss << val;
      return (ss.str());
    }

/**
 * @doc
 * @doc-symbol hbs::RangedValue::RangedValue
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 110
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a ranged value initialized with zero.
 * @description No range validation is performed in the default constructor; choose ranges containing zero when relying on this constructor.
 *
 * @doc-lang fr
 * @brief Crée une valeur bornée initialisée à zéro.
 * @description Le constructeur par défaut ne valide pas l'intervalle ; utilisez des intervalles contenant zéro lorsque vous vous appuyez sur ce constructeur.
 */
    RangedValue(void)
    {
      val = 0;
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::RangedValue(value)
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 120
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a ranged value from an initial value.
 * @param v Initial value, validated through $Soperator=@.
 * @return-failure May throw $Thbs::NotInRange@ when $SES@ is $CExcessStrategy::THROW@.
 *
 * @doc-lang fr
 * @brief Crée une valeur bornée depuis une valeur initiale.
 * @param v Valeur initiale, validée via $Soperator=@.
 * @return-failure Peut lancer $Thbs::NotInRange@ quand $SES@ vaut $CExcessStrategy::THROW@.
 */
    RangedValue(const T			&v)
    {
      *this = v;
    }
/**
 * @doc
 * @doc-symbol hbs::RangedValue::~RangedValue
 * @doc-kind function
 * @doc-module rangedvalue
 * @doc-order 130
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Destroys a ranged value.
 *
 * @doc-lang fr
 * @brief Détruit une valeur bornée.
 */
    ~RangedValue(void) {}
  };
}

#endif	//	BUNNY_RANGED_VALUE_HPP
