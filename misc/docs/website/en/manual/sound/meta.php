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

$version_that_support = [
  "t_bunny_sound" => [0, $latest_version],
  "t_bunny_music" => [0, $latest_version],
  "t_bunny_effect" => [0, $latest_version],
  "bunny_load_music" => [0, $latest_version],
  "bunny_load_effect" => [0, $latest_version],
  "bunny_sound_volume" => [0, $latest_version],
  "bunny_sound_loop" => [0, $latest_version],
  "bunny_sound_play" => [0, $latest_version],
  "bunny_sound_pause" => [12, $latest_version],
  "bunny_sound_stop" => [0, $latest_version],
  "bunny_delete_sound" => [0, $latest_version],

  "bunny_sound_pitch" => [12, $latest_version],
  "bunny_sound_position" => [12, $latest_version],
  "bunny_sound_attenuation" => [12, $latest_version],
  "bunny_sound_set_cursor" => [12, $latest_version],
  "bunny_sound_get_cursor" => [12, $latest_version],
  "bunny_music_get_cursor" => [7, 11],
  "bunny_sound_get_duration" => [7, $latest_version],
  "bunny_sound_is_playing" => [11, $latest_version],

  "bunny_new_effect" => [7, $latest_version],
  "bunny_compute_effect" => [7, $latest_version],
  "SAMPLE_PER_SECONDS" => [7, $latest_version],

  "bunny_make_effect_unique" => [12, $latest_version],
];
