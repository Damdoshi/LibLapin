<?php
$functions = [
  40 => [
    "t_bunny_map_cmp",
    "t_bunny_map_dup",
    "t_bunny_map_del",
    "t_bunny_map",
    "bunny_new_map",
    "bunny_delete_map",
    "bunny_map_clear",
    "bunny_map_size",
    "bunny_map_empty",
    "bunny_map_data",
    "bunny_map_get_data",
    "bunny_map_set_data",
    "bunny_map_foreach",
    "bunny_map_fast_foreach",
  ],
  50 => [
    "bunny_map_get_subtree",
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
  "t_bunny_map_cmp" => [11, $latest_version],
  "t_bunny_map_dup" => [11, $latest_version],
  "t_bunny_map_del" => [11, $latest_version],
  "t_bunny_map" => [11, $latest_version],
  "bunny_new_map" => [11, $latest_version],
  "bunny_delete_map" => [11, $latest_version],
  "bunny_map_clear" => [12, $latest_version],
  "bunny_map_size" => [11, $latest_version],
  "bunny_map_empty" => [11, $latest_version],
  "bunny_map_data" => [11, $latest_version],
  "bunny_map_get_data" => [11, $latest_version],
  "bunny_map_set_data" => [11, $latest_version],
  "bunny_map_foreach" => [11, $latest_version],
  "bunny_map_fast_foreach" => [11, $latest_version],
  "bunny_map_get_subtree" => [11, $latest_version],
];

