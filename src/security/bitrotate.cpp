// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			<string.h>
#include			"lapin_private.h"

/*
** Bitrotate applies several rotations on 64 bits blocks.
**
** The key is read 24 bits at a time and split this way:
** - 6 bits: rotation for the whole 64 bits packet.
** - 5 bits: rotation for the two 32 bits packets.
** - 4 bits: rotation for the four 16 bits packets.
** - 3 bits: rotation for the eight 8 bits packets.
** - 2 bits: rotation for the sixteen 4 bits packets.
** - 1 bit : rotation for the thirty two 2 bits packets.
** - 3 bits: tweak added once more for each packet inside a layer.
**
** The rotation fields are sign-extended. The tweak is unsigned.
*/

static int			signed_field(const uint32_t		key,
					     const size_t		shift,
					     const size_t		bits)
{
  const uint32_t			mask = (1 << bits) - 1;
  uint32_t			field;

  field = (key >> shift) & mask;
  if (field & (1 << (bits - 1)))
    return ((int)field - (int)(1 << bits));
  return ((int)field);
}

static int			positive_modulo(const int		value,
						const size_t		modulo)
{
  int				ret;

  ret = value % (int)modulo;
  if (ret < 0)
    ret += modulo;
  return (ret);
}

static void			rotate_packets(uint8_t			*block,
					       const size_t		packet_size,
					       const int		base_rotation,
					       const int		tweak)
{
  uint8_t			copy[8];
  uint8_t			result[8];
  size_t			packet;
  size_t			bit;
  size_t			packet_count;
  int				rotation;

  memcpy(&copy[0], &block[0], sizeof(copy));
  memset(&result[0], 0, sizeof(result));
  packet_count = 64 / packet_size;
  for (packet = 0; packet < packet_count; ++packet)
    {
      rotation = positive_modulo(base_rotation + (int)packet * tweak, packet_size);
      for (bit = 0; bit < packet_size; ++bit)
	if (bunny_bitfield_get(&copy[0], packet * packet_size + bit))
	  bunny_bitfield_set(&result[0], packet * packet_size + ((bit + rotation) % packet_size));
    }
  memcpy(&block[0], &result[0], sizeof(result));
}

static uint32_t			read_key(const t_bunny_cipher_key	*key,
					 const size_t			block)
{
  size_t			idx;

  idx = (block * 3) % key->length;
  return (((uint8_t)key->key[idx]) |
	  ((uint8_t)key->key[(idx + 1) % key->length] << 8) |
	  ((uint8_t)key->key[(idx + 2) % key->length] << 16));
}

static void			cipher_block(uint8_t			*block,
					     const uint32_t		key)
{
  const int			tweak = (key >> 21) & 0x7;

  rotate_packets(block, 64, signed_field(key, 0, 6), tweak);
  rotate_packets(block, 32, signed_field(key, 6, 5), tweak);
  rotate_packets(block, 16, signed_field(key, 11, 4), tweak);
  rotate_packets(block, 8, signed_field(key, 15, 3), tweak);
  rotate_packets(block, 4, signed_field(key, 18, 2), tweak);
  rotate_packets(block, 2, signed_field(key, 20, 1), tweak);
}

static void			uncipher_block(uint8_t			*block,
					       const uint32_t		key)
{
  const int			tweak = (key >> 21) & 0x7;

  rotate_packets(block, 2, -signed_field(key, 20, 1), -tweak);
  rotate_packets(block, 4, -signed_field(key, 18, 2), -tweak);
  rotate_packets(block, 8, -signed_field(key, 15, 3), -tweak);
  rotate_packets(block, 16, -signed_field(key, 11, 4), -tweak);
  rotate_packets(block, 32, -signed_field(key, 6, 5), -tweak);
  rotate_packets(block, 64, -signed_field(key, 0, 6), -tweak);
}

void				__bunny_bitrotate(char			*cnt,
						  size_t		len,
						  const t_bunny_cipher_key *key,
						  bool			cipher)
{
  uint8_t			block[8];
  size_t			i;
  size_t			k;

  if (cnt == NULL || key == NULL || key->length <= 0)
    return ;
  for (i = 0, k = 0; i + 8 <= len; i += 8, ++k)
    {
      memcpy(&block[0], &cnt[i], sizeof(block));
      if (cipher)
	cipher_block(&block[0], read_key(key, k));
      else
	uncipher_block(&block[0], read_key(key, k));
      memcpy(&cnt[i], &block[0], sizeof(block));
    }
}

