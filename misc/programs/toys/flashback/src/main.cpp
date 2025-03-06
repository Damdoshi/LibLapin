
#include		"flashback.hpp"

BallBase::BallBase(const Flashback &fb)
  : position({(double)(rand() % fb.window->buffer.width), (double)(rand() % fb.window->buffer.height)}),
    speed({(rand() % 3000) / 100.0 - 15, (rand() % 3000) / 100.0 - 15})
{
  unsigned int cols[4] = {RED, GREEN, BLUE, TEAL};
  int cnt = fb.window->buffer.width / 4;
  int col = position.x / cnt;

  color = cols[col];
}

BouncerBase::BouncerBase(const Flashback &fb,
			 unsigned int col,
			 int c)
  : BallBase(fb)
{
  size.x = 50;
  size.y = fb.window->buffer.height;
  position.x = (c + 1.0) / 4.0 * fb.window->buffer.width;
  position.y = 0;
  speed.x = speed.y = 0;
  color = col;
}

extern "C" {
  bunny_declare_context(flashback);
}

t_bunny_context		context[1] =
  {
    {
      .key = flashback_key,
      .loop = flashback_loop,
      .display = flashback_display
    }
  };

int			main(void)
{
  static Flashback	fb;
  
  fb.window = bunny_start(1440, 900, false, "Flashback");
  fb.balls.reserve(5000);
  for (int i = 0; i < 100; ++i)
    fb.balls.emplace_back(fb.wclock, std::cerr, fb);
  bunny_set_context(&context[0]);
  try {
    bunny_loop(fb.window, 50, &fb);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  bunny_stop(fb.window);
  return (0);
}

