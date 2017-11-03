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

/*!
** Turn the sent float or double into a fixed point arithmetic decimal.
** \param val The value to convert
** \param prc The amount of bits used to represent the decimal part
** \param siz The size in bits of the fixed point decimal. Max is 64.
** \return A fixed point arithemtic decimal number of siz bits, that
** can be convert back to a float or double thanks to bunny_to_floating_decimal.
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
# define	bunny_to_floating_decimal(val, prc)		\
  ((val) / (double)(1 << (prc)))

#endif	/*	__LAPIN_FIXED_POINT_H__				*/
