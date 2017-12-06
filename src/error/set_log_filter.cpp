// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<iostream>
#include		"lapin_private.h"

std::vector<std::string> gl_log_filter;

bool			bunny_filter_label(const char	*labels)
{
  size_t		i;

  if (gl_log_filter.empty())
    return (true);
  for (i = 0; i < gl_log_filter.size(); ++i)
    if (strstr(labels, gl_log_filter[i].c_str()) != NULL)
      return (true);
  return (false);
}

void			bunny_set_log_filter(const char	*label)
{
  std::string		str;
  int			i, j;

  i = j = 0;
  gl_log_filter.clear();
  while (label[j] && label[i])
    {
      for (j = i; label[j] && label[j] != ','; ++j);
      str.assign(&label[i], j - i);
      gl_log_filter.push_back(str);
      i = j + 1;
    }
}
