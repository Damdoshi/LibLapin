<?php
$functions = [
  40 => [
    "t_bunny_threadpool",
    "bunny_new_threadpool",
    "bunny_delete_threadpool",
    "t_bunny_function",
    "bunny_thread_push",
    "bunny_thread_foreach",
    "bunny_thread_wait_completion"
  ],
  50 => [
    "bunny_set_async_computation",
    "bunny_async_computation_push",
    "bunny_async_computation_foreach",
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
  "t_bunny_threadpool" => [11, $latest_version],
  "bunny_new_threadpool" => [11, $latest_version],
  "bunny_delete_threadpool" => [11, $latest_version],
  "t_bunny_function" => [11, $latest_version],
  "bunny_thread_push" => [11, $latest_version],
  "bunny_thread_foreach" => [11, $latest_version],
  "bunny_thread_wait_completion" => [11, $latest_version],

  "bunny_set_async_computation" => [12, $latest_version],
  "bunny_async_computation_push" => [12, $latest_version],
  "bunny_async_computation_foreach" => [12, $latest_version],
];

