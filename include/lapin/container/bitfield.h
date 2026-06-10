/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file bitfield.h
** Bitfield helpers and bit rotation utilities.
**
** Bits are addressed from the least significant bit of the first byte. Heap and
** stack allocation helpers create byte arrays large enough to store the
** requested number of bits.
*/

#ifndef				__LAPIN_BITFIELD_H__
# define			__LAPIN_BITFIELD_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<stdint.h>

/*!
** Abstract heap-allocated bitfield.
**
** Use bunny_new_bitfield to create it and bunny_delete_bitfield to release it.
** It stores boolean values compactly, up to eight flags per byte.
*/
/**
 * @doc
 * @doc-symbol t_bunny_bitfield
 * @doc-kind type
 * @doc-module bitfield
 * @doc-order 100
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a compact array of bits.
 * @description Bits are addressed from the least significant bit of the first byte.
 * @see bunny_new_bitfield, bunny_bitfield_get
 *
 * @doc-lang fr
 * @brief Représente un tableau compact de bits.
 * @description Les bits sont adressés depuis le bit de poids faible du premier octet.
 * @see bunny_new_bitfield, bunny_bitfield_get
 */
typedef void			t_bunny_bitfield;

/*! Fixed-size 64-bit bitfield suitable for stack allocation. */
/**
 * @doc
 * @doc-symbol t_bunny_auto_bitfield64
 * @doc-kind type
 * @doc-module bitfield
 * @doc-order 1120
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a fixed-size 64-bit bitfield stored by value.
 * @see bunny_auto_bitfield_set, bunny_auto_bitfield_get
 *
 * @doc-lang fr
 * @brief Représente un bitfield fixe de 64 bits stocké par valeur.
 * @see bunny_auto_bitfield_set, bunny_auto_bitfield_get
 */
typedef uint64_t		t_bunny_auto_bitfield64;
/*! Fixed-size 32-bit bitfield suitable for stack allocation. */
/**
 * @doc
 * @doc-symbol t_bunny_auto_bitfield32
 * @doc-kind type
 * @doc-module bitfield
 * @doc-order 1140
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a fixed-size 32-bit bitfield stored by value.
 * @see bunny_auto_bitfield_set, bunny_auto_bitfield_get
 *
 * @doc-lang fr
 * @brief Représente un bitfield fixe de 32 bits stocké par valeur.
 * @see bunny_auto_bitfield_set, bunny_auto_bitfield_get
 */
typedef uint32_t		t_bunny_auto_bitfield32;
/*! Fixed-size 16-bit bitfield suitable for stack allocation. */
/**
 * @doc
 * @doc-symbol t_bunny_auto_bitfield16
 * @doc-kind type
 * @doc-module bitfield
 * @doc-order 1160
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a fixed-size 16-bit bitfield stored by value.
 * @see bunny_auto_bitfield_set, bunny_auto_bitfield_get
 *
 * @doc-lang fr
 * @brief Représente un bitfield fixe de 16 bits stocké par valeur.
 * @see bunny_auto_bitfield_set, bunny_auto_bitfield_get
 */
typedef uint16_t		t_bunny_auto_bitfield16;
/*! Fixed-size 8-bit bitfield suitable for stack allocation. */
/**
 * @doc
 * @doc-symbol t_bunny_auto_bitfield8
 * @doc-kind type
 * @doc-module bitfield
 * @doc-order 1180
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a fixed-size 8-bit bitfield stored by value.
 * @see bunny_auto_bitfield_set, bunny_auto_bitfield_get
 *
 * @doc-lang fr
 * @brief Représente un bitfield fixe de 8 bits stocké par valeur.
 * @see bunny_auto_bitfield_set, bunny_auto_bitfield_get
 */
typedef uint8_t			t_bunny_auto_bitfield8;

/*!
** Create a bitfield that can handle at least bit bits.
** \param bit The amount of bit the bitfield will contains
** \return A bitfield or NULL on error
*/
/**
 * @doc
 * @doc-symbol bunny_new_bitfield
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a heap bitfield large enough to store a number of bits.
 * @param bit The number of bits to store.
 * @return-success Returns the allocated bitfield.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Crée un bitfield sur le tas assez grand pour stocker un nombre de bits.
 * @param bit Le nombre de bits à stocker.
 * @return-success Renvoie le bitfield alloué.
 * @return-failure Renvoie $CNULL@ si l'allocation échoue.
 * @see t_bunny_bitfield
 */
