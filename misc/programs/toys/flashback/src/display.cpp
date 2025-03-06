
#include		"flashback.hpp"

inline t_bunny_position tbp(t_bunny_accurate_position a)
{
  t_bunny_position b;

  b.x = a.x;
  b.y = a.y;
  return (b);
}

extern "C"
t_bunny_response	flashback_display(Flashback	&fb)
{
  bpos			siz = {2, 2};
  size_t		i;

  bunny_clear(&fb.window->buffer, BLACK);
  for (i = 0; i < fb.balls.size(); ++i)
    {
      BallBase		&ball = fb.balls[i];

      bunny_set_circle(&fb.window->buffer, tbp(ball.position), siz, ball.color);
    }
  for (i = 0; i < fb.bouncers.size(); ++i)
    {
      BouncerBase	&bouncer = fb.bouncers[i];
      unsigned int	col[3] = {ALPHA(128, RED), ALPHA(128, RED), ALPHA(128, RED)};
      t_bunny_position	pos[3] = {
	{(int)(bouncer.position.x + bouncer.size.x), (int)(bouncer.position.y)},
	{(int)(bouncer.position.x), (int)(bouncer.position.y + bouncer.size.y)},
	{(int)(bouncer.position.x), (int)(bouncer.position.y)}
      };

      bunny_set_polygon(&fb.window->buffer, pos, col);
      pos[2].x = bouncer.position.x + bouncer.size.x;
      pos[2].y = bouncer.position.y + bouncer.size.y;
      bunny_set_polygon(&fb.window->buffer, pos, col);
    }
  for (i = 0; i < fb.wclock; ++i)
    {
      t_bunny_position	p = {(int)i + 5, 5};

      if (i < fb.oldest)
	bunny_set_pixel(&fb.window->buffer, p, WHITE);
      else
	bunny_set_pixel(&fb.window->buffer, p, RED);
    }
  bunny_display(fb.window);
  return (GO_ON);
}
