<?php
$functions = [
  10 => [
    "t_bunny_sound",
    "t_bunny_music",
    "t_bunny_effect",
    "bunny_load_music",
    "bunny_load_effect",
    "bunny_sound_volume",
    "bunny_sound_loop",
    "bunny_sound_play",
    "bunny_sound_pause",
    "bunny_sound_stop",
    "bunny_delete_sound",
  ],
  20 => [
    "bunny_sound_pitch",
    "bunny_sound_position",
    "bunny_sound_attenuation",
    "bunny_sound_set_cursor",
    "bunny_sound_get_cursor",
    "bunny_sound_get_duration",
    "bunny_sound_is_playing",
  ],
  30 => [
    "bunny_new_effect",
    "bunny_compute_effect",
    "SAMPLE_PER_SECONDS",
  ],
  50 => [
    "bunny_make_effect_unique",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
