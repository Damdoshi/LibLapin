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
