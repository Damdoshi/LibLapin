<?php
$functions = [
  30 => [
    "t_bunny_subprocess",
    "bunny_popen",
    "bunny_pclose",
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
    "t_bunny_subprocess" => [11, $latest_version],
    "bunny_popen" => [11, $latest_version],
    "bunny_pclose" => [11, $latest_version],
];

