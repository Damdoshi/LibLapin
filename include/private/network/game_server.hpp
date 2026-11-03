// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Neutral reliable game relay internals.

#ifndef                         __LAPIN_NETWORK_GAME_SERVER_HPP__
# define                        __LAPIN_NETWORK_GAME_SERVER_HPP__
# include                       <arpa/inet.h>
# include                       <map>
# include                       <set>
# include                       "network.hpp"

namespace                       network
{
  inline uint64_t               HostToNetwork64(uint64_t value)
  {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return ((uint64_t)htonl((uint32_t)(value >> 32))) |
      ((uint64_t)htonl((uint32_t)value) << 32);
#else
    return (value);
#endif
  }

  inline uint64_t               NetworkToHost64(uint64_t value)
  {
    return (HostToNetwork64(value));
  }

  inline Info                   GameServerInfo(const t_bunny_network_info &info)
  {
    return (Info(info.sockaddr, info.socklen));
  }

  inline t_bunny_network_info   GameServerInfo(const Info &info)
  {
    return ((const t_bunny_network_info&)info);
  }

  inline bool                   GameServerPacketTypeIsRequest
    (t_bunny_game_server_packet_type type)
  {
    return (type >= BGSP_REGISTER && type <= BGSP_QUIT);
  }

  class                         GameServer
  {
  private:
    struct                      Player
    {
      t_bunny_game_player_id    id = 0;
      Info                      info;
      std::set<t_bunny_game_room_id> rooms;
    };

    struct                      Room
    {
      t_bunny_game_room_id      id = 0;
      std::set<t_bunny_game_player_id> players;
    };

    uint64_t                    service;
    t_bunny_game_server_limits  limits;
    std::set<Info>              listeners;
    std::map<t_bunny_game_player_id, Player> players;
    std::map<Info, t_bunny_game_player_id> player_by_info;
    std::map<t_bunny_game_room_id, Room> rooms;

    bool                        Send(const Info &target,
                                     t_bunny_game_server_packet_type type,
                                     t_bunny_game_player_id player,
                                     t_bunny_game_room_id room,
                                     uint32_t code,
                                     const void *data = NULL,
                                     size_t size = 0) const;
    bool                        Error(const Info &target,
                                      t_bunny_game_server_error error,
                                      t_bunny_game_player_id player = 0,
                                      t_bunny_game_room_id room = 0) const;
    bool                        NotifyRoom(const Room &room,
                                           t_bunny_game_server_packet_type type,
                                           t_bunny_game_player_id player,
                                           bool include_player) const;

    Player                      *FindPlayer(const Info &info);
    const Player                *FindPlayer(const Info &info) const;

    bool                        Register(const Info &info,
                                         t_bunny_game_player_id id);
    bool                        Join(const Info &info,
                                     t_bunny_game_room_id room);
    bool                        Leave(Player &player,
                                      t_bunny_game_room_id room,
                                      bool explicit_leave);
    bool                        Leave(const Info &info,
                                      t_bunny_game_room_id room);
    bool                        Relay(const Info &info,
                                      t_bunny_game_room_id room,
                                      const void *data,
                                      size_t size);
    bool                        Remove(Player &player);

  public:
    GameServer(uint64_t service,
               const t_bunny_game_server_limits *limits);
    ~GameServer(void);

    t_bunny_network_info        Open(uint16_t port,
                                     int timeout,
                                     bool resend);
    bool                        Close(const Info &listener);
    bool                        Handle(const t_bunny_communication &communication);
    bool                        Multicast(t_bunny_game_room_id room,
                                         t_bunny_game_player_id sender,
                                         const void *data,
                                         size_t size) const;
    bool                        Remove(t_bunny_game_player_id player);

    size_t                      PlayerCount(void) const;
    size_t                      RoomCount(void) const;
    size_t                      RoomPlayerCount(t_bunny_game_room_id room) const;
    bool                        HasPlayer(t_bunny_game_player_id player) const;
    bool                        PlayerIsInRoom(t_bunny_game_player_id player,
                                               t_bunny_game_room_id room) const;
  };
}

#endif  //                      __LAPIN_NETWORK_GAME_SERVER_HPP__
