# bunnygameserver

`bunnygameserver` is a neutral room-based relay built on LibLapin's
`BP_UDP_RELIABLE` transport. It does not interpret game payloads.

A single `t_bunny_game_server` may open several UDP ports. All listeners feed
the same player and room registry, so they are interchangeable accesses to the
same logical service.

## Standalone use

```sh
bunnygameserver -s 42 -p 25000 -p 25001
```

The default port is `0x6279` (25209), the default service identifier is `0`, and
the default RUDP timeout is 5000 ms.

## Protocol

All multi-byte fields of `t_bunny_game_server_wire_packet` are in network byte
order. `bunny_game_server_pack` and `bunny_game_server_unpack` should be used
instead of filling the wire structure manually.

Client requests:

- `BGSP_REGISTER`: `player` contains the requested opaque player identifier.
- `BGSP_JOIN_ROOM`: `room` contains the room identifier.
- `BGSP_LEAVE_ROOM`: `room` contains the room identifier.
- `BGSP_MULTICAST`: `room` selects the room and `payload` is opaque game data.
- `BGSP_QUIT`: unregisters the endpoint.

Server responses:

- `BGSP_REGISTERED`: registration acknowledgement.
- `BGSP_PLAYER_JOINED` / `BGSP_PLAYER_LEFT`: room presence notifications.
- `BGSP_MESSAGE`: relayed game data; `player` identifies the sender.
- `BGSP_ERROR`: `code` contains a `t_bunny_game_server_error` value.

The sender identity present in a client packet is never trusted after
registration. The server resolves the player from the RUDP peer endpoint.

## Embedded use

```c
t_bunny_game_server *relay = bunny_new_game_server(42, NULL);
bunny_game_server_open(relay, 25000, 5000, true);

while (running)
{
  bunny_network_poll(20.0);
  while (bunny_network_inbox())
  {
    t_bunny_communication com = bunny_network_read();

    if (!bunny_game_server_handle(relay, &com))
      handle_application_packet(&com);
    if (com.data)
      bunny_free(com.data);
  }
}

bunny_delete_game_server(relay);
```

Several relay objects can coexist when they use distinct `service` identifiers.
Pass each incoming communication to them until one returns `true`.
