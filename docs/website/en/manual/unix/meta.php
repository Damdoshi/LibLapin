<?php
$functions = [
  30 => [
    "t_bunny_subprocess",
    "bunny_popen",
    "bunny_pclose",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}