# define			bunny_new_bitfield(bit)			\
  (t_bunny_bitfield*)bunny_calloc					\
  (((size_t)(bit) / 8 + ((size_t)(bit) % 8 ? 1 : 0)) * sizeof(uint8_t), 1)

/*!
** Create a bitfield on stack that can handle at least bit bits.
**
** The allocation is made with bunny_alloca and disappears when leaving the
** current function. Bits are not initialized. Do not release this bitfield with
** bunny_delete_bitfield.
**
** \param bit The amount of bit the bitfield will contains
** \return A bitfield
*/
/**
 * @doc
 * @doc-symbol bunny_new_abitfield
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 220
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates a temporary bitfield on the current function stack.
 * @param bit The number of bits to store.
 * @return-success Returns the temporary bitfield.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Crée un bitfield temporaire sur la pile de la fonction courante.
 * @param bit Le nombre de bits à stocker.
 * @return-success Renvoie le bitfield temporaire.
 * @see t_bunny_bitfield
 */
# define			bunny_new_abitfield(bit)    \
  (t_bunny_bitfield*)bunny_alloca					\
  (((size_t)(bit) / 8 + ((size_t)(bit) % 8 ? 1 : 0)) * sizeof(uint8_t))

/*!
** Delete a bitfield
** \param bf The bitfield to delete.
*/
/**
 * @doc
 * @doc-symbol bunny_delete_bitfield
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 240
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a heap bitfield.
 * @param bf The bitfield to release.
 * @return-success This macro does not return a value.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Détruit un bitfield alloué sur le tas.
 * @param bf Le bitfield à libérer.
 * @return-success Cette macro ne renvoie pas de valeur.
 * @see t_bunny_bitfield
 */
# define			bunny_delete_bitfield(bf)		\
  bunny_free(bf)

/*!
** Set a single bit inside the sent bitfield
** \param bf The bitfield to edit
** \param bit The bit to set
*/
/**
 * @doc
 * @doc-symbol bunny_bitfield_set
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 260
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Sets one bit in a bitfield.
 * @param bf The bitfield to edit.
 * @param bit The bit index to set.
 * @return-success The selected bit becomes $Ctrue@.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Positionne un bit dans un bitfield.
 * @param bf Le bitfield à modifier.
 * @param bit L'indice du bit à positionner.
 * @return-success Le bit sélectionné devient $Ctrue@.
 * @see t_bunny_bitfield
 */
# define			bunny_bitfield_set(bf, bit)		\
  (((char*)bf)[(size_t)(bit) / 8] |= (1 << ((size_t)(bit) % 8)))

/*!
** Set a single bit inside the sent auto bitfield
** \param bf The bitfield to edit
** \param bit The bit to set
*/
/**
 * @doc
 * @doc-symbol bunny_auto_bitfield_set
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 1280
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Sets one bit in an automatic bitfield value.
 * @param bf The automatic bitfield variable to edit.
 * @param bit The bit index to set.
 * @return-success The selected bit becomes $Ctrue@.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Positionne un bit dans une valeur de bitfield automatique.
 * @param bf La variable bitfield automatique à modifier.
 * @param bit L'indice du bit à positionner.
 * @return-success Le bit sélectionné devient $Ctrue@.
 * @see t_bunny_bitfield
 */
# define			bunny_auto_bitfield_set(bf, bit)	\
  bunny_bitfield_set(&bf, bit)

/*!
** Unset a single bit inside the sent bitfield
** \param bf The bitfield to edit
** \param bit The bit to clear
*/
/**
 * @doc
 * @doc-symbol bunny_bitfield_clr
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 300
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Clears one bit in a bitfield.
 * @param bf The bitfield to edit.
 * @param bit The bit index to clear.
 * @return-success The selected bit becomes $Cfalse@.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Efface un bit dans un bitfield.
 * @param bf Le bitfield à modifier.
 * @param bit L'indice du bit à effacer.
 * @return-success Le bit sélectionné devient $Cfalse@.
 * @see t_bunny_bitfield
 */
# define			bunny_bitfield_clr(bf, bit)		\
  (((char*)bf)[(size_t)(bit) / 8] &= ~(1 << ((size_t)(bit) % 8)))

/*!
** Unset a single bit inside the sent auto bitfield
** \param bf The bitfield to edit
** \param bit The bit to clear
*/
/**
 * @doc
 * @doc-symbol bunny_auto_bitfield_clr
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 1320
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Clears one bit in an automatic bitfield value.
 * @param bf The automatic bitfield variable to edit.
 * @param bit The bit index to clear.
 * @return-success The selected bit becomes $Cfalse@.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Efface un bit dans une valeur de bitfield automatique.
 * @param bf La variable bitfield automatique à modifier.
 * @param bit L'indice du bit à effacer.
 * @return-success Le bit sélectionné devient $Cfalse@.
 * @see t_bunny_bitfield
 */
