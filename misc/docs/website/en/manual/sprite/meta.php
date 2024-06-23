<?php
$functions = [
  40 => [
    "t_bunny_frame_browsing",
    "t_bunny_animation",
    "t_bunny_sprite",
    "bunny_load_sprite",
    "bunny_sprite_animate",
    "bunny_sprite_is_still",
    "bunny_sprite_animation_name",
    "bunny_sprite_set_animation",
    "bunny_sprite_set_animation_name",
    "bunny_sprite_set_animation_id",
    "bunny_sprite_get_animation",
    "bunny_sprite_stop_repeat",
  ],
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}

$version_that_support = [
  "t_bunny_frame_browsing" => [12, $latest_version],
  "t_bunny_animation" => [12, $latest_version],
  "t_bunny_sprite" => [12, $latest_version],
  "bunny_load_sprite" => [12, $latest_version],
  "bunny_sprite_animate" => [12, $latest_version],
  "bunny_sprite_is_still" => [12, $latest_version],
  "bunny_sprite_animation_name" => [12, $latest_version],
  "bunny_sprite_set_animation" => [12, $latest_version],
  "bunny_sprite_set_animation_name" => [12, $latest_version],
  "bunny_sprite_set_animation_id" => [12, $latest_version],
  "bunny_sprite_get_animation" => [12, $latest_version],
  "bunny_sprite_stop_repeat" => [12, $latest_version],
];
