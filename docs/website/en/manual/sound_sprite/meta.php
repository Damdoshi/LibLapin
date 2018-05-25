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
    "bunny_sound_sprite_trap_is_talking",
    "bunny_sound_sprite_name",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
