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
