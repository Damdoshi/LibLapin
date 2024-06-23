<?php
$functions = [
  30 => [
    "t_bunny_monitored_type",
    "bunny_add_monitored_value",
    "bunny_remove_monitored_value",
    "bunny_display_monitored_value",
    "bunny_print_monitored_value",
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
  "t_bunny_monitored_type" => [12, $latest_version],
  "bunny_add_monitored_value" => [12, $latest_version],
  "bunny_remove_monitored_value" => [12, $latest_version],
  "bunny_display_monitored_value" => [12, $latest_version],
  "bunny_print_monitored_value" => [12, $latest_version],
];

