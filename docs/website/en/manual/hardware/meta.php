<?php
$functions = [
  30 => [
    "t_bunny_hardware",
    "bunny_new_hardware",
    "bunny_delete_hardware",
    "bunny_hardware_read",
    "bunny_hardware_write",
  ],
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
