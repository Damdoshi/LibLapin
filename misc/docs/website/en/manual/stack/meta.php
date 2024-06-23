<?php
$functions = [
  20 => [
    "t_bunny_stack",
    "t_bunny_stack_node",
    "bunny_new_stack",
    "bunny_delete_stack",
    "bunny_stack_size",
    "bunny_stack_empty",
    "bunny_stack_top",
    "bunny_stack_push",
    "bunny_stack_pop",
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
  "t_bunny_stack" => [11, $latest_version],
  "t_bunny_stack_node" => [11, $latest_version],
  "bunny_new_stack" => [11, $latest_version],
  "bunny_delete_stack" => [11, $latest_version],
  "bunny_stack_size" => [11, $latest_version],
  "bunny_stack_empty" => [11, $latest_version],
  "bunny_stack_top" => [11, $latest_version],
  "bunny_stack_push" => [11, $latest_version],
  "bunny_stack_pop" => [11, $latest_version],
];
