// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#ifndef				__LAPIN_NETWORK_PEER_HPP__
# define			__LAPIN_NETWORK_PEER_HPP__
# include			<set>
# include			"communication.hpp"

/*
** il faut pouvoir accumuler des trucs a envoyer au joueur, meme quand
** il n'est pas connecté, afin de pouvoir rattraper le retard lorsqu'il revient
** DE FAIT: il faut que Peer soit mis au courant lorsqu'un truc est vraiment
** envoyé par un descriptor - car si ce n'est pas le cas, il faut relancer la
** demande d'écriture concernée
*/

namespace			network
{
  class				Descriptor;
  class				Peer
  {
  private:
    Info			info;
    // Which descriptor are currently used for this peer
    std::set<Descriptor*>	descriptors;
    std::list<std::vector<char>> outqueue;
    bool			doomed;

    // Transfert de demande d'écriutre de Peer a Descriptor
    bool			Write(void);

    friend			::Network;

  public:
    operator			bool (void) const;
    operator			const Info & (void) const;
    operator			int (void) const;

    // Associer ou retirer un descripteur du pair
    bool			AttachDescriptor(Descriptor		&desc);
    Peer			&operator<<(Descriptor			&desc);
    bool			DetachDescriptor(const Descriptor	&desc);
    Peer			&operator>>(const Descriptor		&desc);

    // Dépot d'une demande d'écriture
    bool			Write(const char			*data,
				      size_t				len);
    template <typename		T>
    bool			Write(T const				&data)
    {
      return (Write(&data, sizeof(data)));
    }
    template <typename		T>
    Peer			&operator<<(T const			&data)
    {
      if (Write(data) == false)
	throw IOException("Operator<< failed in cascade of a Write failure");
      return (*this);
    }
    bool			PopWriteRequest(void);

    // On établi un nouvel ensemble d'information
    Peer			&operator=(const Info			&info);
    // On identifie que le pair est celui qu'on cherche ou pas
    bool			operator==(const Info			&info);
    bool			operator!=(const Info			&info);

    bool			Doom(void);
    bool			Close(void);

    Peer(void);
    ~Peer(void);
  };
}


#endif	//				__LAPIN_NETWORK_PEER_HPP__
