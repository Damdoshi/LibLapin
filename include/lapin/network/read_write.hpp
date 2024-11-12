// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#ifndef			__LAPIN_NETWORK_READWRITE_HPP__
# define		__LAPIN_NETWORK_READWRITE_HPP__

class			ReadWritePeer : public Descriptor
{
private:
  ssize_t		Write(const char	*data,
			      size_t		datalen) const
  {
    return (write(fd, data, datalen));
  }
  ssize_t		Read(char		*data,
			     size_t		datalen) const
  {
    return (read(fd, data, datalen));
  }
};

#endif	//		__LAPIN_NETWORK_READWRITE_HPP__

