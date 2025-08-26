// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

bool		network::Peer::Dump(t_bunny_configuration	*cnf) const
{
  bool		ok = true;
  int		i;
  
  ok = ok && bunny_configuration_setf_int(cnf, doomed, "Doomed");
  ok = ok && bunny_configuration_setf_double(cnf, last_message, "LastMessage");
  i = 0;
  for (auto it = descriptors.begin(); it != descriptors.end(); ++it)
    ok = ok && bunny_configuration_setf_int(cnf, (*it)->position, "Descriptors[%d]", i++);

  i = 0;
  for (auto it = outqueue.begin(); it != outqueue.end(); ++it)
    {
      char	buffer[128];
      char	*tmp = &buffer[0];
      size_t	j;

      bunny_write_cstring((*it).data.data(), &tmp, sizeof(buffer) - 4);
      j = strlen(buffer);
      if (j >= (*it).data.size())
	{
	  buffer[j++] = '.';
	  buffer[j++] = '.';
	  buffer[j++] = '.';
	}
      buffer[j] = 0;

      ok = ok && bunny_configuration_setf_string(cnf, buffer, "OutputQueue[%d].Content", i);
      ok = ok && bunny_configuration_setf_int(cnf, (int)(*it).data.size(), "OutputQueue[%d].Length", i);
      i = i + 1;
    }
  return (ok);
}

