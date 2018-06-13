<?php
$functions = [
  00 => [
    "t_bunny_window",
    "bunny_start",
    "bunny_stop",
    "bunny_display",
  ],
  10 => [
    "bunny_set_key_repeat",
  ],
  20 => [
    "bunny_get_screen_resolution",
    "bunny_get_fullscreen_modes",
    "bunny_start_style",
    "t_bunny_window_style",
    "bunny_set_mouse_visibility",
    "bunny_set_mouse_position_window",
    "bunny_set_mouse_position",
    "bunny_request_focus",
    "bunny_move_window",
    "bunny_resize_window",
  ],
  30 => [
    "bunny_vertical_sync",
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
  "t_bunny_window" => [0, $latest_version],
  "bunny_start" => [0, $latest_version],
  "bunny_stop" => [0, $latest_version],
  "bunny_display" => [0, $latest_version],

  "bunny_set_key_repeat" => [6, $latest_version],

  "bunny_get_screen_resolution" => [9, $latest_version],
  "bunny_get_fullscreen_modes" => [11, $latest_version],
  "bunny_start_style" => [3, $latest_version],
  "t_bunny_window_style" => [3, $latest_version],
  "bunny_set_mouse_visibility" => [6, $latest_version],
  "bunny_set_mouse_position_window" => [6, $latest_version],
  "bunny_set_mouse_position" => [6, $latest_version],
  "bunny_request_focus" => [6, $latest_version],
  "bunny_move_window" => [9, $latest_version],
  "bunny_resize_window" => [9, $latest_version],

  "bunny_vertical_sync" => [12, $latest_version],
];
