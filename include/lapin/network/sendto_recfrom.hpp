// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#ifndef			__LAPIN_NETWORK_SENDTORECVFROM_HPP__
# define		__LAPIN_NETWORK_SENDTORECVFROM_HPP__

class			SendToRecvFromPeer : public Descriptor
{
private:
  ssize_t		Write(const char	*data,
			      size_t		datalen) const
  {
    return (sendto(fd, data, datalen, 0, (sockaddr*)&sockaddr, socklen));
  }
  ssize_t		Read(char		*data,
			     size_t		datalen) const
  {
    /// probleme ici, une socket TCP détermine un pair, pas une socket UDP...
    /// donc mon design est naze. je me suis encore fait avoir par ma méconnaissance d'UDP.
    return (read(fd, data, datalen));
  }
};

#endif	//		__LAPIN_NETWORK_SENDTORECVFROM_HPP__

