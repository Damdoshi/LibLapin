<?php
$functions = [
  30 => [
    "t_bunny_node",
    "t_bunny_list",
    "bunny_new_list",
    "bunny_delete_list",
    "bunny_list_size",
    "bunny_list_empty",
    "bunny_list_front",
    "bunny_list_back",
    "bunny_list_push_front",
    "bunny_list_push_back",
    "bunny_list_pop_front",
    "bunny_list_pop_back",
    "bunny_list_clear",
    "bunny_list_data",
    "bunny_list_begin",
    "bunny_list_end",
    "bunny_list_next",
    "bunny_list_prev",
  ],
  40 => [
    "bunny_list_filter",
    "bunny_list_sort",
    "bunny_list_tie",
    "bunny_list_foreach",
    "bunny_list_fast_foreach",
    "bunny_list_all",
    "bunny_list_all_rev",
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
  "t_bunny_node" => [11, $latest_version],
  "t_bunny_list" => [11, $latest_version],
  "bunny_new_list" => [11, $latest_version],
  "bunny_delete_list" => [11, $latest_version],
  "bunny_list_size" => [11, $latest_version],
  "bunny_list_empty" => [11, $latest_version],
  "bunny_list_front" => [11, $latest_version],
  "bunny_list_back" => [11, $latest_version],
  "bunny_list_push_front" => [11, $latest_version],
  "bunny_list_push_back" => [11, $latest_version],
  "bunny_list_pop_front" => [11, $latest_version],
  "bunny_list_pop_back" => [11, $latest_version],
  "bunny_list_clear" => [11, $latest_version],
  "bunny_list_data" => [11, $latest_version],
  "bunny_list_begin" => [11, $latest_version],
  "bunny_list_end" => [11, $latest_version],
  "bunny_list_next" => [11, $latest_version],
  "bunny_list_prev" => [11, $latest_version],
  "bunny_list_filter" => [11, $latest_version],
  "bunny_list_sort" => [11, $latest_version],
  "bunny_list_tie" => [11, $latest_version],
  "bunny_list_foreach" => [11, $latest_version],
  "bunny_list_fast_foreach" => [11, $latest_version],
  "bunny_list_all" => [11, $latest_version],
  "bunny_list_all_rev" => [11, $latest_version]
];

