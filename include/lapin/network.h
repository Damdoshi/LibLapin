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


/**
 * @doc
 * @doc-symbol network
 * @doc-kind module
 * @doc-module network
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Provides asynchronous peer-oriented network transports.
 * @description The current public API opens endpoints described by t_bunny_network_info, supports several TCP/UDP framing modes and exchanges t_bunny_communication messages through the LibLapin event/network internals.
 * @header lapin/network.h
 *
 * @doc-lang fr
 * @brief Fournit des transports réseau asynchrones orientés pairs.
 * @description L'API publique actuelle ouvre des extrémités décrites par t_bunny_network_info, prend en charge plusieurs modes de tramage TCP/UDP et échange des t_bunny_communication via les internes événement/réseau de la LibLapin.
 * @header lapin/network.h
 */

/**
 * @doc
 * @doc-symbol BUNNY_NETWORK_MAXIMUM_PACKET_SIZE
 * @doc-kind macro
 * @doc-module network
 * @doc-order 10
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Maximum payload size accepted by the network layer.
 * @description Its value is 128 KiB.
 *
 * @doc-lang fr
 * @brief Taille maximale de charge utile acceptée par la couche réseau.
 * @description Sa valeur est 128 Kio.
 */
# define			BUNNY_NETWORK_MAXIMUM_PACKET_SIZE		(128 * 1024)


/**
 * @doc
 * @doc-symbol t_bunny_network
 * @doc-kind type
 * @doc-module network
 * @doc-order 20
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Abstract legacy network object type.
 * @description This typedef is kept as an opaque handle type for compatibility with code that refers to abstract network objects. The current API primarily manipulates t_bunny_network_info.
 * @see t_bunny_network_info
 *
 * @doc-lang fr
 * @brief Type abstrait historique d'objet réseau.
 * @description Ce typedef est conservé comme type de handle opaque pour compatibilité avec le code qui mentionne des objets réseau abstraits. L'API actuelle manipule surtout t_bunny_network_info.
 * @see t_bunny_network_info
 */
typedef void			t_bunny_network;


/**
 * @doc
 * @doc-symbol t_bunny_network_info
 * @doc-kind struct
 * @doc-module network
 * @doc-order 30
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Identifies a local or remote network endpoint.
 * @field sockaddr IPv4 socket address.
 * @field socklen Size of sockaddr.
 * @description Values of this type are used as handles by the current network API. They can describe an opened local transport or a remote peer.
 * @see bunny_new_network_info, bunny_network_open, bunny_network_write
 *
 * @doc-lang fr
 * @brief Identifie une extrémité réseau locale ou distante.
 * @field sockaddr Adresse de socket IPv4.
 * @field socklen Taille de sockaddr.
 * @description Les valeurs de ce type servent de handles à l'API réseau actuelle. Elles peuvent décrire un transport local ouvert ou un pair distant.
 * @see bunny_new_network_info, bunny_network_open, bunny_network_write
 */
typedef struct			s_bunny_network_info
{
  struct sockaddr_in		sockaddr;
  socklen_t			socklen;
}				t_bunny_network_info;

int				bunny_infocmp(t_bunny_network_info		a,
					      t_bunny_network_info		b);
t_bunny_network_info		bunny_new_network_info(const char		*ip,
						       uint16_t			port);


/**
 * @doc
 * @doc-symbol t_bunny_comtype
 * @doc-kind enum
 * @doc-module network
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Describes the kind of network communication received.
 * @value BCT_NOTHING No event.
 * @value BCT_NETCONNECTED A peer has connected.
 * @value BCT_NETDISCONNECTED A peer has disconnected.
 * @value BCT_MESSAGE A message payload is available.
 * @value BCT_POLL_ERROR Polling failed.
 * @value BCT_SENDTO_ERROR Sending failed.
 * @value BCT_RECVFROM_ERROR Receiving failed.
 * @value BCT_MALLOC_ERROR Allocation failed while handling network data.
 * @see t_bunny_communication
 *
 * @doc-lang fr
 * @brief Décrit le type de communication réseau reçue.
 * @value BCT_NOTHING Aucun événement.
 * @value BCT_NETCONNECTED Un pair s'est connecté.
 * @value BCT_NETDISCONNECTED Un pair s'est déconnecté.
 * @value BCT_MESSAGE Une charge utile de message est disponible.
 * @value BCT_POLL_ERROR Le polling a échoué.
 * @value BCT_SENDTO_ERROR L'envoi a échoué.
 * @value BCT_RECVFROM_ERROR La réception a échoué.
 * @value BCT_MALLOC_ERROR Une allocation a échoué pendant le traitement réseau.
 * @see t_bunny_communication
 */
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


