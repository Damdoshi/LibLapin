// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include	"lapin_private.h"

int		Network::Dump(int		fd) const
{
  t_bunny_configuration *tmp;
  t_bunny_configuration *sub;
  size_t	index;
  ssize_t	len;
  ssize_t	ret;
  char		*out;

  tmp = bunny_new_configuration();
  bunny_configuration_setf_int(tmp, (int)nbr, "MaxIndex");
  index = 0;
  for (auto it = peers.begin(); it != peers.end(); ++it)
    {
      if (!bunny_configuration_setf_string(tmp, "", "Peers[%zu].NetInfo", index))
	goto FreeLeave;
      if (!bunny_configuration_getf_node(tmp, &sub, "Peers[%zu]", index))
	goto FreeLeave;
      if (!it->first.Dump(sub))
	goto FreeLeave;
      if (!it->second.Dump(sub))
	goto FreeLeave;
      index += 1;
    }

  for (index = 0; index < nbr; ++index)
    if (descriptors[index].Dump(tmp, index) == false)
      goto FreeLeave;

  out = bunny_write_configuration(BC_DABSIC, tmp);

  if (!out)
    goto FreeLeave;
  bunny_delete_configuration(tmp);
  len = strlen(out);
  index = 0;
  do
    {
      if ((ret = write(fd, &out[index], len - index)) == -1)
	{
	  bunny_free(out);
	  return (-index);
	}
      index += ret;
    }
  while (ret > 0);
  bunny_free(out);
  return (index);

 FreeLeave:
  bunny_delete_configuration(tmp);
  return (0);
}
