<?php
$functions = [
  40 => [
    "t_bunny_history",
    "bunny_new_history",
    "bunny_delete_history",
    "bunny_history_add_frame",
    "bunny_history_get_frame",
    "bunny_history_erase_frame",
    "bunny_history_erase_before",
    "bunny_history_erase_after",
    "bunny_history_clear"
  ],
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
