// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static char		sdb[4 * 1024]; /* sequence debug buffer */

const char		*bunny_sequence_debug(t_bunny_configuration	*cnf)
{
  Sequence		*seq = ((SmallConf*)cnf)->sequence;
  int			start;
  int			end;
  int			i;

  i = 0;
  sdb[0] = '\0';
  if (seq->instruction_pointer.top() < 20)
    {
      start = 0;
      end = seq->instruction_pointer.top() + 20;
    }
  else
    {
      start = seq->instruction_pointer.top() - 20;
      end = start + 40;
    }
  for (; start < end; ++start)
    {
      auto it = seq->labels.find(start);
      Sequence::Line	&line = seq->lines[start];

      i += snprintf(&sdb[i], sizeof(sdb) - i, "%04d %s",
		    start, start == seq->instruction_pointer.top() ? "->" : "  ");
      if (it != seq->labels.end())
	i += snprintf(&sdb[i], sizeof(sdb) - i, "%s:\n", it->second.c_str());
      i += snprintf(&sdb[i], sizeof(sdb) - i, "%s", line.command.c_str());
      for (size_t i = 0; i < line.nbr_parameters; ++i)
	{
	  if (i != 0)
	    i += snprintf(&sdb[i], sizeof(sdb) - i, ",");
	  i += snprintf(&sdb[i], sizeof(sdb) - i, " ");
	  std::stringstream ss;

	  writevalue(ss, line.parameters[i]);
	  i += snprintf(&sdb[i], sizeof(sdb) - i, "%s", ss.str().c_str());
	}
      i += snprintf(&sdb[i], sizeof(sdb) - i, "\n");
    }
  return (&sdb[0]);
}