/**
 * @doc
 * @doc-symbol t_bunny_communication
 * @doc-kind struct
 * @doc-module network
 * @doc-order 240
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Represents one network event or message.
 * @field comtype Event kind.
 * @field info Peer or endpoint involved in the event.
 * @field time Event time.
 * @field data Message data. For BCT_MESSAGE, ownership is transferred to the user and it must be released with bunny_free.
 * @field size Message size in bytes.
 * @field errno_code System error code when comtype reports an error.
 * @see t_bunny_comtype, bunny_network_write
 *
 * @doc-lang fr
 * @brief Représente un événement ou message réseau.
 * @field comtype Type d'événement.
 * @field info Pair ou extrémité impliqué dans l'événement.
 * @field time Date de l'événement.
 * @field data Données du message. Pour BCT_MESSAGE, la possession est transférée à l'utilisateur et la mémoire doit être libérée avec bunny_free.
 * @field size Taille du message en octets.
 * @field errno_code Code d'erreur système lorsque comtype signale une erreur.
 * @see t_bunny_comtype, bunny_network_write
 */
typedef struct			s_bunny_communication
{
  t_bunny_comtype		comtype;
  t_bunny_network_info		info;
  double			time;
  char				*data;	// This data is now owned by user. free with bunny_free.
  size_t			size;
  int				errno_code;
}				t_bunny_communication;


/**
 * @doc
 * @doc-symbol t_bunny_protocol
 * @doc-kind enum
 * @doc-module network
 * @doc-order 280
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Selects the transport and packet framing mode.
 * @value BP_UDP_IMMEDIATE UDP transport delivering received datagrams immediately.
 * @value BP_TCP_IMMEDIATE TCP transport delivering received bytes immediately.
 * @value BP_UDP_RELIABLE Reliable UDP mode with message tracking, heartbeat and resend logic.
 * @value BP_TCP_FIXED_SIZE TCP mode where all packets have the same fixed size.
 * @value BP_TCP_SIZED_PLUS_DATA TCP mode where each packet is prefixed by a uint32_t size.
 * @value BP_TCP_TERMINATED_DATA TCP mode where packets are terminated by a byte marker.
 * @see bunny_network_open
 *
 * @doc-lang fr
 * @brief Sélectionne le transport et le mode de tramage des paquets.
 * @value BP_UDP_IMMEDIATE Transport UDP livrant immédiatement les datagrammes reçus.
 * @value BP_TCP_IMMEDIATE Transport TCP livrant immédiatement les octets reçus.
 * @value BP_UDP_RELIABLE Mode UDP fiable avec suivi de messages, heartbeat et renvoi automatique.
 * @value BP_TCP_FIXED_SIZE Mode TCP où tous les paquets ont une taille fixe.
 * @value BP_TCP_SIZED_PLUS_DATA Mode TCP où chaque paquet est préfixé par une taille uint32_t.
 * @value BP_TCP_TERMINATED_DATA Mode TCP où les paquets sont terminés par un marqueur d'un octet.
 * @see bunny_network_open
 */
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
						   bool			resend,
						   uint16_t		port,
						   const char		*ip);
bool				bunny_network_doom(t_bunny_network_info	a);
bool				bunny_network_close(t_bunny_network_info a);

int				bunny_network_dump(int			fd);


