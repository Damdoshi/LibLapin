// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	<string.h>
#include	"lapin_private.h"

bool		SmallConf::operator==(const SmallConf			&o) const
{
  if (last_type != o.last_type)
    return (false);
  if (last_type == INTEGER)
    {
      int	a, b;

      if (GetInt(&a) == false || o.GetInt(&b) == false)
	return (false);
      return (a == b);
    }
  if (last_type == DOUBLE)
    {
      double	a, b;

      if (GetDouble(&a) == false || o.GetDouble(&b) == false)
	return (false);
      return (a == b);
    }
  if (last_type == STRING)
    {
      const char *a, *b;

      if (GetString(&a) == false || o.GetString(&b) == false)
	return (false);
      return (strcmp(a, b) == 0);
    }
  return (false);
}

bool		SmallConf::operator!=(const SmallConf			&o) const
{
  return (!((*this) == o));
}

bool		SmallConf::operator<(const SmallConf			&o) const
{
  if (last_type != o.last_type)
    return (false);
  if (last_type == INTEGER)
    {
      int	a, b;

      if (GetInt(&a) == false || o.GetInt(&b) == false)
	return (false);
      return (a < b);
    }
  if (last_type == DOUBLE)
    {
      double	a, b;

      if (GetDouble(&a) == false || o.GetDouble(&b) == false)
	return (false);
      return (a < b);
    }
  if (last_type == STRING)
    {
      const char *a, *b;

      if (GetString(&a) == false || o.GetString(&b) == false)
	return (false);
      return (strcmp(a, b) < 0);
    }
  return (false);
}

bool		SmallConf::operator<=(const SmallConf			&o) const
{
  if (last_type != o.last_type)
    return (false);
  if (last_type == INTEGER)
    {
      int	a, b;

      if (GetInt(&a) == false || o.GetInt(&b) == false)
	return (false);
      return (a <= b);
    }
  if (last_type == DOUBLE)
    {
      double	a, b;

      if (GetDouble(&a) == false || o.GetDouble(&b) == false)
	return (false);
      return (a <= b);
    }
  if (last_type == STRING)
    {
      const char *a, *b;

      if (GetString(&a) == false || o.GetString(&b) == false)
	return (false);
      return (strcmp(a, b) <= 0);
    }
  return (false);
}

bool		SmallConf::operator>(const SmallConf			&o) const
{
  if (last_type != o.last_type)
    return (false);
  if (last_type == INTEGER)
    {
      int	a, b;

      if (GetInt(&a) == false || o.GetInt(&b) == false)
	return (false);
      return (a > b);
    }
  if (last_type == DOUBLE)
    {
      double	a, b;

      if (GetDouble(&a) == false || o.GetDouble(&b) == false)
	return (false);
      return (a > b);
    }
  if (last_type == STRING)
    {
      const char *a, *b;

      if (GetString(&a) == false || o.GetString(&b) == false)
	return (false);
      return (strcmp(a, b) > 0);
    }
  return (false);
}

bool		SmallConf::operator>=(const SmallConf			&o) const
{
  if (last_type != o.last_type)
    return (false);
  if (last_type == INTEGER)
    {
      int	a, b;

      if (GetInt(&a) == false || o.GetInt(&b) == false)
	return (false);
      return (a >= b);
    }
  if (last_type == DOUBLE)
    {
      double	a, b;

      if (GetDouble(&a) == false || o.GetDouble(&b) == false)
	return (false);
      return (a >= b);
    }
  if (last_type == STRING)
    {
      const char *a, *b;

      if (GetString(&a) == false || o.GetString(&b) == false)
	return (false);
      return (strcmp(a, b) >= 0);
    }
  return (false);
}
