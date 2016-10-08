// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include			"Client.hpp"

bool				bpt::NetCom::Client::CheckFullPacket(void)
{
  int				t;

  if (this->cursor - this->buffer < (t = this->packet_size.size) ||
      this->cursor == UNUSED_BUFFER || this->size_received != 4 ||
      this->buffer == NULL || this->buffer == TOO_BIG)
    {
      this->communication.comtype = EXPIRED;
      this->communication.expired.time = 0;
      return (false);
    }
  this->communication.comtype = MESSAGE;
  this->communication.message.time = 0;
  this->communication.message.client = this->master_info.socket;
  this->communication.message.size = this->packet_size.size;
  this->communication.message.buffer.character = this->buffer;
  this->buffer = NULL;
  this->cursor = NULL;
  this->packet_size.size = 0;
  this->size_received = 0;
  return (true);
}