/**
 * @doc
 * @doc-symbol t_bunny_written
 * @doc-kind type
 * @doc-module network
 * @doc-order 370
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback called after a queued network write is completed.
 * @param a Endpoint or peer associated with the write.
 * @param wtdata User data passed to bunny_network_writec.
 * @see bunny_network_writec, bunny_network_write
 *
 * @doc-lang fr
 * @brief Callback appelé après la fin d'une écriture réseau en file.
 * @param a Extrémité ou pair associé à l'écriture.
 * @param wtdata Donnée utilisateur passée à bunny_network_writec.
 * @see bunny_network_writec, bunny_network_write
 */
typedef void			(*t_bunny_written)(t_bunny_network_info	a,
						   void			*wtdata);

bool				bunny_network_writec(t_bunny_network_info a,
						     const void		*data,
						     size_t		len,
						     t_bunny_written	wt,
						     void		*wtdata);

/**
 * @doc
 * @doc-symbol bunny_network_write
 * @doc-kind macro
 * @doc-module network
 * @doc-order 380
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Queues network data for sending without completion callback.
 * @param a Target endpoint or peer.
 * @param d Data to send.
 * @param l Data size in bytes.
 * @return-success Returns true if the write request was accepted.
 * @return-failure Returns false on error.
 * @see bunny_network_writec
 *
 * @doc-lang fr
 * @brief Met des données réseau en file d'envoi sans callback de fin.
 * @param a Extrémité ou pair cible.
 * @param d Données à envoyer.
 * @param l Taille des données en octets.
 * @return-success Renvoie true si la demande d'écriture est acceptée.
 * @return-failure Renvoie false en cas d'erreur.
 * @see bunny_network_writec
 */
# define			bunny_network_write(a, d, l)	\
  bunny_network_writec(a, d, l, NULL, NULL)


/**
 * @doc
 * @doc-symbol t_bunny_identity_status
 * @doc-kind enum
 * @doc-module network
 * @doc-order 500
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Authentication state of a known network identity.
 * @value BIS_IDENTITY_REFUSED The identity challenge failed.
 * @value BIS_AWAITING_CONFIRMATION The identity exists but is not validated yet.
 * @value BIS_IDENTITY_CONFIRMED The identity has been validated.
 * @see t_bunny_identity
 *
 * @doc-lang fr
 * @brief État d'authentification d'une identité réseau connue.
 * @value BIS_IDENTITY_REFUSED Le défi d'identité a échoué.
 * @value BIS_AWAITING_CONFIRMATION L'identité existe mais n'est pas encore validée.
 * @value BIS_IDENTITY_CONFIRMED L'identité a été validée.
 * @see t_bunny_identity
 */
typedef enum			e_bunny_identity_status
  {
    BIS_IDENTITY_REFUSED	= -1,
    BIS_AWAITING_CONFIRMATION	=  0,
    BIS_IDENTITY_CONFIRMED	= +1
  }				t_bunny_identity_status;

// An array of t_bunny_identity is terminated by an empty char identity

/**
 * @doc
 * @doc-symbol IDENTITY_SIZE
 * @doc-kind macro
 * @doc-module network
 * @doc-order 510
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Maximum storage size of an identity name, including its final zero byte.
 * @see t_bunny_identity, IDENTITY_SECRET_SIZE
 *
 * @doc-lang fr
 * @brief Taille maximale de stockage d'un nom d'identité, octet zéro final inclus.
 * @see t_bunny_identity, IDENTITY_SECRET_SIZE
 */
# define			IDENTITY_SIZE				64

/**
 * @doc
 * @doc-symbol IDENTITY_SECRET_SIZE
 * @doc-kind macro
 * @doc-module network
 * @doc-order 515
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Storage size of an identity secret in bytes.
 * @see t_bunny_identity, IDENTITY_SIZE
 *
 * @doc-lang fr
 * @brief Taille de stockage d'un secret d'identité en octets.
 * @see t_bunny_identity, IDENTITY_SIZE
 */
# define			IDENTITY_SECRET_SIZE			64

