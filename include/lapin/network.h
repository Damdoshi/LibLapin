/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2025
**
** Bibliotheque Lapin
*/

/*!
** \file network.h
** The network module contains facilities to create an asynchronous TCP
** server and a TCP client.
*/

#ifndef				__LAPIN_NETWORK_H__
# define			__LAPIN_NETWORK_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# include			<sys/types.h>
# include			<sys/socket.h>
# include			<netinet/in.h>

# define			BUNNY_NETWORK_MAXIMUM_PACKET_SIZE		(128 * 1024)

typedef void			t_bunny_network;

typedef struct			s_bunny_network_info
{
  struct sockaddr_in		sockaddr;
  socklen_t			socklen;
}				t_bunny_network_info;

int				bunny_infocmp(t_bunny_network_info		a,
					      t_bunny_network_info		b);
t_bunny_network_info		bunny_new_network_info(const char		*ip,
						       uint16_t			port);

typedef enum			e_bunny_comtype
  {
    BCT_NOTHING			= 0,
    BCT_NETCONNECTED		= 1,
    BCT_NETDISCONNECTED		= 2,
    BCT_MESSAGE			= 3,
    BCT_POLL_ERROR		= 4,
    BCT_SENDTO_ERROR		= 5,
    BCT_RECVFROM_ERROR		= 6,
    BCT_MALLOC_ERROR		= 7
  }				t_bunny_comtype;

typedef struct			s_bunny_communication
{
  t_bunny_comtype		comtype;
  t_bunny_network_info		info;
  double			time;
  char				*data;
  size_t			size;
  int				errno_code;
  void				*_private[2];
}				t_bunny_communication;

typedef enum			e_bunny_protocol
  {
    BP_UDP_IMMEDIATE,		// UDP - Return immediatly read data
    BP_TCP_IMMEDIATE,		// TCP - Return immediatly read data
    BP_UDP_RELIABLE,		// UDP - In/out messages, heartbeat, reception confirmation, automatic resend and ping estimation
    BP_TCP_FIXED_SIZE,		// TCP - All packets have the same size
    BP_TCP_SIZED_PLUS_DATA,	// TCP - uint32_t + data
    BP_TCP_TERMINATED_DATA	// TCP - data + uint8_t
  }				t_bunny_protocol;

// Functions that are supposed to be used by programmers
t_bunny_network_info		bunny_network_open(t_bunny_protocol	pcol,
						   size_t		size,
						   char			terminator,
						   int			timeout, // mseconds
						   uint16_t		port,
						   const char		*ip);
bool				bunny_network_doom(t_bunny_network_info	a);
bool				bunny_network_close(t_bunny_network_info a);

int				bunny_network_dump(int			fd);

typedef void			(*t_bunny_written)(t_bunny_network_info	a,
						   void			*wtdata);

bool				bunny_network_writec(t_bunny_network_info a,
						     const void		*data,
						     size_t		len,
						     t_bunny_written	wt,
						     void		*wtdata);
# define			bunny_network_write(a, d, l)	\
  bunny_network_writec(a, d, l, NULL, NULL)

typedef enum			e_bunny_identity_status
  {
    BIS_IDENTITY_REFUSED	= -1,
    BIS_AWAITING_CONFIRMATION	=  0,
    BIS_IDENTITY_CONFIRMED	= +1
  }				t_bunny_identity_status;

// An array of t_bunny_identity is terminated by an empty char identity
# define			IDENTITY_SIZE				64
# define			IDENTITY_SECRET_SIZE			64
typedef struct			s_bunny_identity
{
  char				identity[IDENTITY_SIZE]; // nul terminated
  char				secret[IDENTITY_SECRET_SIZE]; // 512 bits
  t_bunny_identity_status	validated;
  t_bunny_hash			last_challenge;
  t_bunny_network_info		info;
  double			usual_delay; // Last Back and forth / 2 delay
  double			estimated_clock_difference;
  double			last_exchange; // Last exchange date
}				t_bunny_identity;

