<?php
$functions = [
  30 => [
    "t_bunny_camera",
    "t_bunny_capture",
    "bunny_new_camera",
    "bunny_delete_camera",
    "bunny_new_capture",
    "bunny_delete_capture",
    "bunny_capture_get_size",
    "bunny_capture",
    "bunny_capture_new_pixelarray",
    "bunny_capture_new_picture",
    "bunny_capture_to_pixelarray",
    "bunny_capture_to_picture",
  ],
  40 => [
    "bunny_headtrack",
    "bunny_stabilize_headtrack",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
