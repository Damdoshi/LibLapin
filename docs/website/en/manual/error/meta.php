<?php
$functions = [
  20 => [
    "t_bunny_error",
    "BUNNY_DEBUG",
    "BUNNY_LOG",
    "bunny_errno",
    "bunny_strerror",
    "bunny_perror",
  ],
  30 => [
    "bunny_set_error_descriptor",
    "bunny_get_error_descriptor",
    "bunny_set_log_descriptor",
    "bunny_get_log_descriptor",
    "bunny_set_log_filter",
    "bunny_set_log_mode",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
