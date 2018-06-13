<?php
$functions = [
  40 => [
    "t_bunny_astack",
    "t_bunny_astack_node",
    "bunny_new_astack",
    "bunny_astack_size",
    "bunny_astack_empty",
    "bunny_astack_top",
    "bunny_astack_push",
    "bunny_astack_pop",
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
  "t_bunny_astack" => [11, $latest_version],
  "t_bunny_astack_node" => [11, $latest_version],
  "bunny_new_astack" => [11, $latest_version],
  "bunny_astack_size" => [11, $latest_version],
  "bunny_astack_empty" => [11, $latest_version],
  "bunny_astack_top" => [11, $latest_version],
  "bunny_astack_push" => [11, $latest_version],
  "bunny_astack_pop" => [11, $latest_version],
];

