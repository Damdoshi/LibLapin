/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2026
** Pentacle Technologie 2008-2026
** EFRITS 2022-2026
**
** Bibliothèque Lapin
*/

#include		<assert.h>
#include		<stdint.h>
#include		<stdlib.h>
#include		<string.h>
#include		"lapin.h"

static void		assert_bits(const t_bunny_bitfield	*bf,
				    const size_t			*bits,
				    size_t			 nbits,
				    size_t			 len)
{
  size_t		i;
  size_t		j;
  bool			expected;

  for (i = 0; i < len; ++i)
    {
      expected = false;
      for (j = 0; j < nbits; ++j)
	if (bits[j] == i)
	  expected = true;
      assert(bunny_bitfield_get(bf, i) == expected);
    }
}

static void		test_heap_bitfield_set_clear_get(void)
{
  t_bunny_bitfield	*bf;
  size_t		set_bits[] = {0, 1, 7, 8, 31, 32, 63, 64, 69};
  size_t		after_clear[] = {0, 7, 8, 31, 32, 64, 69};
  size_t		i;

  assert((bf = bunny_new_bitfield(70)) != NULL);
  for (i = 0; i < 70; ++i)
    assert(bunny_bitfield_get(bf, i) == false);
  for (i = 0; i < NBRCELL(set_bits); ++i)
    bunny_bitfield_set(bf, set_bits[i]);
  assert_bits(bf, set_bits, NBRCELL(set_bits), 70);
  bunny_bitfield_clr(bf, 1);
  bunny_bitfield_clr(bf, 63);
  assert_bits(bf, after_clear, NBRCELL(after_clear), 70);
  bunny_bitfield_clr(bf, 63);
  assert_bits(bf, after_clear, NBRCELL(after_clear), 70);
  bunny_delete_bitfield(bf);
}

static void		test_auto_bitfields(void)
{
  t_bunny_auto_bitfield8	bf8 = 0;
  t_bunny_auto_bitfield16 bf16 = 0;
  t_bunny_auto_bitfield32 bf32 = 0;
  t_bunny_auto_bitfield64 bf64 = 0;

  bunny_auto_bitfield_set(bf8, 7);
  bunny_auto_bitfield_set(bf16, 15);
  bunny_auto_bitfield_set(bf32, 31);
  bunny_auto_bitfield_set(bf64, 63);
  assert(bunny_auto_bitfield_get(bf8, 7));
  assert(bunny_auto_bitfield_get(bf16, 15));
  assert(bunny_auto_bitfield_get(bf32, 31));
  assert(bunny_auto_bitfield_get(bf64, 63));
  bunny_auto_bitfield_clr(bf8, 7);
  bunny_auto_bitfield_clr(bf16, 15);
  bunny_auto_bitfield_clr(bf32, 31);
  bunny_auto_bitfield_clr(bf64, 63);
  assert(!bunny_auto_bitfield_get(bf8, 7));
  assert(!bunny_auto_bitfield_get(bf16, 15));
  assert(!bunny_auto_bitfield_get(bf32, 31));
  assert(!bunny_auto_bitfield_get(bf64, 63));
}

static void		test_binary_rotations(void)
{
  uint8_t		a = 0x81;
  uint16_t		b = 0x8001;
  uint32_t		c = 0x80000001u;

  assert((uint8_t)bunny_left_binary_rotation(a, 0) == 0x81);
  assert((uint8_t)bunny_right_binary_rotation(a, 0) == 0x81);
  assert((uint8_t)bunny_left_binary_rotation(a, 8) == 0x81);
  assert((uint8_t)bunny_right_binary_rotation(a, 8) == 0x81);
  assert((uint8_t)bunny_left_binary_rotation(a, 1) == 0x03);
  assert((uint8_t)bunny_right_binary_rotation(a, 1) == 0xC0);
  assert((uint16_t)bunny_left_binary_rotation(b, 1) == 0x0003);
  assert((uint16_t)bunny_right_binary_rotation(b, 1) == 0xC000);
  assert((uint32_t)bunny_left_binary_rotation(c, 4) == 0x00000018u);
  assert((uint32_t)bunny_right_binary_rotation(c, 4) == 0x18000000u);
}

static void		test_bitfield_rotations(void)
{
  t_bunny_bitfield	*bf;
  size_t		initial[] = {0, 1, 9};
  size_t		left[] = {1, 2, 3};
  size_t		right[] = {0, 1, 9};
  size_t		wrapped[] = {0, 8, 9};
  size_t		i;

  assert((bf = bunny_new_bitfield(16)) != NULL);
  for (i = 0; i < NBRCELL(initial); ++i)
    bunny_bitfield_set(bf, initial[i]);
  bunny_left_bitfield_rotation(bf, 10, 0);
  assert_bits(bf, initial, NBRCELL(initial), 10);
  bunny_left_bitfield_rotation(bf, 10, 2);
  assert_bits(bf, left, NBRCELL(left), 10);
  bunny_right_bitfield_rotation(bf, 10, 2);
  assert_bits(bf, right, NBRCELL(right), 10);
  bunny_right_bitfield_rotation(bf, 10, 11);
  assert_bits(bf, wrapped, NBRCELL(wrapped), 10);
  bunny_left_bitfield_rotation(bf, 0, 3);
  assert_bits(bf, wrapped, NBRCELL(wrapped), 10);
  bunny_right_bitfield_rotation(NULL, 10, 3);
  bunny_delete_bitfield(bf);
}

static void		test_stack_bitfield(void)
{
  t_bunny_bitfield	*bf = bunny_new_abitfield(24);
  size_t		i;

  memset(bf, 0, 3);
  bunny_bitfield_set(bf, 0);
  bunny_bitfield_set(bf, 23);
  for (i = 0; i < 24; ++i)
    assert(bunny_bitfield_get(bf, i) == (i == 0 || i == 23));
}

static void		test_allocation_failure(void)
{
  bunny_malloc_failure(true);
  assert(bunny_new_bitfield(64) == NULL);
  bunny_malloc_failure(false);
}

int			main(void)
{
  test_heap_bitfield_set_clear_get();
  test_auto_bitfields();
  test_binary_rotations();
  test_bitfield_rotations();
  test_stack_bitfield();
  test_allocation_failure();
  return (EXIT_SUCCESS);
}
