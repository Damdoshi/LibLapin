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
