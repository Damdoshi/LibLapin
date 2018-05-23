<?php
$functions = [
  30 => [
    "t_bunny_vector",
    "bunny_new_vector",
    "bunny_delete_vector",
    "bunny_vector_size",
    "bunny_vector_empty",
    "bunny_vector_elem_size",
    "bunny_vector_data",
    "bunny_vector_address",
    "bunny_vector_resize",
    "bunny_vector_crop"
  ],
  40 => [
    "bunny_build_vector",
    "t_bunny_comparator",
    "bunny_vector_sort",
    "bunny_vector_untie",
    "t_bunny_vector_foreach",
    "bunny_vector_foreach",
    "bunny_vector_fast_foreach",
  ],
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
