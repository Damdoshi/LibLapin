// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#ifndef					__COMMUNICATOR_HPP__
# define				__COMMUNICATOR_HPP__
# include				<iostream>
# include				<string>
# include				<queue>
# include				"NetAbs.hpp"
# include				"Communication.hpp"
# define				UNUSED_BUFFER		((char*)-1)
# define				TOO_BIG			((char*)-1)
# undef					ERROR

namespace				bpt
{
  namespace				NetCom
  {
    /// END OF COMMAND ('\r' '\n' '\0')
    extern char				EOC[3];
    typedef enum			e_PacketProtocol
      {
	RAW				= 0,
	SIZABLE
      }					PacketProtocol;

    template <typename T>
    T					To(void					*buffer)
    {
      return ((T)buffer);
    }

    class				Communicator : public bpt::NetAbs::NetAbs
    {
    protected:
      typedef union			u_SizeBuffer
      {
	unsigned int			size;
	char				buffer[4];
      }					SizeBuffer;
      typedef struct			s_WriteRequest
      {
	char				*buffer;
	char				*cursor;
	SizeBuffer			packet_size;
	unsigned char			size_send;
	unsigned char			data_len;

	s_WriteRequest(const void	*buffer,
		       unsigned int	packet,
		       unsigned int	datalen = UMAX);
	~s_WriteRequest(void);
      }					WriteRequest;

      NetAbs::INetAccess::Info		master_info;
      std::string			port;
      Communication			communication;

      NetAbs::INetAccess::WatchedSocket	fds_read;
      NetAbs::INetAccess::WatchedSocket	fds_write;
      NetAbs::INetAccess::WatchedSocket	fds_error;

      unsigned int			max_size;
      unsigned int			chunk_size;
      bool				init;
      const PacketProtocol		protocol;

      Communication			&RetError(ErrorType			error,
						  unsigned int			time);
      Communication			&RetExpired(unsigned int		time);
      unsigned int			MicroSeconds(struct timeval		*now,
						     struct timeval		*before);

      Communicator(void) : protocol(SIZABLE) {}
    public:
      virtual const Communication	&operator()(unsigned int		timeout = 0) = 0;
      virtual bool			Write(const void			*buffer,
					      unsigned int			size,
					      unsigned int			client = 0) = 0;
      void				Error(ErrorType				error);
      void				Obsolete(void);
      void				SetPacketMaxSize(unsigned int		x);
      unsigned int			GetPacketMaxSize(void) const;
      void				SetChunkSize(unsigned int		x);
      unsigned int			GetChunkSize(void) const;
      const Communication		&GetCommunication(void) const;
      bool				IsInit(void) const;

      int				GetFd(void) const;
      
      Communicator(const std::string	&port = "",
		   unsigned int		max_size = 1024 * 4,
		   unsigned int		chunk_size = 512);
      Communicator(PacketProtocol	protocol = SIZABLE,
		   const std::string	&port = "",
		   unsigned int		max_size = 1024 * 4,
		   unsigned int		chunk_size = 512);
      virtual ~Communicator(void);
    };
    bool			operator==(const bpt::NetCom::Communication	&com,
					   bpt::NetCom::ComType			comtype);
    bool			operator==(bpt::NetCom::ComType			comtype,
					   const bpt::NetCom::Communication	&com);
  }
}

#endif	//		__COMMUNICATOR_HPP__