/**
 * @doc
 * @doc-symbol t_bunny_identity
 * @doc-kind struct
 * @doc-module network
 * @doc-order 520
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Stores identity and timing information for a known peer.
 * @field identity Zero-terminated identity name.
 * @field secret Shared secret associated with the identity.
 * @field validated Current identity validation state.
 * @field last_challenge Last challenge hash.
 * @field info Network endpoint associated with the identity.
 * @field usual_delay Estimated one-way communication delay.
 * @field estimated_clock_difference Estimated difference between local and remote clocks.
 * @field last_exchange Date of the last exchange.
 * @see gl_bunny_identity, bunny_resolve_identity
 *
 * @doc-lang fr
 * @brief Stocke l'identité et les informations temporelles d'un pair connu.
 * @field identity Nom d'identité terminé par zéro.
 * @field secret Secret partagé associé à l'identité.
 * @field validated État courant de validation de l'identité.
 * @field last_challenge Dernier hachage de défi.
 * @field info Extrémité réseau associée à l'identité.
 * @field usual_delay Délai de communication aller estimé.
 * @field estimated_clock_difference Différence estimée entre horloges locale et distante.
 * @field last_exchange Date du dernier échange.
 * @see gl_bunny_identity, bunny_resolve_identity
 */
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

/**
 * @doc
 * @doc-symbol gl_bunny_identity
 * @doc-kind variable
 * @doc-module network
 * @doc-order 530
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Global array of currently known network identities.
 * @description The array is terminated by an entry whose identity string is empty.
 * @see t_bunny_identity, bunny_resolve_identity
 *
 * @doc-lang fr
 * @brief Tableau global des identités réseau actuellement connues.
 * @description Le tableau est terminé par une entrée dont la chaîne identity est vide.
 * @see t_bunny_identity, bunny_resolve_identity
 */
extern t_bunny_identity		gl_bunny_identity[1025];

t_bunny_identity		*bunny_resolve_identity
  (t_bunny_identity		*id,
   t_bunny_network_info		in
   );


/**
 * @doc
 * @doc-symbol t_bunny_standard_command_type
 * @doc-kind enum
 * @doc-module network
 * @doc-order 600
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Lists standard protocol commands handled by LibLapin.
 * @value BSCT_HEARTBEAT Heartbeat command.
 * @value BSCT_HEARTBEAT_RESPONSE Response to a heartbeat.
 * @value BSCT_CHALLENGE_REQUEST Request for an identity challenge.
 * @value BSCT_CHALLENGE Challenge payload.
 * @value BSCT_CHALLENGE_RESPONSE Response to a challenge.
 * @value BSCT_CHALLENGE_RESULT Result of a challenge response.
 * @value BSCT_LAST_STANDARD_COMMAND First value available for user-defined command extensions.
 * @see t_bunny_standard_command, bunny_handle_standard_command
 *
 * @doc-lang fr
 * @brief Liste les commandes de protocole standard traitées par la LibLapin.
 * @value BSCT_HEARTBEAT Commande heartbeat.
 * @value BSCT_HEARTBEAT_RESPONSE Réponse à un heartbeat.
 * @value BSCT_CHALLENGE_REQUEST Demande de défi d'identité.
 * @value BSCT_CHALLENGE Charge utile de défi.
 * @value BSCT_CHALLENGE_RESPONSE Réponse à un défi.
 * @value BSCT_CHALLENGE_RESULT Résultat d'une réponse de défi.
 * @value BSCT_LAST_STANDARD_COMMAND Première valeur disponible pour les extensions de commandes utilisateur.
 * @see t_bunny_standard_command, bunny_handle_standard_command
 */
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


/**
 * @doc
 * @doc-symbol t_bunny_heartbeat_command
 * @doc-kind struct
 * @doc-module network
 * @doc-order 610
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Represents a LibLapin standard heartbeat command packet layout.
 * @description This low-level structure is part of the standard-command protocol machinery and is normally manipulated through t_bunny_standard_command, bunny_handle_standard_command and bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 *
 * @doc-lang fr
 * @brief Représente le layout de paquet d'une commande heartbeat LibLapin.
 * @description Cette structure bas niveau fait partie de la mécanique du protocole de commandes standard et se manipule normalement via t_bunny_standard_command, bunny_handle_standard_command et bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 */
