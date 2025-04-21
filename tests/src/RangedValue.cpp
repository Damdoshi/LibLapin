// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Macroboy Y

#include	<assert.h>
#include	"RangedValue.hpp"

int		main(void)
{
  hbs::RangedValue<int, -2, 5, hbs::ExcessStrategy::LOOP> loop;

  assert((int)(loop = 0) == 0);
  assert(loop + 2 == 2);
  assert(loop + 10 == 10);
  assert(loop - 3 == -3);
  assert(loop * 0 == 0);
  assert(&loop == &loop.val);
  assert((loop = 13) == -1);
  assert((loop = 12) == -2);
  assert((loop = 11) == 4);
  assert((loop = 10) == 3);
  assert((loop = 9) == 2);
  assert((loop = 8) == 1);
  assert((loop = 7) == 0);
  assert((loop = 6) == -1);
  assert((loop = 5) == -2);
  assert((loop = 4) == 4);
  assert((loop = 3) == 3);
  assert((loop = 2) == 2);
  assert((loop = 1) == 1);
  assert((loop = -1) == -1);
  assert((loop = -2) == -2);
  assert((loop = -3) == 4);
  assert((loop = -4) == 3);
  assert((loop = -5) == 2);
  assert((loop = -6) == 1);
  assert((loop = -7) == 0);
  assert((loop = -8) == -1);
  assert((loop = -9) == -2);
  assert((loop = -10) == 4);
  assert((loop = -11) == 3);
  assert((loop = -12) == 2);
  assert(loop * 2 == 4);
  assert(loop / 2 == 1);
  assert(loop % 3 == 2);
  assert(++loop == 3);
  assert(loop++ == 3);
  assert(loop++ == 4);
  assert(loop == -2);
  assert(--loop == 4);
  assert(loop-- == 4);
  assert(loop == 3);
  assert((std::string)loop == "3");

  hbs::RangedValue<int, -2, 5, hbs::ExcessStrategy::CLAMP> clamp;

  assert((clamp = 10) == 4);
  assert((clamp = -5) == -2);

  hbs::RangedValue<int, -2, 5, hbs::ExcessStrategy::THROW> sro;
  bool good = false;

  try
    {
      sro = 20;
    }
  catch (std::logic_error &e)
    {
      assert(std::string(e.what()) == "Value 20 is not in [-2; 5[\n");
      good = true;
    }
  assert(good);
  return (0);
}

