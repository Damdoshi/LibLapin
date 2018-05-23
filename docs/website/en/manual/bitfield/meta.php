<?php
$functions = [
  20 => [
    "t_bunny_bitfield",
    "bunny_new_bitfield",
    "bunny_delete_bitfield",
    "bunny_bitfield_set",
    "bunny_bitfield_get",
    "bunny_bitfield_clr",
  ],
  40 => [
    "t_bunny_auto_bitfield64",
    "t_bunny_auto_bitfield32",
    "t_bunny_auto_bitfield16",
    "t_bunny_auto_bitfield8",
    "bunny_auto_bitfield_set",
    "bunny_auto_bitfield_get",
    "bunny_auto_bitfield_clr",
    "bunny_new_abitfield",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