typedef struct			s_bunny_heartbeat_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_HEARTBEAT
  float				declared_sending_date;
}				t_bunny_heartbeat_command;


/**
 * @doc
 * @doc-symbol t_bunny_heartbeat_response_command
 * @doc-kind struct
 * @doc-module network
 * @doc-order 620
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Represents a LibLapin standard heartbeat response command packet layout.
 * @description This low-level structure is part of the standard-command protocol machinery and is normally manipulated through t_bunny_standard_command, bunny_handle_standard_command and bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 *
 * @doc-lang fr
 * @brief Représente le layout de paquet d'une commande de réponse heartbeat LibLapin.
 * @description Cette structure bas niveau fait partie de la mécanique du protocole de commandes standard et se manipule normalement via t_bunny_standard_command, bunny_handle_standard_command et bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 */
typedef struct			s_bunny_heartbeat_response_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_HEARTBEAT_RESPONSE
  float				declared_sending_date;
  float				original_sending_date;
}				t_bunny_heartbeat_response_command;


/**
 * @doc
 * @doc-symbol t_bunny_challenge_request_command
 * @doc-kind struct
 * @doc-module network
 * @doc-order 630
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Represents a LibLapin standard identity challenge request command packet layout.
 * @description This low-level structure is part of the standard-command protocol machinery and is normally manipulated through t_bunny_standard_command, bunny_handle_standard_command and bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 *
 * @doc-lang fr
 * @brief Représente le layout de paquet d'une commande de demande de défi d’identité LibLapin.
 * @description Cette structure bas niveau fait partie de la mécanique du protocole de commandes standard et se manipule normalement via t_bunny_standard_command, bunny_handle_standard_command et bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 */
typedef struct			s_bunny_challenge_request_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_CHALLENGE_REQUEST
  float				declared_sending_date;
  char				identity[IDENTITY_SIZE]; // Who are you?
}				t_bunny_challenge_request_command;


/**
 * @doc
 * @doc-symbol t_bunny_challenge_command
 * @doc-kind struct
 * @doc-module network
 * @doc-order 640
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Represents a LibLapin standard identity challenge command packet layout.
 * @description This low-level structure is part of the standard-command protocol machinery and is normally manipulated through t_bunny_standard_command, bunny_handle_standard_command and bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 *
 * @doc-lang fr
 * @brief Représente le layout de paquet d'une commande de défi d’identité LibLapin.
 * @description Cette structure bas niveau fait partie de la mécanique du protocole de commandes standard et se manipule normalement via t_bunny_standard_command, bunny_handle_standard_command et bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 */
typedef struct			s_bunny_challenge_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_CHALLENGE
  float				declared_sending_date;
  uint8_t			challenge[24];
}				t_bunny_challenge_command;


/**
 * @doc
 * @doc-symbol t_bunny_challenge_response_command
 * @doc-kind struct
 * @doc-module network
 * @doc-order 650
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Represents a LibLapin standard identity challenge response command packet layout.
 * @description This low-level structure is part of the standard-command protocol machinery and is normally manipulated through t_bunny_standard_command, bunny_handle_standard_command and bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 *
 * @doc-lang fr
 * @brief Représente le layout de paquet d'une commande de réponse à un défi d’identité LibLapin.
 * @description Cette structure bas niveau fait partie de la mécanique du protocole de commandes standard et se manipule normalement via t_bunny_standard_command, bunny_handle_standard_command et bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 */
typedef struct			s_bunny_challenge_response_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_CHALLENGE_RESPONSE
  float				declared_sending_date;
  uint64_t			response;
}				t_bunny_challenge_response_command;


/**
 * @doc
 * @doc-symbol t_bunny_challenge_result_command
 * @doc-kind struct
 * @doc-module network
 * @doc-order 660
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Represents a LibLapin standard identity challenge result command packet layout.
 * @description This low-level structure is part of the standard-command protocol machinery and is normally manipulated through t_bunny_standard_command, bunny_handle_standard_command and bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 *
 * @doc-lang fr
 * @brief Représente le layout de paquet d'une commande de résultat de défi d’identité LibLapin.
 * @description Cette structure bas niveau fait partie de la mécanique du protocole de commandes standard et se manipule normalement via t_bunny_standard_command, bunny_handle_standard_command et bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 */
