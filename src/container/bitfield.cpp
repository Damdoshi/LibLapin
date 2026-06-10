// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include	<stdint.h>
#include	"lapin_private.h"

static bool	bitfield_get_bit(const t_bunny_bitfield	*bf,
				 size_t				bit)
{
  const uint8_t	*ptr = (const uint8_t*)bf;

  return ((ptr[bit / 8] & (uint8_t)(1u << (bit % 8))) != 0);
}

static void	bitfield_set_bit(t_bunny_bitfield		*bf,
				 size_t				bit,
				 bool				val)
{
  uint8_t	*ptr = (uint8_t*)bf;
  uint8_t	msk = (uint8_t)(1u << (bit % 8));

  if (val)
    ptr[bit / 8] |= msk;
  else
    ptr[bit / 8] &= (uint8_t)~msk;
}

static void	bitfield_rotate(t_bunny_bitfield		*bf,
			size_t				len,
			size_t				shift,
			bool				left)
{
  t_bunny_bitfield *tmp;
  size_t	bytes;
  size_t	i;
  size_t	dst;

  if (bf == NULL || len == 0)
    return ;
  shift %= len;
  if (shift == 0)
    return ;
  bytes = len / 8 + (len % 8 ? 1 : 0);
  if ((tmp = (t_bunny_bitfield*)bunny_calloc(bytes, 1)) == NULL)
    scream_error_if(return, bunny_errno, "%p bitfield, %zu len, %zu shift", "container", bf, len, shift);
  for (i = 0; i < len; ++i)
    if (bitfield_get_bit(bf, i))
      {
	dst = left ? (i + shift) % len : (i + len - shift) % len;
	bitfield_set_bit(tmp, dst, true);
      }
  for (i = 0; i < len; ++i)
    bitfield_set_bit(bf, i, bitfield_get_bit(tmp, i));
  bunny_free(tmp);
}

/*!
** Rotate the content of a bitfield to the left.
**
** The rotation is circular: bits that leave the high end of the selected range
** are reintroduced at the low end. Only the first len bits are considered.
**
** \param bf The bitfield to rotate.
** \param len The number of bits that belong to the rotated field.
** \param shift The number of positions to rotate.
*/
/**
 * @doc
 * @doc-symbol bunny_left_bitfield_rotation
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 1420
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Rotates a range of bits in a bitfield to the left.
 * @param bf The bitfield to rotate.
 * @param len The number of bits included in the rotation.
 * @param shift The number of bits to rotate.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Effectue une rotation vers la gauche sur une plage de bits d'un bitfield.
 * @param bf Le bitfield à faire tourner.
 * @param len Le nombre de bits inclus dans la rotation.
 * @param shift Le nombre de bits de rotation.
 * @see t_bunny_bitfield
 */
void		bunny_left_bitfield_rotation(t_bunny_bitfield	*bf,
				     size_t			len,
				     size_t			shift)
{
  bitfield_rotate(bf, len, shift, true);
}

/*!
** Rotate the content of a bitfield to the right.
**
** The rotation is circular: bits that leave the low end of the selected range
** are reintroduced at the high end. Only the first len bits are considered.
**
** \param bf The bitfield to rotate.
** \param len The number of bits that belong to the rotated field.
** \param shift The number of positions to rotate.
*/
/**
 * @doc
 * @doc-symbol bunny_right_bitfield_rotation
 * @doc-kind function
 * @doc-module bitfield
 * @doc-order 1440
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Rotates a range of bits in a bitfield to the right.
 * @param bf The bitfield to rotate.
 * @param len The number of bits included in the rotation.
 * @param shift The number of bits to rotate.
 * @see t_bunny_bitfield
 *
 * @doc-lang fr
 * @brief Effectue une rotation vers la droite sur une plage de bits d'un bitfield.
 * @param bf Le bitfield à faire tourner.
 * @param len Le nombre de bits inclus dans la rotation.
 * @param shift Le nombre de bits de rotation.
 * @see t_bunny_bitfield
 */
void		bunny_right_bitfield_rotation(t_bunny_bitfield	*bf,
				      size_t			len,
				      size_t			shift)
{
  bitfield_rotate(bf, len, shift, false);
}
