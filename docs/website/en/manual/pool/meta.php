<?php
$functions = [
  50 => [
    "t_bunny_pool",
    "bunny_new_pool",
    "bunny_delete_pool",
    "bunny_pool_capacity",
    "bunny_pool_size",
    "bunny_pool_empty",
    "bunny_pool_elem_size",
    "bunny_pool_elem_index",
    "bunny_pool_clear",
    "bunny_pool_new",
    "bunny_pool_free",
    "t_bunny_pool_foreach",
    "bunny_pool_foreach",
    "bunny_pool_fast_foreach",
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
  "t_bunny_pool" => [11, $latest_version],
  "bunny_new_pool" => [11, $latest_version],
  "bunny_delete_pool" => [11, $latest_version],
  "bunny_pool_capacity" => [11, $latest_version],
  "bunny_pool_size" => [11, $latest_version],
  "bunny_pool_empty" => [11, $latest_version],
  "bunny_pool_elem_size" => [11, $latest_version],
  "bunny_pool_elem_index" => [11, $latest_version],
  "bunny_pool_clear" => [11, $latest_version],
  "bunny_pool_new" => [12, $latest_version],
  "bunny_pool_free" => [12, $latest_version],
  "t_bunny_pool_foreach" => [11, $latest_version],
  "bunny_pool_foreach" => [11, $latest_version],
  "bunny_pool_fast_foreach" => [11, $latest_version],

  "bunny_pool_get" => [11, 11],
  "bunny_pool_getv" => [11, 11],
  "bunny_pool_release" => [11, 11],
  "bunny_pool_free_elem" => [11, 11],
  "bunny_pool_occupied_elem" => [11, 11],
];
