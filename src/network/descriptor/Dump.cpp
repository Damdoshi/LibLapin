// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		network::Descriptor::Dump(t_bunny_configuration	*cnf,
					  size_t		index) const
{
  const char	*proto[] = {"UDP", "FixedTCP", "SizedTCP", "TerminatedTCP"};
  bool		ok = true;
  
  ok = ok && bunny_configuration_setf_string(cnf, proto[protocol], "Descriptors[%zu].Protocol", index);
  if (protocol == FIXED_SIZE || protocol == SIZE_PLUS_DATA)
    ok = ok && bunny_configuration_setf_int(cnf, (int)size, "Descriptors[%zu].Size", index);
  if (protocol == TERMINATED)
    {
      char	term[2] = {terminator, 0};

      ok = ok && bunny_configuration_setf_string(cnf, &term[0], "Descriptors[%zu].Terminator", index);
    }
  ok = ok && bunny_configuration_setf_int(cnf, position, "Descriptors[%zu].PollPosition", index);
  ok = ok && bunny_configuration_setf_int(cnf, active, "Descriptors[%zu].Active", index);
  ok = ok && bunny_configuration_setf_int(cnf, doomed, "Descriptors[%zu].Doomed", index);
  ok = ok && bunny_configuration_setf_int(cnf, fd, "Descriptors[%zu].Descriptor", index);
  ok = ok && bunny_configuration_setf_int(cnf, ip, "Descriptors[%zu].IP", index);
  ok = ok && bunny_configuration_setf_int(cnf, (int)port, "Descriptors[%zu].Port", index);

  // Outqueue data
  int		i = 0;

  for (auto it = outqueue.begin(); it != outqueue.end(); ++it)
    {
      char	buffer[128];
      char	*tmp = &buffer[0];
      size_t	j;
#define min(a, b) (((a) < (b)) ? (a) : (b))
      size_t	minn = min(sizeof(buffer) - 4, (*it).size);

      bunny_write_cstring((*it).data, &tmp, minn);
      j = strlen(buffer);
      if (j >= (*it).size)
	{
	  buffer[j++] = '.';
	  buffer[j++] = '.';
	  buffer[j++] = '.';
	}
      buffer[j] = 0;

      ok = ok && bunny_configuration_setf_string(cnf, buffer, "Descriptors[%zu].OutputQueue[%d].Content", index, i);
      ok = ok && bunny_configuration_setf_int(cnf, (int)(*it).size, "Descriptors[%zu].OutputQueue[%d].Length", index, i);
      i = i + 1;
    }
  if (outqueue.size())
    ok = ok && bunny_configuration_setf_int(cnf, wcursor, "Descriptors[%zu].OutputQueue[0].Written", index);
  
  // Inqueue data
  i = 0;
  for (auto it = inqueue.begin(); it != inqueue.end(); ++it)
    {
      char	buffer[128];
      char	*tmp = &buffer[0];
      size_t	j;
      size_t	minn = min(sizeof(buffer) - 4, (*it).size);

      bunny_write_cstring((*it).data, &tmp, minn);
      j = strlen(buffer);
      if (j <= (*it).size)
	{
	  buffer[j++] = '.';
	  buffer[j++] = '.';
	  buffer[j++] = '.';
	}
      buffer[j] = 0;

      ok = ok && bunny_configuration_setf_string(cnf, buffer, "Descriptors[%zu].InputQueue[%d].Content", index, i);
      ok = ok && bunny_configuration_setf_int(cnf, (int)(*it).size, "Descriptors[%zu].InputQueue[%d].Length", index, i);
      i = i + 1;
    }
  if (inbuffer)
    {
      ok = ok && bunny_configuration_setf_int(cnf, rcursor, "Descriptors[%zu].CurrentInputBufferSize", index);
    }

  return(ok);
}

