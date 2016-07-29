// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2014
//
// INI io system

#include		<cstdlib>
#include		"Ini.hpp"

const bpt::string	&bpt::Ini::Access(const bpt::string	&scope,
					  const bpt::string	&field,
					  unsigned int		_case) const
{
  std::map<bpt::string, Scope>::const_iterator			it0;

  if ((it0 = datas.find(scope)) == datas.end())
    return (errmsg = "ini: cannot find scope.");
  std::map<bpt::string, FieldValue>::const_iterator		it1;

  if ((it1 = it0->second.find(field)) == it0->second.end())
    return (errmsg = "ini: cannot find field.");

  if (it1->second.size() <= _case)
    return (errmsg = "ini: array index is out of range.");

  return (it1->second[_case]);
}

bpt::string		&bpt::Ini::Access(const bpt::string	&scope,
					  const bpt::string	&field,
					  unsigned int		_case)
{
  std::vector<bpt::string>					&r = datas[scope][field];

  if (_case >= r.size())
    r.resize(_case + 1);
  return (r[_case]);
}

int			bpt::Ini::AccessInt(const bpt::string	&code,
					    const bpt::string	&field,
					    unsigned int	_case)
{
  return (std::atoi(Access(code, field, _case).c_str()));
}

int			bpt::Ini::AccessInt(const bpt::string	&code,
					    const bpt::string	&field,
					    unsigned int	_case) const
{
  const bpt::string	&str = Access(code, field, _case);

  if (&str == &npos)
    return (0);
  return (std::atoi(str.c_str()));
}

double			bpt::Ini::AccessDbl(const bpt::string	&code,
					    const bpt::string	&field,
					    unsigned int	_case)
{
  return (std::atof(Access(code, field, _case).c_str()));
}

double			bpt::Ini::AccessDbl(const bpt::string	&code,
					    const bpt::string	&field,
					    unsigned int	_case) const
{
  const bpt::string	&str = Access(code, field, _case);

  if (&str == &npos)
    return (0);
  return (std::atof(str.c_str()));
}
