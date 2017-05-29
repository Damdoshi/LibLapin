/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file bitfield.h
**
**
**
*/

#ifndef				__LAPIN_BITFIELD_H__
# define			__LAPIN_BITFIELD_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<stdint.h>

typedef void			t_bunny_bitfield;

typedef uint64_t		t_bunny_auto_bitfield64;
typedef uint32_t		t_bunny_auto_bitfield32;
typedef uint16_t		t_bunny_auto_bitfield16;
typedef uint8_t			t_bunny_auto_bitfield8;

/*!
** Create a bitfield that can handle at least bit bits.
** \param bit The amount of bit the bitfield will contains
** \return A bitfield or NULL on error
*/
# define			bunny_new_bitfield(bit)			\
  (t_bunny_bitfield*)bunny_malloc					\
  (((size_t)(bit) / 8 + ((size_t)(bit) % 8 ? 1 : 0)) * sizeof(uint8_t))

/*!
** Delete a bitfield
** \param bf The bitfield to delete.
*/
# define			bunny_delete_bitfield(bf)		\
  bunny_free(bf)

/*!
** Set a single bit inside the sent bitfield
** \param bf The bitfield to edit
** \param bit The bit to set
*/
# define			bunny_bitfield_set(bf, bit)		\
  (((char*)bf)[(size_t)(bit) / 8] |= (1 << ((size_t)(bit) % 8)))

/*!
** Set a single bit inside the sent auto bitfield
** \param bf The bitfield to edit
** \param bit The bit to set
*/
# define			bunny_auto_bitfield_set(bf, bit)	\
  bunny_bitfield_set(&bf, bit)

/*!
** Unset a single bit inside the sent bitfield
** \param bf The bitfield to edit
** \param bit The bit to clear
*/
# define			bunny_bitfield_clr(bf, bit)		\
  (((char*)bf)[(size_t)(bit) / 8] &= ~(1 << ((size_t)(bit) % 8)))

/*!
** Unset a single bit inside the sent auto bitfield
** \param bf The bitfield to edit
** \param bit The bit to clear
*/
# define			bunny_auto_bitfield_clr(bf, bit)	\
  bunny_bitfield_clr(&bf, bit)

/*!
** Get the state of the sent bit in the sent bitfield
** \param bf The bitfield to read
** \param bit The bit to get
** \return True or false
*/
# define			bunny_bitfield_get(bf, bit)		\
  !!(((char*)bf)[(size_t)(bit) / 8] & (1 << ((size_t)(bit) % 8)))

/*!
** Get the state of the sent bit in the sent bitfield
** \param bf The bitfield to read
** \param bit The bit to get
** \return True or false
*/
# define			bunny_auto_bitfield_get(bf, bit)	\
  bunny_bitfield_get(&bf, bit)
  
#endif	/*			__LAPIN_BITFIELD_H__			*/
