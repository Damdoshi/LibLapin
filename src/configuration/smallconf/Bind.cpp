// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	<string.h>
#include	"lapin_private.h"

void		SmallConf::Bind(int	*v)
{
  GetInt(v);
  distant_int = v;
}

void		SmallConf::Bind(double	*v)
{
  GetDouble(v);
  distant_double = v;
}

void		SmallConf::Bind(char	*v)
{
  int		i;

  GetInt(&i);
  *v = i & 0xFF;
  distant_char = v;
}

void		SmallConf::Bind(char	**v)
{
  GetString((const char**)v);
  distant_string = v;
}

void		SmallConf::Unbind(void)
{
  distant_int = NULL;
  distant_double = NULL;
  distant_char = NULL;
  distant_string = NULL;
}

