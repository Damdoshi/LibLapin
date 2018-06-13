<?php
$functions = [
  00 => [
    "t_bunny_buffer",
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
  "t_bunny_buffer" => [0, $latest_version],
];
