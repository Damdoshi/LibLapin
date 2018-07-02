/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** LibLapin Test
*/

#include		<map>
#include		<iostream>
#include		<assert.h>
#include		<lapin.h>

int			main(int	argc,
			     char	**argv)
{
  Bunny::IdString	hcstr = "hardcoded string"_IS;
  std::map<uint64_t, std::string> collide_detector;
  int			i;

  std::cout << "Hardcoded string: " << hcstr << std::endl;
  assert(hcstr == "hardcoded string");
  assert(hcstr == "hardcoded string"_IS);
  for (i = 1; i < argc; ++i)
    {
      std::string	dstr = argv[i];
      Bunny::IdString	istr = argv[i];

      hcstr = argv[i];
      assert(hcstr == argv[i]);
      assert(!(hcstr != argv[i]));
      assert(!(hcstr < argv[i]));

      assert(hcstr == dstr);
      assert(!(hcstr != dstr));
      assert(!(hcstr < dstr));

      assert(hcstr == istr);
      assert(!(hcstr != istr));
      assert(!(hcstr < istr));

      std::string	_hcstr = hcstr;

      assert(_hcstr == argv[i]);

      const char	*_dstr = hcstr;

      assert(strcmp(_dstr, hcstr) == 0);

      uint64_t		h1, h2;

      h1 = hcstr;
      h2 = istr;
      assert(h1 == h2);

      if (collide_detector.find(h1) == collide_detector.end())
	collide_detector[h1] = (const char*)hcstr;
      else if (hcstr != collide_detector[h1])
	{
	  std::cout << collide_detector[h1] << " collide with " << hcstr << std::endl;
	  assert(hcstr != collide_detector[h1]);
	}

      std::cout << hcstr << " (" << h1 << ") " << "OK!" << std::endl;
    }
  return (EXIT_FAILURE);
}
