<?php
$functions = [
  40 => [
    "t_bunny_context_runtime_info",
    "bunny_context_key",
    "bunny_context_click",
    "Bunny::SetContext",
    "Bunny::Context",
  ],
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}

