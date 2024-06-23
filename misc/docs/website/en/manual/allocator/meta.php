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
    "LAPIN_ALLOCATOR_OVERLOAD",
    "LAPIN_ALLOCATOR_DEACTIVATED",
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

$version_that_support = [
  "bunny_malloc" => [2, $latest_version],
  "bunny_free" => [2, $latest_version],
  "bunny_calloc" => [2, $latest_version],
  "bunny_realloc" => [2, $latest_version],

  "set_max_heap_size" => [2, 8],
  "bunny_set_maximum_ram" => [9, $latest_version],
  "bunny_set_memory_check" => [10, $latest_version],
  "bunny_allocator_reset" => [11, $latest_version],
  "bunny_malloc_failure" => [11, $latest_version],

  "LAPIN_ALLOCATOR_OVERLOAD" => [2, 10],
  "LAPIN_ALLOCATOR_DEACTIVATED" => [2, 10],

  "BUNNY_ALLOCATOR_OVERLOAD" => [11, $latest_version],
  "BUNNY_ALLOCATOR_DEACTIVATED" => [11, $latest_version],
];

