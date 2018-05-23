<?php
$functions = [
  00 => [
    "t_bunny_position",
    "t_bunny_size",
    "t_bunny_accurate_position",
    "t_bunny_accurate_size",
    "t_bunny_area",
    "t_bunny_accurate_area",
  ],
  20 => [
    "bunny_real_width",
    "bunny_real_height",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
