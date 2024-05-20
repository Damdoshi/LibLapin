<?php
$functions = [
  30 => [
    "t_bunny_hardware",
    "bunny_new_hardware",
    "bunny_delete_hardware",
    "bunny_hardware_read",
    "bunny_hardware_write",
    
    "t_bunny_vm110n",
    "bunny_new_vm110n",
    "bunny_delete_vm110n",
    "bunny_vm110n_read",
    "bunny_vm110n_write",
  ],
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}

$version_that_support = [
  "t_bunny_hardware" => [9, 12],
  "bunny_new_hardware" => [9, 12],
  "bunny_delete_hardware" => [9, 12],
  "bunny_hardware_read" => [9, 12],
  "bunny_hardware_write" => [9, 12],
];

$version_that_support = array_merge($version_that_support, [
    "t_bunny_vm110n" => [12, $latest_version],
    "bunny_new_vm110n" => [12, $latest_version],
    "bunny_delete_vm110n" => [12, $latest_version],
    "bunny_vm110n_read" => [12, $latest_version],
    "bunny_vm110n_write" => [12, $latest_version],
]);
