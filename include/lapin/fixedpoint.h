/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*
** \file fixedpoint.h
** The point of this module is to allow you to send double and
** floats over the internet by converting them into a cheaper
** format and turning them back after.
** The cost of this operation is a loss of precision, which
** in most case in video game is not a problem.
*/

#ifndef		__LAPIN_FIXED_POINT_H__
# define	__LAPIN_FIXED_POINT_H__
# include	<stdint.h>


/**
 * @doc
 * @doc-symbol fixedpoint
 * @doc-kind module
 * @doc-module fixedpoint
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Converts floating point numbers to compact fixed-point integers and back.
 * @description This module is mainly useful when serializing approximate real values, for example over the network, with a predictable integer representation.
 * @header lapin/fixedpoint.h
 *
 * @doc-lang fr
 * @brief Convertit des nombres flottants en entiers à virgule fixe compacts, et inversement.
 * @description Ce module sert surtout à sérialiser des valeurs réelles approximatives, par exemple sur le réseau, avec une représentation entière prévisible.
 * @header lapin/fixedpoint.h
 */

/*!
** Turn the sent float or double into a fixed point arithmetic decimal.
** \param val The value to convert
** \param prc The amount of bits used to represent the decimal part
** \param siz The size in bits of the fixed point decimal. Max is 64.
** \return A fixed point arithemtic decimal number of siz bits, that
** can be convert back to a float or double thanks to bunny_to_floating_decimal.
*/


/**
 * @doc
 * @doc-symbol bunny_to_fixed_decimal
 * @doc-kind macro
 * @doc-module fixedpoint
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Converts a floating value to a fixed-point integer representation.
 * @param val Floating value to convert.
 * @param prc Number of bits reserved for the fractional part.
 * @param siz Total number of bits kept in the fixed-point representation. The maximum useful size is 64.
 * @return-success Returns the fixed-point integer representation of val.
 * @see bunny_to_floating_decimal
 *
 * @doc-lang fr
 * @brief Convertit une valeur flottante en représentation entière à virgule fixe.
 * @param val Valeur flottante à convertir.
 * @param prc Nombre de bits réservés à la partie fractionnaire.
 * @param siz Nombre total de bits conservés dans la représentation à virgule fixe. La taille utile maximale est 64.
 * @return-success Renvoie la représentation entière à virgule fixe de val.
 * @see bunny_to_floating_decimal
 */
# define	bunny_to_fixed_decimal(val, prc, siz)		\
  ((uint64_t)((val) * (1 << (prc))) & ((uint64_t)-1 >> (64 - siz)))

/*!
** Turn the sent fixed point arithemtic decimal into a floating point
** arithmetic decimal.
** \param val The value to convert
** \param prc The precision of the fixed point arithmetic decimal,
** in bits for the decimal part, maximum is 64.
** \return A floating point arithmetic decimal.
*/


/**
 * @doc
 * @doc-symbol bunny_to_floating_decimal
 * @doc-kind macro
 * @doc-module fixedpoint
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Converts a fixed-point integer representation back to a floating value.
 * @param val Fixed-point integer value to convert.
 * @param prc Number of bits used by the fractional part when val was encoded.
 * @return-success Returns the approximate floating value represented by val.
 * @see bunny_to_fixed_decimal
 *
 * @doc-lang fr
 * @brief Reconvertit une représentation entière à virgule fixe en valeur flottante.
 * @param val Valeur entière à virgule fixe à convertir.
 * @param prc Nombre de bits utilisés par la partie fractionnaire lors de l'encodage de val.
 * @return-success Renvoie la valeur flottante approximative représentée par val.
 * @see bunny_to_fixed_decimal
 */
# define	bunny_to_floating_decimal(val, prc)		\
  ((val) / (double)(1 << (prc)))

#endif	/*	__LAPIN_FIXED_POINT_H__				*/
