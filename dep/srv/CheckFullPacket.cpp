// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		<string.h>
#include		"Server.hpp"

bool			bpt::NetCom::Server::RawPacket(void)
{
  std::list<Client*>::iterator	i;
  char				*sub;
  char				*rbuf;
  int				to_remove;
  int				to_left;

  for (i = this->client.begin(); i != this->client.end(); ++i)
    if ((*i)->buffer != NULL && (sub = strstr((*i)->buffer, EOC)) != NULL)
      {
	to_remove = sub - (*i)->buffer;
	rbuf = new char[to_remove + 1];
	rbuf[to_remove] = '\0';
	memcpy(rbuf, (*i)->buffer, to_remove);
	to_left = &(*i)->buffer[(*i)->size_received] - &sub[strlen(sub)];
	memmove((*i)->buffer, &sub[2], to_left);
	(*i)->cursor = (*i)->buffer;
	this->communication.comtype = MESSAGE;
	this->communication.message.time = 0;
	this->communication.message.client = (*i)->info->socket;
	this->communication.message.size = (*i)->packet_size.size;
	this->communication.message.buffer.character = rbuf;
	return (true);
      }
  return (false);
}

bool			bpt::NetCom::Server::SizablePacket(void)
{
  std::list<Client*>::iterator	i;
  int			t;

  for (i = this->client.begin(); i != this->client.end(); ++i)
    if ((*i)->cursor - (*i)->buffer >= (t = (*i)->packet_size.size) && (*i)->cursor != UNUSED_BUFFER && (*i)->buffer != NULL)
      {
	this->communication.comtype = MESSAGE;
	this->communication.message.time = 0;
	this->communication.message.client = (*i)->info->socket;
	this->communication.message.size = (*i)->packet_size.size;
	this->communication.message.buffer.character = (*i)->buffer;
	(*i)->buffer = NULL;
	(*i)->cursor = NULL;
	(*i)->packet_size.size = 0;
	(*i)->size_received = 0;
	return (true);
      }
    else if ((*i)->buffer == TOO_BIG && (*i)->packet_size.size == 0)
      {
	(*i)->buffer = NULL;
	(*i)->cursor = NULL;
	(*i)->packet_size.size = 0;
	(*i)->size_received = 0;
      }
  return (false);
}

bool			bpt::NetCom::Server::CheckFullPacket(void)
{
  if (this->protocol == SIZABLE)
    return (this->SizablePacket());
  return (this->RawPacket());
}
