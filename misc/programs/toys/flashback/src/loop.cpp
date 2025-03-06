
#include		"flashback.hpp"

extern "C"
t_bunny_response	flashback_loop(Flashback	&fb)
{
  hbs::Tick		oldest = -1;  
  size_t		i;
  size_t		j;

  for (i = 0; i < fb.balls.size(); ++i)
    {
      BallBase		&ball = fb.balls[i];

      auto tmp = fb.balls[i].OldestTick();
      if (tmp < oldest)
	oldest = tmp;
      ball.position += ball.speed;
      if (ball.position.x < 0 || ball.position.x >= fb.window->buffer.width)
	ball.speed.x *= -1;
      if (ball.position.y < 0 || ball.position.y >= fb.window->buffer.height)
	ball.speed.y *= -1;

      for (j = 0; j < fb.bouncers.size(); ++j)
	{
	  BouncerBase	&bouncer = fb.bouncers[j];
	  
	  if (ball.position.x > bouncer.position.x &&
	      ball.position.x < bouncer.position.x + bouncer.size.x)
	    ball.speed.x *= -1;
	}
    }
  fb.oldest = oldest;
  fb.wclock += 1;
  return (GO_ON);
}

