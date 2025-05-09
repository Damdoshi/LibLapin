// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include		"lapin_private.h"

double			Network::Poll(double			tmout,
				      bool			rasap)
{
  struct timespec	bef;
  struct timespec	now;
  int			rd;
  size_t		i;

  tmout /= 1000.0;
  do
    {
      clock_gettime(CLOCK_MONOTONIC, &bef);
      MoveWriteRequest();
      clock_gettime(CLOCK_MONOTONIC, &now);
      if ((tmout -= (now.tv_sec - bef.tv_sec) + (now.tv_nsec - bef.tv_nsec) / 1e9) < 0)
	tmout = 0; // Faut augmenter le timeout la...
      bef = now;

      // Monitor I/O
      if ((rd = poll(pollfd, nbr, tmout * 1000)) == -1)
	{
	  //
	  return (nan(""));
	}

      // Handle I/O
      for (i = 0; i < nbr && rd > 0; ++i)
	if (pollfd[i].revents)
	  {
	    Descriptor &desc = descriptors[i];

	    if (pollfd[i].revents & POLLIN)
	      {
		if (desc.protocol != network::Descriptor::IMMEDIATE_RETRIEVE && desc.ip == 0)
		  desc.Accept(pollfd, nbr, NBRCELL(pollfd));
		else
		  desc.Read();
	      }
	    if (pollfd[i].revents & POLLOUT)
	      desc.Write();
	    if (desc.IsDoomed() && !desc.GetReceivedPacketCount() && !desc.GetSendingPacketCount())
	      Close(i);
	    rd -= 1;
	  }
      // Check if there is more time to do another loop
      clock_gettime(CLOCK_MONOTONIC, &now);
      if ((tmout -= (now.tv_sec - bef.tv_sec) + (now.tv_nsec - bef.tv_nsec) / 1e9) < 0)
	tmout = 0;      
    }
  while (!rasap && tmout > 0);
  return (tmout);
}

double			Network::operator()(double		tmout,
					    bool		rasap)
{
  return (Poll(tmout, rasap));
}
