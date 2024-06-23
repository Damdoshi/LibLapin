<?php
$functions = [
  40 => [
    "t_bunny_value_type",
    "t_bunny_value",
    "t_bunny_prototype",
    "t_bunny_get_function_list",
    "t_bunny_plugin",
    "bunny_new_plugin",
    "bunny_delete_plugin",
    "bunny_plugin_get_function",
  ],
  50 => [
    "bunny_plugin_call",
    "bunny_plugin_callv",
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
  "t_bunny_value_type" => [12, $latest_version],
  "t_bunny_value" => [12, $latest_version],
  "t_bunny_prototype" => [12, $latest_version],
  "t_bunny_get_function_list" => [12, $latest_version],
  "t_bunny_plugin" => [12, $latest_version],
  "bunny_new_plugin" => [12, $latest_version],
  "bunny_delete_plugin" => [12, $latest_version],
  "bunny_plugin_get_function" => [12, $latest_version],
  "bunny_plugin_call" => [12, $latest_version],
  "bunny_plugin_callv" => [12, $latest_version],
];
