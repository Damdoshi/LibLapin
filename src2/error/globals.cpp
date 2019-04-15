// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/logs.hpp"

namespace		bunny
{
  std::stack<
    std::pair<int, std::string>
    >			LogStack;
  int			LogVerbosity = 2;
  t_bunny_log_length	LogLength = BLL_SHORT_LOG;
  bool			FlushOnError = true;
  bool			FlushOnReturn = false;
  std::vector<
    std::string>	AcceptedLabels;
  int			LogDescriptor = -1;
  int			FailDescriptor = -1;
  int			CriticalDescriptor = 2;
}


