// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/logs.hpp"

void			_bunny_log(const char		*proto,
				   const char		*func,
				   t_bunny_log_type	logt,
				   const char		*labels,
				   const char		*msg)
{
  std::vector<
    std::string
    >			v;
  std::string		str(labels);
  size_t		i, j;

  for (i = j = 0; i < str.size(); i = j + 1)
    {
      for (j = i; labels[j] != ',' && labels[j]; ++j);
      v.push_back(str.substr(i, j - i));
    }
  bunny::Log
    (bunny::LogVerbosity,
     std::string(proto),
     std::string(func),
     logt,
     v,
     std::string(msg),
     ""
     );
}

