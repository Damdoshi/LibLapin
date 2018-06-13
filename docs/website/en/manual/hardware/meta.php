<?php
$functions = [
  30 => [
    "t_bunny_hardware",
    "bunny_new_hardware",
    "bunny_delete_hardware",
    "bunny_hardware_read",
    "bunny_hardware_write",
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
  "t_bunny_hardware" => [9, $latest_version],
  "bunny_new_hardware" => [9, $latest_version],
  "bunny_delete_hardware" => [9, $latest_version],
  "bunny_hardware_read" => [9, $latest_version],
  "bunny_hardware_write" => [9, $latest_version],
];

