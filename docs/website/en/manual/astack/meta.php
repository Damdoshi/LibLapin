<?php
$functions = [
  40 => [
    "t_bunny_astack",
    "t_bunny_astack_node",
    "bunny_new_astack",
    "bunny_astack_size",
    "bunny_astack_empty",
    "bunny_astack_top",
    "bunny_astack_push",
    "bunny_astack_pop",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
