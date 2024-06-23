<?php
$functions = [
  40 => [
    "bunny_to_fixed_decimal",
    "bunny_to_floating_decimal",
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
  "bunny_to_fixed_decimal" => [12, $latest_version],
  "bunny_to_floating_decimal" => [12, $latest_version],
];
