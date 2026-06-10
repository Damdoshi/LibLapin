// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include		<errno.h>
#include		"lapin_private.h"

double			Network::Poll(double			tmout,
				      bool			rasap)
{
  struct timespec	bef;
  struct timespec	now;
  int			rd;
  size_t		i;
  auto			queue_poll_error = [](Descriptor &desc, int err)
    {
      try
	{
	  desc.inqueue.emplace_back(BCT_POLL_ERROR, err);
	  desc.inqueue.back().info = desc.info;
	}
      catch (...)
	{}
    };

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
	    short revents = pollfd[i].revents;

	    if (revents & POLLNVAL)
	      {
		queue_poll_error(desc, EBADF);
		desc.Close();
		rd -= 1;
		continue;
	      }
	    if (revents & POLLIN)
	      {
		if (istcp(desc.protocol) && desc.ip == 0)
		  desc.Accept(nbr, NBRCELL(pollfd));
		else if (!desc.Read())
		  desc.Doom();
	      }
	    if (revents & POLLOUT)
	      if (!desc.Write())
		desc.Doom();
	    if (revents & POLLERR)
	      {
		queue_poll_error(desc, 0);
		desc.Doom();
	      }
	    if (revents & POLLHUP)
	      {
		if (!(revents & POLLIN))
		  {
		    try
		      {
			desc.inqueue.emplace_back(desc.info, false);
		      }
		    catch (...)
		      {}
		  }
		desc.Doom();
	      }
	    if (desc.IsDoomed() && !desc.GetReceivedPacketCount() && !desc.GetSendingPacketCount())
	      Close(desc.info);
	    rd -= 1;
	  }
      // Check if there is more time to do another loop
      clock_gettime(CLOCK_MONOTONIC, &now);
      if ((tmout -= (now.tv_sec - bef.tv_sec) + (now.tv_nsec - bef.tv_nsec) / 1e9) < 0)
	tmout = 0;
    }
  while (!rasap && tmout > 0);

  // Manage doomed Peers
  for (auto it = peers.begin(); it != peers.end();)
    if (it->second.doomed && !it->second.outqueue.size() && it->second.rudp_pending.empty())
      it = peers.erase(it);
    else
      ++it;
  return (tmout);
}

double			Network::operator()(double		tmout,
					    bool		rasap)
{
  return (Poll(tmout, rasap));
}

