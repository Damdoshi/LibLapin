<?php
$functions = [
  0 => [
    "bunny_malloc",
    "bunny_free",
  ],
  10 => [
    "bunny_set_maximum_ram",
  ],
  20 => [
    "bunny_calloc",
    "bunny_realloc",
  ],
  40 => [
    "BUNNY_ALLOCATOR_OVERLOAD",
    "BUNNY_ALLOCATOR_DEACTIVATED",
  ],
  50 => [
    "bunny_set_memory_check",
    "bunny_allocator_reset",
    "bunny_malloc_failure",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}

