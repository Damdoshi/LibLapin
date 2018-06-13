<?php
$functions = [
  10 => [
    "t_bunny_time",
    "bunny_get_time",
    "bunny_usleep",
    "bunny_sleep"
  ],
  20 => [
    "bunny_delta_time",
    "bunny_get_current_time",
  ],
  40 => [
    "t_bunny_call_order",
    "t_bunny_trap_function",
    "t_bunny_trap",
    "bunny_new_trap",
    "bunny_delete_trap",
    "bunny_reset_clock",
  ],
  50 => [
    "bunny_asynclock",
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
  "t_bunny_time" => [12, $latest_version],
  "bunny_get_time" => [12, $latest_version],
  "bunny_usleep" => [12, $latest_version],
  "bunny_sleep" => [12, $latest_version],
  "bunny_delta_time" => [12, $latest_version],
  "bunny_get_current_time" => [12, $latest_version],
  "t_bunny_call_order" => [12, $latest_version],
  "t_bunny_trap_function" => [12, $latest_version],
  "t_bunny_trap" => [12, $latest_version],
  "bunny_new_trap" => [12, $latest_version],
  "bunny_delete_trap" => [12, $latest_version],
  "bunny_reset_clock" => [12, $latest_version],
  "bunny_asynclock" => [12, $latest_version],
];
