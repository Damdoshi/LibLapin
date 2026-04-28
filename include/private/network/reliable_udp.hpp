// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Internal Reliable UDP framing for LibLapin network layer.
// Semantics: reliable, unordered, non-blocking delivery for gameplay-oriented use.

#ifndef                 __LAPIN_NETWORK_RELIABLE_UDP_HPP__
# define                __LAPIN_NETWORK_RELIABLE_UDP_HPP__
# include               <stdint.h>
# include               <stddef.h>

namespace               network
{
  static const uint32_t RUDP_MAGIC = 0x42525544; // "BRUD" Bunny Reliable UDP
  static const uint8_t  RUDP_VERSION = 1;
  static const double   RUDP_RESEND_DELAY = 0.15;
  static const unsigned RUDP_MAX_ATTEMPTS = 64;
  static const unsigned RUDP_SEND_WINDOW = 32;
  static const size_t   RUDP_DELIVERED_HISTORY = 4096;

  enum                  ReliableUdpPacketType : uint8_t
  {
    RUDP_DATA = 1,
    RUDP_ACK = 2
  };

#pragma pack(push, 1)
  struct                ReliableUdpHeader
  {
    uint32_t            magic;
    uint8_t             version;
    uint8_t             type;
    uint16_t            header_size;
    uint32_t            sequence;
    uint32_t            acknowledge;
    uint32_t            payload_size;
  };
#pragma pack(pop)
}

#endif
