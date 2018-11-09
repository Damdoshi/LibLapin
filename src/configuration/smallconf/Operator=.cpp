// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	<string.h>
#include	"lapin_private.h"

SmallConf	&SmallConf::operator=(const SmallConf		&o)
{
  if (&o == this)
    return (*this);
  switch (o.last_type)
    {
    case INTEGER:
      {
	int tmp;

	o.GetInt(&tmp);
	SetInt(tmp);
	break ;
      }
    case DOUBLE:
      {
	double tmp;

	o.GetDouble(&tmp);
	SetDouble(tmp);
	break ;
      }
    case STRING:
      {
	const char *tmp;

	o.GetString(&tmp);
	SetString(tmp, false);
	break ;
      }
    case RAWSTRING:
      {
	const char *tmp;

	o.GetString(&tmp);
	SetString(tmp, true);
	break ;
      }
    }
  return (*this);
}

SmallConf	&SmallConf::Assign(const SmallConf		&o,
				   SmallConf			*root,
				   SmallConf			*local,
				   SmallConf			*artif,
				   SmallConf			*param)
{
  if (&o == this)
    return (*this);
  switch (o.last_type)
    {
    case INTEGER:
      {
	int tmp;

	o.GetInt(&tmp, root, local, artif, param);
	SetInt(tmp);
	break ;
      }
    case DOUBLE:
      {
	double tmp;

	o.GetDouble(&tmp, root, local, artif, param);
	SetDouble(tmp);
	break ;
      }
    case STRING:
      {
	const char *tmp;

	o.GetString(&tmp, root, local, artif, param);
	SetString(tmp, false);
	break ;
      }
    case RAWSTRING:
      {
	const char *tmp;

	o.GetString(&tmp, root, local, artif, param);
	SetString(tmp, true);
	break ;
      }
    }
  return (*this);
}

