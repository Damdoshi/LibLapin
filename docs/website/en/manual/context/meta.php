<?php
$functions = [
  40 => [
    "t_bunny_context_runtime_info",
    "bunny_context_key",
    "bunny_context_click",
    "Bunny::SetContext",
    "Bunny::Context",
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
  "t_bunny_context_runtime_info" => [12, $latest_version],

  "bunny_context_key" => [12, $latest_version],
  "bunny_context_click" => [12, $latest_version],

  "Bunny::SetContext" => [13, $latest_version],
  "Bunny::Context" => [13, $latest_version],
];
