<?php
$functions = [
  30 => [
    "t_bunny_constructor",
    "t_bunny_destructor",
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
  "t_bunny_constructor" => [11, $latest_version],
  "t_bunny_destructor" => [11, $latest_version],
];
