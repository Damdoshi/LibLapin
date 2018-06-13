<?php
$functions = [
  00 => [
    "t_bunny_position",
    "t_bunny_size",
    "t_bunny_accurate_position",
    "t_bunny_accurate_size",
    "t_bunny_area",
    "t_bunny_accurate_area",
  ],
  20 => [
    "bunny_real_width",
    "bunny_real_height",
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

    "t_bunny_position" => [0, $latest_version],
    "t_bunny_size" => [9, $latest_version],

    "t_bunny_accurate_position" => [6, $latest_version],
    "t_bunny_accurate_size" => [9, $latest_version],

    "t_bunny_area" => [0, $latest_version],
    "t_bunny_accurate_area" => [6, $latest_version],

    "bunny_real_width" => [12, $latest_version],
    "bunny_real_height" => [12, $latest_version],
];