# define			bunny_auto_bitfield_clr(bf, bit)	\
  bunny_bitfield_clr(&bf, bit)

/*!
** Get the state of the sent bit in the sent bitfield
** \param bf The bitfield to read
** \param bit The bit to get
** \return True or false
*/
/**
 * @doc
 * @doc-symbol bunny_bitfield_get
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 340
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reads one bit from a bitfield.
 * @param bf The bitfield to read.
 * @param bit The bit index to read.
 * @return-success Returns $Ctrue@ if the bit is set.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Lit un bit depuis un bitfield.
 * @param bf Le bitfield à lire.
 * @param bit L'indice du bit à lire.
 * @return-success Renvoie $Ctrue@ si le bit est positionné.
 * @see t_bunny_bitfield
 */
# define			bunny_bitfield_get(bf, bit)		\
  !!(((char*)bf)[(size_t)(bit) / 8] & (1 << ((size_t)(bit) % 8)))

/*!
** Get the state of the sent bit in the sent bitfield
** \param bf The bitfield to read
** \param bit The bit to get
** \return True or false
*/
/**
 * @doc
 * @doc-symbol bunny_auto_bitfield_get
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 1360
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reads one bit from an automatic bitfield value.
 * @param bf The automatic bitfield variable to read.
 * @param bit The bit index to read.
 * @return-success Returns $Ctrue@ if the bit is set.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Lit un bit depuis une valeur de bitfield automatique.
 * @param bf La variable bitfield automatique à lire.
 * @param bit L'indice du bit à lire.
 * @return-success Renvoie $Ctrue@ si le bit est positionné.
 * @see t_bunny_bitfield
 */
# define			bunny_auto_bitfield_get(bf, bit)	\
  bunny_bitfield_get(&bf, bit)

/*!
** Rotate an integer expression to the left over its whole binary width.
*/
/**
 * @doc
 * @doc-symbol bunny_left_binary_rotation
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 1380
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Rotates an integer expression to the left.
 * @param data The integer expression to rotate.
 * @param shift The number of bits to rotate.
 * @return-success Returns the rotated value.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Effectue une rotation entière vers la gauche.
 * @param data L'expression entière à faire tourner.
 * @param shift Le nombre de bits de rotation.
 * @return-success Renvoie la valeur après rotation.
 * @see t_bunny_bitfield
 */
# define			bunny_left_binary_rotation(data, shift)	\
  (((data) << ((size_t)(shift) % (sizeof(data) * 8))) |		\
   ((data) >> (((sizeof(data) * 8) - ((size_t)(shift) % (sizeof(data) * 8))) % (sizeof(data) * 8))))

/*!
** Rotate an integer expression to the right over its whole binary width.
*/
/**
 * @doc
 * @doc-symbol bunny_right_binary_rotation
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 1400
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Rotates an integer expression to the right.
 * @param data The integer expression to rotate.
 * @param shift The number of bits to rotate.
 * @return-success Returns the rotated value.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Effectue une rotation entière vers la droite.
 * @param data L'expression entière à faire tourner.
 * @param shift Le nombre de bits de rotation.
 * @return-success Renvoie la valeur après rotation.
 * @see t_bunny_bitfield
 */
# define			bunny_right_binary_rotation(data, shift)\
  (((data) >> ((size_t)(shift) % (sizeof(data) * 8))) |		\
   ((data) << (((sizeof(data) * 8) - ((size_t)(shift) % (sizeof(data) * 8))) % (sizeof(data) * 8))))

/*!
** Rotate len bits of a bitfield to the left.
**
** Bits shifted out of the selected range re-enter at its beginning.
**
** \param bf The bitfield to rotate.
** \param len The number of bits to include in the rotation.
** \param shift The amount of bits to rotate.
*/
void				bunny_left_bitfield_rotation(t_bunny_bitfield	*bf,
						     size_t		len,
						     size_t		shift);

/*!
** Rotate len bits of a bitfield to the right.
**
** Bits shifted out of the selected range re-enter at its end.
**
** \param bf The bitfield to rotate.
** \param len The number of bits to include in the rotation.
** \param shift The amount of bits to rotate.
*/
void				bunny_right_bitfield_rotation(t_bunny_bitfield	*bf,
						      size_t		len,
						      size_t		shift);


#endif	/*			__LAPIN_BITFIELD_H__			*/
