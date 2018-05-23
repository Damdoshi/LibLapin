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
