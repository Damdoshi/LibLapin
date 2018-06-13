<?php
$functions = [
  40 => [
    "t_bunny_comtype",
    "t_bunny_comerror",
    "t_bunny_network_error",
    "t_bunny_expired",
    "t_bunny_connected",
    "t_bunny_disconnected",
    "t_bunny_message",
    "t_bunny_communication",
    "t_bunny_server",
    "t_bunny_protocol",
    "bunny_new_server",
    "bunny_delete_server",
    "bunny_server_poll",
    "bunny_server_write",
    "bunny_server_packet_ready",
    "bunny_server_doom_client",
    "t_bunny_client",
    "bunny_new_client",
    "bunny_delete_client",
    "bunny_client_poll",
    "bunny_client_packet_ready",
    "bunny_client_write",
    "t_bunny_network",
  ],
  50 => [
    "bunny_new_server_opt",
    "bunny_new_client_opt",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}

$version_that_support = [
  "t_bunny_comtype" => [9, $latest_version],
  "t_bunny_comerror" => [9, $latest_version],
  "t_bunny_network_error" => [9, $latest_version],
  "t_bunny_expired" => [9, $latest_version],
  "t_bunny_connected" => [9, $latest_version],
  "t_bunny_disconnected" => [9, $latest_version],
  "t_bunny_message" => [9, $latest_version],
  "t_bunny_communication" => [9, $latest_version],
  "t_bunny_server" => [9, $latest_version],
  "t_bunny_protocol" => [9, $latest_version],
  "bunny_new_server" => [9, $latest_version],
  "bunny_delete_server" => [9, $latest_version],
  "bunny_server_poll" => [9, $latest_version],
  "bunny_server_write" => [9, $latest_version],
  "bunny_server_packet_ready" => [9, $latest_version],
  "bunny_server_doom_client" => [9, $latest_version],
  "t_bunny_client" => [9, $latest_version],
  "bunny_new_client" => [9, $latest_version],
  "bunny_delete_client" => [9, $latest_version],
  "bunny_client_poll" => [9, $latest_version],
  "bunny_client_packet_ready" => [9, $latest_version],
  "bunny_client_write" => [9, $latest_version],
  "t_bunny_network" => [9, $latest_version],
  "bunny_new_server_opt" => [9, $latest_version],
  "bunny_new_client_opt" => [9, $latest_version],
];

