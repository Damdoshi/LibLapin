<?php
$functions = [
  20 => [
    "t_bunny_queue",
    "bunny_new_queue",
    "bunny_delete_queue",
    "bunny_queue_size",
    "bunny_queue_empty",
    "bunny_queue_front",
    "bunny_queue_push",
    "bunny_queue_pop",
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
  "t_bunny_queue" => [11, $latest_version],
  "bunny_new_queue" => [11, $latest_version],
  "bunny_delete_queue" => [11, $latest_version],
  "bunny_queue_size" => [11, $latest_version],
  "bunny_queue_empty" => [11, $latest_version],
  "bunny_queue_front" => [11, $latest_version],
  "bunny_queue_push" => [11, $latest_version],
  "bunny_queue_pop" => [11, $latest_version],
];

