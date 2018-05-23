<?php
$functions = [
  10 => [
    "t_bunny_time",
    "bunny_get_time",
    "bunny_usleep",
    "bunny_sleep"
  ],
  20 => [
    "bunny_delta_time",
    "bunny_get_current_time",
  ],
  40 => [
    "t_bunny_call_order",
    "t_bunny_trap_function",
    "t_bunny_trap",
    "bunny_new_trap",
    "bunny_delete_trap",
    "bunny_reset_clock",
  ],
  50 => [
    "bunny_asynclock",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
