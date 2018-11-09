// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	<string.h>
#include	"lapin_private.h"

void		SmallConf::Bind(int	*v)
{
  if (GetInt(v) == false)
    SetInt(*v);
  distant_int = v;
}

void		SmallConf::Bind(double	*v)
{
  if (GetDouble(v) == false)
    SetDouble(*v);
  distant_double = v;
}

void		SmallConf::Bind(char	*v)
{
  int		i;

  if (GetInt(&i) == false)
    SetInt((int)*v & 0xFF);
  else
    *v = i & 0xFF;
  distant_char = v;
}

void		SmallConf::Bind(bool	*v)
{
  int		i;

  if (GetInt(&i) == false)
    SetInt(!!(int)*v);
  else
    *v = !!i;
  distant_bool = v;
}

void		SmallConf::Bind(char	**v)
{
  if (GetString((const char**)v) == false)
    {
      if (!*v)
	*v = bunny_strdup("");
      SetString(*v);
    }
  distant_string = v;
}

void		SmallConf::Unbind(void)
{
  distant_int = NULL;
  distant_double = NULL;
  distant_char = NULL;
  distant_string = NULL;
}

