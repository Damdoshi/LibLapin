/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** LibLapin Test
*/

#include		<iostream>
#include		<assert.h>
#include		<lapin.h>

class			LocalContext : public Bunny::Context<LocalContext>
{
 public:
  t_bunny_window	*win;
  size_t		i;

  t_bunny_response	Loop(void)
  {
    if (++i > 5)
      return (EXIT_ON_SUCCESS);
    std::cout << "Loop" << std::endl;
    return (GO_ON);
  }

  t_bunny_response	Entering(void)
  {
    i = 0;
    std::cout << "Entering" << std::endl;
    return (GO_ON);
  }

  void			Leaving(t_bunny_response	rs)
  {
    (void)rs;
    std::cout << "Leaving" << std::endl;
  }

  LocalContext(void)
    : i(rand())
  {}
  ~LocalContext(void)
  {}
};

int			main(void)
{
  LocalContext		lc;

  assert(lc.win = bunny_start(640, 480, false, "Context test"));
  Bunny::SetContext(lc);
  assert(bunny_loop(lc.win, 20, &lc) == EXIT_ON_SUCCESS);
  assert(lc.i == 6);
  bunny_stop(lc.win);
  return (EXIT_FAILURE);
}

