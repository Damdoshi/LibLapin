// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include		<string.h>
#define			__LAPIN_H__
#include		"private2/logs.hpp"

void			bunny_filter_label(const char		*labels)
{
  int			i, j;

  bunny::AcceptedLabels.clear();
  if (labels && *labels)
    for (i = j = 0; labels[i]; i = j)
      {
	if (labels[i] == ',')
	  i += 1;
	for (j = i; labels[j] != ',' && labels[j]; ++j);
	bunny::AcceptedLabels.emplace_back(&labels[i], j - i);
      }
}

