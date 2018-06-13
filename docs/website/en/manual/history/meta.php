<?php
$functions = [
  40 => [
    "t_bunny_history",
    "bunny_new_history",
    "bunny_delete_history",
    "bunny_history_add_frame",
    "bunny_history_get_frame",
    "bunny_history_erase_frame",
    "bunny_history_erase_before",
    "bunny_history_erase_after",
    "bunny_history_clear"
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
  "t_bunny_history" => [12, $latest_version],
  "bunny_new_history" => [12, $latest_version],
  "bunny_delete_history" => [12, $latest_version],
  "bunny_history_add_frame" => [12, $latest_version],
  "bunny_history_get_frame" => [12, $latest_version],
  "bunny_history_erase_frame" => [12, $latest_version],
  "bunny_history_erase_before" => [12, $latest_version],
  "bunny_history_erase_after" => [12, $latest_version],
  "bunny_history_clear" => [12, $latest_version],
];
