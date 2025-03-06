
#include		"flashback.hpp"

extern "C"
t_bunny_response	flashback_loop(Flashback		&fb);

extern "C"
t_bunny_response	flashback_key(t_bunny_event_state	state,
				      t_bunny_keysym		sym,
				      Flashback			&fb)
{
  if (state == GO_DOWN)
    return (GO_ON);
  if (sym == BKS_F1)
    fb.wclock -= 10;
  if (sym == BKS_F2)
    fb.wclock -= 20;
  if (sym == BKS_F3)
    fb.wclock -= 40;
  if (sym == BKS_F4)
    fb.wclock -= 80;

  if (sym >= BKS_F5 && sym <= BKS_F8)
    {
      hbs::Tick now = fb.wclock;

      if (sym == BKS_F5)
	fb.wclock -= 20;
      if (sym == BKS_F6)
	fb.wclock -= 40;
      if (sym == BKS_F7)
	fb.wclock -= 80;
      if (sym == BKS_F8)
	fb.wclock = fb.oldest;

      if (fb.bouncers.size())
	fb.bouncers.clear();
      else
	{
	  fb.bouncers.emplace_back(fb.wclock, std::cerr, fb, RED, 0);
	  fb.bouncers.emplace_back(fb.wclock, std::cerr, fb, GREEN, 1);
	  fb.bouncers.emplace_back(fb.wclock, std::cerr, fb, BLUE, 2);
	}

      while (fb.wclock != now)
	flashback_loop(fb);
    }


  if (fb.wclock < fb.oldest)
    fb.wclock = fb.oldest;


  if (sym == BKS_F12) // Provoquer un ExcessiveLag
    fb.wclock = 0;
  return (GO_ON);
}

