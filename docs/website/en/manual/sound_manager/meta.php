<?php
$functions = [
  30 => [
    "t_bunny_music_track",
    "t_bunny_sound_type",
    "t_bunny_sound_manager",
    "gl_bunny_sound_manager",
    "bunny_sound_manager_add",
    "bunny_sound_manager_remove",
    "bunny_sound_manager_play_music",
    "bunny_sound_manager_stop_music",
    "bunny_sound_manager_play_sound",
    "bunny_sound_manager_stop_sound",
    "bunny_sound_manager_volume",
    "bunny_sound_manager_pitch",
    "bunny_managed_sound_volume",
    "bunny_managed_sound_pitch",
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
  "t_bunny_music_track" => [12, $latest_version],
  "t_bunny_sound_type" => [12, $latest_version],
  "t_bunny_sound_manager" => [12, $latest_version],
  "gl_bunny_sound_manager" => [12, $latest_version],
  "bunny_sound_manager_add" => [12, $latest_version],
  "bunny_sound_manager_remove" => [12, $latest_version],
  "bunny_sound_manager_play_music" => [12, $latest_version],
  "bunny_sound_manager_stop_music" => [12, $latest_version],
  "bunny_sound_manager_play_sound" => [12, $latest_version],
  "bunny_sound_manager_stop_sound" => [12, $latest_version],
  "bunny_sound_manager_volume" => [12, $latest_version],
  "bunny_sound_manager_pitch" => [12, $latest_version],
  "bunny_managed_sound_volume" => [12, $latest_version],
  "bunny_managed_sound_pitch" => [12, $latest_version],
];