// Currently connected users
extern t_bunny_identity		gl_bunny_identity[1025];

t_bunny_identity		*bunny_resolve_identity
  (t_bunny_identity		*id,
   t_bunny_network_info		in
   );

typedef enum			s_bunny_standard_command_type
  {
    BSCT_HEARTBEAT		= 0,
    BSCT_HEARTBEAT_RESPONSE,
    BSCT_CHALLENGE_REQUEST,
    BSCT_CHALLENGE,
    BSCT_CHALLENGE_RESPONSE,
    BSCT_CHALLENGE_RESULT,
    BSCT_LAST_STANDARD_COMMAND
    // To be freely extended, starting by number BCST_LAST_STANDARD_COMMAND
  }				t_bunny_standard_command_type;

typedef struct			s_bunny_heartbeat_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_HEARTBEAT
  float				declared_sending_date;
}				t_bunny_heartbeat_command;

typedef struct			s_bunny_heartbeat_response_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_HEARTBEAT_RESPONSE
  float				declared_sending_date;
  float				original_sending_date;
}				t_bunny_heartbeat_response_command;

typedef struct			s_bunny_challenge_request_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_CHALLENGE_REQUEST
  float				declared_sending_date;
  char				identity[IDENTITY_SIZE]; // Who are you?
}				t_bunny_challenge_request_command;

typedef struct			s_bunny_challenge_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_CHALLENGE
  float				declared_sending_date;
  uint8_t			challenge[24];
}				t_bunny_challenge_command;

typedef struct			s_bunny_challenge_response_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_CHALLENGE_RESPONSE
  float				declared_sending_date;
  uint64_t			response;
}				t_bunny_challenge_response_command;

typedef struct			s_bunny_challenge_result_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_CHALLENGE_RESPONSE
  float				declared_sending_date;
  uint8_t			result;
}				t_bunny_challenge_result_command;

typedef struct			s_bunny_clear_standard_command_header
{
  uint8_t			ciphered:1;
  uint32_t			command:31;
  float				declared_sending_date;
}				t_bunny_clear_standard_command_header;

typedef struct			s_bunny_ciphered_standard_command_header
{
  uint8_t			ciphered:1;
  uint32_t			command:31;
  float				declared_sending_date;
  uint8_t			mask_source[8];
}				t_bunny_ciphered_standard_command_header;

typedef union			u_bunny_standard_command
{
  struct {
    uint8_t			ciphered:1;
    uint32_t			command:31;
    float			declared_sending_date;
    uint8_t			mask_source[8]; // to do wide_hash(mask.secret, data_size); and then uncipher
  };
  t_bunny_heartbeat_command	heartbeat;
  t_bunny_heartbeat_response_command heartbeat_response;
  t_bunny_challenge_request_command challenge_request;
  t_bunny_challenge_command	challenge;
  t_bunny_challenge_response_command challenge_response;
  t_bunny_challenge_result_command challenge_result;
}				t_bunny_standard_command;

typedef enum			e_bunny_standard_command_handling
  {
    BSCH_FAILURE		= -1, // Standard command was a bunny one and failed
    BSCH_TO_BE_DONE		= 0, // Standard command is to be handled by lib user
    BSCH_SUCCESS		= 1 // Standard command done. Cmd can be free
  }				t_bunny_standard_command_handling;

t_bunny_standard_command_handling bunny_handle_standard_command
  (t_bunny_identity		*id, // Server side: who's talking. Client side: me
   t_bunny_standard_command	*cmd,
   size_t			cmd_size,
   t_bunny_hash_algorithm	hash,
   t_bunny_ciphering		ciphering
   );

bool				bunny_cipher_standard_command
  (t_bunny_identity		*id, // Server side, the target. Client side: me
   t_bunny_standard_command	*cmd,
   size_t			cmd_size,
   t_bunny_hash_algorithm	hash,
   t_bunny_ciphering		ciphering
   );

#endif	/*			__LAPIN_NETWORK_H__			*/
