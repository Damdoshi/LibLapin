<?php
$functions = [
  40 => [
    "t_bunny_splash_screen",
    "gl_bunny_splash_context",
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
  "t_bunny_splash_screen" => [12, $latest_version],
  "gl_bunny_splash_context" => [12, $latest_version],
];

