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

$version_that_support = [
  "BUNNY_DEBUG" => [12, $latest_version],
  "BUNNY_LOG" => [12, $latest_version],
  "t_bunny_error" => [12, $latest_version],
  "bunny_errno" => [12, $latest_version],
  "bunny_strerror" => [12, $latest_version],
  "bunny_perror" => [12, $latest_version],
  "bunny_set_error_descriptor" => [12, $latest_version],
  "bunny_get_error_descriptor" => [12, $latest_version],
  "bunny_set_log_descriptor" => [12, $latest_version],
  "bunny_get_log_descriptor" => [12, $latest_version],
  "bunny_set_log_filter" => [12, $latest_version],
  "bunny_set_log_mode" => [12, $latest_version],
];
