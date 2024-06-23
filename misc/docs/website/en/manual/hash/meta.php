<?php
$functions = [
  30 => [
    "t_bunny_hash",
    "bunny_hash",
    "t_bunny_my_hash",
    "gl_bunny_my_hash",
    "bunny_wide_hash",
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
  "t_bunny_hash" => [11, $latest_version],
  "bunny_hash" => [11, $latest_version],
  "t_bunny_my_hash" => [11, $latest_version],
  "gl_bunny_my_hash" => [11, $latest_version],
  "bunny_wide_hash" => [11, $latest_version],
];
