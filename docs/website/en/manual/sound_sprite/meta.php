<?php
$functions = [
  40 => [
    "t_bunny_sound_sprite",
    "t_bunny_sound_slice",
    "bunny_load_sound_sprite",
    "bunny_sound_sprite_play_slice",
    "bunny_sound_sprite_play_slice_name",
    "bunny_sound_sprite_play_slice_id",
    "bunny_sound_sprite_stop_slice",
    "bunny_sound_sprite_trap_or_sync",
    "bunny_sound_sprite_is_talking",
    "bunny_sound_sprite_slice_name",
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
  "t_bunny_sound_sprite" => [12, $latest_version],
  "t_bunny_sound_slice" => [12, $latest_version],
  "bunny_load_sound_sprite" => [12, $latest_version],
  "bunny_sound_sprite_play_slice" => [12, $latest_version],
  "bunny_sound_sprite_play_slice_name" => [12, $latest_version],
  "bunny_sound_sprite_play_slice_id" => [12, $latest_version],
  "bunny_sound_sprite_stop_slice" => [12, $latest_version],
  "bunny_sound_sprite_trap_or_sync" => [12, $latest_version],
  "bunny_sound_sprite_is_talking" => [12, $latest_version],
  "bunny_sound_sprite_slice_name" => [12, $latest_version],
];
