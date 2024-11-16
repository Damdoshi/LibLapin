// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#ifndef			__LAPIN_NETWORK_HPP__
# define		__LAPIN_NETWORK_HPP__
# include		<sys/select.h>
# include		<sys/types.h>
# include		<poll.h>
# include		<map>
# include		"descriptor.hpp"
# include		"peer.hpp"

class			Network
{
protected:
  using Descriptor	= network::Descriptor;
  using Info		= network::Info;
  using Protocol	= network::Descriptor::Protocol;
  using Communication	= network::Communication;
  using Peer		= network::Peer;

  // Contacts identifiés
  std::map<Info, Peer>	peers;
  // Connexions réseaux diverses
  Descriptor		descriptors[FD_SETSIZE];
  struct pollfd		pollfd[FD_SETSIZE];
  size_t		nbr;

  void			MoveWriteRequest(void);

  friend		network::Descriptor;
  friend		network::Peer;
  
public:
  // On veut ouvrir un serveur ou un client.
  const Info		*Open(const std::string		&name,
			      Protocol			protocol = Protocol::IMMEDIATE_RETRIEVE,
			      size_t			size = 1024 * 64,
			      char			terminator = 0,
			      uint16_t			port = 0x6279, // "by"
			      const std::string		&ip = "");

  // Résoudre les opérations d'écriture et de lecture
  double		operator()(double		timeout = 0.02,
				   bool			return_asap = false);
  double		Poll(double			timeout = 0.02,
			     bool			return_asap = false);

  // Information sur les paquets en attente de récupération
  // et les paquets en attente d'envoi
  int			GetReceivedPacketCount(void) const;
  int			GetSendingPacketCount(void) const;
  // Est ce que je suis vide en lecture?
  operator		bool (void) const;

  // Ecrire un message a quelqu'un
  bool			SetMessage(const Info		&info,
				   const char		*data,
				   size_t		len);
  template <typename T>
  bool			SetMessage(const Info		&info,
				   T const		&r)
  {
    return (SetMessage(info, (const char*)&r, sizeof(r)));
  }

  // Récupérer un message en attente
  bool			GetMessage(Communication	&com,
				   Info			&info);

  // Commencer à clore la conversation avec un pair ou avec un service réseau
  bool			Doom(const Info			&info);
  bool			Doom(int			fd);
  // Arreter de parler a un pair ou fermer un service réseau tout de suite
  bool			Close(const Info		&info);
  bool			Close(int			fd);

  Network(void);
  ~Network(void);
};

#endif	//		__LAPIN_NETWORK_HPP__
