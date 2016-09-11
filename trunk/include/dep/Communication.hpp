// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#ifndef			__BPT_COMMUNICATION_HPP__
# define		__BPT_COMMUNICATION_HPP__
# undef			ERROR

namespace		bpt
{
  namespace		NetCom
  {
    typedef union	u_Buffer
    {
      char		*character;
      void		*unknown;
    }			Buffer;
    typedef union	u_ConstBuffer
    {
      const char	*character;
      const void	*unkown;
    }			ConstBuffer;

    typedef enum	e_ComType
      {
	ERROR		= 0,
	EXPIRED		= 1,
	CONNECTED	= 2,
	DISCONNECTED	= 3,
	MESSAGE		= 4
      }			ComType;
    typedef enum	e_ErrorType
      {
	SYSTEM_FAIL	= 0,
	SELECT_FAIL	= 1,
	ACCEPT_FAIL	= 2,
	WRITE_FAIL	= 3,
	READ_FAIL	= 4,
	ALLOC_FAIL	= 5,
	GETTIME_FAIL	= 6,
	LAST_ERROR
      }			ErrorType;
    typedef struct	s_Error
    {
      ComType		comtype;
      unsigned int	time;
      ErrorType		errortype;
    }			Error;
    typedef struct	s_Expired
    {
      ComType		comtype;
      unsigned int	time;
    }			Expired;
    typedef struct	s_Connected
    {
      ComType		comtype;
      unsigned int	time;
      unsigned int	client;
    }			Connected;
    typedef struct	s_Disconnected
    {
      ComType		comtype;
      unsigned int	time;
      unsigned int	client;
    }			Disconnected;
    typedef struct	s_Message
    {
      ComType		comtype;
      unsigned int	time;
      unsigned int	client;
      unsigned int	size;
      Buffer		buffer;
    }			Message;
    typedef struct	s_Info
    {
      ComType		comtype;
      unsigned int	time;
      unsigned int	client;
    }			Info;
    typedef union	u_Communication
    {
      ComType		comtype;
      Error		error;
      Expired		expired;
      Connected		connected;
      Disconnected	disconnected;
      Message		message;
      Info		info;
    }			Communication;
  }
}

#endif	//		__BPT_COMMUNICATION_HPP__
