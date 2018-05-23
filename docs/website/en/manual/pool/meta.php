<?php
$functions = [
  50 => [
    "t_bunny_pool",
    "bunny_new_pool",
    "bunny_delete_pool",
    "bunny_pool_capacity",
    "bunny_pool_size",
    "bunny_pool_empty",
    "bunny_pool_elem_size",
    "bunny_pool_elem_index",
    "bunny_pool_clear",
    "bunny_pool_new",
    "bunny_pool_free",
    "t_bunny_pool_foreach",
    "bunny_pool_foreach",
    "bunny_pool_fast_foreach",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