typedef struct			s_bunny_challenge_result_command
{
  uint8_t			ciphered:1; // 0
  uint32_t			command:31; // BSCT_CHALLENGE_RESPONSE
  float				declared_sending_date;
  uint8_t			result;
}				t_bunny_challenge_result_command;


/**
 * @doc
 * @doc-symbol t_bunny_clear_standard_command_header
 * @doc-kind struct
 * @doc-module network
 * @doc-order 680
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Represents a LibLapin standard clear standard command header packet layout.
 * @description This low-level structure is part of the standard-command protocol machinery and is normally manipulated through t_bunny_standard_command, bunny_handle_standard_command and bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 *
 * @doc-lang fr
 * @brief Représente le layout de paquet d'une en-tête de commande standard non chiffrée LibLapin.
 * @description Cette structure bas niveau fait partie de la mécanique du protocole de commandes standard et se manipule normalement via t_bunny_standard_command, bunny_handle_standard_command et bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 */
typedef struct			s_bunny_clear_standard_command_header
{
  uint8_t			ciphered:1;
  uint32_t			command:31;
  float				declared_sending_date;
}				t_bunny_clear_standard_command_header;


/**
 * @doc
 * @doc-symbol t_bunny_ciphered_standard_command_header
 * @doc-kind struct
 * @doc-module network
 * @doc-order 690
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Represents a LibLapin standard ciphered standard command header packet layout.
 * @description This low-level structure is part of the standard-command protocol machinery and is normally manipulated through t_bunny_standard_command, bunny_handle_standard_command and bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 *
 * @doc-lang fr
 * @brief Représente le layout de paquet d'une en-tête de commande standard chiffrée LibLapin.
 * @description Cette structure bas niveau fait partie de la mécanique du protocole de commandes standard et se manipule normalement via t_bunny_standard_command, bunny_handle_standard_command et bunny_cipher_standard_command.
 * @see t_bunny_standard_command, t_bunny_standard_command_type
 */
typedef struct			s_bunny_ciphered_standard_command_header
{
  uint8_t			ciphered:1;
  uint32_t			command:31;
  float				declared_sending_date;
  uint8_t			mask_source[8];
}				t_bunny_ciphered_standard_command_header;


/**
 * @doc
 * @doc-symbol t_bunny_standard_command
 * @doc-kind union
 * @doc-module network
 * @doc-order 700
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Union representing any standard network command.
 * @description The first fields form a common header, then the union can be read through one of the specialized command structures depending on command.
 * @see t_bunny_standard_command_type, bunny_handle_standard_command, bunny_cipher_standard_command
 *
 * @doc-lang fr
 * @brief Union représentant n'importe quelle commande réseau standard.
 * @description Les premiers champs forment un en-tête commun, puis l'union peut être lue via l'une des structures spécialisées selon command.
 * @see t_bunny_standard_command_type, bunny_handle_standard_command, bunny_cipher_standard_command
 */
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


/**
 * @doc
 * @doc-symbol t_bunny_standard_command_handling
 * @doc-kind enum
 * @doc-module network
 * @doc-order 710
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Result of standard command processing.
 * @value BSCH_FAILURE The command was standard and failed.
 * @value BSCH_TO_BE_DONE The command is not handled by LibLapin and must be handled by user code.
 * @value BSCH_SUCCESS The command was standard and was processed successfully.
 * @see bunny_handle_standard_command
 *
 * @doc-lang fr
 * @brief Résultat du traitement d'une commande standard.
 * @value BSCH_FAILURE La commande était standard et a échoué.
 * @value BSCH_TO_BE_DONE La commande n'est pas traitée par la LibLapin et doit être traitée par le code utilisateur.
 * @value BSCH_SUCCESS La commande était standard et a été traitée avec succès.
 * @see bunny_handle_standard_command
 */
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
