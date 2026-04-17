// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#ifndef			__LAPIN_NETWORK_PROTOCOL_SPEC_HPP__
# define		__LAPIN_NETWORK_PROTOCOL_SPEC_HPP__
# include		"communication.hpp"
# include		"lapin.h"

namespace		network
{
  struct		ProtoSpec
  {
    bool		pcol_set = false;
    Protocol		protocol = BP_UDP_RELIABLE;
    size_t		size = 1024 * 64;
    char		terminator = '\0';
    int			timeout = 3000;
    bool		resend = true;
    
    ProtoSpec		&operator=(const ProtoSpec	&proto)
    {
      if (this != &proto)
	memcpy(this, &proto, sizeof(*this));
      return (*this);
    }

    bool		operator==(Protocol		proto) const
    {
      return (pcol_set && protocol == proto);
    }

    operator		bool(void) const
    {
      return (pcol_set);
    }

    bool		Dump(t_bunny_configuration	*cnf) const
    {
      const char	*proto[] = {"UDP", "TCP", "RDM", "FixedTCP", "SizedTCP", "TerminatedTCP"};
      bool		ok = true;

      ok = ok && bunny_configuration_setf_string(cnf, proto[protocol], "Protocol");
      if (protocol == BP_TCP_FIXED_SIZE || protocol == BP_TCP_SIZED_PLUS_DATA)
	ok = ok && bunny_configuration_setf_int(cnf, (int)size, "Size");
      if (protocol == BP_TCP_TERMINATED_DATA)
	{
	  char	term[2] = {terminator, 0};

	  ok = ok && bunny_configuration_setf_string(cnf, &term[0], "Terminator");
	}
      if (protocol == BP_UDP_RELIABLE)
	{
	  ok = ok && bunny_configuration_setf_int(cnf, timeout, "Timeout");
	  ok = ok && bunny_configuration_setf_int(cnf, (int)resend, "Resend");
	}
      return (ok);
    }
  };
}

#endif
