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
