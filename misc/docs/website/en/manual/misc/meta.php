<?php
$functions = [
  10 => [
    "bunny_memdup",
    "bunny_swap",
  ],
  20 => [
    "bunny_load_file",
    "bunny_save_file",
    "bunny_delete_file",
    "NBRCELL",
  ],
  30 => [
    "bunny_evaluate",
    "bunny_base64_encode",
    "bunny_base64_decode",
    "bunny_base64_check",
    "bunny_split",
    "bunny_delete_split",
    "t_bunny_split",
  ],
  40 => [
    "bunny_smooth_move",
    "bunny_reach",
    "bunny_big_buffer",
  ],
  50 => [
    "bunny_make_file_unique",
    "STRINGIFY",
    "bunny_printl",
    "bunny_printlerr",
    "bunny_trace",
    "bunny_next_level_experience",
    "bunny_consistancy",
    "bunny_managed_ressource",
    "bunny_set_ressource_management",
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
  "bunny_load_file" => [11, $latest_version],
  "bunny_save_file" => [11, $latest_version],
  "bunny_make_file_unique" => [12, $latest_version],
  "bunny_delete_file" => [12, $latest_version],
  "bunny_evaluate" => [11, $latest_version],
  "bunny_base64_encode" => [12, $latest_version],
  "bunny_base64_decode" => [12, $latest_version],
  "bunny_base64_check" => [12, $latest_version],

  "t_bunny_split" => [12, $latest_version],
  "bunny_split" => [12, $latest_version],
  "bunny_delete_split" => [12, $latest_version],

  "bunny_memdup" => [12, $latest_version],
  "bunny_swap" => [11, $latest_version],

  "STRINGIFY" => [11, $latest_version],
  "NBRCELL" => [11, $latest_version],
  "bunny_printl" => [11, $latest_version],
  "bunny_printlerr" => [11, $latest_version],
  "bunny_trace" => [11, $latest_version],
  "bunny_next_level_experience" => [12, $latest_version],
  "bunny_smooth_move" => [12, $latest_version],
  "bunny_consistancy" => [11, $latest_version],
  "bunny_managed_ressource" => [12, $latest_version],
  "bunny_set_ressource_management" => [12, $latest_version],
  "bunny_big_buffer" => [12, $latest_version],
  "bunny_reach" => [12, $latest_version],
];

