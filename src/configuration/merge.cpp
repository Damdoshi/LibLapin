// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Lapin library

#include	"lapin_private.h"

static void	RightToLeft(SmallConf				&l,
			    SmallConf				&r)
{
  if (r.have_value)
    l = r;
  for (auto it = r.Begin(); it != r.End(); ++it)
    RightToLeft(l[it->first], *it->second);
  for (size_t i = 0; i < r.Size(); ++i)
    RightToLeft(l[i], r[i]);
}

bool		bunny_configuration_merge(int			cnt,
					  t_bunny_configuration	*target,
					  ...)
{
  bool		cmode = bunny_configuration_get_create_mode();
  SmallConf	*tar = (SmallConf*)target;
  SmallConf	*sub;
  va_list	lst;
  int		i;

  bunny_configuration_create_mode(true);
  va_start(lst, target);
  for (i = 0; i < cnt; ++i)
    {
      if (!(sub = va_arg(lst, SmallConf*)))
	continue ;
      RightToLeft(*tar, *sub);
    }
  bunny_configuration_create_mode(cmode);
  return (true);
}

