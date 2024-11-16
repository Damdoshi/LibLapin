/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2025
** Pentacle Technologie 2008-2025
** EFRITS 2022-2025
**
** Bibliothèque Lapin
*/

#include		<assert.h>
#define			private			public
#define			protected		public
#include		"lapin_private.hpp"

int			main(void)
{
  network::Peer		p;
  char			zero[sizeof(network::Info)];

  memset(zero, 0, sizeof(zero));
  assert(memcmp(p.info, zero) == 0);
  assert(p.descriptors.empty());
  assert(p.outqueue.empty());

  assert((bool)p == false);
  const network::Info	&info = p;
  assert(&info == &p.info);
  assert(p == info);
  assert(!(p != info));
  assert((int)p == 0);
  assert(p = info);
  assert(p == info);

  assert(p.PopWriteRequest() == false);

  assert(p.Write("abcd", 4));
  assert(p.outqueue.first().size() == 4);
  assert(p.PopWriteRequest());
  assert(p.Write(zero));
  assert(p.outqueue.first().size() == sizeof(zero));
  p << zero;
  assert(p.PopWriteRequest());
  assert(p.PopWriteRequest());
  assert(p.PopWriteRequest() == false);

  return (0);
}

